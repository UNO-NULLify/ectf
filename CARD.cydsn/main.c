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
#include "SuperSecretHash.h"
#include <stdio.h>

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
    uint8 message[36];
    unsigned char AESkey[32];
    //Hashing shit
    char buf[8]="";
    char temp[4]="";
    unsigned char keyValues[8];
    volatile const uint8* CARD_IDPtr = CARD_ID;
    
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
    keyValues[0]  =  (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT0) ;
    keyValues[1] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT1  ) ;
    keyValues[2] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT2  ) ;
    keyValues[3] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_WAFER ) ;

    keyValues[4]  =  (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_X   ) ;
    keyValues[5] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_Y     ) ;
    keyValues[6] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_SORT  ) ;
    keyValues[7] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_MINOR ) ;
    //Take UniqueId and grab the eight bytes and store them somehow and then hash stuff to expand it
    buf[0] = CARD_IDPtr[0];
    buf[1] = CARD_IDPtr[1];
    buf[2] = CARD_IDPtr[2];
    buf[3] = CARD_IDPtr[3];
    for(int x=0; x < 8; x=x+1)
    {
        for(int y=0; y < 7; y=y+1)
        {
            for(int z=0; z < 7; z=z+1)
            {
                for(int w=0; w < 7; w=w+1)
                {
                    memcpy(&temp[0], &keyValues[x],1);
                    memcpy(&temp[1], &keyValues[y],1);
                    memcpy(&temp[2], &keyValues[z],1);
                    memcpy(&temp[3], &keyValues[w],1);
                    SALT_HASaltH_SALT(buf, temp, 4, 8);
                }            
            }
        }
        memcpy(&AESkey[x*4], buf, 4);
    }
    //Get rid of our previous data
    memset(keyValues, 0, 8);
    memset(buf, 0, 8);
    memset(temp, 0, 4);    

    //Check the message that was received
    if(message[0] == '3')
    {
        pushMessage(AESkey, 32); // Public Key
    }
    memset(AESkey, 0, 32);
}

int main(void)
{
    // enable global interrupts -- DO NOT DELETE
    CyGlobalIntEnable;
    
    // start reset button
    Reset_isr_StartEx(Reset_ISR);
    
    /* Declare vairables here */
    uint8 i;
    uint8 message[32];
    //AES shit
    struct AES_ctx ctx;
    unsigned char AESkey[32]="";
    //Hashing shit
    char buf[8]="";
    char temp[4]="";
    unsigned char keyValues[8]="";
    volatile const uint8* CARD_IDPtr = CARD_ID;
    
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
        
        // Receive OpCode
        pullMessage(message);
        // Send back a muther fuckign K
        pushMessage((uint8*)RECV_K, strlen(RECV_K));
        // change PIN or broadcast UUID
        if(message[0] == GIVE_CARD_ID)
        {
            pushMessage(CARD_ID, CARD_ID_LEN);
        }
        // Get the bloody 2
        if(message[0] == GIVE_SIG)
        {
            // Pull dat phat chall
            pullMessage(message);
            keyValues[0]  =  (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT0) ;
            keyValues[1] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT1  ) ;
            keyValues[2] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT2  ) ;
            keyValues[3] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_WAFER ) ;

            keyValues[4]  =  (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_X   ) ;
            keyValues[5] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_Y     ) ;
            keyValues[6] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_SORT  ) ;
            keyValues[7] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_MINOR ) ;
            //Take UniqueId and grab the eight bytes and store them somehow and then hash stuff to expand it
            buf[0] = CARD_IDPtr[0];
            buf[1] = CARD_IDPtr[1];
            buf[2] = CARD_IDPtr[2];
            buf[3] = CARD_IDPtr[3];
            for(int x=0; x < 8; x=x+1)
            {
                for(int y=0; y < 7; y=y+1)
                {
                    for(int z=0; z < 7; z=z+1)
                    {
                        for(int w=0; w < 7; w=w+1)
                        {
                            memcpy(&temp[0], &keyValues[x],1);
                            memcpy(&temp[1], &keyValues[y],1);
                            memcpy(&temp[2], &keyValues[z],1);
                            memcpy(&temp[3], &keyValues[w],1);
                            SALT_HASaltH_SALT(buf, temp, 4, 8);
                        }
                    }
                }
                memcpy(&AESkey[x*4], buf, 4);
            }
            //Get rid of our previous data
            memset(keyValues, 0, 8);
            memset(buf, 0, 8);
            memset(temp, 0, 4);
            //Do AES
            AES_init_ctx(&ctx, AESkey);
            AES_ECB_encrypt(&ctx, message);
            AES_ECB_encrypt(&ctx, &message[16]);
            //Get rid of our AESKey
            memset(AESkey, 0, 32);
            memset(&ctx, 0, sizeof(struct AES_ctx));
            //Push AES encrypted chall
            pushMessage(message, 32);
            memset(message, 0, 32);
        }
    }
}

/* [] END OF FILE */
