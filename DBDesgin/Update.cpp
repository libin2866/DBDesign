#include"stdafx.h"
#include"Update.h"
#include"FileOperation.h"
/*Sample SQL
UPDATE mytable(SET age='21' WHERE username='test')IN myDB;

*/


CString Update(void){
	CString result;
	int i=1;
	char dbName[15];
	char tableName[15];
	char conditionColumn[15];
	char condition[15];
	char destColumn[15];
	char dest[15];
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
	strcpy(dbName,globalDB);//��¼ͨ�����ݿ⣬���û�� IN db�������ΪĬ�����ݿ�
	if(AWord[i].type==insym){//in XXX  xxxΪĿ�����ݿ�
		i++;
		if(AWord[i].type==identifier){
			strcpy(dbName,AWord[i].word);//��������ݿ������������ø�����ѡ��Ҫ���������ݿ⣬���жϸ����ݿ�治����//////////////�ļ�����
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
	//////////////////////�ļ�����////////////
	strcpy(tableName,AWord[1].word);
	strcpy(conditionColumn,AWord[8].word);
	strcpy(condition,AWord[10].word);
	strcpy(destColumn,AWord[4].word);
	strcpy(dest,AWord[6].word);
	//UpdateTable

	if(!UpdateData(dbName,tableName,conditionColumn,condition,destColumn,dest)){
		result="����ʧ��!";
		return result;

	}

	result="���³ɹ�";
	return result;

}