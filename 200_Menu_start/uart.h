#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <stdlib.h>

void uart_putch(unsigned char data);
unsigned char uart_getch(void);

void uart_putchar(unsigned char data, FILE *stream);
unsigned uart_getchar(FILE *stream);


void uart_init(unsigned long iBaudrate);

/* http://www.ermicro.com/blog/?p=325 */

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

#endif // UART_H 

