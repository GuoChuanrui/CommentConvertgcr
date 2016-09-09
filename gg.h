#include<stdio.h>
#define UL unsigned long

//定义状态
typedef enum
{
	NO_COMMENT_STATE,
	C_COMMENT_STATE,
	CPP_COMMENT_STATE,
	END_STATE
}STATE_ENUM;

//定义状态机
typedef struct STATE_MACHINE
{
	FILE *inputfile;
	FILE *outputfile;
	STATE_ENUM ulstate;
}STATE_MACHINE;

