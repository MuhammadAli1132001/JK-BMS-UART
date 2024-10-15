#include <Arduino.h>
#include <LiquidCrystal.h>
#include "jk_bms.h"
//#include "menu.h"

void printCapacity();
void printCurrent(uint8_t byte1, uint8_t byte2);
void printVoltage(uint8_t byte1, uint8_t byte2);
void printPower();

extern LiquidCrystal (lcd,PD3,PD1,PC7,PC6,PC5,PC4);
extern byte menuLevel;
extern char buttonPressed;
static uint8_t receivedBuffer[RECEVIED_BUFFER_LENGTH];
static unsigned long previousMillis = 0;
float current = 0.0;
float voltage = 0.0;
float power = 0.0;
float powerkilo = 0.0;

uint8_t Remainingcapacity = 0;

void setup()  {

  Serial_begin(115200);
  //configure_menu_button();
  lcd_begin(16,2);
  //create_char();
  lcd_clear();
  pinMode(PB5,OUTPUT);
} 

void loop()  {

  
  lcd_print_s("salam");

 unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000)
  {
    requestToJkmBms();
    fillBatteryBuffer(receivedBuffer);
    lcd_clear();

    // lcd_print_ub(receivedBuffer[0],HEX);
    // lcd_print_ub(receivedBuffer[1],HEX);
    // lcd_print_ub(receivedBuffer[2],HEX);
    // lcd_print_ub(receivedBuffer[3],HEX);
    // lcd_print_ub(receivedBuffer[4],HEX);

    Remainingcapacity = receivedBuffer[4];
    printCapacity();
    printVoltage( receivedBuffer[0],receivedBuffer[1]);
    printCurrent(receivedBuffer[2],receivedBuffer[3]);
    printPower(); 
    
    previousMillis = currentMillis;
    digitalWrite(PB5,HIGH);
    delay(50);
    digitalWrite(PB5,LOW);
    delay(50);   
  }
}

void printCapacity()
{
    lcd_setCursor(0,0);
    lcd_print_u(Remainingcapacity);
    lcd_print_s("%  ");

}
void printVoltage(uint8_t byte1, uint8_t byte2)
{
    lcd_setCursor(0,1);
    voltage = byte1 << 8 | byte2;
    lcd_print_f(voltage * 0.01);
    lcd_print_c('V');
}
void printCurrent(uint8_t byte1, uint8_t byte2){
  
  lcd_setCursor(9,0);
  current = byte1 << 8 | byte2;
  lcd_print_f(current * 0.01);
  lcd_print_c('A');
}

void printPower(){

  power = voltage * current * 0.01 * 0.01;
  lcd_setCursor(9,1);

    if(power >= 1000)
    {
      powerkilo = power / 1000;
      lcd_print_fd(powerkilo, 1);
      lcd_print_s("kW");

    }
    else
    {
      lcd_print_fd(power,1);
      lcd_print_c('W');

    }
}

