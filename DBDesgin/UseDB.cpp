#include"stdafx.h"
#include"UseDB.h"
#include <vector>
#include"resource.h"
using namespace std;

char globalDB[15];//����洢USE db;ִ��֮�� ��ΪĬ��Ҫ���������ݿ�
CString UseDB(void){

	CString result;
	char dbName[15];
	if(AWord[1].type!=identifier){
		result="'USE' �������﷨����©�����ݿ�����";//ȱ�����ݿ�����
		return result;
	}
	if(AWord[2].type!=semicolon){
		result="SQL������﷨����©�˷ֺţ�";//ȱ�ٷֺ�
		return result;
	}
	////////////////////////////////�ļ�����
	strcpy(dbName,AWord[1].word);//
	if(!IsDBExists(dbName))
	{
		result="�Բ��𣬸����ݿⲻ����";//�Ҳ������ݿ�
		return result;
	};
	strcpy(globalDB,dbName);//����Ϊȫ�ֱ���
	vector<vector<char*> >tables( 20, vector<char*>(0) );//��ű�
	//int total=tables.size;//��Ŀ
	/*FOR TEST DEMO*/
	//��ȡ��
	tables[0].push_back("MyTable0");
	tables[1].push_back("MyTable2");
	//��ȡ����ÿһ��
	tables[0].push_back("MySubTable1");
	tables[0].push_back("MySubTable2");
	tables[1].push_back("MySubTable3");
	tables[1].push_back("MySubTable4");
/*
	vector<char*> returntables=ShowTables(dbName);  
	for(int i=0;i<returntables.size();i++)
	{tables[i].push_back(returntables[i]);//�Ȱѱ����
	   vector<char*> returncolumns=ShowColumns(dbName,returntables[i]);
	  for(int j=0;j<returncolumns.size();j++){
		  tables[i].push_back(returncolumns[i]);
	  }//j
	}//i

	*/
	//vector< vector<char*> > Array( 20, vector<char*>(0) );

	//Array[0].push_back("MySubTable0");

	TreeDlg *tr1dlg=new TreeDlg;
	//tr1dlg.DoModal();
	tr1dlg->counts=2;
	tr1dlg->tables=tables;
	//tr1dlg->tables=returntables.size();
	strcpy(tr1dlg->title,dbName);
	tr1dlg->Create(IDD_TREEDIALOG);
	tr1dlg->ShowWindow(SW_SHOW);

	result="�����ɹ���";
	return result;
}