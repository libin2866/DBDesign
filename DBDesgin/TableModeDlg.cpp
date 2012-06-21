// TableModeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBDesgin.h"
#include "TableModeDlg.h"
#include "afxdialogex.h"


// TableModeDlg �Ի���

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

 /*mTreeΪһ��CTreeCtrl���󣬶��Ҹô����Ѿ�����*/

 HTREEITEM hItem;

 for(int  i = 0; i <mytables.size(); i++ )//v.size() ��ʾvector����Ԫ�صĸ���
  {
	   hItem = mTree.InsertItem(mytables[i] ,TVI_ROOT);//���뵽Tree��
  }

	return 0;
}



// TableModeDlg ��Ϣ�������
void TableModeDlg::PostNcDestroy(void)
{
	CDialog::PostNcDestroy();
    delete this;
}