#include"stdafx.h"
#include <vector>
using namespace std;

bool InitDataBase(char* dbName);//��ʼ�����ݿ�

bool IsDBExists(char* dbName);//�ж����ݿ��Ƿ����

bool BuildTable(char* dbName,char* tableName ,int columns );//������д����������ݿ⣬�Ȳ�д����ֶΣ�

bool BuildModel(char*,char*,TableMode);//д����ֶ�

bool EditModel(char *dbName,char* tableName, TableMode tableMode);//�޸ı�

bool RenameTableFile(char* dbName,char* prename,char* latname);//������

bool DeleteTable(char* dbName,char *tableName);//ɾ����

vector<char*> ShowTables(char* dbName);//�������ݿ�����б� 

vector<char*> ShowColumns(char* dbName,char* tableName);//����һ�����ݿ���һ�ű���������� \

bool IsTableExists(char*dbName,char* tableName);//�ж�һ�����ݿ���ĳ�ű��Ƿ����(�޸ı�ʱ�ã�

bool IsColumnExists(char* dbName,char *tableName,char *column);//�ж�һ�����ݿ���ָ������ֶ��Ƿ���ڣ��޸��ֶ�ʱ�ã�

