#pragma once
#include "Config.h"

// CThemeOptionDlg 对话框

class CThemeOptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThemeOptionDlg)

public:
	CThemeOptionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CThemeOptionDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_THEME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
	int m_nThemeType;
	CString m_strElemPath;

public:
	afx_msg void OnBnClickRadio(UINT nID);
	
	afx_msg void OnBnClickedButtonSelfSettingElementPathFile();

	void Save();
};
