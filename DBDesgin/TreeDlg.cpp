// TreeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBDesgin.h"
#include "TreeDlg.h"
#include "afxdialogex.h"


// TreeDlg �Ի���

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


// TreeDlg ��Ϣ�������




BOOL TreeDlg::OnInitDialog(void)
{

	CDialog::OnInitDialog();

	SetWindowText(title);

	//*++++++++++++++++++++++++++++++++++++++++++++++++*/

 /*mTreeΪһ��CTreeCtrl���󣬶��Ҹô����Ѿ�����*/

 HTREEITEM hItem,hSubItem,hSubItem2;

 for(int  i = 0; i < counts; i++ )//v.size() ��ʾvector����Ԫ�صĸ���
  {
	   if(tables[i].empty()) break;
	  hItem = mTree.InsertItem(tables[i][0] ,TVI_ROOT);
	  for(int j=1;j<tables[i].size();j++)
        // cout << tables[ i ] << " "; //��ÿ��Ԫ����ʾ����
	{ //hItem = mTree.InsertItem(tables[ i ][j] ,TV0I_ROOT);
	  hSubItem = mTree.InsertItem(tables[ i ][j],hItem);
	  }//j
  }

 //hItem = mTree.InsertItem("Parent1",TVI_ROOT);
 ////�ڸ���������Parent1

 // hSubItem = mTree.InsertItem("Child1_1",hItem);
 //     //��Parent1�����һ���ӽ��

 // hSubItem2 = mTree.InsertItem("Baby One more Kiss",hSubItem);
 //
 // hSubItem = mTree.InsertItem("Child1_2",hItem,hSubItem);
 //    //��Parent1�����һ���ӽ�㣬����Child1_1����
 //
 // hSubItem = mTree.InsertItem("Child1_3",hItem,hSubItem);
 //
 //hItem = mTree.InsertItem("Parent2",TVI_ROOT,hItem);   

 //hItem = mTree.InsertItem("Parent3",TVI_ROOT,hItem);

 /*++++++++++++++++++++++++++++++++++++++++++++++++*/



	return 0;
}


void TreeDlg::PostNcDestroy(void)
{
	CDialog::PostNcDestroy();
    delete this;
}