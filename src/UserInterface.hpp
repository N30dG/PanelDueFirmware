/*
 * UserInterface.hpp
 *
 *  Created on: 7 Jan 2017
 *      Author: David
 */

#ifndef SRC_USERINTERFACE_HPP_
#define SRC_USERINTERFACE_HPP_

#include "ColourSchemes.hpp"
#include "PrinterStatus.hpp"
#include "Display.hpp"
#include "FirmwareFeatures.hpp"
#include "Events.hpp"


namespace UI
{
	extern void CreateMainWindow(uint32_t language, const ColourScheme& colours, uint32_t p_infoTimeout);
}

#endif /* SRC_USERINTERFACE_HPP_ */
