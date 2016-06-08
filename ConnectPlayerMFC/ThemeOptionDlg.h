#pragma once
#include "Config.h"

// CThemeOptionDlg �Ի���

class CThemeOptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThemeOptionDlg)

public:
	CThemeOptionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CThemeOptionDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_THEME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

protected:
	int m_nThemeType;
	CString m_strElemPath;

public:
	afx_msg void OnBnClickRadio(UINT nID);
	
	afx_msg void OnBnClickedButtonSelfSettingElementPathFile();

	void Save();
};
