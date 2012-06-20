// TableModeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DBDesgin.h"
#include "TableModeDlg.h"
#include "afxdialogex.h"


// TableModeDlg 对话框

IMPLEMENT_DYNAMIC(TableModeDlg, CDialogEx)

TableModeDlg::TableModeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(TableModeDlg::IDD, pParent)
{

}

TableModeDlg::~TableModeDlg()
{
}

void TableModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TableModeDlg, CDialogEx)
END_MESSAGE_MAP()


// TableModeDlg 消息处理程序
