#include"stdafx.h"
#include"SELECT.h"
/*
SELECT * 
FROM mytable,yourtble WHERE Condition??

SELECT username FROM mytable;
SELECT username,age FROM mytable;
SELECT username FROM mytable,yourtable WHERE mytable.id=yourtable.id AND age='10';


*/


CString Select(void){
	CString result;
	int i=0;
	if(AWord[1].type!=times){//若不是*,选择全部
			do{
			i++;
			if(AWord[i].type==identifier){//标识符，可能有多个，执行相应操作
				////////////对应的操作///////////////////////
				i++;
			}else{
				result="SQL语句错误！缺少标识符或者多了','?";
				return result;
			}

		}while(AWord[i].type==comma);//select a,b,c from 这里a,b,c需要一个循环

	}
	//i++;
	if(AWord[i].type!=fromsym){
		result="SQL语句错误！缺少FROM?";
		return result;
	}
	do{
		i++;
		if(AWord[i].type==identifier){//标识符，可能有多个，执行相应操作 这里对应表
			////////////对应的操作///////////////////////
			i++;
		}else{
			result="SQL语句错误！缺少表或者多了','?";
			return result;
		}
	 }while(AWord[i].type==comma);//select xxx from a,b,c WHERE 这里a,b,c需要一个循环

	if(AWord[i].type!=wheresym){
		if(AWord[i].type==semicolon){//没有where的条件，直接结束
				////////////////////////////这里可以插入单表查询的操作,
				result="查找完成";
				return result;
			}//semicolon
		else{
		result="SQL语句错误！缺少WHERE?";
		return result;
		}
	}else{
		i++;
		if(AWord[i].type==identifier){//可能为表名 table.id=table2.id 也可能为列名
			//////////////////////////////////??
			i++;
			if(AWord[i].type==period){//进行连接查询
				i++;
				if(AWord[i].type!=identifier){
					result="SQL语句错误！.后缺少对应的列名?";
					return result;
				}
				//////////////////table1.id1分析出来了 这里可以有操作
				i++;
				if(AWord[i].type!=eql){
					result="SQL语句错误！连接查询缺少'='号?";
					return result;
				}
				//////////////////table1.id1=分析出来了 这里可以有操作
				i++;
				if(AWord[i].type!=identifier){
					result="SQL语句错误！连接查询'='后缺少表名?";
					return result;
				}
				//////////////////table1.id1=table2分析出来了 这里可以有操作
				i++;
				if(AWord[i].type!=period){
					result="SQL语句错误！连接查询缺少'.'?";
					return result;
				}
				//////////////////table1.id1=table2.分析出来了 这里可以有操作
				i++;
				if(AWord[i].type!=identifier){
					result="SQL语句错误！连接查询'.'后缺少列名?";
					return result;
				}//////////////////table1.id1=table2.id2分析出来了 这里可以有操作
				i++;
			}//period
			if(AWord[i].type==geql||AWord[i].type==eql||AWord[i].type==leql||AWord[i].type==lss||AWord[i].type==gtr){//逻辑运算
				///////////////////////
				i++;
				///////////////////

			}



		}//identifier1
		else{
			result="SQL语句错误！WHERE后缺少表名或列名?";
					return result;
		}

	}//wheresym





	result="查找完成";
	return result;

}