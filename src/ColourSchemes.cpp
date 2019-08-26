/*
 * ColourSchemes.cpp
 *
 * Created: 01/09/2016 13:13:29
 *  Author: David
 */ 

#ifndef OEM_COLOURS

#include "ColourSchemes.hpp"
#include "UserInterfaceConstants.hpp"
#include "Icons/Icons.hpp"

const ColourScheme colourSchemes[NumColorSchemes] =
{
	// Dark colour scheme #1

	{
		.index = 0,

	},

	// Dark colour scheme #2

	{
		.index = 1,

		/**** "Are You Sure"-Popup ****/
		.popupBackColor = UTFT::fromRGB(30, 30, 30),
		.popupFontColor = UTFT::fromRGB(255, 255, 255),
		.popupButtonBackColor = UTFT::fromRGB(58, 58, 58),
		.popupBorderColor = UTFT::fromRGB(255, 255, 255),


		/**** Toolbar ****/
		.toolBarBackColor = UTFT::fromRGB(15, 15, 15),
		.toolBarFontColor = UTFT::fromRGB(255,255,255),
		.toolBarActiveColor = UTFT::fromRGB(33, 150, 243),

		/**** Menubar ****/
		.menuBarBackColor = UTFT::fromRGB(58, 58, 58),
		.menuBarFontColor = UTFT::fromRGB(255, 255, 255),
		.menuBarActiveColor = UTFT::fromRGB(33, 150, 255),


		/**** Main Section ****/
		.mainBackColor = UTFT::fromRGB(30, 30, 30),
		.mainFontColor = UTFT::fromRGB(255, 255, 255),
		.mainPanelColor = UTFT::fromRGB(81, 81, 81),
		.mainDarkButtonColor = UTFT::fromRGB(58, 58, 58),
		.mainActiveColor = UTFT::fromRGB(33, 150, 243),
		.mainWarningColor = UTFT::fromRGB(251, 140, 0),
		.dropdownBackColor = UTFT::fromRGB(58, 58, 58),
	}
};

#endif

// End

