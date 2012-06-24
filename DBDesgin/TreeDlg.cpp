// TreeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DBDesgin.h"
#include "TreeDlg.h"
#include "afxdialogex.h"


// TreeDlg 对话框

IMPLEMENT_DYNAMIC(TreeDlg, CDialogEx)

TreeDlg::TreeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(TreeDlg::IDD, pParent)
{

}

TreeDlg::~TreeDlg()
{
}

void TreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, mTree);
}


BEGIN_MESSAGE_MAP(TreeDlg, CDialogEx)
END_MESSAGE_MAP()


// TreeDlg 消息处理程序




BOOL TreeDlg::OnInitDialog(void)
{

	CDialog::OnInitDialog();

	SetWindowText(title);

	//*++++++++++++++++++++++++++++++++++++++++++++++++*/

 /*mTree为一个CTreeCtrl对象，而且该窗口已经创建*/

 HTREEITEM hItem,hSubItem,hSubItem2;

 for(int  i = 0; i < counts; i++ )//v.size() 表示vector存入元素的个数
  {
	   if(tables[i].empty()) break;
	  hItem = mTree.InsertItem(tables[i][0] ,TVI_ROOT);
	  for(int j=1;j<tables[i].size();j++)
        // cout << tables[ i ] << " "; //把每个元素显示出来
	{ //hItem = mTree.InsertItem(tables[ i ][j] ,TV0I_ROOT);
	  hSubItem = mTree.InsertItem(tables[ i ][j],hItem);
	  }//j
  }

 //hItem = mTree.InsertItem("Parent1",TVI_ROOT);
 ////在根结点上添加Parent1

 // hSubItem = mTree.InsertItem("Child1_1",hItem);
 //     //在Parent1上添加一个子结点


 /*++++++++++++++++++++++++++++++++++++++++++++++++*/



	return 0;
}


void TreeDlg::PostNcDestroy(void)
{
	CDialog::PostNcDestroy();
    delete this;
}