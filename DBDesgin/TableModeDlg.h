#pragma once


// TableModeDlg �Ի���

class TableModeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TableModeDlg)

public:
	TableModeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TableModeDlg();

// �Ի�������
	enum { IDD = IDD_TABLETREEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
