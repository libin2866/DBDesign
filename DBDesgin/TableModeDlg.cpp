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
	//  DDX_Control(pDX,IDC_TREE2, mTree);
	DDX_Control(pDX, IDC_TREE2, mTree);
}


BEGIN_MESSAGE_MAP(TableModeDlg, CDialogEx)
END_MESSAGE_MAP()


BOOL TableModeDlg::OnInitDialog(void)
{

	CDialog::OnInitDialog();

	SetWindowText(title);

	//*++++++++++++++++++++++++++++++++++++++++++++++++*/

 /*mTree为一个CTreeCtrl对象，而且该窗口已经创建*/

 HTREEITEM hItem;

 for(int  i = 0; i <mytables.size(); i++ )//v.size() 表示vector存入元素的个数
  {
	   hItem = mTree.InsertItem(mytables[i] ,TVI_ROOT);//插入到Tree中
  }

	return 0;
}



// TableModeDlg 消息处理程序
void TableModeDlg::PostNcDestroy(void)
{
	CDialog::PostNcDestroy();
    delete this;
}