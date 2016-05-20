#pragma once

#include "global.h"
#include "GameControl.h"

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
	void DrawTipFrame(int nRow, int nCol);
	//bool IsLink();
	void DrawTipLine(Vertex asvPath[4], int nVexNum);
	DECLARE_MESSAGE_MAP()

	void InitElement();
	void InitBackground();


protected:

	CDC m_dcMem;
	CDC m_dcElement;
	CDC m_dcMark;
	CDC m_dcBG;

	CPoint m_ptGameTop;
	CSize m_sizeElem;
	bool m_bFirstPoint;
	CRect m_rtGameRect;
	Vertex m_ptSelFirst;
	Vertex m_ptSelSec;
	CGameControl m_gameControl;

	bool m_bPlaying;
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
