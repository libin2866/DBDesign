#include"stdafx.h"
#include "CreateDB.h"

CString CreateDB(void){
	
	CString result;
	char dbName[15];
	if(AWord[2].type!=identifier){
		result="'CREATE DATABASE' �������﷨����©�����ݿ�����";//ȱ�����ݿ�����
		return result;
	}
	if(AWord[3].type!=semicolon){
		result="SQL������﷨����©�˷ֺţ�";//ȱ�ٷֺ�
		return result;
	}
	/////////////////

	strcpy(dbName,AWord[2].word);//���ݿ�����
	InitDataBase(dbName);//��ʼ�����ݿ�

	result="�����ɹ���";
	return result;

}