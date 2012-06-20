#include"stdafx.h"
#include <vector>
using namespace std;

bool InitDataBase(char* dbName);//��ʼ�����ݿ�

bool IsDBExists(char* dbName);//�ж����ݿ��Ƿ����

bool BuildTable(char* dbName,char* tableName ,int columns );//������д����������ݿ⣬�Ȳ�д����ֶΣ�

bool BuildModel(char*,char*,TableMode);//д����ֶ�

bool EditModel(char *dbName,char* tableName, char* oldcolumn,TableMode tableMode);//�޸ı�(���ж����ݿ���ֶ�oldcolumn�Ƿ���ڣ�������ֱ�ӷ���false)

bool RenameTableFile(char* dbName,char* prename,char* latname);//������(���ж����ݿ�ͱ�prename�Ƿ���ڣ�������ֱ�ӷ���false)

bool DeleteTable(char* dbName,char *tableName);//ɾ�������ж����ݿ�ͱ��Ƿ���ڣ�

vector<char*> ShowTables(char* dbName);//�������ݿ�����б������ж����ݿ��Ƿ����)

vector<char*> ShowColumns(char* dbName,char* tableName);//����һ�����ݿ���һ�ű����������



vector<char*> ShowFields(char* dbName,char* tableName);//�鿴ĳ�ű�������ֶΡ�

//��������(���жϱ��Ƿ����),���ݲ�ѯ������Fileds����һһ��Ӧ���һ����жϲ���������Ƿ�����������˺���ֻ�踺��������ݣ�
bool InsertData(char* dbName,char* tableName,vector<char*> newData);


//bool IsTableExists(char*dbName,char* tableName);//�ж�һ�����ݿ���ĳ�ű��Ƿ����(�޸ı�ʱ�ã�

//bool IsColumnExists(char* dbName,char *tableName,char *column);//�ж�һ�����ݿ���ָ������ֶ��Ƿ���ڣ��޸��ֶ�ʱ�ã�

