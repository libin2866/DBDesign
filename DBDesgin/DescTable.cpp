// DescTable.cpp : 实现文件
//

#include "stdafx.h"
#include "DescTable.h"


// DescTable
CString DescTable(void){
	CString result;
	char dbName[15];
	char tableName[15];
	if(AWord[1].type!=identifier){
		result="'USE' 附近有语法错误！漏了数据库名？";//缺少数据库名称
		return result;
	}
	if(AWord[2].type!=semicolon){
		result="SQL语句有语法错误！漏了分号？";//缺少分号
		return result;
	}
	strcpy(dbName,AWord[1].word);//
	if(!IsDBExists(dbName))
	{
		result="对不起，该数据库不存在";//找不到数据库
		return result;
	};

	return result;
}
