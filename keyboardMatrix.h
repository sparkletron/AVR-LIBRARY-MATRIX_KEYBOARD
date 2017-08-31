/*
 * keyboardMatrix.h
 *
 *  Created on: Feb 10, 2015
 *      Author: John Convertino
 *      email: electrobs@gmail.com
 *		
 *		Library for matrix keyboard of any size and port.
 *		Returns 10 to 17 for first row, 20 to 27 for 2nd and etc.
 *		No key pressed returns 0.
 *
    Copyright (C) 2015 John Convertino

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *		Version: 0.1
 */

#ifndef KEYBOARDMATRIX_H_
#define KEYBOARDMATRIX_H_

#include <inttypes.h>

/* row_port is a output port (ex &PORTD), row size is the max row size,
 * col_port is a input port (&PINC), and col size is the max column size.
 */
void initKeyboardMatrix(volatile uint8_t *row_port, uint8_t row_size, volatile uint8_t *col_port, uint8_t col_size);

//call to scan matrix, has a built in time check but should be called as often as possible
void scanMatrix();

//gets the current key if col_port pin is high at current col index
uint8_t getKey();


#endif /* KEYBOARDMATRIX_H_ */
