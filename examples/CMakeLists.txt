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

SET(PROGS
    doc01
    doc02
    ex01
    ex02
    ex03
    ex04
    ex05
    ex06
    ex07
    ex08
    ex09
    ex10
    ex11
    ex12
    ex13
    stiffmat
)

SET(TESTS
)

FOREACH(var ${PROGS})
    ADD_EXECUTABLE        (${var} "${var}.cpp")
    TARGET_LINK_LIBRARIES (${var} ${LIBS})
    SET_TARGET_PROPERTIES (${var} PROPERTIES COMPILE_FLAGS "${FLAGS}" LINK_FLAGS "${LFLAGS}")
ENDFOREACH(var)

FOREACH(var ${TESTS})
    ADD_EXECUTABLE        (${var} "${var}.cpp")
    ADD_TEST              (${var} ${var})
    TARGET_LINK_LIBRARIES (${var} ${LIBS})
    SET_TARGET_PROPERTIES (${var} PROPERTIES COMPILE_FLAGS "${FLAGS}" LINK_FLAGS "${LFLAGS}")
ENDFOREACH(var)
