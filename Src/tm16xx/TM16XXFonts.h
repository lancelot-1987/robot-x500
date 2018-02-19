/*
TM16XXFonts.h - Font definition for TM16XX.

Copyright (C) 2011 Ricardo Batista (rjbatista <at> gmail <dot> com)

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


The bits are displayed by mapping bellow
 -- 0 --
|       |
5       1
 -- 6 --
4       2
|       |
 -- 3 --  .7

*/

#ifndef TM16XXFonts_h
#define TM16XXFonts_h


#include <stdint.h>

// definition for standard hexadecimal numbers
extern const uint32_t NUMBER_FONT[];

// definition for the displayable ASCII chars
extern const uint32_t FONT_DEFAULT[];

#endif
