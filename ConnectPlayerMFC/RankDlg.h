#pragma once
#include "afxcmn.h"


// CRankDlg 对话框

class CRankDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRankDlg)

public:
	CRankDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRankDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RANK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
	int m_nMode = -1;
	CListCtrl m_ListRank;
	afx_msg void OnClickRadio(UINT nID);
public:

	virtual BOOL OnInitDialog();
	void DisplayRank(int nMode);

	//bool compare(const SCORE& score1, const SCORE& score2) {
	//	return score1.nGrade > score2.nGrade;
	//}
};
