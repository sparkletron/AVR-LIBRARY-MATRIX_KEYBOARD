/*
 * keyboadMatrix.c
 *
 *  Created on: Feb 10, 2015
 *      Author: John Convertino
 *      email: electrobs@gmail.com
 *		
 *		Library for matrix keyboard of any size and port.
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
 *		Version: 0.2
 *		Feb 10, 2015 0.2 Fixed address offset for col port (setup for PORT* not PIN*)
 *		Feb 10, 2015 0.1 Initial version, does scan inc with scan and gets key with getKey.
 *
 *		TODO
 */

#include <avr/common.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "commonTimer.h"

#define WAIT_TIME 1

typedef struct
{
    uint8_t row_index;
    uint8_t row_size;
    uint8_t col_index;
    uint8_t col_size;
    volatile uint8_t *row_port;
    volatile uint8_t *col_port;
} s_matrix;

static s_matrix matrix;

void initKeyboardMatrix(volatile uint8_t *row_port, uint8_t row_size, volatile uint8_t *col_port, uint8_t col_size)
{
  matrix.row_size = row_size;
  matrix.row_index = 0;
  matrix.col_size = col_size;
  matrix.col_index = 0;
  matrix.row_port = row_port;
  matrix.col_port = col_port;
  //setup DDR ports row as output (1's) and column as input (0's)
  *((matrix.row_port)-1) |= ~(~0U << matrix.row_size);
  *((matrix.col_port)+1) &= (~0U << matrix.col_size);
  //set row port bit 0 to 1
  *(matrix.row_port) &= (~0 << matrix.row_size);
  *(matrix.row_port) |= (1 << matrix.row_index);
}

void scanMatrix()
{
  uint8_t bufSREG = SREG;
  cli();
  static uint64_t pastMilliseconds = 0;

  if((e_milliseconds - pastMilliseconds) < WAIT_TIME)
  {
      SREG = bufSREG;
      return;
  }

  pastMilliseconds = e_milliseconds;

  matrix.row_index++;

  if(matrix.row_index >= matrix.row_size)
  {
      matrix.row_index = 0;
      matrix.col_index++;
      if(matrix.col_index >= matrix.col_size)
        matrix.col_index = 0;
  }

  *(matrix.row_port) &= (~0U << matrix.row_size);
  *(matrix.row_port) |= (1 << matrix.row_index);

  SREG = bufSREG;

}

uint8_t getKey()
{
  uint8_t bufSREG = SREG;
  cli();
  if(*(matrix.col_port) & (1 << matrix.col_index))
  {
      SREG = bufSREG;
      return ((matrix.row_index + 1) * 10 + matrix.col_index);
  }
  SREG = bufSREG;
  return 0;
}
