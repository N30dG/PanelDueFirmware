/*
 * ColourScheme.h
 *
 * Created: 01/09/2016 13:13:05
 *  Author: David
 */ 

#ifndef COLOURSCHEME_H_
#define COLOURSCHEME_H_

#include "Hardware/UTFT.hpp"

// Some common colours
const Colour white = 0xFFFF, black = 0x0000;

// Definition of a colour scheme
struct ColourScheme
{
	size_t index;


	/**** "Are You Sure"-Popup ****/
	Colour popupBackColor;
	Colour popupFontColor;
	Colour popupButtonBackColor;
	Colour popupBorderColor;


	/**** Toolbar ****/
	Colour toolBarBackColor;
	Colour toolBarFontColor;
	Colour toolBarActiveColor;


	/*** MenuBar ****/
	Colour menuBarBackColor;
	Colour menuBarFontColor;
	Colour menuBarActiveColor;


	/**** Main Section ****/
	Colour mainBackColor;
	Colour mainFontColor;
	Colour mainPanelColor;
	Colour mainDarkButtonColor;
	Colour mainActiveColor;
	Colour mainWarningColor;
	Colour dropdownBackColor;
};

extern const ColourScheme colourSchemes[];

#endif /* COLOURSCHEME_H_ */
