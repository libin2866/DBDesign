#include"stdafx.h"
#include"SELECT.h"
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
	if(AWord[1].type!=times){//������*,ѡ��ȫ��
			do{
			i++;
			if(AWord[i].type==identifier){//��ʶ���������ж����ִ����Ӧ����
				////////////��Ӧ�Ĳ���///////////////////////
				i++;
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
			i++;
		}else{
			result="SQL������ȱ�ٱ���߶���','?";
			return result;
		}
	 }while(AWord[i].type==comma);//select xxx from a,b,c WHERE ����a,b,c��Ҫһ��ѭ��

	if(AWord[i].type!=wheresym){
		if(AWord[i].type==semicolon){//û��where��������ֱ�ӽ���
				////////////////////////////������Բ��뵥���ѯ�Ĳ���,
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
					//////////////////table1.id1=���������� ��������в���
					i++;
					if(AWord[i].type!=identifier){
						result="SQL���������Ӳ�ѯ'='��ȱ�ٱ���?";
						return result;
					}
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
					}//////////////////table1.id1=table2.id2���������� ��������в���
					i++;
				}//period
				if(AWord[i].type==geql||AWord[i].type==eql||AWord[i].type==leql||AWord[i].type==lss||AWord[i].type==gtr){//�߼�����
					///////////////////////
					i++;
					///////////////////

				}



			}//identifier1
			else{
				result="SQL������WHERE��ȱ�ٱ���������?";
						return result;
			}

		}while(AWord[i].type==andsym);

	}//wheresym





	result="�������";
	return result;

}