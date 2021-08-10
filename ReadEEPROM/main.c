#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <string.h>
//#include "include/libSample.h"
#include "libTestOfBoard.h"

#define MAX_PATH 	1024
#define TESTING_MSG	"Hello, world!"

// #define EEPROM_I2C_ID //7
// #define EEPROM_I2C_ADDRESS //0x57

int main(void){

    //TOB_WriteEEPROM(eeprom_cfg, eeprom_result);

    //printf("------> %s %d \n", __FUNCTION__, __LINE__); fflush(stdout);

    EEPROM_CFG eeprom_cfg[MAX_PATH] = {0};
    EEPROM_Result eeprom_result[MAX_PATH] = {0};

    TOB_ReadEEPROM(eeprom_cfg, eeprom_result);

    // printf("EEPROM_CFG", eeprom_cfg);
    // printf("EEPROM_Result", eeprom_result);

    //printf("------> %s %d \n", __FUNCTION__, __LINE__); fflush(stdout);

    return 0;
}