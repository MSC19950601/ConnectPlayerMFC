
// ConnectPlayerMFCDlg.h : 头文件
//

#pragma once


// CConnectPlayerMFCDlg 对话框
class CConnectPlayerMFCDlg : public CDialogEx
{
// 构造
public:
	CConnectPlayerMFCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONNECTPLAYERMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CDC m_dcMem;


	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void InitBackground();

public:
	afx_msg void OnBnClickedButtonBasicModel();
	afx_msg void OnBnClickedButtonRelaxModel();
	afx_msg void OnBnClickedButtonGradeModel();
	afx_msg void OnBnClickedButtonRisk();
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedButtonQuit();
};
