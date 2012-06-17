
#include "stdafx.h"

#include "CreateTable.h"

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
	int c=0;
	int mark;//判断是否列名后面有数据类型
	bool keymark;//判断是否设置key 或者not key 若没有 则执行默认的操作
	bool nullmark;//判断是否设置null 或者not null 若没有 则执行默认的操作
	bool validmark;
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
				i++;
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
}else{//lparen的while
		result="缺少'('!";
		return result;
	}

	///////再进行写入文件操作//////

	i=3;//回到开始
	if(AWord[2].type==identifier)
	strcpy(tableName,AWord[2].word);//操作表名//////////////这里需要文件处理，把表名存入文件。
	
	if(AWord[3].type==lparen){

		do{
			keymark=false;//判断是否设置key 或者not key 若没有 则执行默认的操作not key
			nullmark=false;//判断是否设置null 或者not null 若没有 则执行默认的操作null
			validmark=false;//判断是否设置valid 若没有 则执行默认的操作valid
			i++;//选下一个关键字
			if(AWord[i].type==identifier){//列名
				//strcpy(columnName[c],AWord[i].word);///////////////这里需要文件处理，把列名存入文件。
				c++;i++;
			}
			if(AWord[i].type==datetimesym){//datetime数据类型
				//strcpy(columnName[c],AWord[i].word);///////////////这里需要文件处理，把类型存入文件。
				i++;
			}
			if(AWord[i].type==varcharsym){//varchar数据类型
				//strcpy(columnName[c],AWord[i].word);///////////////这里需要文件处理，把类型存入文件。
				i++;
			}
			if(AWord[i].type==intsym){//int数据类型
				//strcpy(columnName[c],AWord[i].word);///////////////这里需要文件处理，把类型存入文件。
				i++;
			}
			if(AWord[i].type==keysym){
				///////////////这里需要文件处理，把设置key标记。///////////////这里需要文件处理，存入文件。
				i++;keymark=1;
			}
			if(AWord[i].type==notkeysym){
				///////////////这里需要文件处理，把设置key标记。///////////////这里需要文件处理，存入文件。
				i++;keymark=1;
			}
			if(keymark==0){
				//这里执行默认操作 即设置为not key///////////////这里需要文件处理，notkey存入文件。
			}

			if(AWord[i].type==nul){//null标记
				///////////////这里需要文件处理，把设置key标记。///////////////这里需要文件处理，存入文件。
				i++;nullmark=1;
			}
			if(AWord[i].type==notnul){//not null标记
				///////////////这里需要文件处理，把设置key标记。///////////////这里需要文件处理，存入文件。
				i++;nullmark=1;
			}
			if(nullmark==0){
				//这里执行默认操作 即设置为null///////////////这里需要文件处理，默认操作null存入文件。
			}
			if(AWord[i].type==validsym){//VALID标记
				///////////////这里需要文件处理，把设置key标记。///////////////这里需要文件处理，存入文件。
				i++;validmark=1;
			}
			if(AWord[i].type==invalidsym){//INVALID标记
				///////////////这里需要文件处理，把设置key标记。///////////////这里需要文件处理，存入文件。
				i++;validmark=1;
			}
			if(validmark==0){
				//这里执行默认操作 即设置为null///////////////这里需要文件处理，默认操作valid存入文件。
			}

		}while(AWord[i].type==comma);
	}	
	result="操作成功！";
	return result;
}
