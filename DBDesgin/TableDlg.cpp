// TableDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBDesgin.h"
#include "TableDlg.h"
#include "afxdialogex.h"


// TableDlg �Ի���

IMPLEMENT_DYNAMIC(TableDlg, CDialogEx)

TableDlg::TableDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(TableDlg::IDD, pParent)
{

}

TableDlg::~TableDlg()
{
}

void TableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TableDlg, CDialogEx)
END_MESSAGE_MAP()


// TableDlg ��Ϣ�������


BOOL TableDlg::OnInitDialog(void)
{

	CDialog::OnInitDialog();


	return 0;
}


void TableDlg::PostNcDestroy(void)
{
	CDialog::PostNcDestroy();
    delete this;
}