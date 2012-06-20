
#include "stdafx.h"

#include "CreateTable.h"
#include"FileOperation.h"

/*����SQL:
CREATE TABLE mytable(
username varchar KEY NOT_NULL VALID,
age int,
birth datetime);
*/


CString CreateTable(void){
	CString result;
	char tableName[15];
	char dbName[15];
	int i=3;
	//char columnName[15][15];
	int columns=0;
	int mark;//�ж��Ƿ�������������������
	bool keymark;//�ж��Ƿ�����key ����not key ��û�� ��ִ��Ĭ�ϵĲ���
	bool nullmark;//�ж��Ƿ�����null ����not null ��û�� ��ִ��Ĭ�ϵĲ���
	bool validmark;//�ж��Ƿ�������valid ����invalid���
	////////�Ƚ����﷨����///////////////////
	if(AWord[2].type!=identifier){
		result="'CREATE TABLE' �������﷨����©�˱�����";//ȱ�ٱ���
		return result;
	}
	if(AWord[3].type==lparen){

		do{
			mark=false;//����,�������͵ı�ǣ���ֹȱ����������
			i++;//ѡ��һ���ؼ���
			if(AWord[i].type==identifier){//����
				i++;columns++;
			}else {
			result="'(' �������﷨����!ȱ������?";//ȱ�ٱ�ʶ������������
			return result;
			}
			if(AWord[i].type==datetimesym){//datetime��������
				i++;mark=1;//������������,���1
			}
			if(AWord[i].type==varcharsym){//varchar��������
				i++;mark=1;//������������,���1
			}
			if(AWord[i].type==intsym){//int��������
				i++;mark=1;//������������,���1
			}
			if(mark==0){
			result="��������ȱ�ٶ�Ӧ����������!";
			return result;
			}
			if(AWord[i].type==keysym) i++;			
			if(AWord[i].type==notkeysym)i++;
			if(AWord[i].type==nul)	i++;		
			if(AWord[i].type==notnul)	i++;
			if(AWord[i].type==validsym) i++;
			if(AWord[i].type==invalidsym) i++;
		}while(AWord[i].type==comma);//do
		
	if(AWord[i].type!=rparen){
		result="ȱ��')'!";
		return result;
	}
	i++;
	//if(globalDB!=NULL)
	strcpy(dbName,globalDB);//��¼ͨ�����ݿ⣬���û�� IN db�������ΪĬ�����ݿ�

	if(AWord[i].type==insym){//in XXX  xxxΪĿ�����ݿ�
		i++;
		if(AWord[i].type==identifier){
			strcpy(dbName,AWord[i+1].word);//��������ݿ������������ø�����ѡ��Ҫ���������ݿ⣬���жϸ����ݿ�治����//////////////�ļ�����
		}
		else{
		result="ȱ����Ҫ���������ݿ�!";
		return result;
		}
     i++;
	}
	///////////////////////
	if(dbName[0]==NULL) {
		result="����û��ѡ��Ҫ���������ݿ�!";
		return result;

	};////////////////
	if(AWord[i].type!=semicolon){
		result="ȱ��';'!";
		return result;
	}
}else{//lparen��while
		result="ȱ��'('!";
		return result;
	}

	///////�ٽ���д���ļ�����//////

	i=3;//�ص���ʼ
	strcpy(tableName,AWord[2].word);//��������
	BuildTable(dbName,tableName,columns);//д���ļ�
	if(AWord[3].type==lparen){
		do{
			TableMode newcolumn;//�½�һ���ֶ�

			keymark=false;//�ж��Ƿ�����key ����not key ��û�� ��ִ��Ĭ�ϵĲ���not key
			nullmark=false;//�ж��Ƿ�����null ����not null ��û�� ��ִ��Ĭ�ϵĲ���null
			validmark=false;//�ж��Ƿ�����valid ��û�� ��ִ��Ĭ�ϵĲ���valid

			i++;//ѡ��һ���ؼ���

			if(AWord[i].type==identifier){//����
				strcpy(newcolumn.sFiledName,AWord[i].word);
				i++;
			}
			if(AWord[i].type==datetimesym){//datetime��������
				strcpy(newcolumn.sType,AWord[i].word);
				i++;
			}
			if(AWord[i].type==varcharsym){//varchar��������
				strcpy(newcolumn.sType,AWord[i].word);
				i++;
			}
			if(AWord[i].type==intsym){//int��������
				strcpy(newcolumn.sType,AWord[i].word);
				i++;
			}
			if(AWord[i].type==keysym){
				newcolumn.bKey=1;
				i++;keymark=1;
			}
			if(AWord[i].type==notkeysym){
				newcolumn.bKey=0;
				i++;keymark=1;
			}
			if(keymark==0){
				newcolumn.bKey=0;
			}

			if(AWord[i].type==nul){//null���
				newcolumn.bNullFlag=1;
				i++;nullmark=1;
			}
			if(AWord[i].type==notnul){//not null���
				newcolumn.bNullFlag=0;
				i++;nullmark=1;
			}
			if(nullmark==0){
				newcolumn.bNullFlag=1;//Ĭ������Ϊ��
			}
			if(AWord[i].type==validsym){//VALID���
				newcolumn.bValidFlag=1;//��Ч
				i++;validmark=1;
			}
			if(AWord[i].type==invalidsym){//INVALID���
				newcolumn.bValidFlag=0;//��Ч
				i++;validmark=1;
			}
			if(validmark==0){
				newcolumn.bValidFlag=1;//Ĭ������Ч
			}

		 BuildModel(dbName,tableName,newcolumn);//д���ļ�
		}while(AWord[i].type==comma);
	}	
	result="�����ɹ���";
	return result;
}
