#pragma once


// CGameDig 对话框

class CGameDig : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDig)

public:
	CGameDig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDig();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GAME_BASIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void InitBackground();
	CDC m_dcMem;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
