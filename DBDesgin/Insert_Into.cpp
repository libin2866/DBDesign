#include"stdafx.h"
#include"Insert_Into.h"
#include"FileOperation.h"
#include<vector>
using namespace std;
/*Sample SQL:

INSERT INTO mytable VALUES('test','9','2012-6-17')IN mydb;


*/


CString InsertInto(void){
	CString result;
	char tableName[15];
	char dbName[15];
	int i=4;
	int column;
	int c=0;


	if(AWord[2].type!=identifier){
		result="'INSERT INTO' 附近有语法错误！漏了表名？";//缺少表名
		return result;
	}
	if(AWord[3].type!=valuessym){
		result="'SQL语句有语法错误！漏了VALUES？";
		return result;
	}
	if(AWord[4].type!=lparen){
		result="'SQL语句有语法错误！漏了'('？";
		return result;
	}else{
		///////////////这里得先获取表的信息，然后根据表中列数设置column////////////////////////////////
		column=0;//这个是最大的数目,防止出现死循环.也有计数功能
		do{
			i++;
			if(AWord[i].type!=quote){
				result="'SQL语句有语法错误！漏了参数或者多了','号?";//缺少表名
				return result;
			}
			i++;column++;
		}while(AWord[i].type==comma&&column<20);
	}
		
		
	if(AWord[i].type!=rparen){
		result="参数个数不对或者缺少')'!";
		return result;
	}
	i++;
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


	///////////////文件操作/////////////////////

	strcpy(tableName,AWord[2].word);//表名

		///////////////这里得先获取表的信息，然后根据表中列数设置column////////////////////////////////
	  i=5;
	  vector<char*> newData;
		while(column>0){
			newData.push_back(AWord[i].word);
			i++;column--;i++;
		}

	InsertData(dbName,tableName,newData);//插入数据

	result="操作成功！";
	return result;
}