#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Arduino.h>

MPU6050 mpu6050(Wire);
long timer = 0;

void UART_PrintS(const char *str);
void UART_Print_Integer(int32_t num);
void UART_Print_Float(float num);
unsigned char UART_Receive();
void UART_Transmitt(char ch);

int main(void)
{
  init();
  // Serial.begin(9600);
  UCSR0B |= _BV(RXEN0) | _BV(TXEN0); //enable receiver/transmitter
  UCSR0C = 0x06; // asynchronous mode, 8-bit character size,
  UCSR0A |= _BV(U2X0); //Double the UART Transmission Speed (in asynchronous mode only)
  UBRR0 = 207; //baud rate: 9600

  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  while(1)
  {
    mpu6050.update();
    
    if(millis() - timer > 1000)
    {
      
      UART_PrintS("=======================================================\n");
      UART_PrintS("temp: ");UART_Print_Float(mpu6050.getTemp());
      UART_PrintS("\naccX: ");UART_Print_Float(mpu6050.getAccX());
      UART_PrintS("\taccY: ");UART_Print_Float(mpu6050.getAccY());
      UART_PrintS("\taccZ: ");UART_Print_Float(mpu6050.getAccZ());
    
      UART_PrintS("\ngyroX: ");UART_Print_Float(mpu6050.getGyroX());
      UART_PrintS("\tgyroY: ");UART_Print_Float(mpu6050.getGyroY());
      UART_PrintS("\tgyroZ: ");UART_Print_Float(mpu6050.getGyroZ());

      UART_PrintS("\naccAngleX: ");UART_Print_Float(mpu6050.getAccAngleX());
      UART_PrintS("\taccAngleY: ");UART_Print_Float(mpu6050.getAccAngleY());
    
      UART_PrintS("\ngyroAngleX: ");UART_Print_Float(mpu6050.getGyroAngleX());
      UART_PrintS("\tgyroAngleY: ");UART_Print_Float(mpu6050.getGyroAngleY());
      UART_PrintS("\tgyroAngleZ: ");UART_Print_Float(mpu6050.getGyroAngleZ());
      
      UART_PrintS("\nangleX: ");UART_Print_Float(mpu6050.getAngleX());
      UART_PrintS("\tangleY: ");UART_Print_Float(mpu6050.getAngleY());
      UART_PrintS("\tangleZ: ");UART_Print_Float(mpu6050.getAngleZ());
      UART_PrintS("\n=======================================================\n");
      timer = millis();
    }
  }


  return 0;
}

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