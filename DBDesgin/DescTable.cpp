// DescTable.cpp : 实现文件
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
		result="'USE' 附近有语法错误！漏了数据库名？";//缺少数据库名称
		return result;
	}

	strcpy(dbName,globalDB);//记录通用数据库，如果没有 IN db，这个作为默认数据库
	int i=2;
	if(AWord[i].type==insym){//in XXX  xxx为目标数据库
		i++;
		if(AWord[i].type==identifier){
			strcpy(dbName,AWord[i].word);//这个是数据库名，可以利用该名字选择要操作的数据库，先判断该数据库存不存在//////////////文件操作
		}
		else{
		result="缺少您要操作的数据库!";
		return result;
		}
     i++;
	}
	///////////////////////
	if(dbName[0]==NULL) {
		result="您还没有选择要操作的数据库!";
		return result;

	};////////////////
	if(AWord[i].type!=semicolon){
		result="缺少';'!";
		return result;
	}


	///////////文件操作//////////////////
	strcpy(tableName,AWord[1].word);//
	if(!IsTableExists(dbName,tableName))
	{
		result="对不起，该数据库不存在";//找不到数据库
		return result;
	};



	vector<char*> tableModes;//存放表字段

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
