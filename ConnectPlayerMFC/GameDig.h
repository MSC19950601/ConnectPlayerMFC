#pragma once


// CGameDig �Ի���

class CGameDig : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDig)

public:
	CGameDig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDig();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GAME_BASIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void InitBackground();
	CDC m_dcMem;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
