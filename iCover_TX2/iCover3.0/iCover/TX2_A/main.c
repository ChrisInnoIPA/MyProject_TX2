#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/reboot.h>
#include <stdbool.h>
#include <getopt.h>

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
    { "mode",   1, NULL, 'm' },   /* 0:backup, 1:revocery */
    { "source", 1, NULL, 's' },   
    { "target", 1, NULL, 't' },   
};

/*-----------------------------------------------------------------------------------------------------------*/
static void show_usage(char *name)
{
    printf("Syntax: %s [-option ...] \n",              name);
    printf("Sample: %s -m 0 -s /dev/sdb -t os.img \n", name);    
    printf("Sample: %s -m 1 -s os.img -t /dev/sdb \n", name);    
    printf("Option:\n");
    printf("  -m : 0:backup 1:recovery \n");
    printf("  -s : sourec \n");
    printf("  -t : target \n");
}

/*-----------------------------------------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
    ICOVER_INFO info;
    int         opt;

    memset(&info, 0, sizeof(ICOVER_INFO));
    info.mode = -1;

    if(argc < 7)
    {
        show_usage(argv[0]);
        return 0;      
    }  
    
    while((opt = getopt_long(argc, argv, "?hm:s:t:", long_opt, NULL)) != -1)
    {
        switch(opt)
        {
            case 'm':      
                        info.mode = atoi(optarg);     
                        
                        if(info.mode < MODE_BACKUP || info.mode > MODE_RECOVERY)
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

    if(info.mode == MODE_BACKUP)
        printf("Mode : Backup \n");
    else if(info.mode == MODE_RECOVERY)
        printf("Mode : Recovery \n");
    else
        printf("Unknow mode \n");

    if(strlen(info.source) > 0)
        printf("Source : %s \n", info.source);
    else
        printf("Source : unknow \n");

    if(strlen(info.target) > 0)
        printf("target : %s \n", info.target);
    else
        printf("target : unknow \n");

    return 0;
}
