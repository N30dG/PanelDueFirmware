/*
 * Strings.hpp
 *
 *  Created on: 27 Feb 2017
 *      Author: David
 *
 * The encoding used for this file must be UTF-8 to ensure that accented characters are displayed correctly.
 */

#ifndef SRC_STRINGS_HPP_
#define SRC_STRINGS_HPP_

#include "ecv.h"
#include "UserInterfaceConstants.hpp"

#define CSTRING const char * const array
#define Newline			"\n"
#define DegreeSymbol	"\u00B0"

constexpr unsigned int NumLanguages = 1;
constexpr unsigned int NumStatusStrings = 13;

struct StringTable
{
	// Language name
	CSTRING languageName;

	// Main page strings
	CSTRING active;
	CSTRING standby;
	CSTRING tool;

	//Machine Control Strings
	CSTRING position;
	CSTRING extrude;
	CSTRING retract;
	CSTRING mm;
	CSTRING mm2;

	// Setup page
	CSTRING infoTimeout;
	CSTRING info;
	CSTRING version;
	CSTRING freeRam;
	CSTRING general;
	CSTRING baudRate;
	CSTRING volume;
	CSTRING calibrateTouch;
	CSTRING clearSettings;
	CSTRING appearance;
	CSTRING theme;
	CSTRING language;
	CSTRING display;
	CSTRING brightness;
	CSTRING dimming;
	CSTRING mirrorDisplay;
	CSTRING invertDisplay;

	// Misc
	CSTRING confirmFactoryReset;
	CSTRING areYouSure;
	CSTRING touchTheSpot;
	CSTRING status;


	// Heater status values
	CSTRING heaterStatus[5];

	// Colour theme names
	CSTRING colourSchemeNames[NumColorSchemes];

};

const StringTable LanguageTables[NumLanguages] =
{
	// English
	{
		// ISO-639.1 language code
		"en",

		"Active" THIN_SPACE DEGREE_SYMBOL "C",
		"Standby" THIN_SPACE DEGREE_SYMBOL "C",
		"Tool",
		"Position",
		"Extrude",
		"Retract",
		"mm",
		"mm/2",

		//Setup page
		"Info timeout:",
		"Info",
		"Version:",
		"Free RAM:",
		"General",
		"Baud rate:",
		"Volume:",
		"Calibrate touch",
		"Clear settings",
		"Appearance",
		"Theme:",
		"Language:",
		"Display",
		"Brightness:",
		"Dimming:",
		"Mirror Display",
		"Invert Display",

		// Misc
		"Confirm factory reset",
		"Are you sure?",
		"Touch the spot",
		"Status",

		// Heater status strings
		{
			"off",
		    "standby",
			"active",
			"error",
			"tuning"
		},

		// Theme names
		{
			"Light theme",
			"Dark theme"
		},
 	}
};

#endif /* SRC_STRINGS_HPP_ */
