#include"stdafx.h"
#include <vector>
using namespace std;

//��ʼ�����ݿ�
bool InitDataBase(char* dbName);

//�ж����ݿ��Ƿ����
bool IsDBExists(char* dbName);

//�ж�һ�����ݿ���ĳ�ű��Ƿ����
bool IsTableExists(char*dbName,char* tableName);

//������д����������ݿ⣬�Ȳ�д����ֶΣ�
bool BuildTable(char* dbName,char* tableName ,int columns );

//д����ֶ�
bool BuildModel(char*,char*,TableMode);

//�޸ı�(���ж����ݿ���ֶ�oldcolumn�Ƿ���ڣ�������ֱ�ӷ���false)
bool EditModel(char *dbName,char* tableName, char* oldcolumn,TableMode tableMode);

//������(���ж����ݿ�ͱ�prename�Ƿ���ڣ�������ֱ�ӷ���false)
bool RenameTableFile(char* dbName,char* prename,char* latname);

//ɾ�������ж����ݿ�ͱ��Ƿ���ڣ�
bool DeleteTable(char* dbName,char *tableName);

//�鿴ĳ�ű��ֶε���Ŀ����������ʱ�ж���
//int CountColumns(char* dbName,char* tableName,char* columnName);//���columnName����tableMode���sFiledName

//��������(���жϱ��Ƿ����),���ݲ�ѯ������Fileds����һһ��Ӧ���һ����жϲ���������Ƿ�����������˺���ֻ�踺��������ݣ�
bool InsertData(char* dbName,char* tableName,vector<char*> newData);

//�������ݿ�����б������ж����ݿ��Ƿ����)
vector<char*> ShowTables(char* dbName);

//����һ�����ݿ���һ�ű�������ֶ�����ֻ����vector��һ��ѹ��һ���ֶ������ɣ�
vector<char*> ShowColumns(char* dbName,char* tableName);

//����һ�����ݿ���һ�ű�������ֶ�(�����ֶ������������ͣ�KEY��NULL��VALID��vector��һ��ѹ��һ�������ֶ����ݣ��м����ֶξ�ѹ���Σ�
vector<char*> ShowColumnDetail(char* dbName,char* tableName);

//�鿴ĳ�ű�������ֶΡ�
vector<char*> ShowFields(char* dbName,char* tableName);




//bool IsColumnExists(char* dbName,char *tableName,char *column);//�ж�һ�����ݿ���ָ������ֶ��Ƿ���ڣ��޸��ֶ�ʱ�ã�

