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

// SECURITY MODULE

#define MAX_BILLS 128
#define BILL_LEN 16
#define UUID_LEN 36
#define PROV_MSG "P"
#define WITH_OK "K"
#define WITH_BAD "BAD"
#define RECV_OK "K"
#define EMPTY "EMPTY"
#define EMPTY_BILL "*****EMPTY*****"

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
static const uint8 MONEY[MAX_BILLS][BILL_LEN] = {EMPTY_BILL};
static const uint8 BILLS_LEFT[1] = {0x00};


// reset interrupt on button press
CY_ISR(Reset_ISR)
{
    pushMessage((uint8*)"In interrupt\n", strlen("In interrupt\n"));
    SW1_ClearInterrupt();
    CySoftwareReset();
}


// provisions HSM (should only ever be called once)
void provision()
{
    int i;
    uint8 message[64], numbills;
    //AES shit
    struct AES_ctx ctx;
    unsigned char AESkey[32];
    //Hashing shit
    char *buf = malloc(8*sizeof(char));
    char *temp = malloc(4*sizeof(char));
    unsigned char keyValues[32];
    
    for(i = 0; i < 128; i++) {
        PIGGY_BANK_Write((uint8*)EMPTY_BILL, MONEY[i], BILL_LEN);
    }
    
    // synchronize with atm
    syncConnection(SYNC_PROV);
 
    memset(message, 0u, 64);
    strcpy((char*)message, PROV_MSG);
    pushMessage(message, (uint8)strlen(PROV_MSG));
    
    // Get numbills
    pullMessage(message);
    numbills = message[0];
    PIGGY_BANK_Write(&numbills, BILLS_LEFT, 1u);
    
    keyValues[0]  =  (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT0) ;
    keyValues[1] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT1  ) ;
    keyValues[2] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT2  ) ;
    keyValues[3] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_WAFER ) ;

    keyValues[4]  =  (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_X   ) ;
    keyValues[5] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_Y     ) ;
    keyValues[6] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_SORT  ) ;
    keyValues[7] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_MINOR ) ;
    //Take UniqueId and grab the eight bytes and store them somehow and then hash stuff to expand it
    memcpy(buf, "prof", 4);
    for(int x=0; x < 8; x=x+1)
    {
        for(int y=0; y < 8; y=y+1)
        {
            for(int z=0; z < 8; z=z+1)
            {
                for(int w=0; w < 8; w=w+1)
                {
                    memcpy(&temp[0], &keyValues[x],1);
                    memcpy(&temp[2], &keyValues[y],1);
                    memcpy(&temp[3], &keyValues[z],1);
                    memcpy(&temp[4], &keyValues[w],1);
                    SALT_HASaltH_SALT(buf, temp, 4, 32);
                }
                
            }
        }
        if(x % 4 == 0)
        {
            memcpy(&AESkey[x*4], buf, 4);
        }
    }
    pushMessage(AESkey, 32);

    // Load bills
    for (i = 0; i < numbills; i++) {
        pullMessage(message);
        AES_init_ctx(&ctx, AESkey);
        AES_ECB_encrypt(&ctx, message);
        PIGGY_BANK_Write(message, MONEY[i], BILL_LEN);
        pushMessage((uint8*)RECV_OK, strlen(RECV_OK));
    }
}

void decrypt(uint8 data)
{
    //AES shit
    struct AES_ctx ctx;
    unsigned char AESkey[32];
    //Hashing shit
    char *buf = malloc(8*sizeof(char));
    char *temp = malloc(4*sizeof(char));
    unsigned char keyValues[32];
    
    keyValues[0]  =  (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT0) ;
    keyValues[1] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT1  ) ;
    keyValues[2] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT2  ) ;
    keyValues[3] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_WAFER ) ;

    keyValues[4]  =  (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_X   ) ;
    keyValues[5] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_Y     ) ;
    keyValues[6] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_SORT  ) ;
    keyValues[7] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_MINOR ) ;
    //Take UniqueId and grab the eight bytes and store them somehow and then hash stuff to expand it
    memcpy(buf, "prof", 4);
    for(int x=0; x < 8; x=x+1)
    {
        for(int y=0; y < 8; y=y+1)
        {
            for(int z=0; z < 8; z=z+1)
            {
                for(int w=0; w < 8; w=w+1)
                {
                    memcpy(&temp[0], &keyValues[x],1);
                    memcpy(&temp[2], &keyValues[y],1);
                    memcpy(&temp[3], &keyValues[z],1);
                    memcpy(&temp[4], &keyValues[w],1);
                    SALT_HASaltH_SALT(buf, temp, 4, 32);
                    memset(temp, 0, 4);
                }
                
            }
        }
        if(x % 4 == 0)
        {
            memcpy(&AESkey[x*4], buf, 4);
        }
    }
    memset(keyValues, 0, 32);
    memset(temp, 0, 4);
    memset(buf, 0 , 8);
    AES_init_ctx(&ctx, AESkey);
    AES_ECB_decrypt(&ctx, &data);
    memset(AESkey, 0, 32);
    memset(&ctx, 0, sizeof(struct AES_ctx));
}

void dispenseBill()
{
    static uint8 stackloc = 0;
    uint8 message[16];
    volatile const uint8* ptr; 
    
    ptr = MONEY[stackloc];
    
    memset(message, 0u, 16);
    memcpy(message, (void*)ptr, BILL_LEN);
    decrypt(*message);
    pushMessage(message, BILL_LEN);
    
    PIGGY_BANK_Write((uint8*)EMPTY_BILL, MONEY[stackloc], 16);
    stackloc = (stackloc + 1) % 128;
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // start reset button
    Reset_isr_StartEx(Reset_ISR);
    
    /* Declare vairables here */
    
    uint8 i, bills_left;
    uint8 message[64];
    char * token;
    char * temptoken;
    uint8 bills_dispensed;
    
    bills_dispensed = 128;
    
    /*
     * Note:
     *  To write to EEPROM, write to static const uint8 []
     *  To read from EEPROM, read from volatile const uint8 * 
     *      set to write variable
     *
     * PSoC EEPROM is very finnicky if this format is not followed
     */
    static const uint8 PROVISIONED[1] = {0x00}; // write variable
    volatile const uint8* ptr = PROVISIONED;    // read variable
    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    PIGGY_BANK_Start();
    DB_UART_Start();
    
    // provision security module on first boot
    if(*ptr == 0x00)
    {
        provision();
        
        // Mark as provisioned
        i = 0x01;
        PIGGY_BANK_Write(&i, PROVISIONED, 1u);
    }
    
    // Go into infinite loop
    while (1) {
        /* Place your application code here. */

        // synchronize with bank
        syncConnection(SYNC_NORM);
        
        //Get the range
        pullMessage(message);
        
        //Decrypt the message
        decrypt(*message);
        
        //Check to see if message has a starting valid bill
        token = strtok((char *)message, ",");
        if((uint8) *token == bills_dispensed)
        {
            temptoken = strtok((char *)message, ",");
            if((uint8) temptoken + (uint8) token > (uint8) BILLS_LEFT)
            {
                pushMessage((uint8*)WITH_BAD, strlen(WITH_BAD));
            }
            else
            {
                for (uint8 i = (uint8) token; i < (uint8) temptoken; i++)
                {
                    dispenseBill();
                    bills_left = *BILLS_LEFT - ((uint8) temptoken - (uint8) token);
                    PIGGY_BANK_Write(&bills_left, BILLS_LEFT, 0x01);
                }
            }
        }
    }
}

/* [] END OF FILE */
