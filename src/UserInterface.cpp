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

#if DISPLAY_X == 800
const Icon heaterIcons[MaxHeaters] = { IconBed, IconNozzle1, IconNozzle2, IconNozzle3, IconNozzle4, IconNozzle5, IconNozzle6 };
#else
const Icon heaterIcons[MaxHeaters] = { IconBed, IconNozzle1, IconNozzle2, IconNozzle3, IconNozzle4 };
#endif

namespace UI
{
	void CreateMainWindow(uint32_t language, const ColourScheme& colours, uint32_t p_infoTimeout)
	{
		// Set up default colours and margins
		mgr.Init(colours.defaultBackColour);
		DisplayField::SetDefaultFont(DEFAULT_FONT);
		ButtonWithText::SetFont(DEFAULT_FONT);
		CharButtonRow::SetFont(DEFAULT_FONT);
		SingleButton::SetTextMargin(textButtonMargin);
		SingleButton::SetIconMargin(iconButtonMargin);


		DisplayField::SetDefaultColours(colours.popupTextColour, colours.popupBackColour);
		mgr.AddField(new StaticTextField(5, 5, DISPLAY_X - 10, TextAlignment::Centre, "Hello World!"));
	}
}

