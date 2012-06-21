#pragma once
#include"stdafx.h"
#include"resource.h"
#include<vector>
using namespace std;
// TableDlg 对话框

class TableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TableDlg)

public:
	TableDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TableDlg();

// 对话框数据
	enum { IDD = IDD_TABLEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void PostNcDestroy(void);
	BOOL OnInitDialog(void);
		char title[15];
	//vector<char*> tables;//存放表
	vector<vector<char*> >tables;

};
