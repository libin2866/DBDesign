#include"stdafx.h"
#include"FileOperation.h"


bool InitDataBase(char* dbName){//��ʼ�����ݿ�
	CString ext=".dbf";
    CString db=dbName+ext;
	
	CFileStatus status;
	
	if(!CFile::GetStatus(db,status)) // status function
	{//���ļ�
		CFile mFile(db,CFile::modeCreate | CFile::modeWrite);
		//д�������Ϣ?
		//mFile.Write("NULL",strlen("NULL"));
		
		return true;
	}

	return true;
};

bool IsDBExists(char* dbName){
	CString ext=".dbf";
    CString db=dbName+ext;
	
	CFileStatus status;
	if(!CFile::GetStatus(db,status)) // status function
	{//���ļ�
			
		return false;
	}
	return true;

};

bool IsTableExists(char*dbName,char* tableName){

	return true;
}
bool BuildTable(char *dbName,char* tableName,int columns){//������д����������ݿ⣬�Ȳ�д����ֶΣ�
	CString ext=".dbf";
    CString db=dbName+ext;
	
	CFileStatus status;
	
	if(!CFile::GetStatus(db,status)) // status function
	{//���ļ�
		CFile mFile(db, CFile::modeWrite);

	return true;
	}
};


bool BuildModel(char *dbName,char *tableName,TableMode tableMode){
//д����ֶ�


	return true;
};


bool EditModel(char *dbName,char* tableName, char* oldcolumn,TableMode tableMode){//�޸ı�
	return true;
};


bool RenameTableFile(char* dbName,char* prename,char* latname){//������

	return true;
};


bool DeleteTable(char* dbName,char *tableName){//ɾ����

	return true;
};


vector<char*> ShowTables(char* dbName){//�������ݿ�����б� 
	vector<char*> table;

	return table;
};


vector<char*> ShowColumns(char* dbName,char* tableName){//����һ�����ݿ���һ�ű���������� 
	vector<char*> column;
	return column;
}

bool InsertData(char* dbName,char* tableName,vector<char*> newData){

	return true;
}