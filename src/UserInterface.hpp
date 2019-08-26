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


extern StaticTextField *touchCalibInstruction;


namespace UI
{
	extern void ProcessTouch(ButtonPress bp);
	extern void ProcessTouchOutsidePopup(ButtonPress bp);

	extern void UpdateCurrentTemperature(size_t heater, float fval);
	extern void SetNumTools(unsigned int n);
	extern void SetNumHeaters(unsigned int n);
	extern void UpdateHeaterStatus(size_t heater, int ival);
	extern void UpdateActiveTemperature(size_t index, int ival);
	extern void UpdateStandbyTemperature(size_t index, int ival);
	extern void UpdateGeometry(unsigned int p_numAxes, bool p_isDelta);
	extern void UpdateAxisPosition(size_t axis, float fval);
	extern void UpdateHomedStatus(int axis, bool isHomed);
	extern void UpdateFreeRam(int mem);

	extern void CreateMainWindow(uint32_t language, const ColourScheme& colours, uint32_t p_infoTimeout);
}

#endif /* SRC_USERINTERFACE_HPP_ */
