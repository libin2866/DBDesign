#include"stdafx.h"
#include"Update.h"
/*Sample SQL
UPDATE mytable(SET age='21' WHERE username='test')IN myDB;

*/


CString Update(void){
	CString result;
	int i=1;
	char dbName[15];
	if(AWord[i].type!=identifier){
		result="'UPDATE' �������﷨����©�˱�����";//ȱ�ٱ���
		return result;
	}
	i++;
	if(AWord[i].type!=lparen){
		result="SQL������﷨����©��'('��";//ȱ�ٱ���
		return result;

	}else{i++;
		if(AWord[i].type!=setsym){
		result="SQL������﷨����©��SET��";
		return result;
		}i++;
		if(AWord[i].type!=identifier){
		result="SQL������﷨����©��Field��";
		return result;
		}i++;
		if(AWord[i].type!=eql){
		result="SQL������﷨����©��'='��";
		return result;
		}i++;
		if(AWord[i].type!=quote){
		result="SQL������﷨����©��Content��";
		return result;
		}i++;
		if(AWord[i].type!=wheresym){
		result="SQL������﷨����©��WHERE��";
		return result;
		}i++;
		if(AWord[i].type!=identifier){
		result="SQL������﷨����©��Field��";
		return result;
		}i++;
		if(AWord[i].type!=eql){
		result="SQL������﷨����©��'='��";
		return result;
		}i++;
		if(AWord[i].type!=quote){
		result="SQL������﷨����©��Content��";
		return result;
		}i++;
	}
	if(AWord[i].type!=rparen){
		result="SQL������﷨����©��')'��";
		return result;

	}i++;
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
	if(AWord[i].type!=semicolon){
		result="ȱ��';'!";
		return result;
	}



	result="���³ɹ�";
	return result;

}