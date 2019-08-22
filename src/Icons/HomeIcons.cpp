/*
 * HomeIcons.cpp
 *
 * Created: 29/11/2015 12:10:12
 *  Author: David
 */

#include "asf.h"
#include "Configuration.hpp"
#include "Icons.hpp"

extern const uint16_t IconPaletteLight[] =
{
    0x0000, 0x0010, 0x0400, 0x0410, 0x07ff, 0x8000, 0x8400, 0x8410,
    0xc618, 0xf800, 0xffe0, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff
};

extern const uint16_t IconPaletteDark[] =
{
    0x0000, 0x0010, 0x0400, 0x0410, 0x07ff, 0x8000, 0x8400, 0x8410,
    0xc618, 0xf800, 0xffe0, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff
};

extern const uint8_t IconHomeAll[] =
{	35, 30,		// width, height
	0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0xF0, 0x07,
	0x00, 0x00, 0xDE, 0x7F, 0x00, 0x00, 0xF0, 0xFF, 0x07, 0x00, 0x80, 0xFF,
	0x7F, 0x00, 0x00, 0xFC, 0xFF, 0x07, 0x00, 0xE0, 0xFF, 0x7F, 0x00, 0x00,
	0xFF, 0xFF, 0x07, 0x00, 0xFC, 0xFF, 0x7F, 0x00, 0xF0, 0xFF, 0xFF, 0x07,
	0xC0, 0xFF, 0xFF, 0x7F, 0x00, 0xFF, 0xFF, 0xFF, 0x07, 0xFC, 0xFF, 0xFF,
	0x7F, 0xF0, 0xFF, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xFF, 0x7F, 0xE0, 0xFF,
	0xFF, 0x3F, 0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xF8, 0xFF, 0xFF, 0x0F, 0xC0,
	0x87, 0x0F, 0x7E, 0x00, 0x3E, 0x7C, 0xF0, 0x03, 0xF0, 0xE1, 0x83, 0x1F,
	0x80, 0x0F, 0x1F, 0xFC, 0x00, 0x7C, 0xF8, 0xE0, 0x07, 0xE0, 0xFF, 0x07,
	0x3F, 0x00, 0xFF, 0x3F, 0xF8, 0x01, 0xF8, 0xFF, 0xC1, 0x0F, 0xC0, 0xFF,
	0x0F, 0x7E, 0x00, 0xFE, 0x7F, 0xF0, 0x03, 0xF0, 0xFF, 0x83, 0x1F, 0x00
};

extern const uint8_t IconHomeX[] =
{	35, 30,		// width, height
	0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0xF0, 0x07,
	0x00, 0x00, 0xDE, 0x7F, 0x00, 0x00, 0xF0, 0xFF, 0x07, 0x00, 0x80, 0xFF,
	0x7F, 0x00, 0x00, 0xFC, 0xFF, 0x07, 0x00, 0xE0, 0xFF, 0x7F, 0x00, 0x00,
	0xFF, 0xFF, 0x07, 0x00, 0xFC, 0xFF, 0x7F, 0x00, 0xF0, 0xFF, 0xFF, 0x07,
	0xC0, 0xFF, 0xFF, 0x7F, 0x00, 0xFF, 0xFF, 0xFF, 0x07, 0xFC, 0xFF, 0xFF,
	0x7F, 0xF0, 0xFF, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xFF, 0x7F, 0xE0, 0xFF,
	0xFF, 0x3F, 0x00, 0xFF, 0xC3, 0xC3, 0x01, 0xF8, 0x1F, 0x0C, 0x0E, 0xC0,
	0x87, 0x01, 0x78, 0x00, 0x3E, 0x1C, 0xE0, 0x03, 0xF0, 0xE1, 0x81, 0x1F,
	0x80, 0x0F, 0x1F, 0xFE, 0x00, 0x7C, 0x78, 0xE0, 0x07, 0xE0, 0xFF, 0x01,
	0x3E, 0x00, 0xFF, 0x07, 0xE0, 0x01, 0xF8, 0x1F, 0x0C, 0x0E, 0xC0, 0xFF,
	0xF0, 0x70, 0x00, 0xFE, 0xFF, 0xFF, 0x03, 0xF0, 0xFF, 0xFF, 0x1F, 0x00
};

extern const uint8_t IconHomeY[] =
{	35, 30,		// width, height
	0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0xF0, 0x07,
	0x00, 0x00, 0xDE, 0x7F, 0x00, 0x00, 0xF0, 0xFF, 0x07, 0x00, 0x80, 0xFF,
	0x7F, 0x00, 0x00, 0xFC, 0xFF, 0x07, 0x00, 0xE0, 0xFF, 0x7F, 0x00, 0x00,
	0xFF, 0xFF, 0x07, 0x00, 0xFC, 0xFF, 0x7F, 0x00, 0xF0, 0xFF, 0xFF, 0x07,
	0xC0, 0xFF, 0xFF, 0x7F, 0x00, 0xFF, 0xFF, 0xFF, 0x07, 0xFC, 0xFF, 0xFF,
	0x7F, 0xF0, 0xFF, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xFF, 0x7F, 0xE0, 0xFF,
	0xFF, 0x3F, 0x00, 0xFF, 0xC7, 0xC7, 0x01, 0xF8, 0x30, 0x1C, 0x0E, 0xC0,
	0x87, 0x43, 0x78, 0x00, 0x3E, 0x3C, 0xE0, 0x03, 0xF0, 0xE1, 0x83, 0x1F,
	0x80, 0x0F, 0x3F, 0xFE, 0x00, 0xFC, 0xFF, 0xF1, 0x07, 0xE0, 0xFF, 0x8F,
	0x3F, 0x00, 0xFF, 0x7F, 0xFC, 0x01, 0xF8, 0xFF, 0xE3, 0x0F, 0xC0, 0xFF,
	0x1F, 0x7F, 0x00, 0xFE, 0xFF, 0xFF, 0x03, 0xF0, 0xFF, 0xFF, 0x1F, 0x00
};

extern const uint8_t IconHomeZ[] =
{	35, 30,		// width, height
	0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0xF0, 0x07,
	0x00, 0x00, 0xDE, 0x7F, 0x00, 0x00, 0xF0, 0xFF, 0x07, 0x00, 0x80, 0xFF,
	0x7F, 0x00, 0x00, 0xFC, 0xFF, 0x07, 0x00, 0xE0, 0xFF, 0x7F, 0x00, 0x00,
	0xFF, 0xFF, 0x07, 0x00, 0xFC, 0xFF, 0x7F, 0x00, 0xF0, 0xFF, 0xFF, 0x07,
	0xC0, 0xFF, 0xFF, 0x7F, 0x00, 0xFF, 0xFF, 0xFF, 0x07, 0xFC, 0xFF, 0xFF,
	0x7F, 0xF0, 0xFF, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xFF, 0x7F, 0xE0, 0xFF,
	0xFF, 0x3F, 0x00, 0xFF, 0x1F, 0x80, 0x01, 0xF8, 0xFF, 0x00, 0x0C, 0xC0,
	0x87, 0x07, 0x60, 0x00, 0x3E, 0xFC, 0x87, 0x03, 0xF0, 0xE1, 0x1F, 0x1E,
	0x80, 0x0F, 0x7F, 0xF8, 0x00, 0x7C, 0xF8, 0xE1, 0x07, 0xE0, 0xFF, 0x87,
	0x3F, 0x00, 0xFF, 0x1F, 0x80, 0x01, 0xF8, 0xFF, 0x00, 0x0C, 0xC0, 0xFF,
	0x07, 0x60, 0x00, 0xFE, 0xFF, 0xFF, 0x03, 0xF0, 0xFF, 0xFF, 0x1F, 0x00
};

extern const uint8_t IconHomeU[] =
{	35, 30,
	0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0xF0, 0x07,
	0x00, 0x00, 0xDE, 0x7F, 0x00, 0x00, 0xF0, 0xFF, 0x07, 0x00, 0x80, 0xFF,
	0x7F, 0x00, 0x00, 0xFC, 0xFF, 0x07, 0x00, 0xE0, 0xFF, 0x7F, 0x00, 0x00,
	0xFF, 0xFF, 0x07, 0x00, 0xFC, 0xFF, 0x7F, 0x00, 0xF0, 0xFF, 0xFF, 0x07,
	0xC0, 0xFF, 0xFF, 0x7F, 0x00, 0xFF, 0xFF, 0xFF, 0x07, 0xFC, 0xFF, 0xFF,
	0x7F, 0xF0, 0xFF, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xFF, 0x7F, 0xE0, 0xFF,
	0xFF, 0x3F, 0x00, 0xFF, 0x87, 0x87, 0x01, 0xF8, 0x30, 0x3C, 0x0C, 0xC0,
	0x87, 0xE1, 0x61, 0x00, 0x3E, 0x0C, 0x0F, 0x03, 0xF0, 0x61, 0x78, 0x18,
	0x80, 0x0F, 0xC3, 0xC3, 0x00, 0xFC, 0x1F, 0x1E, 0x06, 0xE0, 0xFF, 0x60,
	0x30, 0x00, 0xFF, 0x0F, 0xC0, 0x01, 0xF8, 0x7F, 0x00, 0x0E, 0xC0, 0xFF,
	0x0F, 0x7C, 0x00, 0xFE, 0xFF, 0xFF, 0x03, 0xF0, 0xFF, 0xFF, 0x1F, 0x00
};

extern const uint8_t IconHomeV[] =
{	35, 30,
	0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0xF0, 0x07,
	0x00, 0x00, 0xDE, 0x7F, 0x00, 0x00, 0xF0, 0xFF, 0x07, 0x00, 0x80, 0xFF,
	0x7F, 0x00, 0x00, 0xFC, 0xFF, 0x07, 0x00, 0xE0, 0xFF, 0x7F, 0x00, 0x00,
	0xFF, 0xFF, 0x07, 0x00, 0xFC, 0xFF, 0x7F, 0x00, 0xF0, 0xFF, 0xFF, 0x07,
	0xC0, 0xFF, 0xFF, 0x7F, 0x00, 0xFF, 0xFF, 0xFF, 0x07, 0xFC, 0xFF, 0xFF,
	0x7F, 0xF0, 0xFF, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xFF, 0x7F, 0xE0, 0xFF,
	0xFF, 0x3F, 0x00, 0xFF, 0xE7, 0x9F, 0x01, 0xF8, 0x30, 0x7E, 0x0C, 0xC0,
	0x87, 0xF1, 0x63, 0x00, 0x3E, 0x1C, 0x8F, 0x03, 0xF0, 0xE1, 0x78, 0x1C,
	0x80, 0x0F, 0x8F, 0xF1, 0x00, 0xFC, 0x7F, 0x8C, 0x07, 0xE0, 0xFF, 0x07,
	0x3E, 0x00, 0xFF, 0x3F, 0xF0, 0x01, 0xF8, 0xFF, 0xC3, 0x0F, 0xC0, 0xFF,
	0x3F, 0x7F, 0x00, 0xFE, 0xFF, 0xFF, 0x03, 0xF0, 0xFF, 0xFF, 0x1F, 0x00
};

extern const uint8_t IconHomeW[] =
{	35, 30,
	0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0xF0, 0x07,
	0x00, 0x00, 0xDE, 0x7F, 0x00, 0x00, 0xF0, 0xFF, 0x07, 0x00, 0x80, 0xFF,
	0x7F, 0x00, 0x00, 0xFC, 0xFF, 0x07, 0x00, 0xE0, 0xFF, 0x7F, 0x00, 0x00,
	0xFF, 0xFF, 0x07, 0x00, 0xFC, 0xFF, 0x7F, 0x00, 0xF0, 0xFF, 0xFF, 0x07,
	0xC0, 0xFF, 0xFF, 0x7F, 0x00, 0xFF, 0xFF, 0xFF, 0x07, 0xFC, 0xFF, 0xFF,
	0x7F, 0xF0, 0xFF, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xFF, 0x7F, 0xE0, 0xFF,
	0xFF, 0x3F, 0x00, 0xFF, 0xC7, 0x8F, 0x01, 0xF8, 0x30, 0x7E, 0x0C, 0xC0,
	0x87, 0xF1, 0x63, 0x00, 0x3E, 0x8C, 0x1F, 0x03, 0xF0, 0x61, 0xFC, 0x18,
	0x80, 0x0F, 0x63, 0xC6, 0x00, 0xFC, 0x1F, 0x21, 0x06, 0xE0, 0xFF, 0x00,
	0x30, 0x00, 0xFF, 0x07, 0x80, 0x01, 0xF8, 0x7F, 0x18, 0x0E, 0xC0, 0xFF,
	0xE7, 0x79, 0x00, 0xFE, 0xFF, 0xFF, 0x03, 0xF0, 0xFF, 0xFF, 0x1F, 0x00
};

extern const uint8_t IconBedComp[] =
{	41, 30,		// width, height
	0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
	0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0xE0,
	0x1F, 0x00, 0x00, 0x00, 0x80, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00,
	0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x07, 0x00, 0x00, 0x00, 0xFE,
	0x7F, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xE3, 0x01, 0xC0, 0x7F, 0xE0, 0xFF,
	0x1F, 0xF8, 0x1F, 0x00, 0xFE, 0xFF, 0xFF, 0x0F, 0x00, 0xF0, 0xF8, 0xFF,
	0x03, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00,
	0xE0, 0x01, 0x00, 0x00, 0x00, 0xE0, 0x07, 0x00, 0x00, 0x00, 0xE0, 0x1F,
	0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00,
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00,
	0x60, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00
};

// End
