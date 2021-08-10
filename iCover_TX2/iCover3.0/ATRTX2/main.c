#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/reboot.h>

#define iCover_PATH "DEFAULT SD"

int main(int argc, char const *argv[])
{
    FILE *fp;

    char *buf, tmp[512];
    int len;

    /*------------------------------------------------------------*/
    fp = fopen("/boot/extlinux/extlinux.conf", "r");

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
        if (strstr(tmp, "DEFAULT eMMc"))
            sprintf(tmp, "DEFAULT SD quiet\n");

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