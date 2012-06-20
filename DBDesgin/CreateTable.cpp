
#include "stdafx.h"

#include "CreateTable.h"
#include"FileOperation.h"

/*测试SQL:
CREATE TABLE mytable(
username varchar KEY NOT_NULL VALID,
age int,
birth datetime);
*/


CString CreateTable(void){
	CString result;
	char tableName[15];
	char dbName[15];
	int i=3;
	//char columnName[15][15];
	int columns=0;
	int mark;//判断是否列名后面有数据类型
	bool keymark;//判断是否设置key 或者not key 若没有 则执行默认的操作
	bool nullmark;//判断是否设置null 或者not null 若没有 则执行默认的操作
	bool validmark;//判断是否设置了valid 或者invalid标记
	////////先进行语法分析///////////////////
	if(AWord[2].type!=identifier){
		result="'CREATE TABLE' 附近有语法错误！漏了表名？";//缺少表名
		return result;
	}
	if(AWord[3].type==lparen){

		do{
			mark=false;//清零,数据类型的标记，防止缺少数据类型
			i++;//选下一个关键字
			if(AWord[i].type==identifier){//列名
				i++;columns++;
			}else {
			result="'(' 附近有语法错误!缺少列名?";//缺少标识符来定义列名
			return result;
			}
			if(AWord[i].type==datetimesym){//datetime数据类型
				i++;mark=1;//存在数据类型,标记1
			}
			if(AWord[i].type==varcharsym){//varchar数据类型
				i++;mark=1;//存在数据类型,标记1
			}
			if(AWord[i].type==intsym){//int数据类型
				i++;mark=1;//存在数据类型,标记1
			}
			if(mark==0){
			result="列名后面缺少对应的数据类型!";
			return result;
			}
			if(AWord[i].type==keysym) i++;			
			if(AWord[i].type==notkeysym)i++;
			if(AWord[i].type==nul)	i++;		
			if(AWord[i].type==notnul)	i++;
			if(AWord[i].type==validsym) i++;
			if(AWord[i].type==invalidsym) i++;
		}while(AWord[i].type==comma);//do
		
	if(AWord[i].type!=rparen){
		result="缺少')'!";
		return result;
	}
	i++;
	//if(globalDB!=NULL)
	strcpy(dbName,globalDB);//记录通用数据库，如果没有 IN db，这个作为默认数据库

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
	///////////////////////
	if(dbName[0]==NULL) {
		result="您还没有选择要操作的数据库!";
		return result;

	};////////////////
	if(AWord[i].type!=semicolon){
		result="缺少';'!";
		return result;
	}
}else{//lparen的while
		result="缺少'('!";
		return result;
	}

	///////再进行写入文件操作//////

	i=3;//回到开始
	strcpy(tableName,AWord[2].word);//操作表名
	BuildTable(dbName,tableName,columns);//写入文件
	if(AWord[3].type==lparen){
		do{
			TableMode newcolumn;//新建一个字段

			keymark=false;//判断是否设置key 或者not key 若没有 则执行默认的操作not key
			nullmark=false;//判断是否设置null 或者not null 若没有 则执行默认的操作null
			validmark=false;//判断是否设置valid 若没有 则执行默认的操作valid

			i++;//选下一个关键字

			if(AWord[i].type==identifier){//列名
				strcpy(newcolumn.sFiledName,AWord[i].word);
				i++;
			}
			if(AWord[i].type==datetimesym){//datetime数据类型
				strcpy(newcolumn.sType,AWord[i].word);
				i++;
			}
			if(AWord[i].type==varcharsym){//varchar数据类型
				strcpy(newcolumn.sType,AWord[i].word);
				i++;
			}
			if(AWord[i].type==intsym){//int数据类型
				strcpy(newcolumn.sType,AWord[i].word);
				i++;
			}
			if(AWord[i].type==keysym){
				newcolumn.bKey=1;
				i++;keymark=1;
			}
			if(AWord[i].type==notkeysym){
				newcolumn.bKey=0;
				i++;keymark=1;
			}
			if(keymark==0){
				newcolumn.bKey=0;
			}

			if(AWord[i].type==nul){//null标记
				newcolumn.bNullFlag=1;
				i++;nullmark=1;
			}
			if(AWord[i].type==notnul){//not null标记
				newcolumn.bNullFlag=0;
				i++;nullmark=1;
			}
			if(nullmark==0){
				newcolumn.bNullFlag=1;//默认允许为空
			}
			if(AWord[i].type==validsym){//VALID标记
				newcolumn.bValidFlag=1;//有效
				i++;validmark=1;
			}
			if(AWord[i].type==invalidsym){//INVALID标记
				newcolumn.bValidFlag=0;//无效
				i++;validmark=1;
			}
			if(validmark==0){
				newcolumn.bValidFlag=1;//默认是有效
			}

		 BuildModel(dbName,tableName,newcolumn);//写入文件
		}while(AWord[i].type==comma);
	}	
	result="操作成功！";
	return result;
}
