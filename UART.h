#ifndef UART_h
#define UART_h
#include <Arduino.h>

void UART_PrintS(const char *str);
void UART_Print_Integer(int32_t num);
void UART_Print_Float(float num);
unsigned char UART_Receive();
void UART_Transmitt(char ch);

#endif