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
	///////////////检查语法///////////////////
	if(AWord[2].type!=identifier){
		result="'DELETE FROM' 附近有语法错误！漏了表名？";//缺少表名
		return result;
	}
	if(AWord[3].type!=wheresym){
		result="SQL语句有语法错误！漏了WHERE？";//缺少where
		return result;
	}
	if(AWord[4].type!=identifier){
		result="SQL语句有语法错误！漏了Field？";//缺少field
		return result;
	}
	if(AWord[5].type!=eql){
		result="SQL语句有语法错误！不是'='？";//不是=号
		return result;
	}
	if(AWord[6].type!=quote){
		result="SQL语句有语法错误！漏了content？";//缺少content
		return result;
	}
	strcpy(dbName,globalDB);//记录通用数据库，如果没有 IN db，这个作为默认数据库
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
/////////////文件操作//////////////////////////////////////////
	strcpy(tableName,AWord[2].word);
	strcpy(conditionColumn,AWord[4].word);
	strcpy(condition,AWord[6].word);


	if(!DeleteData(dbName,tableName,conditionColumn,condition)){
		result="删除失败!";
		return result;

	}

	result="删除成功！";
	return result;
}