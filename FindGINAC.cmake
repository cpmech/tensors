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

SET(GINAC_INCLUDE_SEARCH_PATH
  /usr/include
  /usr/include/ginac
  /usr/local/include
  /usr/local/include/ginac)

SET(GINAC_LIBRARY_SEARCH_PATH
  /usr/lib
  /usr/local/lib)

FIND_PATH(GINAC_GINAC_H  ginac/ginac.h  ${GINAC_INCLUDE_SEARCH_PATH})
FIND_LIBRARY(GINAC_GINAC NAMES ginac PATHS ${GINAC_LIBRARY_SEARCH_PATH})

SET(GINAC_FOUND 1)
FOREACH(var GINAC_GINAC_H GINAC_GINAC)
  IF(NOT ${var})
	SET(GINAC_FOUND 0)
  ENDIF(NOT ${var})
ENDFOREACH(var)

IF(GINAC_FOUND)
  SET(GINAC_INCLUDE_DIRS ${GINAC_GINAC_H})
  SET(GINAC_LIBRARIES    ${GINAC_GINAC})
ENDIF(GINAC_FOUND)
