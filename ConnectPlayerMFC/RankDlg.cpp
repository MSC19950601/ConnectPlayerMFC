// RankDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ConnectPlayerMFC.h"
#include "RankDlg.h"
#include "afxdialogex.h"
#include "ScoreLogic.h"
#include "global.h"

#include <vector>
#include <algorithm>

// CRankDlg �Ի���

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


// CRankDlg ��Ϣ�������



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

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	LONG lStyle;
	lStyle = GetWindowLong(m_ListRank.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_ListRank.m_hWnd, GWL_STYLE, lStyle);//����style

	DWORD dwStyle = m_ListRank.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_ListRank.SetExtendedStyle(dwStyle); //������չ���
	CRect rect;
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_ListRank.GetClientRect(&rect);
	// Ϊ�б���ͼ�ؼ��������   
	m_ListRank.InsertColumn(0, _T("����"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_ListRank.InsertColumn(1, _T("�������"), LVCFMT_CENTER, rect.Width() / 2, 1);
	m_ListRank.InsertColumn(2, _T("����"), LVCFMT_CENTER, rect.Width() / 3, 2);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
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


	

