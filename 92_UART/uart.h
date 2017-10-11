#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <stdlib.h>

void uart_putchar(char c, FILE *stream);
char uart_getchar(FILE *stream);

void uart_init(unsigned long iBaudrate);

/* http://www.ermicro.com/blog/?p=325 */

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

//FILE uart_inout = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

#endif // UART_H 

