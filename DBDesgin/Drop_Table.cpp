#include"stdafx.h"
#include"Drop_Table.h"
#include"FileOperation.h"
/*Sample SQL:
DROP TABLE mytable IN myDB;

*/


CString DropTable(void){
	CString result;
	char tableName[15];
	char dbName[15];
	int i=3;
	///////////////����﷨///////////////////
	if(AWord[2].type!=identifier){
		result="'DROP TABLE' �������﷨����©�˱�����";//ȱ�ٱ���
		return result;
	}
	
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

		///////////////�ļ�����///////////////////
	strcpy(tableName,AWord[2].word);//������֣���ȷ����治���ڣ�������ֱ�ӷ���
	
	////////////Ԥ����������Ĳ���//////////////
	if(!DeleteTable(dbName,tableName)){//
		result="�޷�ɾ������ȷ�ϸñ��Ƿ����!";
		return result;

	}
	result="�����ɹ���";
	return result;



}