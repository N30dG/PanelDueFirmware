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

static const char* array const axisNames[] = { "X", "Y", "Z", "U", "V", "W" };
const StringTable * strings = &LanguageTables[0];


/**** Machine Variables ****/
int heaterStatus[MaxHeaters];
int activeTemps[MaxHeaters];
int standbyTemps[MaxHeaters];
static unsigned int numHeaters = 0;


/**** ToolBar ****/
const Icon toolIcons[MaxHeaters] = { IconBed, IconNozzle1, IconNozzle2, IconNozzle3, IconNozzle4, IconNozzle5, IconNozzle6 };
static DisplayField *toolBarBg;
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
const Icon menuIcons[MaxMenuEntrys] = { IconMachineControl, IconConsol, IconCurrentJob, IconFileManagement, IconSettings };
static DisplayField *menuBarBg;
static IconButton *menuEntrys[MaxMenuEntrys];
static DisplayGroup *tabs[MaxMenuEntrys];

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
						if (i == tab)
						{
							menuEntrys[i]->SetColors(colours->menuBarActiveColor, colours->menuBarBackColor);
							tabs[tab]->Show(true);
						}
						else
						{
							menuEntrys[i]->SetColors(colours->menuBarFontColor, colours->menuBarBackColor);
							tabs[i]->Show(false);
						}


					}
				} break;

				case evSelectHead:
				{
					int head = bp.GetIParam();
					PixelNumber x = head * toolbarDropdownWidth;
					PixelNumber xMax = DISPLAY_X - toolbarDropdownWidth;
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
						tddActiveInc->SetEvent(evAdjustActiveTemp, (head<<16|(newTemp+5)) );
						tddActiveDec->SetEvent(evAdjustActiveTemp, (head<<16|(newTemp-5)) );
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
						tddStandbyInc->SetEvent(evAdjustStandbyTemp, (head<<16|(newTemp+5)) );
						tddStandbyDec->SetEvent(evAdjustStandbyTemp, (head<<16|(newTemp-5)) );
					}
					DelayTouchLong();
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

		while (n < numHeaters)
		{
			--numHeaters;
			mgr.Show(tools[numHeaters], false);
		}

		while (numHeaters < n)
		{
			mgr.Show(tools[numHeaters], true);
			++numHeaters;
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


	// Create Toolbar (Nozzle-Bar)
	void CreateToolBar(const ColourScheme& colours) {
		DisplayField::SetDefaultColours(colours.toolBarFontColor, colours.toolBarBackColor);

		// Create tool button's
		for (uint8_t i=0; i<MaxHeaters; i++)
		{
			tools[i] = new IconFloatButton(0, i*toolbarDropdownWidth, toolbarDropdownWidth, 40, toolIcons[i], 0.0, evSelectHead, i);
			tools[i]->Show(false);
			mgr.AddField(tools[i]);
		}

		// Create DropDown-Menü's
		tdd = new PopupWindow(TOOL_DROPDOWN_HEIGHT, TOOL_DROPDOWN_WIDTH, colours.toolBarBackColor, colours.toolBarBackColor);

		tddLabelStatus = new TextField(15, 15, TOOL_DROPDOWN_WIDTH-30, TextAlignment::Left, strings->status);
		tddLabelStatus->setFont(glcd19x21);
		tdd->AddField(tddLabelStatus);
		tddStatus = new TextButton(45, 25, TOOL_DROPDOWN_WIDTH-50, strings->heaterStatus[0], evSwitchHeadStatus);
		tdd->AddField(tddStatus);

		tddLabelActive = new TextField(95, 15, TOOL_DROPDOWN_WIDTH-30, TextAlignment::Left, strings->active);
		tddLabelActive->setFont(glcd19x21);
		tdd->AddField(tddLabelActive);
		tddActiveTemperature = new IntegerButton(125, 50, TOOL_DROPDOWN_WIDTH-100);
		tddActiveTemperature->SetEvent(evAdjustActiveTemp, 0);
		tdd->AddField(tddActiveTemperature);
		tddActiveInc = new TextButton(125, TOOL_DROPDOWN_WIDTH-50, 20, "+", evAdjustActiveTemp);
		tdd->AddField(tddActiveInc);
		tddActiveDec = new TextButton(125, 25, 20, "-", evAdjustActiveTemp);
		tdd->AddField(tddActiveDec);

		tddLabelStandby = new TextField(175, 15, TOOL_DROPDOWN_WIDTH-30, TextAlignment::Left, strings->standby);
		tddLabelStandby->setFont(glcd19x21);
		tdd->AddField(tddLabelStandby);
		tddStandbyTemperature = new IntegerButton(205, 50, TOOL_DROPDOWN_WIDTH-100);
		tddStandbyTemperature->SetEvent(evAdjustStandbyTemp, 0);
		tdd->AddField(tddStandbyTemperature);
		tddStandbyInc = new TextButton(205, TOOL_DROPDOWN_WIDTH-50, 20, "+", evAdjustStandbyTemp);
		tdd->AddField(tddStandbyInc);
		tddStandbyDec = new TextButton(205, 25, 20, "-", evAdjustStandbyTemp);
		tdd->AddField(tddStandbyDec);

		// Add a background Color
		toolBarBg = new StaticToolBar(0, 0, DISPLAY_X, 40);
		mgr.AddField(toolBarBg);
	}


	// Create Menubar + Tab's
	void CreateMenuBar(const ColourScheme& colours) {
		DisplayField::SetDefaultColours(colours.menuBarFontColor, colours.menuBarBackColor);

		// Create menu button's
		for (uint8_t i=0; i<MaxMenuEntrys; i++)
		{
			menuEntrys[i] = new IconButton(i*50+50, 4, 40, 40,menuIcons[i], evSelectTab, i);;
			mgr.AddField(menuEntrys[i]);

			tabs[i] = new DisplayGroup(50, 40, DISPLAY_X-50, DISPLAY_Y-40);
			tabs[i]->SetColors(colours.mainFontColor, colours.mainBackColor);
			tabs[i]->Show(false);

			StaticTextField *t = new StaticTextField(i*100, 100, 300, TextAlignment::Centre, "test!");
			tabs[i]->AddField(t);

			TextButton *b = new TextButton(50, 50, 100, "Button-Test", evSelectTab, 0);
			tabs[i]->AddField(b);

			mgr.AddField(tabs[i]);
		}

		tabs[4]->Show(true);



		// Add a background Color
		menuBarBg = new StaticToolBar(40, 0, 50, DISPLAY_Y);
		mgr.AddField(menuBarBg);
	}


	// Create Main
	void CreateMainWindow(uint32_t language, const ColourScheme& colours, uint32_t p_infoTimeout)
	{
		// Set up default colours and margins
		mgr.Init(colours.defaultBackColour);
		DisplayField::SetDefaultFont(DEFAULT_FONT);
		ButtonWithText::SetFont(DEFAULT_FONT);
		IconFloatButton::SetFont(glcd22x32);
		CharButtonRow::SetFont(DEFAULT_FONT);
		SingleButton::SetTextMargin(textButtonMargin);
		SingleButton::SetIconMargin(iconButtonMargin);

		CreateToolBar(colours);
		CreateMenuBar(colours);
	}
}

