#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/libTestOfBoard.h"
//#include "lib/libTestOfBoard.h"

/*-----------------------------------------*/
#include <cstring>
#include <fstream>	// std::ifstream, std::ofstream
#include <iostream>
#include <string>
#include <unistd.h>
#include "include/Crypto.hpp"

using namespace std;

#define BUFFER_SIZE 64
/*-----------------------------------------*/

#define MAX_PATH 	38
#define ANTMSG	"Aetina Corporation"

#define EEPROM_I2C_ID   7
#define EEPROM_I2C_ADDRESS  0x57
//#define EEPROM_CONTENT	"Aetina Corporation"

// char pszContent[MAX_PATH] = {0};

/*-----------------------------------------*/
void printBytesAsHex(unsigned char *bytes, size_t length, const char *message)
{
	printf("%s: ", message);

	for (unsigned int i = 0; i < length; i++) {
#ifdef WIN32
		__mingw_printf("%02hhx", bytes[i]);
#else
		printf("%02hhx", bytes[i]);
#endif
	}

	puts("");
}
/*-----------------------------------------*/

int EEPromRead(){
    
    Crypto crypto;
    	/* AES */
	secure_string ptext = ANTMSG;
	secure_string ctext, rtext;
	crypto.aes_encrypt(ptext, ctext);
	unsigned char test[ctext.length()];
   	copy(ctext.begin(), ctext.end(), test);

    printf("------> %s %d \n", __FUNCTION__, __LINE__); fflush(stdout);
    
	printBytesAsHex(test, sizeof(test), "TEST");

    char id[256];

    sprintf(id, "%s", test);
    

    crypto.aes_decrypt(ctext, rtext);

	cout << "ptext:" << ptext << endl;

	cout << "rtext:" << rtext << endl;

    EEPROM_CFG eeprom_cfg = {0};
    EEPROM_Result eeprom_result = {0};
    
    eeprom_cfg.nI2C_ID = EEPROM_I2C_ID;
    eeprom_cfg.nAddress = EEPROM_I2C_ADDRESS;
    
    char pszContent[MAX_PATH] = {0};
    memset(pszContent, 0xff, MAX_PATH);
    pszContent[MAX_PATH - 1] = 0;
    eeprom_cfg.pszContent = pszContent;
    printf("%ld\n", strlen(eeprom_cfg.pszContent));
    TOB_ReadEEPROM(&eeprom_cfg, &eeprom_result);

    //printf("%s\n", eeprom_cfg.pszContent);

    char Compier [MAX_PATH];   
    memset(Compier, 0, MAX_PATH);
    int ret;

    //strcpy(pszContent, eeprom_cfg.pszContent);
    //sprintf(Compier, "%s", "Aetina CorporationxxX");
    strcpy(Compier, ANTMSG);
    //strcpy(pszContent, Compier);

    // printf("%d\n", eeprom_cfg.pszContent);
    // printf("%d\n", a);

    printf("%s(%ld)\n", eeprom_cfg.pszContent, strlen(eeprom_cfg.pszContent));       
    printf("%s(%ld)\n", Compier, strlen(Compier));
    ret = strcmp(eeprom_cfg.pszContent, Compier);

    if(ret > 0){
        printf("\nEEPfail\n");
    }
    else if(ret < 0){
        printf("\nEEPfail2\n");
    }
    else if(ret != 0){
        printf("\nEEPfail3\n");
    }
    else{
        printf("\nEEPPass\n");
    }

    // printf("%d\n", eeprom_result.nResult);
    // printf("%d\n", a);

    return 0;
}

int EEPromWrite(){
	Crypto crypto;
    	/* AES */
	secure_string ptext = ANTMSG;
	secure_string ctext, rtext;
	crypto.aes_encrypt(ptext, ctext);
	unsigned char test[ctext.length()];
   	copy(ctext.begin(), ctext.end(), test);

    printf("------> %s %d \n", __FUNCTION__, __LINE__); fflush(stdout);
    
	printBytesAsHex(test, sizeof(test), "TEST");

    char id[256];

    sprintf(id, "%s", test);
    

    crypto.aes_decrypt(ctext, rtext);

	cout << "ptext:" << ptext << endl;

	cout << "rtext:" << rtext << endl;

    if(ptext == rtext)
    {
        printf("OK\n");
    }
    else
    {
        printf("fail\n");
    }

 /*-----------------------------------------*/   

    EEPROM_CFG eeprom_cfg = {0};
    EEPROM_Result eeprom_result = {0};

    eeprom_cfg.nI2C_ID = EEPROM_I2C_ID;
    eeprom_cfg.nAddress = EEPROM_I2C_ADDRESS;

    char pszContent[MAX_PATH] = {0};
    memset(pszContent, 0xff, MAX_PATH);
    eeprom_cfg.pszContent = (char*)test;

    int a = TOB_WriteEEPROM(&eeprom_cfg, &eeprom_result);

    printf("%s\n", eeprom_cfg.pszContent);
    //printf("%d\n", eeprom_result.nResult);
    //printf("%d\n", a);

    return 0;
}

int EEpromdecry()
{
    Crypto crypto;
	/* AES */
	secure_string ptext = ANTMSG;
	secure_string ctext, rtext;
	crypto.aes_encrypt(ptext, ctext);
	unsigned char password[ctext.length()];
   	copy(ctext.begin(), ctext.end(), password);
	printBytesAsHex(password, sizeof(password), "Password");
    crypto.aes_decrypt(ctext, rtext);
	cout << "ptext:" << ptext << endl;
	cout << "rtext:" << rtext << endl;

    if(rtext != ANTMSG)
    {
        printf("fail\n");
    }
    else
    {
        printf("pass\n");
    }

	return 0;
}

int main(void){
    
    EEPromRead();

    //EEPromWrite();

    //EEpromdecry();


    
    //return 0;
}
