#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include "include/libSample.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <string.h>

#define MAX_CMD 	256
#define MAX_MSG		1024

// typedef struct tagLIB{
// 	        CALLBACK_LOG_FUNC 	log_func;
// 		char*			pszMsg;
// }LIB_OBJ;

// static LIB_OBJ g_LIBObj = {0};

// void LIB_Init(void){

// 	g_LIBObj.pszMsg = malloc(sizeof(char) * MAX_MSG);
// 	memset(g_LIBObj.pszMsg, 0, sizeof(char) * MAX_MSG);

// 	if(g_LIBObj.pszMsg == NULL)
// 		return FAILED;

// 	return OK;
// }

// int LIB_SetLogFunc(CALLBACK_LOG_FUNC func){
// 	if(func != NULL)
// 		g_LIBObj.log_func = func;
// }

// int LIB_SetMessage(char* szMsg){

// 	if(szMsg == NULL || g_LIBObj.pszMsg == NULL)
// 		return FAILED;

// 	if(strlen(szMsg) > MAX_MSG)
// 		return INVALID_ARG;

// 	memset(g_LIBObj.pszMsg, 0, sizeof(char) * MAX_MSG);
// 	sprintf(g_LIBObj.pszMsg, "%s", szMsg);

// 	return OK;
// }

// int LIB_GetMessage(char* szMsg){

// 	if(szMsg == NULL || g_LIBObj.pszMsg == NULL)
// 		return FAILED;

// 	sprintf(szMsg, "Get message(%s) from library.", g_LIBObj.pszMsg);

// 	return OK;
// }

// void LIB_Uninit(void){
// 	if(g_LIBObj.pszMsg){
// 		free(g_LIBObj.pszMsg);
// 		g_LIBObj.pszMsg = 0;
// 	}
// 	return OK;
// }

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

bool down(const char *url)
{
    CURL 	 *curl;
    FILE 	 *fp;
    CURLcode res;
    //char 	 *url = "http://172.16.92.151/hfs/1080p.mov";
    // char 	 outfilename[] = "video.mov";
    char outfilename[FILENAME_MAX] = "/home/Videos/video.exe";

	printf("url = %s \n", url);
    
    curl = curl_easy_init();

    if (curl) 
    {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);		

        /* always cleanup */
        curl_easy_cleanup(curl);
        fclose(fp);

		if(res == CURLE_OK)
			return true;
		else
		{
			switch(res)
			{
				case 7:
						printf("Failed to connect() to host or proxy. \n");
						break;
				default:
						break;
			}
		}
    }

	return false;
}


