#ifndef _LIBSAMPLE_
#define _LIBSAMPLE_

enum ERROR_CODE{
	OK,
	INVALID_ARG,
	FAILED,
};

/****************************************
 *
 * APIs of Library
 *
 ****************************************/
typedef void (*CALLBACK_LOG_FUNC)(char *szMsg);

#ifdef __cplusplus

extern "C"{
	//void 		LIB_Init(void);
	//int 		LIB_SetLogFunc(CALLBACK_LOG_FUNC func);
	//int 		LIB_SetMessage(char* szMsg);
	//int 		LIB_GetMessage(char* szMsg);
	//void 		LIB_Uninit(void);
	bool 		down(const char *url);
}
#else
extern	void            LIB_Init(void);
extern	int             LIB_SetLogFunc(CALLBACK_LOG_FUNC func);
extern	int             LIB_SetMessage(char* szMsg);
extern	int             LIB_GetMessage(char* szMsg);
extern	void            LIB_Uninit(void);
#endif
#endif
