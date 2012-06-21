#include"stdafx.h"
#include"UseDB.h"
#include <vector>
#include"resource.h"
using namespace std;

char globalDB[15];//这个存储USE db;执行之后 作为默认要操作的数据库
CString UseDB(void){

	CString result;
	char dbName[15];
	if(AWord[1].type!=identifier){
		result="'USE' 附近有语法错误！漏了数据库名？";//缺少数据库名称
		return result;
	}
	if(AWord[2].type!=semicolon){
		result="SQL语句有语法错误！漏了分号？";//缺少分号
		return result;
	}
	////////////////////////////////文件操作
	strcpy(dbName,AWord[1].word);//
	if(!IsDBExists(dbName))
	{
		result="对不起，该数据库不存在";//找不到数据库
		return result;
	};
	strcpy(globalDB,dbName);//设置为全局变量
	vector<vector<char*> >tables( 20, vector<char*>(0) );//存放表
	//int total=tables.size;//数目
	/*FOR TEST DEMO*/
	//获取表
	tables[0].push_back("MyTable0");
	tables[1].push_back("MyTable2");
	//获取表中每一项
	tables[0].push_back("MySubTable1");
	tables[0].push_back("MySubTable2");
	tables[1].push_back("MySubTable3");
	tables[1].push_back("MySubTable4");
/*
	vector<char*> returntables=ShowTables(dbName);  
	for(int i=0;i<returntables.size();i++)
	{tables[i].push_back(returntables[i]);//先把表放入
	   vector<char*> returncolumns=ShowColumns(dbName,returntables[i]);
	  for(int j=0;j<returncolumns.size();j++){
		  tables[i].push_back(returncolumns[i]);
	  }//j
	}//i

	*/
	//vector< vector<char*> > Array( 20, vector<char*>(0) );

	//Array[0].push_back("MySubTable0");

	TreeDlg *tr1dlg=new TreeDlg;
	//tr1dlg.DoModal();
	tr1dlg->counts=2;
	tr1dlg->tables=tables;
	//tr1dlg->tables=returntables.size();
	strcpy(tr1dlg->title,dbName);
	tr1dlg->Create(IDD_TREEDIALOG);
	tr1dlg->ShowWindow(SW_SHOW);

	result="操作成功！";
	return result;
}