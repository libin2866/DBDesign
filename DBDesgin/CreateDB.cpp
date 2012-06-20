#include"stdafx.h"
#include "CreateDB.h"

CString CreateDB(void){
	
	CString result;
	char dbName[15];
	if(AWord[2].type!=identifier){
		result="'CREATE DATABASE' 附近有语法错误！漏了数据库名？";//缺少数据库名称
		return result;
	}
	if(AWord[3].type!=semicolon){
		result="SQL语句有语法错误！漏了分号？";//缺少分号
		return result;
	}
	/////////////////

	strcpy(dbName,AWord[2].word);//数据库名称
	InitDataBase(dbName);//初始化数据库

	result="操作成功！";
	return result;

}