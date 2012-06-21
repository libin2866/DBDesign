#include"stdafx.h"
#include"FileOperation.h"


bool InitDataBase(char* dbName){//初始化数据库
	CString ext=".dbf";
    CString db=dbName+ext;
	
	CFileStatus status;
	
	if(!CFile::GetStatus(db,status)) // status function
	{//打开文件
		CFile mFile(db,CFile::modeCreate | CFile::modeWrite);
		//写入队列信息?
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
	{//打开文件
			
		return false;
	}
	return true;

};

bool IsTableExists(char*dbName,char* tableName){

	return true;
}
bool BuildTable(char *dbName,char* tableName,int columns){//建立表（写入表名到数据库，先不写入表字段）
	CString ext=".dbf";
    CString db=dbName+ext;
	
	CFileStatus status;
	
	if(!CFile::GetStatus(db,status)) // status function
	{//打开文件
		CFile mFile(db, CFile::modeWrite);

	return true;
	}
};


bool BuildModel(char *dbName,char *tableName,TableMode tableMode){
//写入表字段


	return true;
};


bool EditModel(char *dbName,char* tableName, char* oldcolumn,TableMode tableMode){//修改表
	return true;
};


bool RenameTableFile(char* dbName,char* prename,char* latname){//重命名

	return true;
};


bool DeleteTable(char* dbName,char *tableName){//删除表

	return true;
};


vector<char*> ShowTables(char* dbName){//返回数据库的所有表 
	vector<char*> table;

	return table;
};


vector<char*> ShowColumns(char* dbName,char* tableName){//返回一个数据库中一张表的所有属性 
	vector<char*> column;
	return column;
}

bool InsertData(char* dbName,char* tableName,vector<char*> newData){

	return true;
}