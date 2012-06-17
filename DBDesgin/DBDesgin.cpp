
// DBDesgin.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "DBDesgin.h"
#include "DBDesginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

 bool InitSystem(void);//进行初始化，包括建立磁盘存储文件等操作

// CDBDesginApp

BEGIN_MESSAGE_MAP(CDBDesginApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDBDesginApp 构造

CDBDesginApp::CDBDesginApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CDBDesginApp 对象

CDBDesginApp theApp;


// CDBDesginApp 初始化

BOOL CDBDesginApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CDBDesginDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}



bool InitSystem(void)
{
	FILE* fp;
	int id = 0;
	int userNum = 0;
	fp = fopen("DBIndex.dbf","rb");//DBIndex存储表的信息
	if(fp == NULL)
		fp = fopen("StorageFile.dbf","w");
	fclose(fp);
	
	fp = fopen("DBData.dat","rb");//DBData存放数据
	if(fp == NULL)
		fp = fopen("Data.dat","w");
	fclose(fp);


	//fp = fopen("Syslog.log","rb");//Syslog记录系统日志
	//if(fp == NULL)
	//	fp = fopen("Syslog.log","w");
	//fclose(fp);



	//fp = fopen("userlist","rb");
	//if(fp == NULL)
	//{
	//	char str[100]; 
	//	strcpy(str,"userlist(id int pkey,name char(9),authority int,password char(9))");
	//	int	strNum = getString(ch,0,str);
	//	if(CreateTable(strNum) == true)
	//	{
	//		printf("初始化用户列表成功!\n");
	//		GetDlgItem(IDC_RESULT)->SetWindowText(s);
	//	}
	//	else
	//	{
	//		printf("初始化用户列表有误!\n");
	//		return false;
	//	}
	//
	//	strcpy(str,"userlist values(1,lutao,1,123)");
	//	strNum = getString(ch,0,str);
	//	if(InsertTable(strNum) == true)
	//		printf("插入管理员成功!\n");
	//	else
	//	{
	//		printf("插入管理员失败!\n");
	//		return false;
	//	}
	//}

	return true;
}
