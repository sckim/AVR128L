#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <stdlib.h>

extern char str[80];

void UART_putch(unsigned char data);
unsigned char UART_getch(void);

void UART_putchar(unsigned char data, FILE *stream);
unsigned char UART_getchar(FILE *stream);

void InitUART(unsigned long iBaudrate);

#endif // UART_H 

