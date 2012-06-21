
#include "stdafx.h"
#include"Global.h"
#include <CString>
using namespace std;

int cc,ll;//getchʹ�õļ�������cc��ʾ��ǰ�ַ�(ch)��λ��getch
char ch;//��ǰ�ַ��Ļ����� getch
char line[81];//��ȡ�л�����
char temp[charlength+1];//��ʱ���ţ��������һ���ַ����ڴ��0
char id[charlength+1];//��ǰ��ident,�������һ���ַ����ڴ��0
static int cnum=-1;//������
char sh[charlength];//�洢��ǰ���ַ���
enum symbol sym;//��ǰ�ķ���
int num;//��ǰ����
int iter;//�ռ���ĸ
char word[reservednum][charlength];//������
AnalysisWord AWord[255];//��������������

enum symbol sinsym[256];//ssym,���ַ��ķ���ֵ
enum symbol wordsym[reservednum];//wsym,�����ֶ�Ӧ�ķ���ֵ
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
	/*******************���õ��ַ���**************************/
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
	sinsym['\'']=quote;//������

/*****************���ñ��������֣�������ĸ˳�򣬱����۰����*************/
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
	/*****************************���ñ����ַ���*************************************/
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

int getch(void){//©���ո񣬶�ȡһ���ַ�;ÿ�ζ�һ�У�����line��������line��getsymȡ�պ��ٶ�һ�м���
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
		while(ch!=10)//�س�
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

int getsym(void){//�ʷ���������ȡһ������
		int i,j,k,m=0;
		int frac=0;
		//char str[10];
		while(ch==' '||ch==9||ch==10)//���Կո񣬻��к�TAB
		{
			
			getchdo;
		}
		if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')//���ֻ�������a-z��ͷ���ߴ�д����ĸ
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
			temp[k]=0;//������Ǹ��ַ����Դ��0
			strcpy(id,temp);
			i=0;
			m=0;
			j=reservednum-1;
			do{			//���ַ�������ǰ�����Ƿ�Ϊ������
				k=(i+j)/2;
				if(strcmp(id,word[k])<=0)j=k-1;
				if(strcmp(id,word[k])>=0)i=k+1;
				if(strcmp(id,word[k])==0){m=1;cnum++;
			
				strcpy(AWord[cnum].word,id);
				AWord[cnum].type=wordsym[k];//served
				//AWord[cnum].line=wordLine;//��ʶ��������ַ��洢����
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
			if(ch>='0'&&ch<='9'||ch=='.')//����Ƿ�Ϊ���֣���0..9��ͷ
			{
				//k=0;
				num=0;
				m=0;
				int mi=1;
				int i=0;
				sym=number;
				memset(sh,'\0',charlength);//�����sh��ԭ�������ݣ���ֹ����****************************
				do{
					num=10*num+ch-'0';
					strcat(&sh[i],&ch);
					//k++;
					getchdo;
					i++;
				}while(ch>='0'&&ch<='9');//��ȡ���ֵ�ֵ
				memset(&sh[i],'\0',charlength-i);
				i=0;
				if(ch=='.'){
					m=1;//��������븡����
					strcat(sh,&ch);
					getchdo;
					do{
					frac=10*frac+ch-'0';i++;
					strcat(sh,&ch);
					//k++;
					getchdo;
				}while(ch>='0'&&ch<='9');//��ȡ���ֵ�ֵ
				}
				while(m&&i>0){ mi=mi*10;i--;};//С����λ��
				if(m) {cnum++;
				//printf("%3d     %d.%d           NUMBER           %d.%d\n",cnum,num,frac,num,frac);
	            strcpy(AWord[cnum].word,sh);
				AWord[cnum].type=sym;//number
				//AWord[cnum].num=num+(float)frac/mi;//�洢�Ѿ�ʶ�������
				//AWord[cnum].line=wordLine;//��ʶ��������ַ��洢����
				}
			
				else  {cnum++;//printf("%3d     %-9d     NUMBER           %d\n",cnum,num,num);
				strcpy(AWord[cnum].word,sh);
				AWord[cnum].type=sym;//number
				AWord[cnum].num=num;//�洢�Ѿ�ʶ�������
				
				}
				//k--;
				//if(k>nmax) error(30);//����

				}
			else
			{
				if(ch=='\'')//��ⵥ����
				{
					getchdo;
					memset(sh,'\0',charlength);//�����sh��ԭ�������ݣ���ֹ����****************************
					int countx=0;
					while(ch!='\''&&countx<charlength)//��β
					{
						//char* temp=&ch;
						//memset(temp,'\0',charlength);
						//temp=&ch;
						sh[countx]=ch;
						//strcat(sh,&ch);//����
						getchdo;
						countx++;
					}
					getchdo;
					if(countx<=0) return 2;//���ִ������˵ڶ���'��
					cnum++;//sym=eql;
					strcpy(AWord[cnum].word,sh);	
					AWord[cnum].type=quote;
			
				}
				else
				{
					if(ch=='<')//���С�ڻ�С�ڵ��ڷ���
					{
						getchdo;
						if(ch=='=')
						{
						cnum++;
						
						strcpy(AWord[cnum].word,"<=");
						AWord[cnum].type=leql;//less||equal
						//AWord[cnum].line=wordLine;//��ʶ��������ַ��洢����
						getchdo;
						}
						else {sym=lss;
						cnum++;
						//printf("%3d     <             LESS\n",cnum);
						strcpy(AWord[cnum].word,"<");
						AWord[cnum].type=lss;//less
						//AWord[cnum].line=wordLine;//��ʶ��������ַ��洢����
						}
					}
					else
					{
						if(ch=='>')//�����ڻ���ڵ��ڷ���
						{
							getchdo;
							if(ch=='=')
							{								
								cnum++;
								
								strcpy(AWord[cnum].word,">=");
								AWord[cnum].type=geql;//greater||equal
								//AWord[cnum].line=wordLine;//��ʶ��������ַ��洢����
								getchdo;
							}
							else {
								sym=gtr;
								cnum++;
							strcpy(AWord[cnum].word,">");
							AWord[cnum].type=gtr;//greater
							//AWord[cnum].line=wordLine;//��ʶ��������ַ��洢����
							}
						}
						else if(ch=='='){
							getchdo;
							if(ch=='=')
								{sym=eql;
							  cnum++;
								
								strcpy(AWord[cnum].word,"==");
								AWord[cnum].type=eql;//equal
								//AWord[cnum].line=wordLine;//��ʶ��������ַ��洢����
								getchdo;
							}else
								{	sym=eql;
									cnum++;
									
									strcpy(AWord[cnum].word,"=");
									AWord[cnum].type=eql;//becomes
								//	AWord[cnum].line=wordLine;//��ʶ��������ַ��洢����

								}
							}

							else
							{
								sym=sinsym[ch];//�����Ų�������������ʱ��ȫ�����յ��ַ����Ŵ���
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
									return 1;//�����ֺţ���������
									
								case ',':
									cnum++;m=1;
									strcpy(AWord[cnum].word,",");
									AWord[cnum].type=comma;
									
									break;
							}
								if(!m) {//cnum++; //return 2;
								}//�����ַ�
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