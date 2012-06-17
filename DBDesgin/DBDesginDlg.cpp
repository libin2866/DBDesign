
// DBDesginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DBDesgin.h"
#include "DBDesginDlg.h"
#include "afxdialogex.h"
#include"CreateTable.h"
#include"EditTable.h"
#include"RenameTable.h"
#include"Drop_Table.h"
#include"Insert_Into.h"
#include"DeleteFrom.h"
#include"Update.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CBrush m_brush;//改变颜色

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDBDesginDlg 对话框




CDBDesginDlg::CDBDesginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDBDesginDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDBDesginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDBDesginDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RESET, &CDBDesginDlg::OnBnClickedReset)
	//ON_BN_CLICKED(IDOK, &CDBDesginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_ABOUT, &CDBDesginDlg::OnBnClickedAbout)
	ON_BN_CLICKED(IDC_OPBtn, &CDBDesginDlg::OnBnClickedOpbtn)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDBDesginDlg 消息处理程序

BOOL CDBDesginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	 //CString m_strCaption = " 数据库管理系统"; 
	m_brush.CreateSolidBrush(RGB(255,0,0));
	GetDlgItem(IDC_RESULT)-> SetWindowText("欢迎来到数据库管理系统!");
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//
//BOOL CDBDesginDlg::PreTranslateMessage(MSG* pMsg) 
//{
//    // TODO: Add your specialized code here and/or call the base class
//       // TODO: Add your specialized code here and/or call the base class
//    if   (pMsg->message   ==   WM_KEYDOWN)   
//    {   
//        if   (pMsg->wParam==VK_RETURN)   
//            return TRUE;//截获消息 
//    }   
//    return CDialog::PreTranslateMessage(pMsg);
//}

//BOOL  CDBDesginDlg::PreTranslateMessage(MSG*   pMsg)   
//{ 
//	if(   pMsg-> message   ==   WM_KEYDOWN   ) 
//	{       
//		if(pMsg-> hwnd   ==   GetDlgItem(IDC_SQLStatement)-> m_hWnd) 
//		{ 
//			switch(   pMsg-> wParam   ) 
//			{ 
//			case   VK_RETURN: 
//			//Onbutton1(); 
//			} 
//
//		} 
//		return   CDialog::PreTranslateMessage(pMsg); 
//
//	}
//}


void CDBDesginDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDBDesginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDBDesginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDBDesginDlg::OnBnClickedReset()
{
	if(1==MessageBox("确认清空？","注意",MB_OKCANCEL|MB_ICONWARNING )){
	GetDlgItem(IDC_SQLStatement)-> SetWindowText("");
	}
}


void CDBDesginDlg::OnBnClickedAbout()
{
	CAboutDlg aboutdlg;
	aboutdlg.DoModal();

}


void CDBDesginDlg::OnBnClickedOpbtn()
{
	char sql[200];
	int type;
	CString result;
	GetDlgItemText(IDC_SQLStatement,sql,sizeof(sql));
	type= AnalyseSql(sql);

	if(type==CREATE_TABLE)//Create Table
	{
		result=CreateTable();
	}
	if(type==EDIT_TABLE)//Edit Table
	{
		result=EditTable();
	}
	if(type==RENAME_TABLE) result=RenameTable();
	if(type==DROP_TABLE) result=DropTable();
	if(type==INSERT_INTO) result=InsertInto();
	if(type==DELETE_FROM) result=DeleteFrom();
	if(type==UPDATE) result=Update();


	if(type==0) result="您输入的语句有误！";
	GetDlgItem(IDC_RESULT)-> SetWindowText(result);
}



HBRUSH CDBDesginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	   if (pWnd->GetDlgCtrlID() == IDC_RESULT)
     {
         pDC->SetTextColor(RGB(255, 0, 0));
     }

	return hbr;
}
