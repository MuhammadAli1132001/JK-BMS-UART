#include "lcd.h"

void configureLcdPins(void)
{
  pinMode(RS,OUTPUT);
  pinMode(RW,OUTPUT);
  pinMode(EN,OUTPUT);

  pinMode(D7,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D4,OUTPUT);
}

void lcd_cmd(uint8_t cmd)
{
  printData(cmd&0xF0);
  digitalWrite(RS,LOW);
  digitalWrite(RW,LOW);
  digitalWrite(EN,HIGH);
  delay(2);
  digitalWrite(EN,LOW);
  printData(cmd<<4);
  digitalWrite(RS,LOW);
  digitalWrite(RW,LOW);
  digitalWrite(EN,HIGH);
  delay(2);
  digitalWrite(EN,LOW);
}

void lcdData(uint8_t data)
{
  printData(data&0xF0);
  digitalWrite(RS,HIGH);
  digitalWrite(RW,LOW);
  digitalWrite(EN,HIGH);
  delay(2);
  digitalWrite(EN,LOW);

  printData(data<<4);
  digitalWrite(RS,HIGH);
  digitalWrite(RW,LOW);
  digitalWrite(EN,HIGH);
  delay(2);
  digitalWrite(EN,LOW);
}

void printData(uint8_t data)
{
if ((data & 0x80) == 0x80) { /*Serial_print_s("1");*/ digitalWrite(D7, HIGH); }
else { /*Serial_print_s("0");*/ digitalWrite(D7, LOW); }

if ((data & 0x40) == 0x40) { /*Serial_print_s("1");*/ digitalWrite(D6, HIGH); }
else { /*Serial_print_s("0");*/ digitalWrite(D6, LOW); }

if ((data & 0x20) == 0x20) { /*Serial_print_s("1");*/ digitalWrite(D5, HIGH); }
else { /*Serial_print_s("0");*/ digitalWrite(D5, LOW); }

if ((data & 0x10) == 0x10) { /*Serial_print_s("1");*/ digitalWrite(D4, HIGH); }
else { /*Serial_print_s("0");*/ digitalWrite(D4, LOW); }

}

void lcdInitialization(void)
{
  lcd_cmd(0x01); //Clear the screen.
  lcd_cmd(0x28); //16 Colomn & 2 Rows.  
  lcd_cmd(0x0C); //Turn display on and cursor off.
  lcd_cmd(0x06); //Auto increment cursor.
  lcd_cmd(0x01); //Clear screen.
}

void lcd_string(uint8_t str[], uint8_t data_len)
{
  uint8_t i;
  for (i = 0; i < data_len; i++)
  {
    lcdData(str[i]);
  }
  
}

void intToString(int value, char* buffer, uint8_t bufferSize) {
    uint8_t index = 0;
    uint8_t isNegative = 0;

    // Handle negative numbers
    if (value < 0) {
        isNegative = 1;
        value = -value;
    }

    // Convert digits to characters in reverse order
    do {
        buffer[index++] = (char)(value % 10 + '0');
        value /= 10;
    } while (value > 0 && index < bufferSize - 1);

    // Add '-' for negative numbers
    if (isNegative && index < bufferSize - 1) {
        buffer[index++] = '-';
    }

    // Null-terminate the string
    buffer[index] = '\0';

    // Reverse the string in-place
    for (uint8_t i = 0, j = index - 1; i < j; i++, j--) {
        char temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }
}

void intToStringWithPrefix(int value, const char* prefix, char* buffer, uint8_t bufferSize) {
    uint8_t index = 0;
    uint8_t prefixLength = strlen(prefix);
    uint8_t isNegative = 0;

    // Handle negative numbers
    if (value < 0) {
        isNegative = 1;
        value = -value;
    }

    // Add the specified prefix to the buffer
    for (uint8_t i = 0; i < prefixLength && index < bufferSize - 1; i++) {
        buffer[index++] = prefix[i];
    }

    // Convert digits to characters in reverse order
    do {
        buffer[index++] = (char)(value % 10 + '0');
        value /= 10;
    } while (value > 0 && index < bufferSize - 1);

    // Add '-' for negative numbers
    if (isNegative && index < bufferSize - 1) {
        buffer[index++] = '-';
    }

    // Null-terminate the string
    buffer[index] = '\0';

    // Reverse the string in-place
    for (uint8_t i = prefixLength, j = index - 1; i < j; i++, j--) {
        char temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }
}

