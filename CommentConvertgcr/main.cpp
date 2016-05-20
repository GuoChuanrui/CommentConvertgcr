#include<stdio.h>
/****************************************
 * Function name:  main
 * Argument     :  void
 * Destribute   :  
 * Return value :
 * when   why   what    who
 * 
 ****************************************/

extern int CommentConvert_C(FILE *, FILE *);
extern int CommentConvert_CPP(FILE *, FILE *);
int main()
{
	char ch1[50],ch2[50];
	int n;
	printf("\t***************ע��ת��***************\n");
	printf("\t*   [1] C++ --> C      [2] C --> C++ *\n");
	printf("\t*   [0] Quit                         *\n");
	printf("\t**************************************\n");
	printf("��ѡ��> ");
	scanf("%d",&n);
	

	printf("������ԭ�ļ�����");
	scanf("%s",&ch1);
	printf("\n");
	printf("������Ŀ���ļ�����");
	scanf("%s",&ch2);
	printf("\n");

	FILE *fpIn;
	FILE *fpOut;
	fpIn = fopen(ch1,"r");
	if(NULL == fpIn)
	{
		printf("Error: Open input.c file fail!\n");
		return -1;
	}
	fpOut = fopen(ch2,"w");
	if(NULL == fpOut)
	{
		printf("Error: Open output.c file fail!\n");
		return -1;
	}
	
	switch(n)
	{
	case 1:
		CommentConvert_C(fpIn,fpOut);             // C++ --> C
		break;
	case 2:  
		CommentConvert_CPP(fpIn,fpOut);			  // C --> C++
		break;
	}
	fclose(fpIn);
	fclose(fpOut);
	return 0;
}
