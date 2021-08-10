#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include <fcntl.h>
#include <time.h>
#include <sys/statfs.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/reboot.h>
#include <linux/reboot.h>
#include <linux/fs.h>  
#include "include/ini.h"
#include "include/libTestOfBoard.h"

/*-----------------------------------------------------------------------------------------------------------*/
#define CONF_FILE_PATH  "iCover.ini"
#define ICOVER_PATH     "root=/dev/sda1"
#define EXTLINUX_CONF   "/boot/extlinux/extlinux.conf"

/*-----------------------------------------------------------------------------------------------------------*/
#include <cstring>
#include <fstream>	// std::ifstream, std::ofstream
#include <iostream>
#include <string>
#include <unistd.h>
#include "include/Crypto.hpp"

using namespace std;

#define BUFFER_SIZE 64
/*-----------------------------------------*/
#define MAX_PATH 	39
#define ANTMSG	"Aetina Corporation"

#define EEPROM_I2C_ID   7
#define EEPROM_I2C_ADDRESS  0x57

/*-----------------------------------------------------------------------------------------------------------*/
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
	unsigned char password[ctext.length()];
   	copy(ctext.begin(), ctext.end(), password);
	printBytesAsHex(password, sizeof(password), "Password");
    crypto.aes_decrypt(ctext, rtext);
	cout << "ptext:" << ptext << endl;
	cout << "rtext:" << rtext << endl;
 /*-----------------------------------------*/   

    EEPROM_CFG eeprom_cfg = {0};
    EEPROM_Result eeprom_result = {0};
    
    eeprom_cfg.nI2C_ID = EEPROM_I2C_ID;
    eeprom_cfg.nAddress = EEPROM_I2C_ADDRESS;
    
    char pszContent[MAX_PATH] = {0};
    memset(pszContent, 0xff, MAX_PATH);
    pszContent[MAX_PATH - 1] = 0;
    //eeprom_cfg.pszContent = pszContent;
    eeprom_cfg.pszContent = (char*)password;

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
/*-----------------------------------------------------------------------------------------------------------*/
FILE *f = NULL;

enum
{
    MODE_BACKUP     = 0,
    MODE_RECOVERY,
};

typedef struct
{
    int  mode;
    char source[64];
    char target[64];
} ICOVER_INFO;

/*-----------------------------------------------------------------------------------------------------------*/
static const struct option long_opt[] =
{
    { "mode", 1, NULL, 'm' },  /* 0:backup, 1:revocery */
    { NULL,   0, NULL, '0' },
};

/*-----------------------------------------------------------------------------------------------------------*/
static void show_usage(char *name)
{
    printf("Syntax: %s [-option ...] \n", name);
    printf("Sample: %s -m 0 -s /dev/sdb -t os.img \n", name);
    printf("Sample: %s -m 1 -s os.img -t /dev/sdb \n", name);
    printf("Option:\n");
    printf("  -m : 0:backup 1:recovery \n");
    printf("  -s : sourec \n");
    printf("  -t : target \n");
}
/*-----------------------------------------------------------------------------------------------------------*/
int change_path(void)
{
    //int a = 1;

    char *buf, tmp[64];
    int  len = 1024;
    FILE *fp;

    const char *StartChangePath = "Start change path";
    fprintf(f, "Now mode: %s\n", StartChangePath);

    /*------------------------------------------------------------*/

    const char *ReadExtlinux_conf = "Read extlin_conf";
    fprintf(f, "Now mode: %s\n", ReadExtlinux_conf);

    fp = fopen(EXTLINUX_CONF, "r");

    if (fp == NULL)
    {
        const char *ReadExtlinux_conf_fail = "Read extlin_conf fail";
        fprintf(f, "Now mode: %s\n", ReadExtlinux_conf_fail);

        printf("open %s fail !! \n", EXTLINUX_CONF);
        return 0;
    }

    const char *ReadExtOK = "Read extlin_conf OK";
    fprintf(f, "Now mode: %s\n", ReadExtOK);

    fseek(fp, 0, SEEK_END);
    len = ftell(fp) + strlen(ICOVER_PATH);

    buf = (char*)malloc(len);
    memset(buf, 0, len);
    fseek(fp, 0, SEEK_SET);

    while (fgets(tmp, sizeof(tmp), fp))
    {    
        const char *GetPath = "get path";
        fprintf(f, "Now mode: %s\n", GetPath);

        if (strstr(tmp, "APPEND ${cbootargs} quiet"))
            sprintf(tmp, "APPEND ${cbootargs} %s quiet\n", ICOVER_PATH);

        strcat(buf, tmp);
    }

    //printf("%s (%d)" , buf , strlen(buf));

    const char *GetPathOK = "Get path OK";
    fprintf(f, "Now mode: %s\n", GetPathOK);
    
    fwrite(buf, 1, len, fp);    
    fclose(fp);

    //sleep(1);

    /*------------------------------------------------------------*/

    const char *WriteExtlin_conf = "Write extlin_conf";
    fprintf(f, "Now mode: %s\n", WriteExtlin_conf);

    fp = fopen(EXTLINUX_CONF, "w");

    if (fp == NULL)
    {
        const char *WriteExtlin_conf_fail = "Write extlin_conf fail";
        fprintf(f, "Now mode: %s\n", WriteExtlin_conf_fail);

        printf("open %s fail !! \n", EXTLINUX_CONF);
        return 0;
    }

    const char *WritePath = "Write path";
    fprintf(f, "Now mode: %s\n", WritePath);

    fwrite(buf, 1, len, fp);
    fclose(fp);

    const char *WritePathOK = "Write path OK";
    fprintf(f, "Now mode: %s\n", WritePathOK);

    // free(buf);
    
    const char *reboot_to_iCover3 = "reboot";
    fprintf(f, "Now mode: %s\n", reboot_to_iCover3);

    fclose(f);

    sync();
    
    //sleep(a);

    //printf("123");

    //reboot(RB_AUTOBOOT);

    system("init 6");

    //printf("Entry Yocto");

    return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/
unsigned long long get_disk_length_by_cmd(char *disk)
{
    unsigned long long bytes = 0;

    int fd, ret = 0;

    fd  = open(disk, O_RDONLY | O_NONBLOCK);
    ret = ioctl(fd, BLKGETSIZE64, &bytes);
    close(fd);

    if(ret != 0)
        printf("Fail !! \n");

    return bytes;
}

/*-----------------------------------------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
    EEPromRead();

    f = fopen("iCoverTX2_log.log", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    const char *iCoverTX2Start = "iCoverTX2 Start";
    fprintf(f, "Now mode: %s\n", iCoverTX2Start);

    time_t    t   = time(NULL);
    struct tm *tm = localtime((time_t*) &t);   

    if(tm->tm_year >= 2021)
    {
        printf("Time's up, Please use relsase ver");
        return 0;
    }

    ICOVER_INFO info;
    int opt;
    memset(&info, 0, sizeof(ICOVER_INFO));
    info.mode = -1;

    if (argc < 2)
    {
        show_usage(argv[0]);
        return 0;
    }

    const char *SelMode = "Select Bakcup or Recovery";
    fprintf(f, "Now mode: %s\n", SelMode);

    while ((opt = getopt_long(argc, argv, "?hm:s:t:", long_opt, NULL)) != -1)
    {
        switch (opt)
        {
        case 'm':
            info.mode = atoi(optarg);

            if (info.mode < MODE_BACKUP || info.mode > MODE_RECOVERY)
                info.mode = -1;
            break;
        case 's':
            strcpy(info.source, optarg);
            break;
        case 't':
            strcpy(info.target, optarg);
            break;
        case 'h':
        case '?':
        default:
            show_usage(argv[0]);
            return 0;
        }
    }

    const char *StartSelMode = "Start Select Bakcup or Recovery";
    fprintf(f, "Now mode: %s\n", StartSelMode);

    if (info.mode == MODE_BACKUP)
    {
        const char *BackupMode = "Bakcup mode";
        fprintf(f, "Now mode: %s\n", BackupMode);
        
        PutIniKeyString("Mode", "mode", "1", "./iCover.ini");
        printf("Mode : Backup \n");
    }
    else if (info.mode == MODE_RECOVERY)
    {
        const char *RecoveryMode = "Recovery mode";
        fprintf(f, "Now mode: %s\n", RecoveryMode);

        PutIniKeyString("Mode", "mode", "2", "./iCover.ini");
        printf("Mode : Recovery \n");
    }
    else
    {
        const char *UnknowMode = "Unknow mode";
        fprintf(f, "Now mode: %s\n", UnknowMode);

        printf("Unknow mode \n");
    }

    if (strlen(info.source) > 0)
    {
        const char *writeini_source = "Write ini 0p1";
        fprintf(f, "Now mode: %s\n", writeini_source);

        PutIniKeyString("Source", "source", argv[4] , "./iCover.ini");
        printf("Source : %s \n", info.source);
    }

    if (strlen(info.target) > 0)
    {
        const char *writeini_target = "Write ini OS target";
        fprintf(f, "Now mode: %s\n", writeini_target);

        PutIniKeyString("Target", "target", argv[6], "./iCover.ini");
        printf("target : %s \n", info.target);
    }

    //int mmcblk0p1 = ("Capacity = %.2f GB \n", get_disk_length_by_cmd("/dev/mmcblk0p1") / 1024.0 / 1024.0 / 1024.0);
    //int sda2 = ("Capacity = %.2f GB \n", get_disk_length_by_cmd("/dev/sda2") / 1024.0 / 1024.0 / 1024.0);
    
    const char *SizeCheck = "0p1 & OS target device size check";
    fprintf(f, "Now mode: %s\n", SizeCheck);
    
    char TARGET[100];
    int  ret;
    ret = GetIniKeyString("Target", "target", "./iCover.ini", TARGET);
    printf("ret:%d,%s\n", ret, TARGET);

    long long mmcblk0p1   = get_disk_length_by_cmd("/dev/mmcblk0p1") / 1024.0 / 1024.0 / 1024.0;
    long long storagepath = get_disk_length_by_cmd(TARGET) / 1024.0 / 1024.0 / 1024.0;

    printf(TARGET);

    if(storagepath < mmcblk0p1)
    {    
        const char *Sizesmall = "Target device size to small";
        fprintf(f, "Now mode: %s\n", Sizesmall);
    
        printf("Storage space too small\n");
        return 0;
    }

    const char *RunChangePath = "Run Cahnge Path";
    fprintf(f, "Now mode: %s\n", RunChangePath);

    //fclose(f);

    change_path();

    return 0;
}
