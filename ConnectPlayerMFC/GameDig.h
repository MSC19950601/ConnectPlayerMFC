#pragma once

#include "global.h"
#include "GameControl.h"
#include "afxcmn.h"

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
	void DrawTipLine(Vertex asvPath[MAX_VERTEX_NUM], int nVexNum);
	DECLARE_MESSAGE_MAP()

	void InitElement();
	void InitBackground();


protected:

	CDC m_dcMem;
	CDC m_dcElement;
	CDC m_dcMark;
	CDC m_dcBG;

	CDC m_dcPause;
	CDC m_dcCache;

	CPoint m_ptGameTop;
	CSize m_sizeElem;
	bool m_bFirstPoint;
	CRect m_rtGameRect;
	Vertex m_ptSelFirst;
	Vertex m_ptSelSec;
	CGameControl m_gameControl;

	bool m_bPlaying;

	bool m_bPause;
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
	CProgressCtrl m_GameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void DrawGameTime();
	void JudgeWin();
};
