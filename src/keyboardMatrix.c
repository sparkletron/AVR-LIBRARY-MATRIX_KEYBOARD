/*******************************************************************************
 * @file    keyboadMatrix.c
 * @brief   Library for matrix keyboard of any size and port.
 * @author  Jay Convertino(electrobs@gmail.com)
 * @date    2015.02.10
 * @details OH SO MANY
 * @version 0.2.0
 *
 * PREVIOUS:
 *  Feb 10, 2015 0.2 Fixed address offset for col port (setup for PORT* not PIN*)
 *  Feb 10, 2015 0.1 Initial version, does scan inc with scan and gets key with getKey.
 *
 * @license mit
 *
 * Copyright 2022 Johnathan Convertino
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/

#include <avr/common.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "commonTimer.h"

#define WAIT_TIME 1

void initKeyboardMatrix(struct s_matrix *p_matrix, volatile uint8_t *row_port, uint8_t row_size, volatile uint8_t *col_port, uint8_t col_size)
{
  uint8_t tmpSREG = 0;

  if(p_matrix == NULL) return;

  tmpSREG = SREG;
  cli();

  p_matrix->row_size = row_size;
  p_matrix->row_index = 0;
  p_matrix->col_size = col_size;
  p_matrix->col_index = 0;
  p_matrix->row_port = row_port;
  p_matrix->col_port = col_port;
  //setup DDR ports row as output (1's) and column as input (0's)
  *((p_matrix->row_port)-1) |= ~(~0U << p_matrix->row_size);
  *((p_matrix->col_port)+1) &= (~0U << p_matrix->col_size);
  //set row port bit 0 to 1
  *(p_matrix->row_port) &= (~0 << p_matrix->row_size);
  *(p_matrix->row_port) |= (1 << p_matrix->row_index);

  SREG = tmpSREG;
}

void scanMatrix(struct s_matrix *p_matrix)
{
  uint8_t tmpSREG = 0;

  if(p_matrix == NULL) return;

  tmpSREG = SREG;
  cli();

  static uint64_t pastMilliseconds = 0;

  if((e_milliseconds - pastMilliseconds) < WAIT_TIME)
  {
      SREG = tmpSREG;
      return;
  }

  pastMilliseconds = e_milliseconds;

  p_matrix->row_index++;

  if(p_matrix->row_index >= p_matrix->row_size)
  {
      p_matrix->row_index = 0;
      p_matrix->col_index++;
      if(p_matrix->col_index >= p_matrix->col_size)
        p_matrix->col_index = 0;
  }

  *(p_matrix->row_port) &= (~0U << p_matrix->row_size);
  *(p_matrix->row_port) |= (1 << p_matrix->row_index);

  SREG = tmpSREG;

}

uint8_t getKey(struct s_matrix *p_matrix)
{
  uint8_t tmpSREG = 0;

  if(p_matrix == NULL) return 0;

  tmpSREG = SREG;
  cli();

  if(*(p_matrix->col_port) & (1 << p_matrix->col_index))
  {
      SREG = tmpSREG;
      return ((p_matrix->row_index + 1) * 10 + p_matrix->col_index);
  }

  SREG = tmpSREG;

  return 0;
}
