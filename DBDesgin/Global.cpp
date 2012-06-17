
#include "stdafx.h"
#include"Global.h"
#include <CString>
using namespace std;

int cc,ll;//getch使用的计数器，cc表示当前字符(ch)的位置getch
char ch;//当前字符的缓冲区 getch
char line[81];//读取行缓冲区
char temp[charlength+1];//临时符号，多出来的一个字符用于存放0
char id[charlength+1];//当前的ident,多出来的一个字符用于存放0
static int cnum=-1;//计数用
char sh[charlength];//存储当前的字符串
enum symbol sym;//当前的符号
int num;//当前数字
int iter;//收集字母
char word[reservednum][charlength];//保留字
AnalysisWord AWord[255];//分析出来的内容

enum symbol sinsym[256];//ssym,单字符的符号值
enum symbol wordsym[reservednum];//wsym,保留字对应的符号值
char sql[100];
int length;

SQLTYPE AnalyseSql(char csql[]){
	strcpy(sql,csql);
	length=strlen(csql);
	init();
	cc=ll=0;
	cnum=-1;
	iter=0;
	ch=' ';
	int count=100;
	int mark=0;
	while(count&&!mark) {
		count--;
		mark=getsym();
	}
	if(mark==2){
		return 0;
	}

	 if(AWord[0].type==createsym&&AWord[1].type==tablesym)
		 return CREATE_TABLE;
	 if(AWord[0].type==editsym&&AWord[1].type==tablesym)
		 return EDIT_TABLE;
	 if(AWord[0].type==renamesym&&AWord[1].type==tablesym)
		 return RENAME_TABLE;
	 if(AWord[0].type==dropsym&&AWord[1].type==tablesym)
		 return DROP_TABLE;
	 if(AWord[0].type==insertsym&&AWord[1].type==intosym)
		 return INSERT_INTO;
	 if(AWord[0].type==deletesym&&AWord[1].type==fromsym)
		 return DELETE_FROM;
	 if(AWord[0].type==updatesym)
		 return UPDATE;

	return 0;
}

void init(void){

	int i;//singlecharacter,
	/*******************设置单字符号**************************/
	for(i=0;i<256;i++){
		sinsym[i]=nul;
		strcpy(AWord[i].word,"");
		AWord[i].type=empty;
	}
	sinsym['+']=plus;
	sinsym['-']=minus;
	sinsym['*']=times;
	sinsym['/']=slash;
	sinsym['(']=lparen;
	sinsym[')']=rparen;
	sinsym['=']=eql;
	sinsym[',']=comma;
	sinsym['.']=period;
	sinsym[';']=semicolon;
	sinsym['\'']=quote;//单引号

/*****************设置保留字名字，按照字母顺序，便于折半查找*************/
	strcpy(&(word[0][0]),"CREATE");
	strcpy(&(word[1][0]),"DATABASE");
	strcpy(&(word[2][0]),"DELETE");
	strcpy(&(word[3][0]),"DROP");
	strcpy(&(word[4][0]),"EDIT");
	strcpy(&(word[5][0]),"FROM");
	strcpy(&(word[6][0]),"IN");
	strcpy(&(word[7][0]),"INSERT");
	strcpy(&(word[8][0]),"INTO");
	strcpy(&(word[9][0]),"INVALID");
	strcpy(&(word[10][0]),"KEY");
	strcpy(&(word[11][0]),"NOT_KEY");
	strcpy(&(word[12][0]),"NOT_NULL");
	strcpy(&(word[13][0]),"NULL");
	strcpy(&(word[14][0]),"RENAME");
	strcpy(&(word[15][0]),"SELECT");
	strcpy(&(word[16][0]),"SET");
	strcpy(&(word[17][0]),"TABLE");	
	strcpy(&(word[18][0]),"UPDATE");
	strcpy(&(word[19][0]),"USE");
	strcpy(&(word[20][0]),"VALID");
	strcpy(&(word[21][0]),"VALUES");
	strcpy(&(word[22][0]),"WHERE");
	strcpy(&(word[23][0]),"datetime");
	strcpy(&(word[24][0]),"int");
	strcpy(&(word[25][0]),"varchar");
	/*****************************设置保留字符号*************************************/
	wordsym[0]=createsym;
	wordsym[1]=dbsym;
	wordsym[2]=deletesym;
	wordsym[3]=dropsym;
	wordsym[4]=editsym;
	wordsym[5]=fromsym;
	wordsym[6]=insym;
	wordsym[7]=insertsym;
	wordsym[8]=intosym;
	wordsym[9]=invalidsym;
	wordsym[10]=keysym;
	wordsym[11]=notkeysym;
	wordsym[12]=notnul;
	wordsym[13]=nul;
	wordsym[14]=renamesym;
	wordsym[15]=selectsym;
	wordsym[16]=setsym;
	wordsym[17]=tablesym;
	wordsym[18]=updatesym;
	wordsym[19]=usesym;
	wordsym[20]=validsym;
	wordsym[21]=valuessym;
	wordsym[22]=wheresym;
	wordsym[23]=datetimesym;
	wordsym[24]=intsym;
	wordsym[25]=varcharsym;



}

int getch(void){//漏掉空格，读取一个字符;每次读一行，存入line缓冲区，line被getsym取空后再读一行继续
	if(cc==ll)
	{
		if(cc>=length)
		{
			printf("Program incomplete");
			return -1;
		}
		ll=0;
		cc=0;

		ch=sql[iter];
		while(ch!=10)//回车
		{
			if((ch=sql[iter++])==0)
			//if(EOF==fscanf(charInString,"%c",&ch))
			{
				line[ll]=0;
				break;
			}
			line[ll]=ch;
			ll++;
		}
		if(line[ll]!=0){
			line[ll]=0;
		}
	
	}
		ch=line[cc];
		cc++;
		return 0;
};

int getsym(void){//词法分析，获取一个符号
		int i,j,k,m=0;
		int frac=0;
		//char str[10];
		while(ch==' '||ch==9||ch==10)//忽略空格，换行和TAB
		{
			
			getchdo;
		}
		if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')//名字或保留字以a-z开头或者大写的字母
		{
			k=0;
			do{
				if(k<charlength)
				{
					temp[k]=ch;
					k++;
				}
				getchdo;
			}while(ch>='a'&&ch<='z'||ch>='0'&&ch<='9'||ch>='A'&&ch<='Z'||ch=='_');
			temp[k]=0;//多出的那个字符可以存放0
			strcpy(id,temp);
			i=0;
			m=0;
			j=reservednum-1;
			do{			//二分法搜索当前符号是否为保留字
				k=(i+j)/2;
				if(strcmp(id,word[k])<=0)j=k-1;
				if(strcmp(id,word[k])>=0)i=k+1;
				if(strcmp(id,word[k])==0){m=1;cnum++;
			
				strcpy(AWord[cnum].word,id);
				AWord[cnum].type=wordsym[k];//served
				//AWord[cnum].line=wordLine;//将识别出来的字符存储起来
				break; 
				};
			}while(i<=j);
			//if(k==5){
			//	//getchdo;
			//	if(ch=='.')
			//	{cnum++;//printf("%3d     .             PERIOD\n",cnum);
			//	strcat(AWord[cnum].word,&ch);
			//	AWord[cnum].type=period;//period
			//	}
			//	return 1;
			//}///////////////////////////////////////////toend!!!!


			if(!m) {cnum++;
			strcpy(AWord[cnum].word,id);
			AWord[cnum].type=identifier;;//identifier
			}

		}
		else{
			if(ch>='0'&&ch<='9'||ch=='.')//检测是否为数字，以0..9开头
			{
				//k=0;
				num=0;
				m=0;
				int mi=1;
				int i=0;
				sym=number;
				memset(sh,'\0',charlength);//先清空sh中原来的内容，防止出错****************************
				do{
					num=10*num+ch-'0';
					strcat(&sh[i],&ch);
					//k++;
					getchdo;
					i++;
				}while(ch>='0'&&ch<='9');//获取数字的值
				memset(&sh[i],'\0',charlength-i);
				i=0;
				if(ch=='.'){
					m=1;//标记整数与浮点数
					strcat(sh,&ch);
					getchdo;
					do{
					frac=10*frac+ch-'0';i++;
					strcat(sh,&ch);
					//k++;
					getchdo;
				}while(ch>='0'&&ch<='9');//获取数字的值
				}
				while(m&&i>0){ mi=mi*10;i--;};//小数的位数
				if(m) {cnum++;
				//printf("%3d     %d.%d           NUMBER           %d.%d\n",cnum,num,frac,num,frac);
	            strcpy(AWord[cnum].word,sh);
				AWord[cnum].type=sym;//number
				//AWord[cnum].num=num+(float)frac/mi;//存储已经识别的数字
				//AWord[cnum].line=wordLine;//将识别出来的字符存储起来
				}
			
				else  {cnum++;//printf("%3d     %-9d     NUMBER           %d\n",cnum,num,num);
				strcpy(AWord[cnum].word,sh);
				AWord[cnum].type=sym;//number
				AWord[cnum].num=num;//存储已经识别的数字
				
				}
				//k--;
				//if(k>nmax) error(30);//报错

				}
			else
			{
				if(ch=='\'')//检测单引号
				{
					getchdo;
					memset(sh,'\0',charlength);//先清空sh中原来的内容，防止出错****************************
					int countx=charlength+1;
					while(ch!='\''&&countx)//结尾
					{
						strcat(sh,&ch);//存入
						getchdo;
						countx--;
					}
					getchdo;
					if(countx<=0) return 2;//出现错误少了第二个'号
					cnum++;//sym=eql;
					strcpy(AWord[cnum].word,sh);	
					AWord[cnum].type=quote;
			
				}
				else
				{
					if(ch=='<')//检测小于或小于等于符号
					{
						getchdo;
						if(ch=='=')
						{
						cnum++;
						
						strcpy(AWord[cnum].word,"<=");
						AWord[cnum].type=leql;//less||equal
						//AWord[cnum].line=wordLine;//将识别出来的字符存储起来
						getchdo;
						}
						else {sym=lss;
						cnum++;
						//printf("%3d     <             LESS\n",cnum);
						strcpy(AWord[cnum].word,"<");
						AWord[cnum].type=lss;//less
						//AWord[cnum].line=wordLine;//将识别出来的字符存储起来
						}
					}
					else
					{
						if(ch=='>')//检测大于或大于等于符号
						{
							getchdo;
							if(ch=='=')
							{								
								cnum++;
								
								strcpy(AWord[cnum].word,">=");
								AWord[cnum].type=geql;//greater||equal
								//AWord[cnum].line=wordLine;//将识别出来的字符存储起来
								getchdo;
							}
							else {
								sym=gtr;
								cnum++;
							strcpy(AWord[cnum].word,">");
							AWord[cnum].type=gtr;//greater
							//AWord[cnum].line=wordLine;//将识别出来的字符存储起来
							}
						}
						else if(ch=='='){
							getchdo;
							if(ch=='=')
								{sym=eql;
							  cnum++;
								
								strcpy(AWord[cnum].word,"==");
								AWord[cnum].type=eql;//equal
								//AWord[cnum].line=wordLine;//将识别出来的字符存储起来
								getchdo;
							}else
								{	sym=eql;
									cnum++;
									
									strcpy(AWord[cnum].word,"=");
									AWord[cnum].type=eql;//becomes
								//	AWord[cnum].line=wordLine;//将识别出来的字符存储起来

								}
							}

							else
							{
								sym=sinsym[ch];//当符号不满足上述条件时，全部按照单字符符号处理
								m=0;
								switch(ch){
								case '(':
									cnum++;m=1;
									strcpy(AWord[cnum].word,"(");
									AWord[cnum].type=lparen;//equal
																
									break;
								case ')':
									cnum++;m=1;
									strcpy(AWord[cnum].word,")");
									AWord[cnum].type=rparen;//equal
								
									break;
								case '+':
									cnum++;m=1;
									strcpy(AWord[cnum].word,"+");
									AWord[cnum].type=plus;//equal
									
									break;
								case '-':
									cnum++;m=1;
									strcpy(AWord[cnum].word,"-");
									AWord[cnum].type=minus;
									
									break;
								case '*':
									cnum++;;m=1;
									strcpy(AWord[cnum].word,"*");
									AWord[cnum].type=times;
									
									break;
								case '/':
									cnum++;m=1;
									strcpy(AWord[cnum].word,"/");
									AWord[cnum].type=slash;
									
									break;
								case ';':
									cnum++;m=1;
									strcpy(AWord[cnum].word,";");
									AWord[cnum].type=semicolon;
									return 1;//遇到分号，结束分析
									
								case ',':
									cnum++;m=1;
									strcpy(AWord[cnum].word,",");
									AWord[cnum].type=comma;
									
									break;
							}
								if(!m) {//cnum++; //return 2;
								}//其他字符
							getchdo;
								/*if(sym!=period)
									getchdo;*/
								/*if(ch=='.'){return 1;}*/
							}
					}
				}
			}
		}
	return 0;
};