#include"stdafx.h"
#include <vector>
using namespace std;

bool InitDataBase(char* dbName);//初始化数据库

bool IsDBExists(char* dbName);//判断数据库是否存在

bool BuildTable(char* dbName,char* tableName ,int columns );//建立表（写入表名到数据库，先不写入表字段）

bool BuildModel(char*,char*,TableMode);//写入表字段

bool EditModel(char *dbName,char* tableName, char* oldcolumn,TableMode tableMode);//修改表(先判断数据库和字段oldcolumn是否存在，不存在直接返回false)

bool RenameTableFile(char* dbName,char* prename,char* latname);//重命名(先判断数据库和表prename是否存在，不存在直接返回false)

bool DeleteTable(char* dbName,char *tableName);//删除表（先判断数据库和表是否存在）

vector<char*> ShowTables(char* dbName);//返回数据库的所有表（不用判断数据库是否存在)

vector<char*> ShowColumns(char* dbName,char* tableName);//返回一个数据库中一张表的所有属性



vector<char*> ShowFields(char* dbName,char* tableName);//查看某张表的所有字段。

//插入数据(先判断表是否存在),根据查询出来的Fileds进行一一对应。我会先判断插入的数据是否符合条件，此函数只需负责插入数据）
bool InsertData(char* dbName,char* tableName,vector<char*> newData);


//bool IsTableExists(char*dbName,char* tableName);//判断一个数据库中某张表是否存在(修改表时用）

//bool IsColumnExists(char* dbName,char *tableName,char *column);//判断一个数据库中指定表的字段是否存在（修改字段时用）

