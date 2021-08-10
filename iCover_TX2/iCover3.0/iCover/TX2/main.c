#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/reboot.h>
#include <stdbool.h>

#include "ini.h"

#define CONF_FILE_PATH "iCover.ini"
#define iCover_PATH "Root=/dev/sda1"

int USB_PATH()
{
    FILE *fp;

    char *buf, tmp[64];
    int len;

    /*------------------------------------------------------------*/
    fp = fopen("extlinux.conf", "r");

    if (fp == NULL)
    {
        printf("open %s fail !! \n", "extlinux.conf");
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    len = ftell(fp) + strlen(iCover_PATH);

    buf = malloc(len);
    memset(buf, 0, len);
    fseek(fp, 0, SEEK_SET);

    while (fgets(tmp, sizeof(tmp), fp))
    {
        if (strstr(tmp, "APPEND ${cbootargs} quiet"))
            sprintf(tmp, "      APPEND ${cbootargs} %s quiet\n", iCover_PATH);

        strcat(buf, tmp);
    }

    fclose(fp);

    /*------------------------------------------------------------*/
    fp = fopen("extlinux.conf", "w");

    if (fp == NULL)
    {
        printf("open %s fail !! \n", "extlinux.conf");
        return 0;
    }

    fwrite(buf, 1, len, fp);
    fclose(fp);

    free(buf);
    float i = 100;
    for (; (int)i >= 0; i -= 0.01)
    {
        printf("time remind %.2f\n", i);
        printf("be quick!!!!!");

        system("cls");
    }
    return 0;
}

int TX2_PATH()
{
    FILE *fp;

    char *buf, tmp[64];
    int len;

    /*------------------------------------------------------------*/
    fp = fopen("extlinux.conf", "r");

    if (fp == NULL)
    {
        printf("open %s fail !! \n", "extlinux.conf");
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    len = ftell(fp) - strlen(iCover_PATH) - 1;

    buf = malloc(len);
    memset(buf, 0, len);
    fseek(fp, 0, SEEK_SET);

    while (fgets(tmp, sizeof(tmp), fp))
    {
        if (strstr(tmp, "      APPEND ${cbootargs} ROOT=/dev/sda quiet"))
            sprintf(tmp, "      APPEND ${cbootargs} quiet\n");

        strcat(buf, tmp);
    }

    fclose(fp);

    /*------------------------------------------------------------*/
    fp = fopen("extlinux.conf", "w");

    if (fp == NULL)
    {
        printf("open %s fail !! \n", "extlinux.conf");
        return 0;
    }

    fwrite(buf, 1, len, fp);
    fclose(fp);

    free(buf);

    float i = 100;
    for (; (int)i >= 0; i -= 0.01)
    {
        printf("time remind %.2f\n", i);
        printf("be quick!!!!!");

        system("cls");
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    //char buff[100];
    int ret;

    //USB_PATH();


    if (argv[1] != 0 && strcmp(argv[1], "-b") == 0)
    {
        printf("Backup Start\n");

        ret = PutIniKeyString("Mode", "Backup", "1", "./iCover.ini");
        //system("init 6");
        //printf("put ret:%d\n", ret);
    }
    else if (argv[1] != 0 && strcmp(argv[1], "-r") == 0)
    {
        printf("Recovery Start\n");
        ret = PutIniKeyString("Mode", "Recovery", "1", "./iCover.ini");
        //system("init 6");
    }
    else
    {
        printf("Please enter -b to backup or -r to recovery\n");
    }
    

    return 0;

    // char buff[100];
    // int ret;

    // ret = GetIniKeyString("Automation", "Backup", "./iCover.ini", buff);
    // printf("ret:%d,%s\n", ret, buff);

    // ret = GetIniKeyString("study", "highschool", "./iCover.ini", buff);
    // printf("ret:%d,%s\n", ret, buff);

    // ret = PutIniKeyString("study", "highschool", "zzzz", "./iCover.ini");
    // printf("put ret:%d\n", ret);

    // ret = GetIniKeyString("study", "highschool", "./iCover.ini", buff);
    // printf("ret:%d,%s\n", ret, buff);

    //char iCover;

    //while (1)
    //{
    //system("./iCover.sh");

    // printf("Please enter b to backup or enter r to recovery or enter e to exit: ");
    // iCover = fgetc(stdin);

    // if (iCover == 98)
    // {
    //     printf("Bakcup start...\n");
    //     system("ls -al /iCover/src/partclone.dd");

    //     //AppClose();
    //     break;
    // }
    // else if (iCover == 114)
    // {
    //     printf("Recovery start...\n");

    //     //AppClose();
    //     break;
    // }
    // else if (iCover == 101)
    // {
    //     //AppClose();
    // }
    //}
}