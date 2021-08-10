#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/reboot.h>
#include <stdbool.h>

#include "ini.h"

#define iCover_PATH "DEFAULT SD"

int TX2_PATH()
{
    FILE *fp;

    char *buf, tmp[64];
    int len;

    /*------------------------------------------------------------*/
    fp = fopen("/mnt/boot/extlinux/extlinux.conf", "r");

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
        if (strstr(tmp, "DEFAULT SD"))
            sprintf(tmp, "DEFAULT eMMc");

        strcat(buf, tmp);
    }

    fclose(fp);

    /*------------------------------------------------------------*/
    fp = fopen("/mnt/boot/extlinux/extlinux.conf", "w");

    if (fp == NULL)
    {
        printf("open %s fail !! \n", "extlinux.conf");
        return 0;
    }

    fwrite(buf, 1, len, fp);
    fclose(fp);

    free(buf);

    // float i = 100;
    // for (; (int)i >= 0; i -= 0.01)
    // {
    //     printf("time remind %.2f\n", i);
    //     printf("be quick!!!!!");

    //     system("cls");
    // }

    return 0;
}

int main(int argc, char const *argv[])
{
    char MODE[100];
    char SOURCEDISK[100];
    char IMAGE[100];
    char cmd[512];
    int ret;

    ret = GetIniKeyString("Mode", "mode", "./iCover.ini", MODE);
    printf("ret:%d,%s\n", ret, MODE);

    ret = GetIniKeyString("Source", "source", "./iCover.ini", SOURCEDISK);
    printf("ret:%d,%s\n", ret, SOURCEDISK);

    ret = GetIniKeyString("Target", "target", "./iCover.ini", IMAGE);
    printf("ret:%d,%s\n", ret, IMAGE);

    int value = atoi(MODE);

    if (value == 1)
    {
        // printf("Backup Start\n");
        // printf("mount /dev/sda /mnt\n");
        // printf("./partclone.dd -s %s -o /mnt/%s\n", SOURCEDISK, IMAGE);
        // printf("umount /mnt\n");
        sprintf(cmd, "mount /dev/mmcblk0p1 /mnt");
        system(cmd);

        TX2_PATH();
        
        sprintf(cmd, "umount /mnt");
        system(cmd);

        sprintf(cmd, "mount /dev/mmcblk2p2 /mnt");
        system(cmd);

        sprintf(cmd, "rm /mnt/OS.img");
        system(cmd);

        sprintf(cmd, "./partclone.dd -s %s -o /mnt/%s", SOURCEDISK, IMAGE);
        system(cmd);

        sprintf(cmd, "umount /mnt");
        system(cmd);

        sprintf(cmd, "init 6");
        system(cmd);
    }

    else if (value == 2)
    {
        // printf("Recovery Start\n");
        // printf("mount /dev/sda /mnt\n");
        // printf("./partclone.dd -s /mnt/%s -o %s\n", IMAGE, SOURCEDISK);
        // printf("umount /mnt\n");

        sprintf(cmd, "mount /dev/mmcblk2p2 /mnt");
        system(cmd);

        sprintf(cmd, "./partclone.dd -s /mnt/%s -o %s", IMAGE, SOURCEDISK);
        system(cmd);

        sprintf(cmd, "umount /mnt");
        system(cmd);

        sprintf(cmd, "mount /dev/mmcblk0p1 /mnt");
        system(cmd);

        sprintf(cmd, "umount /mnt");
        system(cmd);

        //TX2_PATH();

        sprintf(cmd, "init 6");
        system(cmd);
    }
    else if (value == 0)
    {
        
    }

    return 0;
}