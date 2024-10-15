#include <Arduino.h>
#include "jk_bms.h"

uint8_t batteryMonitorRequestStatusFrame[21] = 
{   
    0x4E,0x57,0x00,0x13,0x00,0x00,0x00,0x00,0x06,
    0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x68,0x00,
    0x00,0x01,0x29 //JK-BMS request status frame.
};

void requestToJkmBms(void)
{
    Serial_flush();
    Serial_print_sn(batteryMonitorRequestStatusFrame,sizeof(batteryMonitorRequestStatusFrame));
}

void fillBatteryBuffer(uint8_t *buffer)
{
    uint8_t batteryBufferIndex;
    uint8_t ch_byte;
    while (Serial_available() > 0)
    {
        ch_byte = Serial_read();
        if (ch_byte == FRAME_START)
        {
            batteryBufferIndex = 0;
            while (Serial_available() > 0)
            {
                ch_byte = Serial_read();
                if(ch_byte == BATTERY_VOLTAGE_TOKEN)
                {
                    ch_byte = Serial_read();
                    buffer[0] = ch_byte;
                    ch_byte = Serial_read();
                    buffer[1] = ch_byte;
                }
                     
                if(ch_byte == BATTERY_CURRENT_TOKEN)
                {
                    ch_byte = Serial_read();
                    buffer[2] = ch_byte;
                    ch_byte = Serial_read();
                    buffer[3] = ch_byte;
                }
                   
                if(ch_byte == BATTERY_CAPACITY_TOKEN)
                {
                    ch_byte = Serial_read();
                    buffer[4] = ch_byte;
                }
            }
        }
    }
}


//                 lcd_cmd(0x80);
//                 intToString(Counter++,buff,16);
//                 intToStringWithPrefix(Counter++,"Counter:",buff,16);
//                 lcd_string(buff,strlen(buff));
//                 lcd_cmd(0xC0);
//                 lcd_string("Be the Best !!!$",16);


//  ch_byte = Serial_read();
//         if ()
//         intToStringWithPrefix(Counter++,"Counter:",buff,sizeof(buff));
//         lcd_cmd(0x80);
//         lcd_string(buff,strlen(buff));
//         if (ch_byte == 0x84)
//         {

//             while (1);

            
//         }
//     }
//     while(1);


//  ch_byte = Serial_read();
//                 intToString(ch_byte,buff,sizeof(buff));
//                 lcd_cmd(0x80);
//                 lcd_string(buff,strlen(buff));
                
//                 ch_byte = Serial_read();
//                 intToString(ch_byte,buff,sizeof(buff));
//                 lcd_cmd(0xC0);
//                 lcd_string(buff,strlen(buff));