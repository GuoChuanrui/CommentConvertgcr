#include"gg.h"

void EventPro2(char ch);
void EventProAtNo2(char ch);
void EventProAtC2(char ch);
void EventProAtCpp2(char ch);

//��ʼ��״̬��
STATE_MACHINE  g_state = {0};

int CommentConvert_CPP(FILE *inputfile, FILE *outputfile)
{
	if(inputfile==NULL || outputfile==NULL)
	{
		printf("Error: Argument Invalid!\n");
		return -1;
	}

	
	g_state.inputfile = inputfile;
	g_state.outputfile = outputfile;
	g_state.ulstate = NO_COMMENT_STATE;

	
	char ch;
	while(g_state.ulstate != END_STATE)
	{
		ch = fgetc(g_state.inputfile);
		EventPro2(ch);
	}
	return 0;
}

//�¼�����
void EventPro2(char ch)
{
	switch(g_state.ulstate)
	{
	case NO_COMMENT_STATE:
		EventProAtNo2(ch);
		break;
	case C_COMMENT_STATE:
		EventProAtC2(ch);
		break;
	case CPP_COMMENT_STATE:
		EventProAtCpp2(ch);
		break;
	case END_STATE:
		break;
	default:
		break;
	}
}


//��ע��״̬����
void EventProAtNo2(char ch)
{
	char nextch;
	switch(ch)
	{
	case EOF:
		g_state.ulstate=END_STATE;
		break;
	case '/':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/')   //C++
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
			g_state.ulstate = CPP_COMMENT_STATE;
		}
		else if(nextch == '*')   // C����
		{
			fputc(ch,g_state.outputfile);
			fputc('/',g_state.outputfile);
			g_state.ulstate=C_COMMENT_STATE;
		}

		else
		{
			fputc(ch,g_state.outputfile);  
			fputc(nextch,g_state.outputfile);
		}
		break;
	case '*':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/')   //C����
		{
			fputc('/',g_state.outputfile);
			fputc('/',g_state.outputfile);
			g_state.ulstate = C_COMMENT_STATE;
		}
		else
		{
			fputc(ch,g_state.outputfile);  
			fputc(nextch,g_state.outputfile);
		}
		break;

	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}

//C����ע��״̬����
void EventProAtC2(char ch)
{
	char nextch;
	switch(ch)
	{
	case EOF:
		g_state.ulstate = END_STATE;
		break;
	case '*':
		nextch=fgetc(g_state.inputfile);
		if(nextch=='/')     //C���� 
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);			
			fputc('\n',g_state.outputfile);
			g_state.ulstate = NO_COMMENT_STATE;

		}
		else
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
		}
		break;
	case '/':                             
		nextch=fgetc(g_state.inputfile);
		if(nextch=='/')     //C����Ƕ��C++
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);
		}
		else if(nextch=='*')     //C����Ƕ��C����
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);
		}
		else 
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
		}
		break;
	case '\n':
		fputc('\n',g_state.outputfile);
		fputc('/',g_state.outputfile);
		fputc('/',g_state.outputfile);
		break;

	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}

//C++ע��״̬����
void EventProAtCpp2(char ch)
{
	char nextch;
	switch(ch)
	{
	case EOF:
		g_state.ulstate = END_STATE;
		break;
	case '/':
		nextch=fgetc(g_state.inputfile);
		if(nextch=='*')   //C++Ƕ��C����
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);
		}
		else
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
		}
		break;
	case '*':
		nextch=fgetc(g_state.inputfile);
		if(nextch=='/')     //C++Ƕ��C����
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);
		}
		else
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
		}
		break;

	case '\n':          //�����е�ĩβ��
		fputc('\n',g_state.outputfile);
		g_state.ulstate = NO_COMMENT_STATE;
		break;
	default:
		fputc(ch,g_state.outputfile);
		break;
	}	
}

