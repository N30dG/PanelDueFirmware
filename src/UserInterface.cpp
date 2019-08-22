/*
 * UserInterface.cpp
 *
 *  Created on: 7 Jan 2017
 *      Author: David
 */

#include "UserInterface.hpp"

#include "UserInterfaceConstants.hpp"
#include "PanelDue.hpp"
#include "FileManager.hpp"
#include "MessageLog.hpp"
#include "Library/Misc.hpp"
#include "Library/Vector.hpp"
#include "Icons/Icons.hpp"
#include "Hardware/Buzzer.hpp"
#include "Hardware/Reset.hpp"
#include "Hardware/SerialIo.hpp"
#include "Hardware/SysTick.hpp"
#include "Strings.hpp"
#include "Version.hpp"

const StringTable * strings = &LanguageTables[0];

static const char* array const axisNames[] = { "X", "Y", "Z", "U", "V", "W" };
const char* homeCommands[] = { "G28 X", "G28 Y", "G28 Z", "G28 U", "G28 V", "G28 W" };
static const char* array const moveValues[][9] = {
		{"-50", "-10", "-1", "-0.1", "X", "+0.1", "+1", "+10", "+50"},
		{"-50", "-10", "-1", "-0.1", "Y", "+0.1", "+1", "+10", "+50"},
		{"-25", "-5", "-0.5", "-.05", "Z", "+.05", "+0.5", "+5", "+50"},
		{"-50", "-10", "-1", "-0.1", "U", "+0.1", "+1", "+10", "+50"},
		{"-50", "-10", "-1", "-0.1", "V", "+0.1", "+1", "+10", "+50"},
		{"-50", "-10", "-1", "-0.1", "W", "+0.1", "+1", "+10", "+50"}
};
static const char* array const moveParams[][9] = {
		{"-50", "-10", "-1", "-0.1", "0" , "0.1", "1", "10", "50"},
		{"-50", "-10", "-1", "-0.1", "0" , "0.1", "1", "10", "50"},
		{"-25", "-5", "-0.5", "-0.05", "0" , "0.05", "0.5", "5", "25"},
		{"-50", "-10", "-1", "-0.1", "0" , "0.1", "1", "10", "50"},
		{"-50", "-10", "-1", "-0.1", "0" , "0.1", "1", "10", "50"},
		{"-50", "-10", "-1", "-0.1", "0" , "0.1", "1", "10", "50"}
};
static const uint16_t array extrudeValues[] = { 50, 25, 10, 5, 1, 0 };
static const uint16_t array ExtrudeRates[] = { 60, 30, 15, 5, 1, 0 };



/**** Machine Variables ****/
int heaterStatus[MaxHeaters];
int activeTemps[MaxHeaters];
int standbyTemps[MaxHeaters];
uint16_t extrudeAmount=10, extrudeRate=5*60;
static unsigned int numAxes = 0;
static unsigned int numHeaters = 0;
static bool isDelta = 0;


/**** ToolBar ****/
const Icon toolIcons[MaxHeaters] = { IconBed, IconNozzle1, IconNozzle2, IconNozzle3, IconNozzle4, IconNozzle5, IconNozzle6 };
static ColorField *toolBarBg;
static IconFloatButton* tools[MaxHeaters];

static PopupWindow* tdd;

static TextField* tddLabelStatus;
static TextButton* tddStatus;

static TextField* tddLabelActive;
static IntegerButton* tddActiveTemperature;
static TextButton *tddActiveInc, *tddActiveDec;

static TextField* tddLabelStandby;
static IntegerButton* tddStandbyTemperature;
static TextButton *tddStandbyInc, *tddStandbyDec;


/**** MenuBar ****/
const Icon menuIcons[] = { IconMachineControl, IconConsol, IconCurrentJob, IconFileManagement, IconSettings };
static ColorField *menuBarBg;
static IconButton *menuEntrys[MaxMenuEntrys];
static DisplayGroup *tabs[MaxMenuEntrys];


/**** Machine Control Tab ****/
// Status Panel
static ColorField *mcpStatusPanel;
static StaticTextField *mcpToolPositionLabel[2];
static StaticTextField *mcpAxesLabel[MaxAxes];
static FloatField *mcpAxesText[MaxAxes];

// Machine Movement Panel
const Icon homeIcons[] = { IconHomeX, IconHomeY, IconHomeZ, IconHomeU, IconHomeV, IconHomeW };
static ColorField *mcpMovePanel;
static IconButton *mcpHomeAll, *mcpCompensate,*mcpHomeAxes[MaxAxes];
static TextButton *mcpMoveAxes[MaxAxes][numMoveButtons];

//Extrude Panel
static ColorField *mcpExtrudePanel;
static IntegerButton *mcpExtrudeAmount[6], *mcpExtrudeRate[6];
static TextButton *mcpExtrude, *mcpRetract;
static StaticTextField *mcpExtrudeAmountLabel, *mcpExtrudeRateLabel;


namespace UI
{
	void ProcessTouch(ButtonPress bp)
	{
		if (bp.IsValid())
		{
			ButtonBase *f = bp.GetButton();
			mgr.Press(bp, true);
			Event ev = (Event)(f->GetEvent());

			switch(ev)
			{
				case evSelectTab:
				{
					int tab = bp.GetIParam();
					for (uint8_t i=0; i<MaxMenuEntrys; i++)
					{
						menuEntrys[i]->SetColors(colours->menuBarFontColor, colours->menuBarBackColor);
						tabs[i]->Show(false);
					}

					menuEntrys[tab]->SetColors(colours->menuBarActiveColor, colours->menuBarBackColor);
					tabs[tab]->Show(true);
				} break;

				case evSelectHead:
				{
					int head = bp.GetIParam();
					PixelNumber x = head * toolBarButtonWidth;
					PixelNumber xMax = DISPLAY_X - toolDropdownWidth;
					x = (x > xMax) ? xMax : x;

					tddStatus->SetText(strings->heaterStatus[heaterStatus[head]]);
					tddStatus->SetEvent(evSwitchHeadStatus, head);

					tddActiveTemperature->SetValue(activeTemps[head]);
					tddActiveTemperature->SetEvent(evAdjustActiveTemp, (head<<16|((int16_t)-1)) );
					tddActiveInc->SetEvent(evAdjustActiveTemp, (head<<16|((int16_t)activeTemps[head]+5)) );
					tddActiveDec->SetEvent(evAdjustActiveTemp, (head<<16|((int16_t)activeTemps[head]-5)) );

					tddStandbyTemperature->SetValue(standbyTemps[head]);
					tddStandbyTemperature->SetEvent(evAdjustStandbyTemp, head<<16);
					tddStandbyInc->SetEvent(evAdjustStandbyTemp, (head<<16|((int16_t)standbyTemps[head]+5)) );
					tddStandbyDec->SetEvent(evAdjustStandbyTemp, (head<<16|((int16_t)standbyTemps[head]-5)) );

					mgr.SetPopup(tdd, x, 40, true);
				}
				break;

				case evSwitchHeadStatus:
				{
					int head = bp.GetIParam();
					// off/standby: ->active
					if (heaterStatus[head] == 0 || heaterStatus[head] == 1)
					{
						if (head == 0)
						{
							SerialIo::SendString("M140 S");
							SerialIo::SendInt(activeTemps[head]);
							SerialIo::SendChar('\n');
						}
						else
						{
							SerialIo::SendChar('T');
							SerialIo::SendInt(head-1);
							SerialIo::SendChar('\n');
						}
					}
					// active: -> standby
					else if (heaterStatus[head] == 2)
					{
						if (head == 0)
						{
							SerialIo::SendString("M144\n");
						}
						else
						{
							SerialIo::SendString("T-1\n");
						}
					}

				} break;

				case evAdjustActiveTemp:
				{
					unsigned int head = (bp.GetIParam()>>16);
					int newTemp = (bp.GetIParam()&0xFFFF);
					if (head < MaxHeaters)
					{
						if (head == 0)
						{
							SerialIo::SendString("M140 S");
							SerialIo::SendInt(newTemp);
							SerialIo::SendChar('\n');
						}
						else
						{
							SerialIo::SendString(((GetFirmwareFeatures() & noG10Temps) == 0) ? "G10 P" : "M104 T");
							SerialIo::SendInt(head - 1);
							SerialIo::SendString(" S");
							SerialIo::SendInt(newTemp);
							SerialIo::SendChar('\n');
						}
						DelayTouchLong();
						tddActiveTemperature->SetValue(newTemp);
						tddActiveInc->SetEvent(evAdjustActiveTemp, (int)(head<<16|(newTemp+5)) );
						tddActiveDec->SetEvent(evAdjustActiveTemp, (int)(head<<16|(newTemp-5)) );
					}
					DelayTouchLong();
				} break;

				case evAdjustStandbyTemp:
				{
					unsigned int head = (bp.GetIParam()>>16);
					int16_t newTemp = (bp.GetIParam()&0xFFFF);
					if ( (head < MaxHeaters) && (newTemp > 0) )
					{
						if (head == 0)
						{
							SerialIo::SendString("M140 R");
							SerialIo::SendInt(newTemp);
							SerialIo::SendChar('\n');
						}
						else
						{
							SerialIo::SendString(((GetFirmwareFeatures() & noG10Temps) == 0) ? "G10 P" : "M104 T");
							SerialIo::SendInt(head - 1);
							SerialIo::SendString(" R");
							SerialIo::SendInt(newTemp);
							SerialIo::SendChar('\n');
						}
						DelayTouchLong();
						tddStandbyTemperature->SetValue(newTemp);
						tddStandbyInc->SetEvent(evAdjustStandbyTemp, (int)(head<<16|(newTemp+5)) );
						tddStandbyDec->SetEvent(evAdjustStandbyTemp, (int)(head<<16|(newTemp-5)) );
					}
					DelayTouchLong();
				} break;

				case evMoveX:
				case evMoveY:
				case evMoveZ:
				case evMoveU:
				case evMoveV:
				case evMoveW:
				{
					const uint8_t axis = ev - evMoveX;
					SerialIo::SendString("G91\nG1 ");
					SerialIo::SendString(axisNames[axis]);
					SerialIo::SendString(bp.GetSParam());
					SerialIo::SendString(" F6000\nG90\n");

				} break;

				case evExtrudeAmount:
				{
					int idx = bp.GetIParam();
					extrudeAmount = extrudeValues[idx];

					for (int i=0; i<6; i++)
					{
						if (i == idx)
						{
							mcpExtrudeAmount[i]->SetColors(colours->mainFontColor, colours->mainActiveColor);
						}
						else
						{
							mcpExtrudeAmount[i]->SetColors(colours->mainFontColor, colours->mainDarkButtonColor);
						}
					}
				} break;

				case evExtrudeRate:
				{
					int idx = bp.GetIParam();
					extrudeRate = extrudeValues[idx]*60;

					for (int i=0; i<6; i++)
					{
						if (i == idx)
						{
							mcpExtrudeRate[i]->SetColors(colours->mainFontColor, colours->mainActiveColor);
						}
						else
						{
							mcpExtrudeRate[i]->SetColors(colours->mainFontColor, colours->mainDarkButtonColor);
						}
					}
				} break;

				case evExtrude:
				case evRetract:
				{
					SerialIo::SendString("M120\nM83\nG1 E");
					if (ev == evRetract)
					{
						SerialIo::SendChar('-');
					}
					SerialIo::SendInt(extrudeAmount);
					SerialIo::SendString(" F");
					SerialIo::SendInt(extrudeRate);
					SerialIo::SendString("\nM121\n");
				} break;

				case evSendCommand:
				{
					SerialIo::SendString(bp.GetSParam());
					SerialIo::SendChar('\n');
				} break;

				default:
				{

				} break;
			}
		}
	}
	void ProcessTouchOutsidePopup(ButtonPress bp)
	{
		DelayTouchLong();	// by default, ignore further touches for a long time
		TouchBeep();
		mgr.ClearPopup();
	}


	void UpdateCurrentTemperature(size_t heater, float fval)
	{
		if (heater < MaxHeaters && tools[heater] != nullptr)
		{
			tools[heater]->SetValue(fval);
		}
	}
	void UpdateActiveTemperature(size_t index, int ival)
	{
		if (index < MaxHeaters)
		{
			activeTemps[index] = ival;
			if ((size_t)tddActiveTemperature->GetIParam(0) == index) {
				tddActiveTemperature->SetValue(ival);
			}
		}
	}
	void UpdateStandbyTemperature(size_t index, int ival)
	{
		if (index < MaxHeaters)
		{
			standbyTemps[index] = ival;
			if ((size_t)tddStandbyTemperature->GetIParam(0) == index) {
				tddStandbyTemperature->SetValue(ival);
			}
		}
	}
	void SetNumTools(unsigned int n)
	{
		//uint8_t numTools = n;
		for (size_t i=0; i < MaxHeaters; i++)
		{
			// for now, we rely completely on heater informations for building the toolbar
			// should be fixed soon ;)
			//mgr.Show(tools[i], i <= n);
		}
	}
	void SetNumHeaters(unsigned int n)
	{
		if (n > MaxHeaters)
		{
			n = MaxHeaters;
		}
		if (numHeaters != n)
		{
			numHeaters = n;

			mgr.Redraw(toolBarBg);

			for (unsigned int i=0; i<MaxHeaters; i++)
			{
				if (i < n) {
					tools[i]->Show(true);
					mgr.Redraw(tools[i]);
				}
				else
				{
					tools[i]->Show(false);
				}
			}

		}

	}
	void UpdateHeaterStatus(size_t heater, int ival)
	{
		if (heater < MaxHeaters)
		{
			heaterStatus[heater] = ival;
			if (tools[heater] != nullptr)
			{
				if      (ival == 1) tools[heater]->SetColors(colours->toolBarFontColor, colours->toolBarBackColor);		// standby
				else if (ival == 2) tools[heater]->SetColors(colours->toolBarActiveColor, colours->toolBarBackColor);	// active
				else if (ival == 3) tools[heater]->SetColors(colours->toolBarFontColor, colours->toolBarBackColor);		// error
				else if (ival == 4) tools[heater]->SetColors(colours->toolBarFontColor, colours->toolBarBackColor);		// tuning
				else                tools[heater]->SetColors(colours->toolBarFontColor, colours->toolBarBackColor);		// just in case

				if ((size_t)tddStatus->GetIParam(0) == heater)
				{
					tddStatus->SetText(strings->heaterStatus[ival]);
				}
			}
		}
	}
	void UpdateGeometry(unsigned int p_numAxes, bool p_isDelta)
	{
		if (p_numAxes != numAxes || p_isDelta != isDelta)
		{
			numAxes = p_numAxes;
			isDelta = p_isDelta;

			// Status Panel
			PixelNumber labelMargin = mainSectionMargin*2;
			PixelNumber width = DISPLAY_X - menuBarWidth - labelMargin*2;
			PixelNumber axesWidth = width / (numAxes+1);

			if (mcpToolPositionLabel[0] != nullptr)
				mcpToolPositionLabel[0]->SetPositionAndWidth(labelMargin, axesWidth);

			if (mcpToolPositionLabel[1] != nullptr)
				mcpToolPositionLabel[1]->SetPositionAndWidth(labelMargin, axesWidth);


			// Move Panel
			PixelNumber homeMargin = (numAxes <= 3) ? mainSectionMargin : mcpHomeMargin;

			PixelNumber moveHeight = DISPLAY_Y - toolBarHeight - (mcpStatusHeight + mainSectionMargin*3);
			PixelNumber moveY = mcpStatusHeight + mainSectionMargin*2;
			PixelNumber homeHeight = (moveHeight-mainSectionMargin) / (numAxes+1);
			PixelNumber homeY = moveY + mainSectionMargin;

			mcpHomeAll->SetPositionAndHeight(homeY, homeHeight-homeMargin);
			mcpHomeAll->Show(true);

			mcpCompensate->SetPositionAndHeight(homeY, homeHeight-homeMargin);
			mcpCompensate->Show(true);

			homeY = homeY + homeHeight;

			for (size_t i = 0; i < MaxAxes; ++i)
			{
				if (i < numAxes)
				{
					// Status Panel
					if (mcpAxesLabel != nullptr)
					{
						mcpAxesLabel[i]->SetPositionAndWidth(labelMargin+(axesWidth*(i+1)), axesWidth);
						mcpAxesLabel[i]->Show(true);
					}

					if (mcpAxesText != nullptr)
					{
						mcpAxesText[i]->SetPositionAndWidth(labelMargin+(axesWidth*(i+1)), axesWidth);
						mcpAxesText[i]->Show(true);
					}


					// Move Panel
					if (mcpHomeAxes[i] != nullptr)
					{
						mcpHomeAxes[i]->SetPositionAndHeight(homeY, homeHeight-homeMargin);
						mcpHomeAxes[i]->Show(true);
					}

					for (int j=0; j<9; j++)
					{
						if (mcpMoveAxes[i][j] != nullptr)
						{
							mcpMoveAxes[i][j]->SetPositionAndHeight(homeY, homeHeight-homeMargin);
							mcpMoveAxes[i][j]->Show(true);
						}
					}


					homeY = homeY + homeHeight;
				}

				else
				{
					if (mcpAxesLabel[i] != nullptr)
						mcpAxesLabel[i]->Show(false);

					if (mcpAxesText[i] != nullptr)
						mcpAxesText[i]->Show(false);

					if (mcpHomeAxes[i] != nullptr)
						mcpHomeAxes[i]->Show(false);

					for (int j=0; j<9; j++)
					{
						if (mcpMoveAxes[i][j] != nullptr)
						{
							mcpMoveAxes[i][j]->Show(false);
						}
					}
				}

			}

			tabs[0]->SetChanged();

			mcpStatusPanel->SetChanged();

			mcpMovePanel->SetChanged();
			mcpHomeAll->SetChanged();
			mcpCompensate->SetChanged();
		}
	}
	void UpdateAxisPosition(size_t axis, float fval)
	{
		if (axis < MaxAxes)
		{
			if (mcpAxesText[axis] != nullptr)
			{
				mcpAxesText[axis]->SetValue(fval);
			}
		}
	}
	void UpdateHomedStatus(int axis, bool isHomed) {
		SingleButton *homeButton = nullptr;

		if (axis < 0)
		{
			homeButton = mcpHomeAll;
		}
		else if (axis < MaxAxes)
		{
			homeButton = mcpHomeAxes[axis];
		}
		if (homeButton != nullptr)
		{
			if (homeButton->IsVisible())
				homeButton->SetColors(colours->mainFontColor, (isHomed) ? colours->mainActiveColor : colours->mainWarningColor);
		}
	}


	//
	void CreateStringButtonRow(DisplayGroup *pf, PixelNumber y, PixelNumber x, PixelNumber width, PixelNumber height, TextButton *buttons[], size_t numButtons, const char* array const text[], const char* array const params[], Event evt)
	{
		PixelNumber btnWidth = width/numButtons;

		for (size_t i=0; i<numButtons; i++)
		{
			buttons[i] = new TextButton(y, x+(i*btnWidth), btnWidth, height, text[i], evt, params[i]);
			pf->AddField(buttons[i]);
		}
	}
	void CreateStringButtonColumn(DisplayGroup *pf, PixelNumber y, PixelNumber x, PixelNumber width, PixelNumber height, IntegerButton *buttons[], size_t numButtons, const uint16_t values[], Event evt)
	{
		PixelNumber btnHeight = height/numButtons;

		for (size_t i=0; i<numButtons; i++)
		{
			IntegerButton* p;
			p = new IntegerButton((PixelNumber)y+(i*btnHeight), x, width, btnHeight);
			p->SetEvent(evt, i);
			p->SetValue(values[i]);
			buttons[i] = p;
			pf->AddField(p);
		}
	}


	// Create Machine Control Display Group
	void CreateMachineControlPanel()
	{
		const LcdFont fontLabel = glcd20x30;
		const LcdFont fontText = glcd19x21;
		const LcdFont fontButton = glcd19x21;

		// Status Panel
		PixelNumber labelMargin = mainSectionMargin*2;
		PixelNumber width = DISPLAY_X - menuBarWidth - labelMargin*2;
		PixelNumber axesWidth = width / (MaxAxes+1);

		mcpToolPositionLabel[0] = new StaticTextField(labelMargin, labelMargin, axesWidth, TextAlignment::Centre, strings->tool);
		mcpToolPositionLabel[0]->setFont(fontLabel);
		mcpToolPositionLabel[0]->SetColors(colours->mainFontColor, colours->mainPanelColor);

		mcpToolPositionLabel[1] = new StaticTextField(labelMargin+45, labelMargin, axesWidth, TextAlignment::Centre, strings->position);
		mcpToolPositionLabel[1]->setFont(fontLabel);
		mcpToolPositionLabel[1]->SetColors(colours->mainFontColor, colours->mainPanelColor);

		tabs[0]->AddField(mcpToolPositionLabel[0]);
		tabs[0]->AddField(mcpToolPositionLabel[1]);

		// MachineMovement Panel
		PixelNumber moveHeight = DISPLAY_Y - toolBarHeight - (mcpStatusHeight + mainSectionMargin*3);
		PixelNumber moveY = mcpStatusHeight + mainSectionMargin*2;
		PixelNumber homeHeight = (moveHeight-mainSectionMargin) / (MaxAxes+1);
		PixelNumber homeY = moveY + mainSectionMargin;

		mcpHomeAll = new IconButton(homeY, labelMargin, mcpHomeWidth, homeHeight-mcpHomeMargin, IconHomeAll, evSendCommand, "G28");
		mcpHomeAll->SetColors(colours->mainFontColor, colours->mainWarningColor);
		tabs[0]->AddField(mcpHomeAll);

		mcpCompensate = new IconButton(homeY, mcpMoveWidth-mcpHomeWidth, mcpHomeWidth, homeHeight-mcpHomeMargin, IconBedComp, evSendCommand,"G32");
		mcpCompensate->SetColors(colours->mainFontColor, colours->mainActiveColor);
		tabs[0]->AddField(mcpCompensate);

		// Extrude Panel
		PixelNumber extrudeY = homeY;
		PixelNumber extrudeHeight = moveHeight - mainSectionMargin*4 - mcpExtrudeButtonHeight*2;
		PixelNumber extrudeX = mcpMoveWidth+mainSectionMargin*3;
		PixelNumber extrudeWidth = tabs[0]->GetWidth()  - extrudeX - mainSectionMargin;
		PixelNumber extrudeButtonWidth = extrudeWidth / 2;

		mcpExtrudeAmountLabel = new StaticTextField(extrudeY, extrudeX, extrudeButtonWidth-mainSectionMargin, TextAlignment::Centre, strings->mm);
		mcpExtrudeAmountLabel->setFont(glcd20x30);
		mcpExtrudeAmountLabel->SetColors(colours->mainFontColor, colours->mainPanelColor);
		tabs[0]->AddField(mcpExtrudeAmountLabel);
		mcpExtrudeRateLabel = new StaticTextField(extrudeY, extrudeX+extrudeButtonWidth, extrudeButtonWidth-mainSectionMargin, TextAlignment::Centre, strings->mm2);
		mcpExtrudeRateLabel->setFont(glcd20x30);
		mcpExtrudeRateLabel->SetColors(colours->mainFontColor, colours->mainPanelColor);
		tabs[0]->AddField(mcpExtrudeRateLabel);

		extrudeY += UTFT::GetFontHeight(glcd20x30)+2;
		extrudeHeight -= UTFT::GetFontHeight(glcd20x30)+2;

		mcpRetract = new TextButton(extrudeY+extrudeHeight+mainSectionMargin, extrudeX, extrudeWidth-mainSectionMargin, mcpExtrudeButtonHeight, strings->retract, evRetract);
		mcpRetract->SetColors(colours->mainFontColor, colours->mainDarkButtonColor);
		tabs[0]->AddField(mcpRetract);
		mcpExtrude = new TextButton(extrudeY+extrudeHeight+mcpExtrudeButtonHeight+mainSectionMargin*2, extrudeX, extrudeWidth-mainSectionMargin, mcpExtrudeButtonHeight, strings->extrude, evExtrude);
		mcpExtrude->SetColors(colours->mainFontColor, colours->mainDarkButtonColor);
		tabs[0]->AddField(mcpExtrude);

		CreateStringButtonColumn(tabs[0], extrudeY, extrudeX, extrudeButtonWidth-mainSectionMargin, extrudeHeight+2, mcpExtrudeAmount, 6, extrudeValues, evExtrudeAmount);
		mcpExtrudeAmount[2]->SetColors(colours->mainFontColor, colours->mainActiveColor);
		extrudeX += extrudeButtonWidth;
		CreateStringButtonColumn(tabs[0], extrudeY, extrudeX, extrudeButtonWidth-mainSectionMargin, extrudeHeight+2, mcpExtrudeRate, 6, ExtrudeRates, evExtrudeRate);
		mcpExtrudeRate[3]->SetColors(colours->mainFontColor, colours->mainActiveColor);

		homeY = homeY + homeHeight;

		for (int i = 0; i < MaxAxes; i++)
		{
			// Status Panel Entry's
			mcpAxesLabel[i] = new StaticTextField(labelMargin, labelMargin+(axesWidth*(i+1)), axesWidth, TextAlignment::Centre, axisNames[i]);
			mcpAxesLabel[i]->setFont(fontLabel);
			mcpAxesLabel[i]->SetColors(colours->mainFontColor, colours->mainPanelColor);
			mcpAxesLabel[i]->Show(true);
			tabs[0]->AddField(mcpAxesLabel[i]);

			mcpAxesText[i] = new FloatField(labelMargin+49, labelMargin+(axesWidth*(i+1)), axesWidth, TextAlignment::Centre, 2);
			mcpAxesText[i]->setFont(fontText);
			mcpAxesText[i]->SetColors(colours->mainFontColor, colours->mainPanelColor);
			mcpAxesText[i]->Show(true);
			tabs[0]->AddField(mcpAxesText[i]);


			// Machine Movement Panel
			mcpHomeAxes[i] = new IconButton(homeY, labelMargin, mcpHomeWidth, homeHeight-mcpHomeMargin, homeIcons[i], evSendCommand, homeCommands[i]);
			mcpHomeAxes[i]->SetColors(colours->mainFontColor, colours->mainWarningColor);
			tabs[0]->AddField(mcpHomeAxes[i]);

			DisplayField::SetDefaultFont(fontButton);
			DisplayField::SetDefaultColours(colours->mainFontColor, colours->mainDarkButtonColor);
			CreateStringButtonRow(tabs[0], homeY, labelMargin+mcpHomeWidth+mainSectionMargin, mcpMoveWidth-(labelMargin+mcpHomeWidth+mainSectionMargin), homeHeight-mcpHomeMargin, mcpMoveAxes[i], numMoveButtons, moveValues[i], moveParams[i], (Event)((int)evMoveX+i));

			homeY = homeY + homeHeight;
		}

		// StatusPanel-BackGround
		mcpStatusPanel = new ColorField(mainSectionMargin, mainSectionMargin, DISPLAY_X - menuBarWidth - mainSectionMargin*2, 100);
		mcpStatusPanel->SetColors(colours->mainFontColor, colours->mainPanelColor);
		tabs[0]->AddField(mcpStatusPanel);

		// MovementPanel-Background
		mcpMovePanel = new ColorField(moveY, mainSectionMargin, mcpMoveWidth, moveHeight);
		mcpMovePanel->SetColors(colours->mainFontColor, colours->mainPanelColor);
		tabs[0]->AddField(mcpMovePanel);

		// ExtrudePanel-Background
		mcpExtrudePanel = new ColorField(moveY, mcpMoveWidth+mainSectionMargin*2, DISPLAY_X-menuBarWidth-(mcpMoveWidth+mainSectionMargin*3), moveHeight);
		mcpExtrudePanel->SetColors(colours->mainFontColor, colours->mainPanelColor);
		tabs[0]->AddField(mcpExtrudePanel);

	}


	// Create Toolbar (Heater-Bar)
	void CreateToolBar(const ColourScheme& colours) {
		LcdFont fontLabel = glcd19x21;
		LcdFont fontText = glcd20x30;

		DisplayField::SetDefaultColours(colours.toolBarFontColor, colours.toolBarBackColor);

		// Create tool button's
		for (uint8_t i=0; i<MaxHeaters; i++)
		{
			tools[i] = new IconFloatButton(0, i*toolBarButtonWidth + 8, toolBarButtonWidth, toolBarHeight, toolIcons[i], 0.0, evSelectHead, i);
			tools[i]->SetFont(fontLabel);
			mgr.AddField(tools[i]);
		}

		// Add a background Color
		toolBarBg = new ColorField(0, 0, DISPLAY_X, toolBarHeight);
		mgr.AddField(toolBarBg);


		// Create DropDown-Menü's
		tdd = new PopupWindow(toolDropdownHeight, toolDropdownWidth, colours.toolBarBackColor, colours.toolBarBackColor);

		tddLabelStatus = new TextField(15, 15, toolDropdownWidth-30, TextAlignment::Left, strings->status);
		tddLabelStatus->setFont(fontLabel);
		tdd->AddField(tddLabelStatus);
		tddStatus = new TextButton(45, 25, toolDropdownWidth-50, UTFT::GetFontHeight(glcd19x21),strings->heaterStatus[0], evSwitchHeadStatus);
		tdd->AddField(tddStatus);

		tddLabelActive = new TextField(95, 15, toolDropdownWidth-30, TextAlignment::Left, strings->active);
		tddLabelActive->setFont(fontLabel);
		tdd->AddField(tddLabelActive);
		tddActiveTemperature = new IntegerButton(125, 50, toolDropdownWidth-100, UTFT::GetFontHeight(fontText));
		tddActiveTemperature->SetFont(fontText);
		tddActiveTemperature->SetEvent(evAdjustActiveTemp, 0);
		tdd->AddField(tddActiveTemperature);
		tddActiveInc = new TextButton(127, toolDropdownWidth-50, 30, 30, "+", evAdjustActiveTemp);
		tdd->AddField(tddActiveInc);
		tddActiveDec = new TextButton(127, 25, 30, 30, "-", evAdjustActiveTemp);
		tdd->AddField(tddActiveDec);

		tddLabelStandby = new TextField(175, 15, toolDropdownWidth-30, TextAlignment::Left, strings->standby);
		tddLabelStandby->setFont(fontLabel);
		tdd->AddField(tddLabelStandby);
		tddStandbyTemperature = new IntegerButton(205, 50, toolDropdownWidth-100, UTFT::GetFontHeight(fontText));
		tddStandbyTemperature->SetFont(fontText);
		tddStandbyTemperature->SetEvent(evAdjustStandbyTemp, 0);
		tdd->AddField(tddStandbyTemperature);
		tddStandbyInc = new TextButton(207, toolDropdownWidth-50, 30, 30, "+", evAdjustStandbyTemp);
		tdd->AddField(tddStandbyInc);
		tddStandbyDec = new TextButton(207, 25, 30, 30,"-", evAdjustStandbyTemp);
		tdd->AddField(tddStandbyDec);

	}


	// Create Menubar + Tab's
	void CreateMenuBar(const ColourScheme& colours) {
		DisplayField::SetDefaultColours(colours.menuBarFontColor, colours.menuBarBackColor);

		// Create menu button's
		for (uint8_t i=0; i<MaxMenuEntrys; i++)
		{
			menuEntrys[i] = new IconButton(i*50+50, 4, 40, 40, menuIcons[i], evSelectTab, i);;
			mgr.AddField(menuEntrys[i]);

			tabs[i] = new DisplayGroup(menuBarWidth, toolBarHeight, DISPLAY_X-menuBarWidth, DISPLAY_Y-toolBarHeight);
			tabs[i]->SetColors(colours.mainFontColor, colours.mainBackColor);
			tabs[i]->Show(false);

			mgr.AddField(tabs[i]);
		}

		tabs[0]->Show(true);
		menuEntrys[0]->SetColors(colours.menuBarActiveColor, colours.menuBarBackColor);

		// Add a background Color
		menuBarBg = new ColorField(40, 0, 50, DISPLAY_Y);
		mgr.AddField(menuBarBg);

	}


	// Create Main
	void CreateMainWindow(uint32_t language, const ColourScheme& colours, uint32_t p_infoTimeout)
	{
		// Set up default colours and margins
		DisplayField::SetDefaultFont(DEFAULT_FONT);
		TextButton::SetFont(DEFAULT_FONT);

		mgr.Init(colours.mainBackColor);
		CharButtonRow::SetFont(DEFAULT_FONT);
		SingleButton::SetTextMargin(textButtonMargin);
		SingleButton::SetIconMargin(iconButtonMargin);

		CreateToolBar(colours);
		CreateMenuBar(colours);

		CreateMachineControlPanel();
	}
}

