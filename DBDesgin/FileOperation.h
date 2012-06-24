#include"stdafx.h"
#include <vector>
using namespace std;




//初始化数据库
bool InitDataBase(char* dbName);

//判断数据库是否存在
bool IsDBExists(char* dbName);

//判断一个数据库中某张表是否存在
bool IsTableExists(char*dbName,char* tableName);

//建立表（写入表名到数据库，先不写入表字段）
bool BuildTable(char* dbName,char* tableName ,int columns );

//写入表字段
bool BuildModel(char*,char*,TableMode);

//修改表(先判断数据库和字段oldcolumn是否存在，不存在直接返回false)
bool EditModel(char *dbName,char* tableName, char* oldcolumn,TableMode tableMode);

//重命名(先判断数据库和表prename是否存在，不存在直接返回false)
bool RenameTableFile(char* dbName,char* prename,char* latname);

//删除表（先判断数据库和表是否存在）
bool DeleteTable(char* dbName,char *tableName);

//查看某张表字段的数目，插入数据时判断用
//int CountColumns(char* dbName,char* tableName,char* columnName);//这个columnName就是tableMode里的sFiledName

//插入数据(先判断表是否存在),根据查询出来的Fileds进行一一对应。我会先判断插入的数据是否符合条件，此函数只需负责插入数据）
bool InsertData(char* dbName,char* tableName,vector<char*> newData);

//返回数据库的所有表（不用判断数据库是否存在)
vector<char*> ShowTables(char* dbName);

//返回一个数据库中一张表的所有字段名（只需在vector中一次压入一个字段名即可）
vector<char*> ShowColumns(char* dbName,char* tableName);

//返回一个数据库中一张表的所有字段(包括字段名，数据类型，KEY，NULL，VALID，vector中一次压人一个整个字段内容，有几个字段就压几次）
vector<char*> ShowColumnDetail(char* dbName,char* tableName);

//查看某张表的所有字段。
vector<char*> ShowFields(char* dbName,char* tableName);

//更新表中的数据，根据conditionColumn的condition确定哪条记录要改，然后在该记录的destColumn写入dest数据.(看不懂问我）
bool UpdateData(char* dbName,char* tableName,char* conditionColumn,char* condition,char* destColumn,char *dest);

//删除表中的数据(即符合条件的那整条记录)
bool DeleteData(char* dbName,char* tableName,char* conditionColumn,char* condition);


//bool IsColumnExists(char* dbName,char *tableName,char *column);//判断一个数据库中指定表的字段是否存在（修改字段时用）

///////////////////////////查询相关接口//////////////////////////////////
//根据column列的condition返回找到的全部相关内容，即SELECT *中的*号
/*此处的type 可能要处理：-1:无条件 0:等于 1:小于 2:小于等于  3:大于 4:大于等于 (不等于先不考虑) 
type=-1时 column与condition为空，不必考虑
*/
vector<vector<char*>>  SelectAllData(char*dbName,char*tableName,char*column,char*condition,int type);
	
//查找部分数据SELECT table1,table2,....不是*号，而table1,table2存放在vector那个参数destColumn中
//type=-1 时 表示没有where条件 直接返回全部结果
//此处的type 可能要处理：-1:无条件 0:等于 1:小于 2:小于等于  3:大于 4:大于等于 (不等于先不考虑)
vector<vector<char*>> SelectPartData(char*dbName,char*tableName,char*column,char*condition,vector<char*>destColumn,int type);

/**可以考虑建立一个隐式的类似view的文件，存放在一个固定的，可以供以后方便访问的地方
这个是对两个表的连接，即 WHERE table1.column1=table2.column2
*/
char* ConTable(char*dbName,char*table1,char* table2,char* column1,char*  column2);