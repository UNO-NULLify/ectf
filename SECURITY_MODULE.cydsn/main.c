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
static const uint8 ATM_UUID[36]={};
static const uint8 FLAG=0;


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
    //General variables
    int i;
    uint8 message[36]="";
    uint8 numbills;
    //AES variables
    struct AES_ctx ctx;
    unsigned char AESkey[32];
    //Hashing variables
    char buf[8]="";
    char temp[4]="";
    unsigned char keyValues[8];
    
    //Initialize the stack of money
    for(i = 0; i < 128; i++) {
        PIGGY_BANK_Write((uint8*)EMPTY_BILL, MONEY[i], BILL_LEN);
    }
    
    // synchronize with atm
    syncConnection(SYNC_PROV);
    strcpy((char*)message, PROV_MSG);
    pushMessage(message, (uint8)strlen(PROV_MSG));
    
    // Pull the atm UUID
    pullMessage(message);
    PIGGY_BANK_Write(message,ATM_UUID, 36);
    pushMessage((uint8*)RECV_OK, strlen(RECV_OK));
    
    // Get numbills
    pullMessage(message);
    pushMessage((uint8*)RECV_OK, strlen(RECV_OK));
    numbills = message[0];
    PIGGY_BANK_Write(&numbills, BILLS_LEFT, 1u);
    // Grab the some what unique values of the PSOC card
    keyValues[0]  =  (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT0) ;
    keyValues[1] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT1  ) ;
    keyValues[2] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT2  ) ;
    keyValues[3] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_WAFER ) ;

    keyValues[4]  =  (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_X   ) ;
    keyValues[5] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_Y     ) ;
    keyValues[6] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_SORT  ) ;
    keyValues[7] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_MINOR ) ;
    //Generate our AES Key
    memcpy(buf, ATM_UUID, 4);
    for(int x=0; x < 8; x=x+1)
    {
        for(int y=0; y < 8; y=y+1)
        {
            for(int z=0; z < 8; z=z+1)
            {
                for(int w=0; w < 8; w=w+1)
                {
                    //Copy over the specific key values
                    memcpy(&temp[0], &keyValues[x],1);
                    memcpy(&temp[1], &keyValues[y],1);
                    memcpy(&temp[2], &keyValues[z],1);
                    memcpy(&temp[3], &keyValues[w],1);
                    //Call this awesome function to do magic
                    SALT_HASaltH_SALT(buf, temp, 4, 8);
                }
                
            }
        }
        memcpy(&AESkey[x*4], buf, 4);
    }
    //Send our AES Key to the bank
    pushMessage(AESkey, 32);
    AES_init_ctx(&ctx, AESkey);
    // Load bills
    for (i = 0; i < numbills; i++) {
        pullMessage(message);    
        AES_ECB_encrypt(&ctx, message);
        PIGGY_BANK_Write(message, MONEY[i], BILL_LEN);
        pushMessage((uint8*)RECV_OK, strlen(RECV_OK));
    }
}

void decrypt(uint8 *data)
{
    //AES variables
    static struct AES_ctx ctx;
    static int flag=0;
    unsigned char AESkey[32];
    //Hashing variables
    char buf[8]="";
    char temp[4]="";
    unsigned char keyValues[8];
    
    if(flag == 0)
    {
        //Grab our key values
        keyValues[0]  =  (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT0) ;
        keyValues[1] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT1  ) ;
        keyValues[2] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_LOT2  ) ;
        keyValues[3] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_WAFER ) ;

        keyValues[4]  =  (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_X   ) ;
        keyValues[5] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_Y     ) ;
        keyValues[6] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_SORT  ) ;
        keyValues[7] = (unsigned char)(* (reg8 *) CYREG_SFLASH_DIE_MINOR ) ;
        //Generate our AES Key
        memcpy(buf, ATM_UUID, 4);
        for(int x=0; x < 8; x=x+1)
        {
            for(int y=0; y < 8; y=y+1)
            {
                for(int z=0; z < 8; z=z+1)
                {
                    for(int w=0; w < 8; w=w+1)
                    {
                        memcpy(&temp[0], &keyValues[x],1);
                        memcpy(&temp[1], &keyValues[y],1);
                        memcpy(&temp[2], &keyValues[z],1);
                        memcpy(&temp[3], &keyValues[w],1);
                        SALT_HASaltH_SALT(buf, temp, 4, 8);
                        memset(temp, 0, 4);
                    }
                    
                }
            }
            memcpy(&AESkey[x*4], buf, 4);
        }
        memset(keyValues, 0, 8);
        memset(temp, 0, 4);
        memset(buf, 0 , 8);
        AES_init_ctx(&ctx, AESkey);
        memset(AESkey, 0, 32);
        flag = 1;
    }
    if(FLAG == 0)
    {
        AES_ECB_decrypt(&ctx, data);
    }
    else
    {
        memset(&ctx, 0, sizeof(struct AES_ctx));
        PIGGY_BANK_Write((uint8*)0, (uint8*)&FLAG, 1);
        flag = 0;
    }
}

void dispenseBill()
{
    static const uint8 STACKLOC[1] = {0x00};
    uint8 message[16];
    volatile const uint8* stackptr = STACKLOC;
    volatile const uint8* billptr;
    uint8 stackloc;
    
    stackloc = *stackptr;
    billptr = MONEY[stackloc];
    
    memset(message, 0u, 64);
    memcpy(message, (void*)billptr, BILL_LEN);
    decrypt(message);
    pushMessage(message, BILL_LEN);
    PIGGY_BANK_Write((uint8*)EMPTY_BILL, MONEY[stackloc], 16);
    stackloc = (stackloc + 1) % 128;
    PIGGY_BANK_Write(&stackloc, STACKLOC, 1);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // start reset button
    Reset_isr_StartEx(Reset_ISR);
    
    /* Declare vairables here */
    
    uint8 i, bills_left;
    uint8 message[64] = "";
    char * token;
    char * temptoken;
    uint8 last_bill=0;
    int matching = 0;
    uint8 flag[3];
    
    static const uint8 PROVISIONED[1] = {0x00}; // write variable
    volatile const uint8* ptr;    // read variable
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    PIGGY_BANK_Start();
    DB_UART_Start();
    
    ptr = PROVISIONED;
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
        memset(message, 0, 64);
        // synchronize with bank
        syncConnection(SYNC_NORM);
        
        //Get task
        pullMessage(message);
        pushMessage((uint8*)RECV_OK, strlen(RECV_OK));
        //Push ATM_UUID
        if(message[0] == '1')
        {
            pushMessage(ATM_UUID, 36);
        }
        //Dispense
        if(message[0] == '2')
        {
            memset(message, 0, 64);
            pullMessage(message);
            pushMessage((uint8*)RECV_OK, strlen(RECV_OK));
            //Decrypt the message
            decrypt(message);
            decrypt(&message[16]);
            decrypt(&message[32]);
            decrypt(&message[48]);
            
            if (memcmp(&message[0],&message[16],16) == 0)
	            memcpy(flag, WITH_BAD, 3);

            if (memcmp(&message[0],&message[32],16) == 0)
	            memcpy(flag, WITH_BAD, 3);

            if (memcmp(&message[0],&message[48],16) == 0)
	            memcpy(flag, WITH_BAD, 3);

            if (memcmp(&message[16],&message[32],16) == 0)
	            memcpy(flag, WITH_BAD, 3);

            if (memcmp(&message[16],&message[48],16) == 0)
	            memcpy(flag, WITH_BAD, 3);

            if (memcmp(&message[32],&message[48],16) == 0)
	            memcpy(flag, WITH_BAD, 3);
            
                
            matching += abs(memcmp(&message[0],&message[16],1));
            matching += abs(memcmp(&message[0],&message[32],1));
            matching += abs(memcmp(&message[0],&message[48],1));
            matching += abs(memcmp(&message[1],&message[17],1));
            matching += abs(memcmp(&message[1],&message[33],1));
            matching += abs(memcmp(&message[1],&message[49],1));
            matching += abs(memcmp(&message[2],&message[18],1));
            matching += abs(memcmp(&message[2],&message[34],1));
            matching += abs(memcmp(&message[2],&message[50],1));
            matching += abs(memcmp(&message[3],&message[19],1));
            matching += abs(memcmp(&message[3],&message[35],1));
            matching += abs(memcmp(&message[3],&message[51],1));
            
            if(matching != 0)
                memcpy(flag, WITH_BAD, 3);
            
            if(flag[0] == 'B' && flag[1] == 'A' && flag[2] == 'D')
            {
                pushMessage((uint8*)WITH_BAD, strlen(WITH_BAD));
                memset(flag, 0, 3);
            }
            else
            {
                //Check to see if message has a starting valid bill
                token = strtok((char *)message, ",");
                if(atoi(token) == last_bill)
                {
                    temptoken = strtok(NULL, ",");
                    last_bill = (uint8) atoi(temptoken);
                    if((uint8) atoi(temptoken) -  (uint8) atoi(token) > (uint8) BILLS_LEFT)
                    {
                        pushMessage((uint8*)WITH_BAD, strlen(WITH_BAD));
                    }
                    else
                    {
                        for (uint8 i = (uint8) atoi(token); i < (uint8) atoi(temptoken); i++)
                        {
                            dispenseBill();
                            bills_left = *BILLS_LEFT - 1;
                            PIGGY_BANK_Write(&bills_left, BILLS_LEFT, 0x01);
                        }
                        PIGGY_BANK_Write((uint8*)1, (uint8*)&FLAG, 1);
                    }
                }
                pushMessage((uint8*)RECV_OK, strlen(RECV_OK));
            }
        }
    }
}
/* [] END OF FILE */
