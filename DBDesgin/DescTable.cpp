// DescTable.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DescTable.h"
#include"FileOperation.h"
#include"TableModeDlg.h"
/*  Sample SQL

DESC mytable;
DESC mytable IN myDB;

*/



// DescTable
CString DescTable(void){
	CString result;
	char dbName[15];
	char tableName[15];
	if(AWord[1].type!=identifier){
		result="'USE' �������﷨����©�����ݿ�����";//ȱ�����ݿ�����
		return result;
	}

	strcpy(dbName,globalDB);//��¼ͨ�����ݿ⣬���û�� IN db�������ΪĬ�����ݿ�
	int i=2;
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


	///////////�ļ�����//////////////////
	strcpy(tableName,AWord[1].word);//
	if(!IsTableExists(dbName,tableName))
	{
		result="�Բ��𣬸����ݿⲻ����";//�Ҳ������ݿ�
		return result;
	};



	vector<char*> tableModes;//��ű��ֶ�

	tableModes.push_back("MyTable0        INT      1 0 1");
	tableModes.push_back("MyTable2        DATETIME 0 1 1");
	/*tableModes.push_back("MySubTable1");
	tableModes.push_back("MySubTable2");
	tableModes.push_back("MySubTable3");
	tableModes.push_back("MySubTable4");*/
	
	TableModeDlg *tableModeDlg=new TableModeDlg;

		tableModeDlg->mytables=tableModes;
	//tr1dlg->tables=returntables.size();
	strcpy(tableModeDlg->title,tableName);

	tableModeDlg->Create(IDD_TABLETREEDIALOG);
	tableModeDlg->ShowWindow(SW_SHOW);


	return result;
}
