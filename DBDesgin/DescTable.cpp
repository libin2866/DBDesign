// DescTable.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DescTable.h"


// DescTable
CString DescTable(void){
	CString result;
	char dbName[15];
	char tableName[15];
	if(AWord[1].type!=identifier){
		result="'USE' �������﷨����©�����ݿ�����";//ȱ�����ݿ�����
		return result;
	}
	if(AWord[2].type!=semicolon){
		result="SQL������﷨����©�˷ֺţ�";//ȱ�ٷֺ�
		return result;
	}
	strcpy(dbName,AWord[1].word);//
	if(!IsDBExists(dbName))
	{
		result="�Բ��𣬸����ݿⲻ����";//�Ҳ������ݿ�
		return result;
	};

	return result;
}
