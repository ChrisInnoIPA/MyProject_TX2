#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/reboot.h>
#include <stdbool.h>
#include <getopt.h>

#include "ini.h"

#define CONF_FILE_PATH "iCover.ini"
#define iCover_PATH "SD"

enum
{
    MODE_BACKUP = 0,
    MODE_RECOVERY,
};

typedef struct
{
    int mode;
    char source[64];
    char target[64];
} ICOVER_INFO;

/*-----------------------------------------------------------------------------------------------------------*/
static const struct option long_opt[] =
    {
        {"mode", 1, NULL, 'm'}, /* 0:backup, 1:revocery */
                                //{"source", 1, NULL, 's'},
                                //{"target", 1, NULL, 't'},
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
int USB_PATH()
{
    FILE *fp;

    char *buf, tmp[64];
    int len;

    /*------------------------------------------------------------*/
    fp = fopen("/boot/extlinux/extlinux.conf", "r");

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
        if (strstr(tmp, "DEFAULT eMMc"))
            sprintf(tmp, "DEFAULT %s\n", iCover_PATH);

        strcat(buf, tmp);
    }

    fclose(fp);

    /*------------------------------------------------------------*/
    fp = fopen("/boot/extlinux/extlinux.conf", "w");

    if (fp == NULL)
    {
        printf("open %s fail !! \n", "extlinux.conf");
        return 0;
    }

    fwrite(buf, 1, len, fp);
    fclose(fp);

    system("init 6");

    // free(buf);
    // float i = 100;
    // for (; (int)i >= 0; i -= 0.01)
    // {
    //     printf("time remind %.2f\n", i);
    //     printf("be quick!!!!!");

    //     system("cls");
    // }
    return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/
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
        if (strstr(tmp, "DEFAULT SD"))
            sprintf(tmp, "DEFAULT eMMc\n");

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

/*-----------------------------------------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
    ICOVER_INFO info;
    int opt;
    int ret;

    memset(&info, 0, sizeof(ICOVER_INFO));
    info.mode = -1;

    if (argc < 2)
    {
        show_usage(argv[0]);
        return 0;
    }

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

    if (info.mode == MODE_BACKUP)
    {
        ret = PutIniKeyString("Mode", "mode", "1", "./iCover.ini");
        printf("Mode : Backup \n");
    }
    else if (info.mode == MODE_RECOVERY)
    {
        ret = PutIniKeyString("Mode", "mode", "2", "./iCover.ini");
        printf("Mode : Recovery \n");
    }
    else
    {
        printf("Unknow mode \n");
    }

    if (strlen(info.source) > 0)
    {
        ret = PutIniKeyString("Source", "source", "/dev/mmcblb0p1", "./iCover.ini");
        printf("Source : %s \n", info.source);
    }
    else
    {
        //printf("Source : unknow \n");
    }

    if (strlen(info.target) > 0)
    {
        ret = PutIniKeyString("Target", "target", "OS.img", "./iCover.ini");
        printf("target : %s \n", info.target);
    }
    else
    {
        //printf("target : unknow \n");
    }

    USB_PATH();

    return 0;
}
