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


const size_t NumColourSchemes = 3;
const PixelNumber numMessageRows = 5;
const size_t numMoveButtons = 9;


const PixelNumber messageTextWidth = DisplayX;
const PixelNumber touchCalibMargin = 15;
const unsigned int NumDisplayedMacros = 10;
const PixelNumber textButtonMargin = 1;
const PixelNumber iconButtonMargin = 2;


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

/**** Machine Control ****/
const PixelNumber mcpStatusHeight = 100;
const PixelNumber mcpMoveWidth = 548;
const PixelNumber mcpHomeWidth = 50;
const PixelNumber mcpHomeHeight = 36;
const PixelNumber mcpHomeMargin = 5;
const PixelNumber mcpExtrudeButtonHeight = 40;

#endif /* SRC_USERINTERFACECONSTANTS_HPP_ */
