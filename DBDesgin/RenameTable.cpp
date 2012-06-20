#include"stdafx.h"
#include"RenameTable.h"
#include"FileOperation.h"
/*Sample SQL:

RENAME TABLE mytable yourtable IN myDB;

*/


CString RenameTable(void){
	CString result;
	char preName[15];
	char lasName[15];
	char dbName[15];
	int i=4;
	///////////////检查语法///////////////////
	if(AWord[2].type!=identifier){
		result="'RENAME TABLE' 附近有语法错误！漏了表名？";//缺少表名
		return result;
	}
		if(AWord[3].type!=identifier){
		result="语法错误！漏了第二个表名？";//缺少表名
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

		///////////////文件操作///////////////////
	strcpy(preName,AWord[2].word);//原来的名字，先确定表存不存在
	strcpy(lasName,AWord[3].word);//后来的名字
	////////////预留给具体更改操作//////////////
	
	if(!RenameTableFile(dbName,preName,lasName)){
	result="重命名失败！请确认该表是否存在！";
	return result;

	}
	result="操作成功！";
	return result;
}