#pragma once
#include"stdafx.h"
#include"resource.h"
#include <vector>
#include "afxcmn.h"
using namespace std;
// TableModeDlg �Ի���

class TableModeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TableModeDlg)

public:
	TableModeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TableModeDlg();

// �Ի�������
	enum { IDD = IDD_TABLETREEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	char title[15];
	vector<char*> mytables;//��ű�
	//vector<vector<char*> >tables;
	BOOL OnInitDialog(void);
	void PostNcDestroy(void);
	//int counts;//�������
//	CTreeCtrl mTree;
	CTreeCtrl mTree;
};
