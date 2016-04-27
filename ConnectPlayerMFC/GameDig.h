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
	void DrawTipFrame(int nRow, int nCol);
	bool IsLink();
	void DrawTipLine();
	DECLARE_MESSAGE_MAP()

	void InitElement();
	void InitBackground();
protected:

	CDC m_dcMem;
	CDC m_dcElement;
	CDC m_dcMark;
	CDC m_dcBG;

	int m_anMap[4][4];
	CPoint m_ptGameTop;
	CSize m_sizeElem;
	bool m_bFirstPoint;
	CPoint m_ptSelFirst;
	CPoint m_ptSelSec;
	CRect m_rtGameRect;
public:
	
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonBasicModelBeginGame();
	afx_msg void OnBnClickedButtonBasicModelPrompt();
	afx_msg void OnBnClickedButtonBasicModelSuspendGame();
	afx_msg void OnBnClickedButtonBasicModelRearangement();
	afx_msg void OnBnClickedButtonBasicModelSetting();
	afx_msg void OnBnClickedButtonBasicModelHelp();
	void UpdateWindow();
	void UpdateMap();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
