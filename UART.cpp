#include "UART.h"

void UART_PrintS(const char *str)
{
  for(uint8_t i = 0; str[i] != '\0'; ++i)
    UART_Transmitt(str[i]);
}

void UART_Print_Integer(int32_t num)
{
  char buffer[11]; // maximum size of a 32-bit unsigned integer is 10 characters plus null terminator
  snprintf(buffer, sizeof(buffer), "%ld", num); // convert the number to a string
  for (uint8_t i = 0; buffer[i] != '\0'; i++)
    UART_Transmitt(buffer[i]); // send each character of the string via UART
}

void UART_Print_Float(float num)
{
  char buffer[16]; // maximum size of a float is 15 characters plus null terminator
  // snprintf(buffer, sizeof(buffer), "%.2f", num); // convert the number to a string with 2 decimal places
  char *tmpSign = (num < 0) ? "-" : "";
  float tmpVal = (num < 0) ? -num : num;

  int tmpInt1 = tmpVal;                  // Get the integer (392).
  float tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.6).
  int tmpInt2 = trunc(tmpFrac * 10000);  // Turn into integer (123).

  // Print as parts, note that you need 0-padding for fractional bit.

  sprintf (buffer, "%s%d.%04d", tmpSign, tmpInt1, tmpInt2);
  
  for (uint8_t i = 0; buffer[i] != '\0'; i++)
    UART_Transmitt(buffer[i]); // send each character of the string via UART

}

unsigned char UART_Receive()
{
  while(!(UCSR0A & (1 << RXC0)));
  return UDR0;
}

void UART_Transmitt(char ch)
{
  while(!(UCSR0A & (1 << UDRE0)));
  UDR0 = ch;
}