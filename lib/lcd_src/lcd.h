#ifndef __LCD_H__
#define LED_H
#include <Arduino.h>

/*LCD Pins declerations*/
#define RS PD3
#define RW PD2
#define EN PD1

#define D7 PC4
#define D6 PC5
#define D5 PC6
#define D4 PC7

/*Function declerations*/
void configureLcdPins(void);
void lcd_cmd(uint8_t cmd);
void lcdData(uint8_t data);
void printData(uint8_t data);
void lcdInitialization(void);
void lcd_string(uint8_t str[], uint8_t data_len);
void intToString(int value, char* buffer, uint8_t bufferSize);
void intToStringWithPrefix(int value, const char* prefix, char* buffer, uint8_t bufferSize);


#endif //__LCD_H__