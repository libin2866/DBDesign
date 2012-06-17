#include"stdafx.h"
#include"Update.h"
/*Sample SQL
UPDATE mytable(SET age='21' WHERE username='test')IN myDB;

*/


CString Update(void){
	CString result;
	int i=1;
	char dbName[15];
	if(AWord[i].type!=identifier){
		result="'UPDATE' 附近有语法错误！漏了表名？";//缺少表名
		return result;
	}
	i++;
	if(AWord[i].type!=lparen){
		result="SQL语句有语法错误！漏了'('？";//缺少表名
		return result;

	}else{i++;
		if(AWord[i].type!=setsym){
		result="SQL语句有语法错误！漏了SET？";
		return result;
		}i++;
		if(AWord[i].type!=identifier){
		result="SQL语句有语法错误！漏了Field？";
		return result;
		}i++;
		if(AWord[i].type!=eql){
		result="SQL语句有语法错误！漏了'='？";
		return result;
		}i++;
		if(AWord[i].type!=quote){
		result="SQL语句有语法错误！漏了Content？";
		return result;
		}i++;
		if(AWord[i].type!=wheresym){
		result="SQL语句有语法错误！漏了WHERE？";
		return result;
		}i++;
		if(AWord[i].type!=identifier){
		result="SQL语句有语法错误！漏了Field？";
		return result;
		}i++;
		if(AWord[i].type!=eql){
		result="SQL语句有语法错误！漏了'='？";
		return result;
		}i++;
		if(AWord[i].type!=quote){
		result="SQL语句有语法错误！漏了Content？";
		return result;
		}i++;
	}
	if(AWord[i].type!=rparen){
		result="SQL语句有语法错误！漏了')'？";
		return result;

	}i++;
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



	result="更新成功";
	return result;

}