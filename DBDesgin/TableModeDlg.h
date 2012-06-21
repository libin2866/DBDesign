#pragma once
#include"stdafx.h"
#include"resource.h"
#include <vector>
#include "afxcmn.h"
using namespace std;
// TableModeDlg 对话框

class TableModeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TableModeDlg)

public:
	TableModeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TableModeDlg();

// 对话框数据
	enum { IDD = IDD_TABLETREEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	char title[15];
	vector<char*> mytables;//存放表
	//vector<vector<char*> >tables;
	BOOL OnInitDialog(void);
	void PostNcDestroy(void);
	//int counts;//表的数量
//	CTreeCtrl mTree;
	CTreeCtrl mTree;
};
