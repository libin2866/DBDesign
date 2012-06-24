#include"stdafx.h"
#include"SELECT.h"
#include"FileOperation.h"
#include<vector>
#include"TableDlg.h"
using namespace std;
/* Sample SQL

SELECT * 
FROM mytable,yourtble WHERE Condition??

SELECT username FROM mytable;

SELECT username,age FROM mytable;

SELECT username FROM mytable WHERE age>'10';

SELECT username FROM mytable,yourtable WHERE mytable.id=yourtable.id AND age='10';



*/


CString Select(void){
	CString result;
	int i=0;
	char dbName[15];
	char tableName[15];
	char table1[15];
	char column1[15];
	char table2[15];
	char column2[15];
	int tableNum=0;//记录select…… from 的表的个数
	int columnNum=0;//记录select 字段个数
	int statement;//统计条件中语句的个数
	int conn=0;//连接查询的连接个数
	//CString tempcon;
	char condition[15];//逻辑运算中
	int type;
	vector<vector<char*> >returnData( 20, vector<char*>(0) );//存储返回的内容
	vector<char*> destColumn;//表示select column1,column2...中的那些columns
	vector<char*> connTable;//存放已经连接的表

	strcpy(dbName,globalDB);//记录通用数据库，如果没有 IN db，这个作为默认数据库

		if(dbName[0]==NULL) {
		result="您还没有选择要操作的数据库,请先用USE语句选择!";
		return result;

	};////////////////

	if(AWord[1].type!=times){//若是*,则选择全部，显示所有信息
			do{
			i++;
			if(AWord[i].type==identifier){//标识符，可能有多个，执行相应操作
				////////////对应的操作///////////////////////
				i++;columnNum++;//字段个数加一
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
			destColumn.push_back(AWord[i].word);
			i++;tableNum++;//要操作的表的数目增加
		}else{
			result="SQL语句错误！缺少表或者多了','?";
			return result;
		}
	 }while(AWord[i].type==comma);//select xxx from a,b,c WHERE 这里a,b,c需要一个循环

	if(AWord[i].type!=wheresym){
		if(AWord[i].type==semicolon){//没有where的条件，直接结束
				////////////////////////////这里可以插入单表查询的操作,

			//select * from mytable;
			if(AWord[1].type==times){
				type=-1;//-1表示无where部分。
				char *column="";
				char *condition="";
				returnData=SelectAllData(dbName,tableName,column,condition,type);

			}else{//select table1,table2...from mytable;
				char *column="";
				char *condition="";
				type=-1;//-1表示无where部分。
				returnData=SelectPartData(dbName,tableName,column,condition,destColumn,type);
			}
				TableDlg  *tr1dlg=new TableDlg;
				tr1dlg->returnData=returnData;
				strcpy(tr1dlg->title,dbName);
				tr1dlg->Create(IDD_TREEDIALOG);
				tr1dlg->ShowWindow(SW_SHOW);

				result="查找完成";
				return result;
			}//semicolon
		else{
		result="SQL语句错误！缺少WHERE?";
		return result;
		}
	}else{
		do{
			i++;
			if(AWord[i].type==identifier){//可能为表名 table.id=table2.id 也可能为列名
				//////////////////////////////////??
				
				i++;
				if(AWord[i].type==period){//进行连接查询
					strcpy(table1,AWord[i-1].word);//传递表名  后退一个
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
					strcpy(column1,AWord[i].word);//
					//////////////////table1.id1=分析出来了 这里可以有操作
					i++;
					if(AWord[i].type!=identifier){
						result="SQL语句错误！连接查询'='后缺少表名?";
						return result;
					}
					strcpy(table2,AWord[i].word);//传递表名
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
					}
					strcpy(column2,AWord[i].word);
					//////////////////table1.id1=table2.id2分析出来了 这里可以有操作
					connTable.push_back(ConTable(dbName,table1,table2,column1,column2));//这里进行连接表、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、
					conn++;//增加一个连接的标记
					i++;
				}//period

				if(AWord[i].type==geql||AWord[i].type==eql||AWord[i].type==leql||AWord[i].type==lss||AWord[i].type==gtr){//逻辑运算
					///////////////////////
						strcpy(column1,AWord[i-1].word);//传递表名  后退一个
						if(AWord[i].type==eql) type=0;
						if(AWord[i].type==lss) type=1;
						if(AWord[i].type==leql) type=2;
						if(AWord[i].type==gtr) type=3;
						if(AWord[i].type==geql) type=4;
						//if(AWord[i].type==lss) type=5;
					i++;
					if(AWord[i].type!=quote){
						result="SQL语句错误！逻辑运算符后缺少具体条件?";
						return result;
					}
	/*				if(AWord[1].type==times){
						char *column="";
						char *condition="";
						returnData=SelectAllData(dbName,tableName,column,condition,type);
					}
					else
					returnData=SelectPartData(dbName,tableName,column1,condition,destColumn,type);*/
					///////////////////

				}



			}//identifier1
			else{
				result="SQL语句错误！WHERE后缺少表名或列名?";
						return result;
			}

		}while(AWord[i].type==andsym);

	}//wheresym

	//具体操作

	//SELECT username FROM mytable WHERE age>'10';
	//////////////注意：表中不能出现没有初始化的值，若为空值，返回空白字符串，空格也可。
	returnData[0].push_back("MyTable0");
	returnData[1].push_back("MyTable1");
	returnData[2].push_back("MyTable2");
	//获取表中每一项
	returnData[0].push_back("MySubTable01");
	returnData[0].push_back("MySubTable02");
	returnData[0].push_back("MySubTable03");
	returnData[1].push_back("MySubTable11");
	returnData[1].push_back("MySubTable12");
	returnData[1].push_back("MySubTable13");
	returnData[2].push_back("MySubTable21");
	returnData[2].push_back("MySubTable22");
	returnData[2].push_back("MySubTable33");

	TableDlg  *tr1dlg=new TableDlg;
	//tr1dlg.DoModal();
	//tr1dlg->counts=2;
	tr1dlg->returnData=returnData;
	//tr1dlg->tables=returntables.size();
	strcpy(tr1dlg->title,dbName);
	tr1dlg->Create(IDD_TABLEDIALOG);
	tr1dlg->ShowWindow(SW_SHOW);

	result="查找完成!";
	return result;

}