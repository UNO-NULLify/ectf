#include "SuperFastHash.h"
#include "project.h"
#include <stdlib.h>
#include "usbserialprotocol.h"
#include "SW1.h"
#include "Reset_isr.h"

//Takes 8 bytes in and produces 4 bytes through hashing
void SALT_HASaltH_SALT(char* data, char* extra_data, int extra_data_len, int len){
    uint32 output;
    char empty[4] = "";
    strncat(&data[4], extra_data,  extra_data_len);
    output = hash(data, len);
    memcpy(data, &output, 4);
    memcpy(&data[4], empty, 4);
    memcpy(extra_data, empty,4);
}
/* [] END OF FILE */
