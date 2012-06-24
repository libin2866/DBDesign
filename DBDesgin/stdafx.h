
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#define SUCCESS true
#define SQLTYPE int


////////////�����Ƕ���SQL���͵Ķ���///////////////////////
#define CREATE_DB 0
#define CREATE_TABLE 1
#define EDIT_TABLE 2
#define RENAME_TABLE 3
#define DROP_TABLE 4
#define INSERT_INTO 5
#define DELETE_FROM		6
#define UPDATE 7
#define SELECT 8
#define USE_DB 9
#define DESC_TABLE 10
//////////////�ʷ�����////////////////

//�����ָ���
#define reservednum 28  

#define FIELD_NAME_LENGTH 15
#define getchdo if(-1==getch()) return -1
#define getsymdo if(-1==getsym()) return -1

enum symbol{
	empty,nul,createsym,editsym,renamesym,tablesym,dropsym,insertsym,deletesym,
	updatesym,selectsym,setsym,intosym,fromsym,insym,keysym,notkeysym,validsym,usesym,dbsym,
	numsym,	wheresym,notnul,valuessym,
	identifier,number,plus,minus,andsym,descsym,
	times,slash,eql,lss,leql,gtr,geql,lparen,
	rparen,comma,semicolon,period,quote,
	varcharsym,datetimesym,intsym,invalidsym,
};

struct AnalysisWord{
	char word[15];//Store the word
	enum symbol type;//Store the type
	int  num;//Store the number of a num,if not a num,sets 0.
};

typedef struct{
	char sFiledName[FIELD_NAME_LENGTH];//�ֶ���
	char sType[10];//�ֶ�����
	//int iSize;//�ֳ�
	bool bKey;//�Ƿ�Ϊkey 0Ϊ��key 1Ϊkey
	bool bNullFlag;//�Ƿ�����Ϊ��0Ϊ��null 1Ϊnull
	bool bValidFlag;//�Ƿ���Ч
}TableMode,*PTableMode;

extern enum symbol sinsym[256];//ssym,���ַ��ķ���ֵ
extern enum symbol wordsym[reservednum];//wsym,�����ֶ�Ӧ�ķ���ֵ
 extern AnalysisWord AWord[255];//��������������
#include <iostream>
#include <tchar.h>
#pragma once 
// TODO: �ڴ˴����ó���Ҫ��ĸ���ͷ�ļ�
#include<String.h>
//#define norw 25//�ؼ��ָ���
#define charlength 15//������󳤶�
#define nmax 14//number�����λ��
#define symnum 32
#define levmax 3 //����������Ƕ����������[0,levmax]
#define addmax 2047
//#define FAILED false;

 extern char globalDB[15];//����洢USE db;ִ��֮�� ��ΪĬ��Ҫ���������ݿ�

 
