#include"stdafx.h"
#include"Insert_Into.h"
#include"FileOperation.h"
#include<vector>
using namespace std;
/*Sample SQL:

INSERT INTO mytable VALUES('test','9','2012-6-17')IN mydb;


*/


CString InsertInto(void){
	CString result;
	char tableName[15];
	char dbName[15];
	int i=4;
	int column;
	int c=0;


	if(AWord[2].type!=identifier){
		result="'INSERT INTO' �������﷨����©�˱�����";//ȱ�ٱ���
		return result;
	}
	if(AWord[3].type!=valuessym){
		result="'SQL������﷨����©��VALUES��";
		return result;
	}
	if(AWord[4].type!=lparen){
		result="'SQL������﷨����©��'('��";
		return result;
	}else{
		///////////////������Ȼ�ȡ�����Ϣ��Ȼ����ݱ�����������column////////////////////////////////
		column=0;//�����������Ŀ,��ֹ������ѭ��.Ҳ�м�������
		do{
			i++;
			if(AWord[i].type!=quote){
				result="'SQL������﷨����©�˲������߶���','��?";//ȱ�ٱ���
				return result;
			}
			i++;column++;
		}while(AWord[i].type==comma&&column<20);
	}
		
		
	if(AWord[i].type!=rparen){
		result="�����������Ի���ȱ��')'!";
		return result;
	}
	i++;
	strcpy(dbName,globalDB);//��¼ͨ�����ݿ⣬���û�� IN db�������ΪĬ�����ݿ�
	if(AWord[i].type==insym){//in XXX  xxxΪĿ�����ݿ�
		i++;
		if(AWord[i].type==identifier){
			strcpy(dbName,AWord[i].word);//��������ݿ������������ø�����ѡ��Ҫ���������ݿ⣬���жϸ����ݿ�治����//////////////�ļ�����
		}
		else{
		result="ȱ����Ҫ���������ݿ�!";
		return result;
		}
     i++;
	}
	///////////////////////
	if(dbName[0]==NULL) {
		result="����û��ѡ��Ҫ���������ݿ�!";
		return result;

	};////////////////
	
	if(AWord[i].type!=semicolon){
		result="ȱ��';'!";
		return result;
	}


	///////////////�ļ�����/////////////////////

	strcpy(tableName,AWord[2].word);//����

		///////////////������Ȼ�ȡ�����Ϣ��Ȼ����ݱ�����������column////////////////////////////////
	  i=5;
	  vector<char*> newData;
		while(column>0){
			newData.push_back(AWord[i].word);
			i++;column--;i++;
		}

	InsertData(dbName,tableName,newData);//��������

	result="�����ɹ���";
	return result;
}