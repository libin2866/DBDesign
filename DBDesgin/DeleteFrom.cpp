#include"stdafx.h"
#include"DeleteFrom.h"
#include"FileOperation.h"
/*
DELETE FROM mytable WHERE username='test' IN myDB;

*/


CString DeleteFrom(void){
	CString result;
	char tableName[15];
	char dbName[15];
	char conditionColumn[15];
	char condition[15];
	int i=7;
	///////////////����﷨///////////////////
	if(AWord[2].type!=identifier){
		result="'DELETE FROM' �������﷨����©�˱�����";//ȱ�ٱ���
		return result;
	}
	if(AWord[3].type!=wheresym){
		result="SQL������﷨����©��WHERE��";//ȱ��where
		return result;
	}
	if(AWord[4].type!=identifier){
		result="SQL������﷨����©��Field��";//ȱ��field
		return result;
	}
	if(AWord[5].type!=eql){
		result="SQL������﷨���󣡲���'='��";//����=��
		return result;
	}
	if(AWord[6].type!=quote){
		result="SQL������﷨����©��content��";//ȱ��content
		return result;
	}
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
/////////////�ļ�����//////////////////////////////////////////
	strcpy(tableName,AWord[2].word);
	strcpy(conditionColumn,AWord[4].word);
	strcpy(condition,AWord[6].word);


	if(!DeleteData(dbName,tableName,conditionColumn,condition)){
		result="ɾ��ʧ��!";
		return result;

	}

	result="ɾ���ɹ���";
	return result;
}