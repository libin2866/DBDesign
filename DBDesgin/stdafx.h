
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持









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


////////////以下是对于SQL类型的定义///////////////////////
#define CREATE_TABLE 1
#define EDIT_TABLE 2
#define RENAME_TABLE 3
#define DROP_TABLE 4






//////////////词法分析////////////////

//保留字个数
#define reservednum 21   

#define getchdo if(-1==getch()) return -1
#define getsymdo if(-1==getsym()) return -1

enum symbol{
	createsym,editsym,renamesym,tablesym,dropsym,insertsym,deletesym,
	updatesym,selectsym,setsym,intosym,fromsym,insym,keysym,notkeysym,validsym,usesym,dbsym,
	numsym,	wheresym,thensym,nul,notnul,
	identifier,number,plus,minus,
	times,slash,eql,lss,leql,gtr,geql,lparen,
	rparen,comma,semicolon,period,
};

struct AnalysisWord{
	char word[15];//Store the word
	enum symbol type;//Store the type
	int  num;//Store the number of a num,if not a num,sets 0.
};

extern enum symbol sinsym[256];//ssym,单字符的符号值
extern enum symbol wordsym[reservednum];//wsym,保留字对应的符号值
 extern AnalysisWord AWord[255];//分析出来的内容
#include <iostream>
#include <tchar.h>
#pragma once 
// TODO: 在此处引用程序要求的附加头文件
#include<String.h>
//#define norw 25//关键字个数
#define charlength 10//符号最大长度
#define nmax 14//number的最大位数
#define symnum 32
#define levmax 3 //最大允许过程嵌套声明层数[0,levmax]
#define addmax 2047
//#define FAILED false;


