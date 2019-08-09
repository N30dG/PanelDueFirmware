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


/**** All off this is from theold UI! Keept to don't break other thing's, that we do not want to delete for now ***/
const unsigned int MaxHeaters = 7;
#define MaxAxes (6)

const unsigned int NumDisplayedFiles = 10;

extern uint8_t glcd28x32[];
#define DEFAULT_FONT	glcd28x32


const size_t NumColourSchemes = 3;
const PixelNumber numMessageRows = 5;


const PixelNumber messageTextWidth = DisplayX;
const PixelNumber touchCalibMargin = 15;
const unsigned int NumDisplayedMacros = 10;
const PixelNumber textButtonMargin = 1;
const PixelNumber iconButtonMargin = 2;



#endif /* SRC_USERINTERFACECONSTANTS_HPP_ */
