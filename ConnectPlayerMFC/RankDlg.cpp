// RankDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ConnectPlayerMFC.h"
#include "RankDlg.h"
#include "afxdialogex.h"
#include "ScoreLogic.h"
#include "global.h"

#include <vector>
#include <algorithm>

// CRankDlg 对话框

IMPLEMENT_DYNAMIC(CRankDlg, CDialogEx)

CRankDlg::CRankDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_RANK, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CRankDlg::~CRankDlg()
{
}

void CRankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RANK, m_ListRank);
}


BEGIN_MESSAGE_MAP(CRankDlg, CDialogEx)

	ON_COMMAND_RANGE(IDC_RADIO_EASY, IDC_RADIO_GAME, &CRankDlg::OnClickRadio)
END_MESSAGE_MAP()


// CRankDlg 消息处理程序



void CRankDlg::OnClickRadio(UINT nID) {
	if (nID == IDC_RADIO_EASY) {
		m_nMode = 1;
		DisplayRank(m_nMode);
	}
	else {
		m_nMode = 2;
		DisplayRank(m_nMode);
	}
}


BOOL CRankDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	LONG lStyle;
	lStyle = GetWindowLong(m_ListRank.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_ListRank.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_ListRank.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_ListRank.SetExtendedStyle(dwStyle); //设置扩展风格
	CRect rect;
	// 获取编程语言列表视图控件的位置和大小   
	m_ListRank.GetClientRect(&rect);
	// 为列表视图控件添加三列   
	m_ListRank.InsertColumn(0, _T("排行"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_ListRank.InsertColumn(1, _T("玩家姓名"), LVCFMT_CENTER, rect.Width() / 2, 1);
	m_ListRank.InsertColumn(2, _T("积分"), LVCFMT_CENTER, rect.Width() / 3, 2);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CRankDlg::DisplayRank(int nMode) {

	//SCORE list[10];
	std::vector<SCORE> list;
	CScoreLogic logic;
	int num = logic.SearchRank(list, nMode);

	for (int i = 0; i < list.size(); i++) {
		SCORE tempMax = list[i];
		for (int j = i + 1; j < list.size(); j++){
			if (tempMax.nGrade < list[j].nGrade) {
				SCORE temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}
	m_ListRank.DeleteAllItems();
	for (int i = 0; i < num; i++) {
		CString ID; ID.Format(_T("%d"), i + 1);
		m_ListRank.InsertItem(i, ID);
		m_ListRank.SetItemText(i, 1, list.at(i).strName);
		CString sco; sco.Format(_T("%d"), list.at(i).nGrade);
		m_ListRank.SetItemText(i, 2, sco);
	}
}


	

