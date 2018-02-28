/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "project.h"
#include <stdlib.h>
#include "usbserialprotocol.h"
#include "SW1.h"
#include "Reset_isr.h"
#include "aes.h"
#include "SuperFastHash.h"

#define CARD_ID_LEN 36
#define PROV_MSG "P"
#define RECV_K "K"
#define GIVE_CARD_ID '1'
#define GIVE_SIG '2'
#define GIVE_PUB '3'

//CARD

/* 
 * How to read from EEPROM (persistent memory):
 * 
 * // read variable:
 * static const uint8 EEPROM_BUF_VAR[len] = { val1, val2, ... };
 * // write variable:
 * volatile const uint8 *ptr = EEPROM_BUF_VAR;
 * 
 * uint8 val1 = *ptr;
 * uint8 buf[4] = { 0x01, 0x02, 0x03, 0x04 };
 * USER_INFO_Write(message, EEPROM_BUF_VAR, 4u); 
 */

// global EEPROM read variables
static const uint8 CARD_ID[CARD_ID_LEN] = {}; //security


// reset interrupt on button press
CY_ISR(Reset_ISR)
{
    pushMessage((uint8*)"In interrupt\n", strlen("In interrupt\n"));
    SW1_ClearInterrupt();
    CySoftwareReset();
}

// provisions card (should only ever be called once)
void provision()
{
    uint8 message[64];
    unsigned int KEY;
    
    // synchronize with bank
    syncConnection(SYNC_PROV);
 
    pushMessage((uint8*)PROV_MSG, (uint8)strlen(PROV_MSG));
    
    // set account number
    pullMessage(message);
    USER_INFO_Write(message, CARD_ID, CARD_ID_LEN);

    // Send back K
    pushMessage((uint8*)RECV_K, strlen(RECV_K));
    
    // Pull 3
    pullMessage(message);
    
    //Generate Public/Private Key.
    

    //Check the message that was received
    if(message[0] == '3')
    {
        pushMessage((uint8*)KEY, 32); // Public Key
    }
    //Memset Public Key    
    memset(&KEY, 0, 64);
}

int main(void)
{
    // enable global interrupts -- DO NOT DELETE
    CyGlobalIntEnable;
    
    // start reset button
    Reset_isr_StartEx(Reset_ISR);
    
    /* Declare vairables here */
    uint8 i;
    uint8 message[128];
    //uint32 * id[2];
    struct AES_ctx ctx;
    unsigned char key[32];
    uint8_t iv = 21;
    
    // local EEPROM read variable
    static const uint8 PROVISIONED[1] = {0x00};
    
    // EEPROM write variable
    volatile const uint8 *ptr;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    USER_INFO_Start();
    USB_UART_Start();
    
    // Provision card if on first boot
    ptr = PROVISIONED;
    if (*ptr == 0x00) {
        provision();
        
        // Mark as provisioned
        i = 0x01;
        USER_INFO_Write(&i,PROVISIONED, 1u);
    }
    
    // Go into infinite loop
    while (1) {
        /* Place your application code here. */
        
        // syncronize communication with bank
        syncConnection(SYNC_NORM);
        
        // receive pin number from ATM
        pullMessage(message);
        // change PIN or broadcast UUID
        if(message[0] == GIVE_CARD_ID)
        {
            pushMessage(CARD_ID, CARD_ID_LEN);
        }
        if(message[1] == GIVE_SIG)
        {
            pullMessage(message);
            key[0]  =  (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT0) ;
            key[1] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT1  ) ;
            key[2] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT2  ) ;
            key[3] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_WAFER ) ;

            key[4]  =  (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_X   ) ;
            key[5] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_Y     ) ;
            key[6] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_SORT  ) ;
            key[7] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_MINOR ) ;
            //Take UniqueId and grab the eight bytes and store them somehow and then hash stuff to expand it
            temphash = hash(key[0], 1);
            temphash = hash(temphash + key[1], 4);
            
            //Do AES
            AES_init_ctx(&ctx, key);
            AES_ctx_set_iv(&ctx, &iv);
            AES_CBC_encrypt_buffer(&ctx, message, strlen((char*) message));
        }
    }
}

/* [] END OF FILE */
