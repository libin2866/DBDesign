#pragma once
#include"stdafx.h"
#include"resource.h"
#include<vector>
#include "afxcmn.h"
using namespace std;
// TableDlg �Ի���

class TableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TableDlg)

public:
	TableDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TableDlg();

// �Ի�������
	enum { IDD = IDD_TABLEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void PostNcDestroy(void);
	BOOL OnInitDialog(void);
		char title[15];
	//vector<char*> tables;//
	//vector<vector<char*> >tables;
	vector<vector<char*> >returnData;//��������
	CListCtrl mTable;
	afx_msg void OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
