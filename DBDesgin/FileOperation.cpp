//
//  file_connect.cpp
//  Database
//
//  Created by Zellos on 6/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include"stdafx.h"
#include"FileOperation.h"
#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <fstream>
#include <cctype>
#include <sstream>

using namespace std;

class column_model{
    public:
    string column_name;
    short var_Type;         //1=int,2=char,3=Datetime
    short length;
    bitset<8> property;     //0 primary 1 null unique binary unsigned zerofill auto_increasement 8 valid;
    vector<string> key;
    column_model(){        
    }
    column_model(string name){
        this->column_name=name;
    }
	string return_property(){
		string temp;
		if(this->property[0]==1) temp+="key  ";
		if(this->property[1]==1) temp+="null  ";
		if(this->property[7]==1) temp+="valid  ";
		return temp;
	}
	string return_type(){
		if(this->var_Type==1)return "int";
		else if(this->var_Type==2) return "varchar";
		else if(this->var_Type==3) return "Datetime";
		return " ";
	}
    void setproperty(string proerty_name,bool tf){
        if (proerty_name=="primary") {
            this->property[0]=tf;
        }
        else if (proerty_name=="null") {
            this->property[1]=tf;
        }
        else if (proerty_name=="unique") {
            this->property[2]=tf;
        }
        else if (proerty_name=="binary") {
            this->property[3]=tf;
        }
        else if (proerty_name=="unsigned") {
            this->property[4]=tf;
        }
        else if (proerty_name=="zerofill") {
            this->property[5]=tf;
        }
        else if (proerty_name=="auto_increasement") {
            this->property[6]=tf;
        }
		else if(proerty_name=="valid"){
			this->property[7]=tf;
		}
    }
    bool insert_key(string input_key){
        short point_flag=0;
        if (this->length==0) {
            return false;
        }
        if (this->var_Type==1) {
            for (string::iterator key_iter=input_key.begin();key_iter!=input_key.end(); key_iter++) {
                if(!isdigit(*key_iter)){
                    /*if (*key_iter=='.'&&point_flag==0) {
                     point_flag=1;
                     }
                     else{
                     return false;
                     }*/
                    return false;
                }
            }
        }
        else if(this->var_Type==2){
            
        }
        else if(this->var_Type==3){
            
        }
        else{
            return false;
        }
        if(input_key.size()>this->length){
            input_key.erase(this->length+point_flag,input_key.size());
        }
        this->key.push_back(input_key);
        return true;
    }
    bool insert_key(string input_key,vector<string>::size_type pos){
        short point_flag=0;
        if (this->length==0) {
            return false;
        }
        if (this->var_Type==1) {
            for (string::iterator key_iter=input_key.begin();key_iter!=input_key.end(); key_iter++) {
                if(!isdigit(*key_iter)){
                    /*if (*key_iter=='.'&&point_flag==0) {
                        point_flag=1;
                    }
                    else{
                        return false;
                    }*/
                    return false;
                }
            }
        }
        else if(this->var_Type==2){
            
        }
        else if(this->var_Type==3){
            
        }
        else{
            return false;
        }
        if(input_key.size()>this->length){
            input_key.erase(this->length+point_flag,input_key.size());
        }
        vector<string>::iterator insert_pos=this->key.begin();
        for (int i=0; i<pos; i++) {
            insert_pos++;
            if(insert_pos==this->key.end()) return false;
        }
        this->key.insert(insert_pos,1,input_key);
        return true;
    }
    bool delete_key(vector<string>::size_type pos){
        vector<string>::iterator del_iter=this->key.begin();
        if (this->key.size()<pos) {
            return false;
        }
        for (int i=0; i<pos; i++) del_iter++;
        this->key.erase(del_iter);
        return false;
    }
    bool update_key(string update_key,vector<string>::size_type pos){
        short point_flag=0;
        if (this->length==0) {
            return false;
        }
        if (this->var_Type==1) {
            for (string::iterator key_iter=update_key.begin();key_iter!=update_key.end(); key_iter++) {
                if(!isdigit(*key_iter)){
                    /*if (*key_iter=='.'&&point_flag==0) {
                     point_flag=1;
                     }
                     else{
                     return false;
                     }*/
                    return false;
                }
            }
        }
        else if(this->var_Type==2){
            
        }
        else if(this->var_Type==3){
            
        }
        else{
            return false;
        }
        if(update_key.size()>this->length){
            update_key.erase(this->length+point_flag,update_key.size());
        }
        vector<string>::iterator insert_pos=this->key.begin();
        for (int i=0; i<pos; i++) {
            insert_pos++;
            if(insert_pos==this->key.end()) return false;
        }
        *insert_pos=update_key;
        return true;
    }
    void test_out(){
        for (vector<string>::iterator i=this->key.begin() ; i!=this->key.end(); i++) {
            cout << *i << endl;
        }
    }
};

class table_model{
    public:
    string table_name;
    vector<column_model> table;
    table_model(string name){
        this->table_name=name;
    }
    bool create_column(string col_name){
        for (vector<column_model>::iterator col_iter=this->table.begin(); col_iter!=this->table.end(); col_iter++) {
            if (col_iter->column_name==col_name) {
                return false; // �ظ�����
            }
        }
        column_model new_cm(col_name);
        table.push_back(new_cm);
        return true;
    }
    bool delete_column(string col_name){
        for (vector<column_model>::iterator col_iter=this->table.begin(); col_iter!=this->table.end(); col_iter++) {
            if (col_iter->column_name==col_name) {
                table.erase(col_iter);
                return true;
            }
        }
        return false;
    }
    bool alter_key(vector<column_model>::size_type col_num,vector<string>::size_type pos,string key){
        if (this->table.size()<col_num) {
            return false;
        }
        else{
            vector<column_model>::iterator col_iter=this->table.begin();
            for (int i=0; i<col_num; i++) {
                col_iter++;
                if (col_iter==table.end()) {
                    return false;
                }
            }
            if(col_iter->update_key(key,pos)){
                return true;
            }
            else return false;
        }
    }
    bool alter_key(string col_name,vector<string>::size_type pos,string key){
        vector<column_model>::size_type col_num=0;
        for (vector<column_model>::iterator col_iter=this->table.begin(); col_iter!=this->table.end(); col_iter++) {
            if (col_iter->column_name==col_name) break;
            col_num++;
        }
        return this->alter_key(col_num, pos, key);
    }
};

class database_File{
    public:
    string Db_name;
    fstream DB_File_Head;
    fstream DB_File_Data;
    vector<table_model> table_list;
    database_File(string db_name){
        string dat_file_name="\\Database\\";
        string dbf_file_name="\\Database\\";
        this->Db_name=db_name;
        db_name+=".dat";
        dat_file_name+=db_name;
        db_name.erase(db_name.end()-4,db_name.end());
        db_name+=".dbf";
        dbf_file_name+=db_name;
        DB_File_Data.open(dat_file_name.c_str(),fstream::in|fstream::binary);
        DB_File_Head.open(dbf_file_name.c_str(),fstream::in);
        if(!DB_File_Data||!DB_File_Head){
        }
        else{
            this->read_db();
        }
		DB_File_Head.close();
        DB_File_Data.close();
        DB_File_Data.open(dat_file_name.c_str(),fstream::out|fstream::binary|fstream::trunc);
        DB_File_Head.open(dbf_file_name.c_str(),fstream::out|fstream::trunc);
    }
    void write(){
        vector<table_model>::iterator tab_iter;
        vector<column_model>::iterator col_iter;
        vector<string>::iterator key_iter;
        DB_File_Head << Db_name.c_str() << ' ' << table_list.size() << endl;
        for (tab_iter=this->table_list.begin(); tab_iter!=this->table_list.end(); tab_iter++) {
            DB_File_Head << tab_iter->table_name << ' ' << tab_iter->table.size() << endl;
            for (col_iter=tab_iter->table.begin(); col_iter!=tab_iter->table.end(); col_iter++) {
                for (key_iter=col_iter->key.begin(); key_iter!=col_iter->key.end(); key_iter++) {
                    DB_File_Data.write(key_iter->c_str(), col_iter->length);
                }
                DB_File_Head << col_iter->column_name << ' ';
                DB_File_Head << col_iter->var_Type << ' ';
                DB_File_Head << col_iter->length << ' ';
                DB_File_Head << col_iter->key.size() << ' ';
                DB_File_Head << col_iter->property;
                DB_File_Head << endl;
            }
        }
    }
    void read_db(){
        int table_list_size,table_size,column_size;
        string temp_str;
        table_model temp_tm("temp");
        column_model temp_cm;
        DB_File_Head.seekg(fstream::beg);
        DB_File_Data.seekg(fstream::beg);
        DB_File_Head >> this->Db_name;
        DB_File_Head >> table_list_size;
        for (int i=0; i<table_list_size; i++) {
            DB_File_Head.ignore();
            DB_File_Head >> temp_tm.table_name;
            DB_File_Head >> table_size;
            for (int j=0; j<table_size; j++) {
                DB_File_Head >> temp_cm.column_name;
                DB_File_Head >> temp_cm.var_Type;
                DB_File_Head >> temp_cm.length;
                DB_File_Head >> column_size;
                DB_File_Head >> temp_cm.property;
                char *temp_ch=(char *)malloc(temp_cm.length);
                for(int k=0; k<column_size ;k++){
                    DB_File_Data.read(temp_ch,temp_cm.length);
                    temp_cm.key.push_back(temp_ch);
                }
                temp_tm.table.push_back(temp_cm);
                temp_cm.key.erase(temp_cm.key.begin(),temp_cm.key.end());
            }
            this->table_list.push_back(temp_tm);
            temp_tm.table.erase(temp_tm.table.begin(),temp_tm.table.end());
        }
    }
    void connect_out(){
        this->DB_File_Head.close();
        this->DB_File_Data.close();
    }
};


vector<database_File> DB_File_List;


bool InitDataBase(char *dbName){
	string temp_dbname;
	temp_dbname=dbName;
	vector<database_File>::iterator DB_iter;
	for(DB_iter=DB_File_List.begin();DB_iter!=DB_File_List.end();DB_iter++){
		if(DB_iter->Db_name==temp_dbname) return false;
	}
	database_File new_DB(temp_dbname);
	//DB_File_List.push_back(new_DB);



	//CString ext=".dbf";
	//CString datext=".dat";
	//CString pre="\\Database\\";
 //   CString dbfFile=pre+dbName+ext;
	//CString datFile=pre+dbName+datext;
	//CFileStatus status;
	//
	//if(!CFile::GetStatus(dbfFile,status)) // status function
	//{//���ļ�
	//	CFile mFile(dbfFile,CFile::modeCreate | CFile::modeWrite);
	//	//д�������Ϣ?
	//	//mFile.Write("NULL",strlen("NULL"));
	//	
	//}
	//if(!CFile::GetStatus(datFile,status)) // status function
	//{//���ļ�
	//	CFile mFile(datFile,CFile::modeCreate | CFile::modeWrite);
	//	//д�������Ϣ?
	//	//mFile.Write("NULL",strlen("NULL"));
	//	
	//}


	return true;
};

bool IsTableExists(char*dbName,char* tableName){
	string temp_dbname,temp_tableName;
	temp_dbname=dbName;
	temp_tableName=tableName;
	vector<database_File>::iterator DB_iter;
	for(DB_iter=DB_File_List.begin();DB_iter!=DB_File_List.end();DB_iter++){
		if(DB_iter->Db_name==temp_dbname){
			vector<table_model>::iterator tab_iter;
			for(tab_iter=DB_iter->table_list.begin();tab_iter!=DB_iter->table_list.end();tab_iter++){
				if(tab_iter->table_name==temp_tableName) return true;
			}
			return false;
		};
	}
	return false;
};

//������д����������ݿ⣬�Ȳ�д����ֶΣ�
bool BuildTable(char* dbName,char* tableName ,int columns ){
	string temp_dbname,temp_tableName;
	temp_dbname=dbName;
	temp_tableName=tableName;
	vector<database_File>::iterator DB_iter;
	for(DB_iter=DB_File_List.begin();DB_iter!=DB_File_List.end();DB_iter++){
		if(DB_iter->Db_name==temp_dbname){
			table_model new_tab(temp_tableName);
			DB_iter->table_list.push_back(new_tab);
			return true;
		};
	}
	return false;
};

//д����ֶ�
bool BuildModel(char* dbName,char* tableName,TableMode tableMode){

	return true;
};

//�޸ı�(���ж����ݿ���ֶ�oldcolumn�Ƿ���ڣ�������ֱ�ӷ���false)
bool EditModel(char *dbName,char* tableName, char* oldcolumn,TableMode tableMode){
	string temp_dbname,temp_Name;
	temp_dbname=dbName;
	temp_Name=tableName;;
	vector<database_File>::iterator DB_iter;
	for(DB_iter=DB_File_List.begin();DB_iter!=DB_File_List.end();DB_iter++){
		if(DB_iter->Db_name==temp_dbname){
			vector<table_model>::iterator tab_iter;
			for(tab_iter=DB_iter->table_list.begin();tab_iter!=DB_iter->table_list.end();tab_iter++){
				if(tab_iter->table_name==temp_Name){
					temp_Name=oldcolumn;
					vector<column_model>::iterator col_iter;
					for(col_iter=tab_iter->table.begin();col_iter!=tab_iter->table.end();col_iter++){
						if(col_iter->column_name==temp_Name){
							temp_Name=tableMode.sType;
							if(temp_Name=="int") col_iter->var_Type=1;
							else if (temp_Name=="varchar") col_iter->var_Type=2;
							else if (temp_Name=="datetime") col_iter->var_Type=3;
							else return false;
							col_iter->column_name=tableMode.sFiledName;
							if(tableMode.bKey)col_iter->setproperty("primary",true);
							else col_iter->setproperty("primary",false);
							if(tableMode.bNullFlag) col_iter->setproperty("null",true);
							else col_iter->setproperty("null",false);
							if(tableMode.bValidFlag) col_iter->setproperty("valid",true);
							else col_iter->setproperty("valid",false);
							return true;
						}
					}
					return false;
				}
			}
			return false;
		};
	}
	return false;
};

//������(���ж����ݿ�ͱ�prename�Ƿ���ڣ�������ֱ�ӷ���false)
bool RenameTableFile(char* dbName,char* prename,char* latname){
	string temp_dbname,temp_tableName;
	temp_dbname=dbName;
	temp_tableName=prename;;
	vector<database_File>::iterator DB_iter;
	for(DB_iter=DB_File_List.begin();DB_iter!=DB_File_List.end();DB_iter++){
		if(DB_iter->Db_name==temp_dbname){
			vector<table_model>::iterator tab_iter;
			for(tab_iter=DB_iter->table_list.begin();tab_iter!=DB_iter->table_list.end();tab_iter++){
				if(tab_iter->table_name==temp_tableName){
					temp_tableName=latname;
					tab_iter->table_name=temp_tableName;
					return true;
				}
			}
			return false;
		};
	}
	return false;
};

//ɾ�������ж����ݿ�ͱ��Ƿ���ڣ�
bool DeleteTable(char* dbName,char *tableName){
	string temp_dbname,temp_tableName;
	temp_dbname=dbName;
	temp_tableName=tableName;
	vector<database_File>::iterator DB_iter;
	for(DB_iter=DB_File_List.begin();DB_iter!=DB_File_List.end();DB_iter++){
		if(DB_iter->Db_name==temp_dbname){
			vector<table_model>::iterator tab_iter;
			for(tab_iter=DB_iter->table_list.begin();tab_iter!=DB_iter->table_list.end();tab_iter++){
				if(tab_iter->table_name==temp_tableName){
					DB_iter->table_list.erase(tab_iter);
					return true;
				};
			}
			return false;
		};
	}
	return false;
};

//�鿴ĳ�ű��ֶε���Ŀ����������ʱ�ж���
int CountColumns(char* dbName,char* tableName){
	string temp_dbname,temp_tableName;
	temp_dbname=dbName;
	temp_tableName=tableName;
	vector<database_File>::iterator DB_iter;
	for(DB_iter=DB_File_List.begin();DB_iter!=DB_File_List.end();DB_iter++){
		if(DB_iter->Db_name==temp_dbname){
			vector<table_model>::iterator tab_iter;
			for(tab_iter=DB_iter->table_list.begin();tab_iter!=DB_iter->table_list.end();tab_iter++){
				if(tab_iter->table_name==temp_tableName){
					return tab_iter->table.size();
				};
			}
			return 0;
		};
	}
	return 0;
};//���columnName����tableMode���sFiledName

//��������(���жϱ��Ƿ����),���ݲ�ѯ������Fileds����һһ��Ӧ���һ����жϲ���������Ƿ�����������˺���ֻ�踺��������ݣ�
bool InsertData(char* dbName,char* tableName,vector<char*> newData){
	string temp_dbname,temp_tableName,temp_str;
	temp_dbname=dbName;
	vector<database_File>::iterator DB_iter;
	for(DB_iter=DB_File_List.begin();DB_iter!=DB_File_List.end();DB_iter++){
		if(DB_iter->Db_name==temp_dbname){
			vector<table_model>::iterator tab_iter;
			for(tab_iter=DB_iter->table_list.begin();tab_iter!=DB_iter->table_list.end();tab_iter++){
				if(tab_iter->table_name==temp_tableName){
					vector<char*>::iterator inst_key_iter=newData.begin();
					vector<column_model>::iterator key_iter=tab_iter->table.begin();
					for(;(inst_key_iter!=newData.begin())&&(key_iter!=tab_iter->table.end());inst_key_iter++,key_iter++){
						temp_str=*inst_key_iter;
						key_iter->insert_key(temp_str);
					}
					return true;
				};
			}
			return false;
		};
	}
	return false;
};

//�������ݿ�����б������ж����ݿ��Ƿ����)
vector<char*> ShowTables(char* dbName){
	string temp_dbname,temp_tableName;
	char *temp;
	vector<char*> ret_temp;
	temp_dbname=dbName;
	vector<database_File>::iterator DB_iter;
	for(DB_iter=DB_File_List.begin();DB_iter!=DB_File_List.end();DB_iter++){
		if(DB_iter->Db_name==temp_dbname){
			vector<table_model>::iterator tab_iter;
			for(tab_iter=DB_iter->table_list.begin();tab_iter!=DB_iter->table_list.end();tab_iter++){
				temp=(char *)tab_iter->table_name.c_str();
				ret_temp.push_back(temp);
			}
			return ret_temp;
		};
	}
	return ret_temp;
};

//����һ�����ݿ���һ�ű�������ֶ�����ֻ����vector��һ��ѹ��һ���ֶ������ɣ�
vector<char*> ShowColumns(char* dbName,char* tableName){
	vector<char *> ret_temp;
	char *temp=(char *)malloc(15);
	string temp_dbname,temp_Name;
	temp_dbname=dbName;
	temp_Name=tableName;;
	vector<database_File>::iterator DB_iter;
	for(DB_iter=DB_File_List.begin();DB_iter!=DB_File_List.end();DB_iter++){
		if(DB_iter->Db_name==temp_dbname){
			vector<table_model>::iterator tab_iter;
			for(tab_iter=DB_iter->table_list.begin();tab_iter!=DB_iter->table_list.end();tab_iter++){
				if(tab_iter->table_name==temp_Name){
					vector<column_model>::iterator col_iter;
					for(col_iter=tab_iter->table.begin();col_iter!=tab_iter->table.end();col_iter++){
						temp=(char *)col_iter->column_name.c_str();
						ret_temp.push_back(temp);
					}
					return ret_temp;
				}
			}
			return ret_temp;
		};
	}
	return ret_temp;
};


//����һ�����ݿ���һ�ű�������ֶ�(�����ֶ������������ͣ�KEY��NULL��VALID��vector��һ��ѹ��һ�������ֶ����ݣ��м����ֶξ�ѹ���Σ�
vector<char*> ShowColumnDetail(char* dbName,char* tableName){
	vector<char *> ret_temp;
	char *temp=(char *)malloc(15);
	string temp_dbname,temp_Name;
	temp_dbname=dbName;
	temp_Name=tableName;;
	vector<database_File>::iterator DB_iter;
	for(DB_iter=DB_File_List.begin();DB_iter!=DB_File_List.end();DB_iter++){
		if(DB_iter->Db_name==temp_dbname){
			vector<table_model>::iterator tab_iter;
			for(tab_iter=DB_iter->table_list.begin();tab_iter!=DB_iter->table_list.end();tab_iter++){
				if(tab_iter->table_name==temp_Name){
					vector<column_model>::iterator col_iter;
					string temp_str;
					for(col_iter=tab_iter->table.begin();col_iter!=tab_iter->table.end();col_iter++){
						temp_str=col_iter->column_name+"  "+col_iter->return_type()+"  "+col_iter->return_property();
						temp=(char *)temp_str.c_str();
						ret_temp.push_back(temp);
					}
					return ret_temp;
				}
			}
			return ret_temp;
		};
	}
	return ret_temp;
};

//�鿴ĳ�ű�������ֶΡ�
//vector<char*> ShowFields(char* dbName,char* tableName);

//���±��е����ݣ�����conditionColumn��conditionȷ��������¼Ҫ�ģ�Ȼ���ڸü�¼��destColumnд��dest����.(���������ң�
bool UpdateData(char* dbName,char* tableName,char* conditionColumn,char* condition,char* destColumn,char *dest){
	return true;
}

//ɾ�����е�����(��������������������¼)
bool DeleteData(char* dbName,char* tableName,char* conditionColumn,char* condition){
	return true;

}

//�ж����ݿ��Ƿ����
bool IsDBExists(char* dbName){
	CString pre="\\Database\\";
	CString ext=".dbf";
    CString db=pre+dbName+ext;
	
	CFileStatus status;
	if(!CFile::GetStatus(db,status)) // status function
	{//���ļ�
			
		return false;
	}
	return true;
	return true;
}

///////////////////////////��ѯ��ؽӿ�//////////////////////////////////
//����column�е�condition�����ҵ���ȫ��������ݣ���SELECT *�е�*��
/*�˴���type ����Ҫ����-1:������ 0:���� 1:С�� 2:С�ڵ���  3:���� 4:���ڵ��� (�������Ȳ�����) 
type=-1ʱ column��conditionΪ�գ����ؿ���
*/
vector<vector<char*>>  SelectAllData(char*dbName,char*tableName,char*column,char*condition,int type){
	vector<vector<char*>> a;
	return a;
}
	
//���Ҳ�������SELECT table1,table2,....����*�ţ���table1,table2�����vector�Ǹ�����destColumn��
//type=-1 ʱ ��ʾû��where���� ֱ�ӷ���ȫ�����
//�˴���type ����Ҫ����-1:������ 0:���� 1:С�� 2:С�ڵ���  3:���� 4:���ڵ��� (�������Ȳ�����)
vector<vector<char*>> SelectPartData(char*dbName,char*tableName,char*column,char*condition,vector<char*>destColumn,int type){
	vector<vector<char*>> a;
	return a;	
};

/**���Կ��ǽ���һ����ʽ������view���ļ��������һ���̶��ģ����Թ��Ժ󷽱���ʵĵط�
����Ƕ�����������ӣ��� WHERE table1.column1=table2.column2
*/
char* ConTable(char*dbName,char*table1,char* table2,char* column1,char*  column2){
	char* tableName="";
	return tableName;
};