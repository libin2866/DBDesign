
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
	 if(AWord[0].type==createsym&&AWord[1].type==dbsym)
		 return CREATE_DB;
	 if(AWord[0].type==usesym)
		 return USE_DB;
	  if(AWord[0].type==descsym)
		 return DESC_TABLE;
	return -1;
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
	int a=0;
	strcpy(&(word[a++][0]),"AND");
	strcpy(&(word[a++][0]),"CREATE");
	strcpy(&(word[a++][0]),"DATABASE");
	strcpy(&(word[a++][0]),"DELETE");
	strcpy(&(word[a++][0]),"DESC");
	strcpy(&(word[a++][0]),"DROP");
	strcpy(&(word[a++][0]),"EDIT");
	strcpy(&(word[a++][0]),"FROM");
	strcpy(&(word[a++][0]),"IN");
	strcpy(&(word[a++][0]),"INSERT");
	strcpy(&(word[a++][0]),"INTO");
	strcpy(&(word[a++][0]),"INVALID");
	strcpy(&(word[a++][0]),"KEY");
	strcpy(&(word[a++][0]),"NOT_KEY");
	strcpy(&(word[a++][0]),"NOT_NULL");
	strcpy(&(word[a++][0]),"NULL");
	strcpy(&(word[a++][0]),"RENAME");
	strcpy(&(word[a++][0]),"SELECT");
	strcpy(&(word[a++][0]),"SET");
	strcpy(&(word[a++][0]),"TABLE");	
	strcpy(&(word[a++][0]),"UPDATE");
	strcpy(&(word[a++][0]),"USE");
	strcpy(&(word[a++][0]),"VALID");
	strcpy(&(word[a++][0]),"VALUES");
	strcpy(&(word[a++][0]),"WHERE");
	strcpy(&(word[a++][0]),"datetime");
	strcpy(&(word[a++][0]),"int");
	strcpy(&(word[a++][0]),"varchar");
	/*****************************设置保留字符号*************************************/
	a=0;
	wordsym[a++]=andsym;
	wordsym[a++]=createsym;
	wordsym[a++]=dbsym;
	wordsym[a++]=deletesym;
	wordsym[a++]=descsym;
	wordsym[a++]=dropsym;
	wordsym[a++]=editsym;
	wordsym[a++]=fromsym;
	wordsym[a++]=insym;
	wordsym[a++]=insertsym;
	wordsym[a++]=intosym;
	wordsym[a++]=invalidsym;
	wordsym[a++]=keysym;
	wordsym[a++]=notkeysym;
	wordsym[a++]=notnul;
	wordsym[a++]=nul;
	wordsym[a++]=renamesym;
	wordsym[a++]=selectsym;
	wordsym[a++]=setsym;
	wordsym[a++]=tablesym;
	wordsym[a++]=updatesym;
	wordsym[a++]=usesym;
	wordsym[a++]=validsym;
	wordsym[a++]=valuessym;
	wordsym[a++]=wheresym;
	wordsym[a++]=datetimesym;
	wordsym[a++]=intsym;
	wordsym[a++]=varcharsym;



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
					int countx=0;
					while(ch!='\''&&countx<charlength)//结尾
					{
						//char* temp=&ch;
						//memset(temp,'\0',charlength);
						//temp=&ch;
						sh[countx]=ch;
						//strcat(sh,&ch);//存入
						getchdo;
						countx++;
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