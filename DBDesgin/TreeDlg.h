#pragma once
#include"stdafx.h"
#include"resource.h"
#include <vector>
#include "afxcmn.h"
using namespace std;
// TreeDlg 对话框

class TreeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TreeDlg)

public:
	TreeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TreeDlg();

// 对话框数据
	enum { IDD = IDD_TREEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	char title[15];
	//vector<char*> tables;//存放表
	vector<vector<char*> >tables;
	BOOL OnInitDialog(void);
	void PostNcDestroy(void);
	int counts;//表的数量
	CTreeCtrl mTree;
};
