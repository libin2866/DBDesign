#pragma once


// TableModeDlg 对话框

class TableModeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TableModeDlg)

public:
	TableModeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TableModeDlg();

// 对话框数据
	enum { IDD = IDD_TABLETREEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
