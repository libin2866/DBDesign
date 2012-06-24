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
	int tableNum=0;//��¼select���� from �ı�ĸ���
	int columnNum=0;//��¼select �ֶθ���
	int statement;//ͳ�����������ĸ���
	int conn=0;//���Ӳ�ѯ�����Ӹ���
	//CString tempcon;
	char condition[15];//�߼�������
	int type;
	vector<vector<char*> >returnData( 20, vector<char*>(0) );//�洢���ص�����
	vector<char*> destColumn;//��ʾselect column1,column2...�е���Щcolumns
	vector<char*> connTable;//����Ѿ����ӵı�

	strcpy(dbName,globalDB);//��¼ͨ�����ݿ⣬���û�� IN db�������ΪĬ�����ݿ�

		if(dbName[0]==NULL) {
		result="����û��ѡ��Ҫ���������ݿ�,������USE���ѡ��!";
		return result;

	};////////////////

	if(AWord[1].type!=times){//����*,��ѡ��ȫ������ʾ������Ϣ
			do{
			i++;
			if(AWord[i].type==identifier){//��ʶ���������ж����ִ����Ӧ����
				////////////��Ӧ�Ĳ���///////////////////////
				i++;columnNum++;//�ֶθ�����һ
			}else{
				result="SQL������ȱ�ٱ�ʶ�����߶���','?";
				return result;
			}

		}while(AWord[i].type==comma);//select a,b,c from ����a,b,c��Ҫһ��ѭ��

	}
	//i++;
	if(AWord[i].type!=fromsym){
		result="SQL������ȱ��FROM?";
		return result;
	}
	do{
		i++;
		if(AWord[i].type==identifier){//��ʶ���������ж����ִ����Ӧ���� �����Ӧ��
			////////////��Ӧ�Ĳ���///////////////////////
			destColumn.push_back(AWord[i].word);
			i++;tableNum++;//Ҫ�����ı����Ŀ����
		}else{
			result="SQL������ȱ�ٱ���߶���','?";
			return result;
		}
	 }while(AWord[i].type==comma);//select xxx from a,b,c WHERE ����a,b,c��Ҫһ��ѭ��

	if(AWord[i].type!=wheresym){
		if(AWord[i].type==semicolon){//û��where��������ֱ�ӽ���
				////////////////////////////������Բ��뵥���ѯ�Ĳ���,

			//select * from mytable;
			if(AWord[1].type==times){
				type=-1;//-1��ʾ��where���֡�
				char *column="";
				char *condition="";
				returnData=SelectAllData(dbName,tableName,column,condition,type);

			}else{//select table1,table2...from mytable;
				char *column="";
				char *condition="";
				type=-1;//-1��ʾ��where���֡�
				returnData=SelectPartData(dbName,tableName,column,condition,destColumn,type);
			}
				TableDlg  *tr1dlg=new TableDlg;
				tr1dlg->returnData=returnData;
				strcpy(tr1dlg->title,dbName);
				tr1dlg->Create(IDD_TREEDIALOG);
				tr1dlg->ShowWindow(SW_SHOW);

				result="�������";
				return result;
			}//semicolon
		else{
		result="SQL������ȱ��WHERE?";
		return result;
		}
	}else{
		do{
			i++;
			if(AWord[i].type==identifier){//����Ϊ���� table.id=table2.id Ҳ����Ϊ����
				//////////////////////////////////??
				
				i++;
				if(AWord[i].type==period){//�������Ӳ�ѯ
					strcpy(table1,AWord[i-1].word);//���ݱ���  ����һ��
					i++;
					if(AWord[i].type!=identifier){
						result="SQL������.��ȱ�ٶ�Ӧ������?";
						return result;
					}
					
					//////////////////table1.id1���������� ��������в���
					i++;
					if(AWord[i].type!=eql){
						result="SQL���������Ӳ�ѯȱ��'='��?";
						return result;
					}
					strcpy(column1,AWord[i].word);//
					//////////////////table1.id1=���������� ��������в���
					i++;
					if(AWord[i].type!=identifier){
						result="SQL���������Ӳ�ѯ'='��ȱ�ٱ���?";
						return result;
					}
					strcpy(table2,AWord[i].word);//���ݱ���
					//////////////////table1.id1=table2���������� ��������в���
					i++;
					if(AWord[i].type!=period){
						result="SQL���������Ӳ�ѯȱ��'.'?";
						return result;
					}
					//////////////////table1.id1=table2.���������� ��������в���
					i++;
					if(AWord[i].type!=identifier){
						result="SQL���������Ӳ�ѯ'.'��ȱ������?";
						return result;
					}
					strcpy(column2,AWord[i].word);
					//////////////////table1.id1=table2.id2���������� ��������в���
					connTable.push_back(ConTable(dbName,table1,table2,column1,column2));//����������ӱ�����������������������������������������������������������������
					conn++;//����һ�����ӵı��
					i++;
				}//period

				if(AWord[i].type==geql||AWord[i].type==eql||AWord[i].type==leql||AWord[i].type==lss||AWord[i].type==gtr){//�߼�����
					///////////////////////
						strcpy(column1,AWord[i-1].word);//���ݱ���  ����һ��
						if(AWord[i].type==eql) type=0;
						if(AWord[i].type==lss) type=1;
						if(AWord[i].type==leql) type=2;
						if(AWord[i].type==gtr) type=3;
						if(AWord[i].type==geql) type=4;
						//if(AWord[i].type==lss) type=5;
					i++;
					if(AWord[i].type!=quote){
						result="SQL�������߼��������ȱ�پ�������?";
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
				result="SQL������WHERE��ȱ�ٱ���������?";
						return result;
			}

		}while(AWord[i].type==andsym);

	}//wheresym

	//�������

	//SELECT username FROM mytable WHERE age>'10';
	//////////////ע�⣺���в��ܳ���û�г�ʼ����ֵ����Ϊ��ֵ�����ؿհ��ַ������ո�Ҳ�ɡ�
	returnData[0].push_back("MyTable0");
	returnData[1].push_back("MyTable1");
	returnData[2].push_back("MyTable2");
	//��ȡ����ÿһ��
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

	result="�������!";
	return result;

}