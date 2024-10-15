#ifndef __JK_BMS__
#define __JK_BMS__
#include <Arduino.h>

// Constants with descriptive names
#define JK_BMS_READ_INTERVAL            2000 /*How often we read the JK_BMS status (ms)*/
#define FRAME_START                     0x4E /*Frame Start Byte*/
#define FRAME_END                       0x68 /*Frame End Byte*/
#define BATTERY_VOLTAGE_TOKEN           0x83 /*Battery token in the recevived buffer,two bytes*/
#define BATTERY_CURRENT_TOKEN           0x84 /*Battery token in the recevived buffer,two bytes*/
#define BATTERY_CAPACITY_TOKEN          0x85 /*Battery token in the recevived buffer,single byte*/
#define RECEVIED_BUFFER_LENGTH          0x05 /*Buffer length for JK-BMS*/

void requestToJkmBms(void);
void fillBatteryBuffer(uint8_t *buffer);

#endif //__JK_BMS__