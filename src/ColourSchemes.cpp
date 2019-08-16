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

const ColourScheme colourSchemes[NumColourSchemes] =
{
	// Light colour schema. As this one comes first, it is the default.
	{

	},
	
	// Dark colour scheme #1

	{
		.index = 1,

	},

	// Dark colour scheme #2

	{
		.index = 2,
		.pal = IconPaletteDark,

		.titleBarTextColour = white,
		.titleBarBackColour = midGrey,
		.labelTextColour = white,
		.infoTextColour = white,
		.infoBackColour = veryDarkGrey,
		.defaultBackColour = UTFT::fromRGB(30, 30, 30),
		.activeBackColour = red,
		.standbyBackColour = yellow,
		.tuningBackColour = darkGrey,
		.errorTextColour = white,
		.errorBackColour = veryDarkGrey,

		.popupBorderColour = darkGrey,
		.popupBackColour = darkGrey,
		.popupTextColour = white,
		.popupButtonTextColour = white,
		.popupButtonBackColour = veryDarkGrey,
		.popupInfoTextColour = white,
		.popupInfoBackColour = darkGrey,

		.alertPopupBackColour = darkGrey,
		.alertPopupTextColour = white,

		.buttonTextColour = white,
		.buttonPressedTextColour = white,
		.buttonTextBackColour = midGrey,
		.buttonImageBackColour = grey,
		.buttonGradColour = 0,	//UTFT::fromRGB(8, 4, 8),
		.buttonPressedBackColour = grey,
		.buttonPressedGradColour = 0,	//UTFT::fromRGB(8, 8, 8),
		.buttonBorderColour = midGrey,
		.homedButtonBackColour = midGrey,
		.notHomedButtonBackColour = orange,
		.pauseButtonBackColour = darkOrange,
		.resumeButtonBackColour = darkYellow,
		.resetButtonBackColour = darkRed,

		.progressBarColour = midGrey,
		.progressBarBackColour = veryDarkGrey,
		.stopButtonTextColour = white,
		.stopButtonBackColour = red,


		/**** Toolbar ****/
		.toolBarBackColor = UTFT::fromRGB(15, 15, 15),
		.toolBarFontColor = UTFT::fromRGB(255,255,255),
		.toolBarActiveColor = UTFT::fromRGB(33, 150, 243),

		/**** Menubar ****/
		.menuBarBackColor = UTFT::fromRGB(66, 66, 66),
		.menuBarFontColor = UTFT::fromRGB(255, 255, 255),
		.menuBarActiveColor = UTFT::fromRGB(33, 150, 255),


		/**** Main Section ****/
		.mainBackColor = UTFT::fromRGB(30, 30, 30),
		.mainFontColor = UTFT::fromRGB(255, 255, 255)
	}
};

#endif

// End

