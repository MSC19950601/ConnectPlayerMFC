
// ConnectPlayerMFCDlg.h : ͷ�ļ�
//

#pragma once


// CConnectPlayerMFCDlg �Ի���
class CConnectPlayerMFCDlg : public CDialogEx
{
// ����
public:
	CConnectPlayerMFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONNECTPLAYERMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CDC m_dcMem;


	// ���ɵ���Ϣӳ�亯��
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
