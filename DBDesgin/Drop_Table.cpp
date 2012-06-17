#include"stdafx.h"
#include"Drop_Table.h"
/*Sample SQL:
DROP TABLE mytable IN myDB;

*/


CString DropTable(void){
	CString result;
	char tableName[15];
	char dbName[15];
	int i=3;
	///////////////检查语法///////////////////
	if(AWord[2].type!=identifier){
		result="'DROP TABLE' 附近有语法错误！漏了表名？";//缺少表名
		return result;
	}
	

	if(AWord[i].type==insym){//in XXX  xxx为目标数据库
		i++;
		if(AWord[i].type==identifier){
			strcpy(dbName,AWord[i+1].word);//这个是数据库名，可以利用该名字选择要操作的数据库，先判断该数据库存不存在//////////////文件操作
		}
		else{
		result="缺少您要操作的数据库!";
		return result;
		}
		i++;
   	}
	
	if(AWord[i].type!=semicolon){
		result="缺少';'!";
		return result;
	}

		///////////////文件操作///////////////////
	strcpy(tableName,AWord[3].word);//表的名字，先确定表存不存在，表不存在直接返回
	//strcpy(lasName,AWord[4].word);//后来的名字
	////////////预留给具体更改操作//////////////

	result="操作成功！";
	return result;



}