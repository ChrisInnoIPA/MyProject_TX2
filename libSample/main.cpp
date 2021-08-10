#include <stdio.h>
#include <stdbool.h>
#include "include/libSample.h"

#define MAX_PATH 	1024
#define TESTING_MSG	"Aetina Corporation"

void LOG(char *szMsg){
	char szLogMsg[1024] = {0};
	sprintf(szLogMsg, "%s\n", szMsg);
	printf(szLogMsg);
}

int main(void){
	char szPath[MAX_PATH] = {0};
	char szChar = 0;
	bool bIsStop = false;
	bool bMenuIsShow = false;

	//LIB_SetLogFunc(LOG);
	//LIB_Init();

	char szContent[10] = {0};
	FILE * pFile;
    pFile = fopen ("./log.txt","w");
    if (pFile!=NULL)
    {
		//fwrite("hello", 1, strlen("hello"), pFile);
        //fclose (pFile);
    }

	while (!bIsStop){
		if(!bMenuIsShow){
			LOG("[A] SetMessage.");
			LOG("[B] GetMessage.");
			LOG("[Q] Quit.");
			bMenuIsShow = true;
		}

		switch(getchar()){
			case 'A':
				{
					// LOG("----------------------------------------------------------------");
					// LOG("SetMessage...");
					// if(LIB_SetMessage(TESTING_MSG) != OK){
					// 	LOG("Failed.");
					// }
					// char szMsg[MAX_PATH] = {0};
					// sprintf(szMsg, "Send message(%s) to library.", TESTING_MSG);
					// LOG(szMsg);
					// LOG("SetMessage...done");
					// LOG("----------------------------------------------------------------");
					down("http://172.16.92.130/O0917/sm32Xtest_V44-8.exe", "/home/video/123.exe");
					bMenuIsShow = false;
				}
				break;
			case 'B':
				{
					// LOG("----------------------------------------------------------------");
					// LOG("SetMessage...");
					// char szMsg[MAX_PATH] = {0};
					// if(LIB_GetMessage(szMsg) != OK){
					// 	LOG("Failed.");
					// }
					// LOG(szMsg);
					// LOG("SetMessage...done");
					// LOG("----------------------------------------------------------------");
					bMenuIsShow = false;

				}
				break;
			case 'Q':
				bIsStop = true;
				break;
		}		
	}

	//LIB_Uninit();
	LOG("Sample finish.");

	return 0;
}
