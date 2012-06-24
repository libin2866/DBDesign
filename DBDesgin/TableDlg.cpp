// TableDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DBDesgin.h"
#include "TableDlg.h"
#include "afxdialogex.h"

bool methodri=true;
int sort_columnri;

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
	DDX_Control(pDX, IDC_LIST1, mTable);
}


BEGIN_MESSAGE_MAP(TableDlg, CDialogEx)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &TableDlg::OnLvnColumnclickList1)
END_MESSAGE_MAP()


// TableDlg 消息处理程序


BOOL TableDlg::OnInitDialog(void)
{

	CDialog::OnInitDialog();
	mTable.ModifyStyle(0,LVS_REPORT|LVS_SHOWSELALWAYS);//|LVS_SINGLESEL
	mTable.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	mTable.SetTextColor(RGB(160,32,240));                  //显示字体的颜色
	DWORD dwStyle = mTable.GetStyle();
	dwStyle |= LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT;
	mTable.SetExtendedStyle(dwStyle);
	mTable.SetBkColor(RGB(240,255,200));             //选中此列时的颜色
	mTable.SetTextBkColor(RGB(240,255,200));
	SetWindowText(title);
	/*
	m_list.SetImageList(&m_listSmall,LVSIL_SMALL);//设置ImageList 
m_list.InsertColumn(0,\"Col 1\",LVCFMT_LEFT,300,0);//设置列 
m_list.InsertColumn(1,\"Col 2\",LVCFMT_LEFT,300,1); 
m_list.InsertColumn(2,\"Col 3\",LVCFMT_LEFT,300,2); 
m_list.InsertItem(0,\"Item 1_1\");//插入行 
m_list.SetItemText(0,1,\"Item 1_2\");//设置该行的不同列的显示字符 
m_list.SetItemText(0,2,\"Item 1_3\") 
  	*/


	int columns;int nRow=0;
	CString strnum;
	for(columns=0;columns<returnData.size();columns++){
		 if(returnData[columns].empty()) break;
		 //插入列名
		mTable.InsertColumn(columns,returnData[columns][0],LVCFMT_LEFT,180,columns);//LVCFMT_LEFT   LVCFMT_CENTER
		strnum.Format("%d",columns);
		mTable.InsertItem(columns,strnum);//插入第columns行,以及其对应的数据
		nRow++;//统计行数
		//for(int j=2;j<returnData[columns].size();j++){
		//mTable.SetItemText(j,columns,returnData[columns][j]);//在第columns行，插入其他数据
		//}
	}
	//mTable.InsertItem(columns,strnum);//插入第columns行,以及其对应的数据
int j;
int i;
for(j=0;j<nRow;j++){
		 //if(returnData[j].empty()) break;
		for(i=columns-1;i>=0;i--)
		 {
		mTable.SetItemText(j,i,returnData[i][j+1]);//在第j行，插入剩余数据
		}

}
//m_list.SetImageList(&m_listSmall,LVSIL_SMALL);//设置ImageList 
//mTable.InsertColumn(0,"Col 1",LVCFMT_LEFT,180,0);//设置列 
//mTable.InsertColumn(1,"Col 2",LVCFMT_LEFT,180,1); 
//mTable.InsertColumn(2,"Col 3",LVCFMT_LEFT,180,2); 
//mTable.InsertItem(0,"Item 1_1");//插入行 
//mTable.SetItemText(0,1,"Item 1_2");//设置该行的不同列的显示字符 
//mTable.SetItemText(0,2,"Item 1_3") ;	
	return 0;
}


void TableDlg::PostNcDestroy(void)
{
	CDialog::PostNcDestroy();
    delete this;
}


static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{

	 // 从参数中提取所需比较lc的两行数据
 
	 int row1 = (int) lParam1;
	 int row2 = (int) lParam2;
 
	 CListCtrl* lc = (CListCtrl*)lParamSort;
 
	 CString lp1 = lc->GetItemText(row1,sort_columnri);
	 CString lp2 = lc->GetItemText(row2,sort_columnri);
 

	 // 比较，对不同的列，不同比较，注意记录前一次排序方向，下一次要相反排序
	//
 //
	//	if (sort_columnri==2||sort_columnri==3||sort_columnri==0)
	//	{ 
	//// int型比较
	//	if (methodri)
	//	return atoi(lp1)-atoi(lp2);
	//	else
	//	return atoi(lp2)-atoi(lp1);
	//	}
	 /*else*/
	 
	// 文字型比较
	 if (methodri)
	 return lp1.CompareNoCase(lp2);
	 else
	 return lp2.CompareNoCase(lp1);
	 //}
 
	 return 0;

}

void TableDlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	sort_columnri = pNMLV->iSubItem;//点击的列

	int count = mTable.GetItemCount();
	if(methodri)methodri=false;
	else methodri=true;

	for (int i=0;i<count;i++)
	  mTable.SetItemData(i,i); // 每行的比较关键字，此处为列序号（点击的列号），可以设置为其他 比较函数的第一二个参数

	mTable.SortItems(MyCompareProc,(DWORD_PTR)&mTable);//排序 第二个参数是比较函数的第三个参数
	*pResult = 0;
}
