// TableDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DBDesgin.h"
#include "TableDlg.h"
#include "afxdialogex.h"


// TableDlg 对话框

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


// TableDlg 消息处理程序


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