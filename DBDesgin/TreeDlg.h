#pragma once
#include"stdafx.h"
#include"resource.h"
#include <vector>
#include "afxcmn.h"
using namespace std;
// TreeDlg �Ի���

class TreeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TreeDlg)

public:
	TreeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TreeDlg();

// �Ի�������
	enum { IDD = IDD_TREEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	char title[15];
	//vector<char*> tables;//��ű�
	vector<vector<char*> >tables;
	BOOL OnInitDialog(void);
	void PostNcDestroy(void);
	int counts;//�������
	CTreeCtrl mTree;
};
