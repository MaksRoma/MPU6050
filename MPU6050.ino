#include <MPU6050_tockn.h>
#include <Wire.h>
// #include <Arduino.h>
#include "UART.h"

MPU6050 mpu6050(Wire);
long timer = 0;


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