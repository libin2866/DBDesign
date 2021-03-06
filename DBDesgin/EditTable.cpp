#include "stdafx.h"

#include"EditTable.h"
#include"FileOperation.h"
/*Sample SQL:
EDIT TABLE mytable(
uname username varchar  NOT_KEY  NOT_NULL  VALID)IN myDB;
*/

CString EditTable(void){
	CString result;
	char tableName[15];
	char dbName[15];
	bool mark;
	bool nullmark;
	bool keymark;
	bool validmark;
	int i=4;
	///////////////检查语法///////////////////
	if(AWord[2].type!=identifier){
		result="'EDIT TABLE' 附近有语法错误！漏了表名？";//缺少表名
		return result;
	}
	if(AWord[3].type==lparen){

			mark=false;//清零,数据类型的标记，防止缺少数据类型
			if(AWord[i].type==identifier){//列名
				i++;
			}else {
			result="'(' 附近有语法错误!缺少旧列名?";//缺少标识符来定义列名
			return result;
			}
			if(AWord[i].type==identifier){//列名
				i++;
			}else {
			result="'(' 附近有语法错误!缺少新列名?";//缺少标识符来定义列名
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
		
	if(AWord[i].type!=rparen){
		result="缺少')'!";
		return result;
	}
	i++;strcpy(dbName,globalDB);//记录通用数据库，如果没有 IN db，这个作为默认数据库
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
	if(dbName==NULL) {
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
	//先判断是否存在
	strcpy(tableName,AWord[2].word);//操作表名//////////////这里需要文件处理，把表名存入文件。
   
	i=4;//第四个是旧列名,第五个为新列名，第六个为数据类型
	TableMode newcolumn;//新建一个字段
	char oldcolumn[15];//旧字段
	keymark=false;//判断是否设置key 或者not key 若没有 则执行默认的操作not key
	nullmark=false;//判断是否设置null 或者not null 若没有 则执行默认的操作null
	validmark=false;//判断是否设置valid 若没有 则执行默认的操作valid

	//i++;//选下一个关键字
	if(AWord[i].type==identifier){//旧列名，查找用
		strcpy(oldcolumn,AWord[i].word);
		i++;
	}

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

	if(!EditModel(dbName,tableName,oldcolumn,newcolumn)){//写入文件
		result="修改失败！旧字段不存在？";
		return result;
		}
	
	result="操作成功！";

	return result;
}
