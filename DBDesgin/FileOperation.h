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

//���±��е����ݣ�����conditionColumn��conditionȷ��������¼Ҫ�ģ�Ȼ���ڸü�¼��destColumnд��dest����.(���������ң�
bool UpdateData(char* dbName,char* tableName,char* conditionColumn,char* condition,char* destColumn,char *dest);

//ɾ�����е�����(��������������������¼)
bool DeleteData(char* dbName,char* tableName,char* conditionColumn,char* condition);


//bool IsColumnExists(char* dbName,char *tableName,char *column);//�ж�һ�����ݿ���ָ������ֶ��Ƿ���ڣ��޸��ֶ�ʱ�ã�

///////////////////////////��ѯ��ؽӿ�//////////////////////////////////
//����column�е�condition�����ҵ���ȫ��������ݣ���SELECT *�е�*��
/*�˴���type ����Ҫ����-1:������ 0:���� 1:С�� 2:С�ڵ���  3:���� 4:���ڵ��� (�������Ȳ�����) 
type=-1ʱ column��conditionΪ�գ����ؿ���
*/
vector<vector<char*>>  SelectAllData(char*dbName,char*tableName,char*column,char*condition,int type);
	
//���Ҳ�������SELECT table1,table2,....����*�ţ���table1,table2�����vector�Ǹ�����destColumn��
//type=-1 ʱ ��ʾû��where���� ֱ�ӷ���ȫ�����
//�˴���type ����Ҫ����-1:������ 0:���� 1:С�� 2:С�ڵ���  3:���� 4:���ڵ��� (�������Ȳ�����)
vector<vector<char*>> SelectPartData(char*dbName,char*tableName,char*column,char*condition,vector<char*>destColumn,int type);

/**���Կ��ǽ���һ����ʽ������view���ļ��������һ���̶��ģ����Թ��Ժ󷽱���ʵĵط�
����Ƕ�����������ӣ��� WHERE table1.column1=table2.column2
*/
char* ConTable(char*dbName,char*table1,char* table2,char* column1,char*  column2);