#####################################################################################
# Tensors - A C++ library to work with tensors                                      #
# Copyright (C) 2004 Dorival de Moraes Pedroso <dorival.pedroso em gmail.com>       #
#                                                                                   #
# This file is part of Tensors.                                                     #
#                                                                                   #
# Tensors is free software; you can redistribute it and/or modify it under the      #
# terms of the GNU General Public License as published by the Free Software         #
# Foundation; either version 2 of the License, or (at your option) any later        #
# version.                                                                          #
#                                                                                   #
# Tensors is distributed in the hope that it will be useful, but WITHOUT ANY        #
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A   #
# PARTICULAR PURPOSE. See the GNU General Public License for more details.          #
#                                                                                   #
# You should have received a copy of the GNU General Public License along with      #
# Tensors; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, #
# Fifth Floor, Boston, MA 02110-1301, USA                                           #
#####################################################################################

PROJECT                (TENSORS)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
ENABLE_TESTING         ()

### options #########################################################################

OPTION(MAKE_VERBOSE       "Show additional messages during compilation/link?" OFF)
OPTION(MAKE_OPTIMIZED     "Make optimized (-O3)"                              ON )
OPTION(MAKE_ALL_WARNINGS  "Make with all warnings (-Wall)"                    ON )
OPTION(MAKE_DEBUG_SYMBOLS "Make with debug symbols (-g3)"                     OFF)

IF(MAKE_VERBOSE)
	SET(CMAKE_VERBOSE_MAKEFILE TRUE)
ENDIF(MAKE_VERBOSE)

IF(MAKE_ALL_WARNINGS)
	ADD_DEFINITIONS(-Wall)
ENDIF(MAKE_ALL_WARNINGS)

IF(MAKE_DEBUG_SYMBOLS)
	ADD_DEFINITIONS(-g3)
ENDIF(MAKE_DEBUG_SYMBOLS)

IF(MAKE_OPTIMIZED)
	ADD_DEFINITIONS(-O3)
ENDIF(MAKE_OPTIMIZED)

ADD_DEFINITIONS(-fmessage-length=0)

### dependencies ####################################################################

INCLUDE(${TENSORS_SOURCE_DIR}/FindGINAC.cmake)
IF(GINAC_FOUND)
    INCLUDE_DIRECTORIES (${GINAC_GINAC_H})
    SET (LIBS ${LIBS} ${GINAC_GINAC})
ELSE(GINAC_FOUND)
    MESSAGE("Error: this project needs GiNaC (sudo apt-get install libginac-dev)")
ENDIF(GINAC_FOUND)

### tests ###########################################################################

INCLUDE_DIRECTORIES (${TENSORS_SOURCE_DIR})

SUBDIRS (examples)
