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

#ifndef KEYBOARDMATRIX_H_
#define KEYBOARDMATRIX_H_

#include <inttypes.h>

/**
 * @struct s_matrix
 * @brief Struct for containing keyboard matrix instances
 */
struct s_matrix
{
   /**
   * @var s_matrix::row_index
   * keep track of indexed row
   */
   uint8_t row_index;
   /**
   * @var s_matrix::row_size
   * max size of row
   */
   uint8_t row_size;
   /**
   * @var s_matrix::col_index
   * keep track of indexed column
   */
   uint8_t col_index;
   /**
   * @var s_matrix::col_size
   * max size of column
   */
   uint8_t col_size;
   /**
   * @var s_matrix::row_port
   * port for row
   */
   volatile uint8_t *row_port;
   /**
   * @var s_matrix::col_port
   * port for column
   */
   volatile uint8_t *col_port;
}

/***************************************************************************//**
 * @brief   Initialize keyboard matrix
 *
 * @param   p_matrix matrix struct pointer
 * @param   row_port pointer to row register (PORT).
 * @param   row_size number of rows.
 * @param   col_port pointer to column register (PORT).
 * @param   col_size number of columns.
 ******************************************************************************/
void initKeyboardMatrix(struct s_matrix *p_matrix, volatile uint8_t *row_port, uint8_t row_size, volatile uint8_t *col_port, uint8_t col_size);

/***************************************************************************//**
 * @brief   call to scan matrix, has a built in time check but should be called as often as possible
 *
 * @param   p_matrix matrix struct pointer
 ******************************************************************************/
void scanMatrix(struct s_matrix *p_matrix);

/***************************************************************************//**
 * @brief   gets the current key if col_port pin is high at current col index
 *
 * @param   p_matrix matrix struct pointer
 ******************************************************************************/
uint8_t getKey(struct s_matrix *p_matrix);


#endif /* KEYBOARDMATRIX_H_ */
