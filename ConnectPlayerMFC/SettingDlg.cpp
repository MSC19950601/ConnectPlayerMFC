// SettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ConnectPlayerMFC.h"
#include "SettingDlg.h"
#include "afxdialogex.h"


// CSettingDlg �Ի���

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SETTING, m_tabSetting);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE,IDC_TAB_SETTING,&CSettingDlg::OnSelchangeTabSetting)
	ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSettingDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSettingDlg ��Ϣ�������


void CSettingDlg::OnBnClickedOk()
{
	
	m_dlgTheme.Save();
	CDialogEx::OnOK();
}


void CSettingDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


BOOL CSettingDlg::OnInitDialog()
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

	m_tabSetting.InsertItem(0, TEXT("��������"));
	//m_tabSetting.InsertItem(1, TEXT("��Ч"));

	m_dlgTheme.Create(IDD_CONFIG_THEME, &m_tabSetting);
	CRect tabRect;
	m_tabSetting.GetClientRect(&tabRect);    // ��ȡ��ǩ�ؼ��ͻ���Rect   
											 // ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ   
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	m_dlgTheme.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CSettingDlg::OnSelchangeTabSetting(NMHDR* pNMHDR, LRESULT* pResult) {
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	*pResult = 0;

	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect   

					  // ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ   
	m_tabSetting.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch (m_tabSetting.GetCurSel())
	{
	case 0:
		m_dlgTheme.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);

		//m_androidDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 1:
		m_dlgTheme.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

		break;
	default:
		break;
	}


}
