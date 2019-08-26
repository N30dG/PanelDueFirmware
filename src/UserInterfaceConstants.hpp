/*
 * UserInterfaceConstants.hpp
 *
 *  Created on: 10 Jan 2017
 *      Author: David
 */

#ifndef SRC_USERINTERFACECONSTANTS_HPP_
#define SRC_USERINTERFACECONSTANTS_HPP_

#include "Configuration.hpp"
#include "DisplaySize.hpp"


/**** All off this is from the old UI! ****/
/**** Keept to don't break other thing's, that we do not want to delete for now ***/
const unsigned int MaxHeaters = 7;
#define MaxAxes (6)

const unsigned int NumDisplayedFiles = 10;

extern uint8_t glcd28x32[];
extern uint8_t glcd22x32[];
extern uint8_t glcd20x30[];
extern uint8_t glcd19x21[];
#define DEFAULT_FONT	glcd22x32


const size_t NumColorSchemes = 2;
const PixelNumber numMessageRows = 5;
const size_t numMoveButtons = 9;


const PixelNumber messageTextWidth = DisplayX;
const PixelNumber touchCalibMargin = 15;
const unsigned int NumDisplayedMacros = 10;
const PixelNumber textButtonMargin = 1;
const PixelNumber iconButtonMargin = 2;


/**** Popup ****/
const PixelNumber popupMargin = 10;


/**** "Are You Sure"-Popup ****/
const PixelNumber areYouSurePopupWidth = DISPLAY_X - 100;
const PixelNumber areYouSurePopupHeight = 200;
const PixelNumber areYouSureButtonWidth = 200;
const PixelNumber areYouSureButtonHeight = 50;


/**** Menu Bar ****/
const PixelNumber menuBarWidth = 50;
const uint8_t MaxMenuEntrys = 5;


/**** Tool Bar ****/
const PixelNumber toolBarHeight = 40;
const PixelNumber toolBarButtonWidth = 112;
const PixelNumber toolDropdownWidth = 180;
const PixelNumber toolDropdownHeight = 250;


/**** Menu Bar ****/
const PixelNumber mainSectionMargin = 10;



/**** Panel common ****/
const PixelNumber pButtonHeight = 40;

const PixelNumber pRow1Label = 40;
const PixelNumber pRow1Item = 70;
const PixelNumber pRow1Button = 65;

const PixelNumber pRow2Label = 110;
const PixelNumber pRow2Item = 140;
const PixelNumber pRow2Button = 135;


/**** Machine Control ****/
const PixelNumber mcpStatusHeight = 100;
const PixelNumber mcpMoveWidth = 548;
const PixelNumber mcpHomeWidth = 50;
const PixelNumber mcpHomeHeight = 36;
const PixelNumber mcpHomeMargin = 5;
const PixelNumber mcpExtrudeButtonHeight = 40;


/**** Setup ****/
const PixelNumber spInfoX = mainSectionMargin;
const PixelNumber spInfoY = mainSectionMargin;
const PixelNumber spInfoHeight = 110;
const PixelNumber spInfoWidth = 300;

const PixelNumber spGeneralX = mainSectionMargin*2+spInfoWidth;
const PixelNumber spGeneralY = mainSectionMargin;
const PixelNumber spGeneralWidth = DISPLAY_X - (menuBarWidth + mainSectionMargin*3 + spInfoWidth);
const PixelNumber spGeneralHeight = 240;

const PixelNumber spAppearanceX = mainSectionMargin;
const PixelNumber spAppearanceY = mainSectionMargin*2 + spInfoHeight;
const PixelNumber spAppearanceHeight = 190;
const PixelNumber spAppearanceWidth = spInfoWidth;

const PixelNumber spDisplayX = mainSectionMargin*2 + spInfoWidth;
const PixelNumber spDisplayY = mainSectionMargin*2 + spGeneralHeight;
const PixelNumber spDisplayWidth = DISPLAY_X - (menuBarWidth + mainSectionMargin*3 + spInfoWidth);
const PixelNumber spDisplayHeight = 170;

#endif /* SRC_USERINTERFACECONSTANTS_HPP_ */
