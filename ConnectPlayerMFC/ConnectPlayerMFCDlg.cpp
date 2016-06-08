
// ConnectPlayerMFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ConnectPlayerMFC.h"
#include "ConnectPlayerMFCDlg.h"
#include "afxdialogex.h"
#include "EasySize.h"
#include "GameDig.h"
#include "RankDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CConnectPlayerMFCDlg �Ի���



CConnectPlayerMFCDlg::CConnectPlayerMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONNECTPLAYERMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConnectPlayerMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConnectPlayerMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BASIC_MODEL, &CConnectPlayerMFCDlg::OnBnClickedButtonBasicModel)
	ON_BN_CLICKED(IDC_BUTTON_RELAX_MODEL, &CConnectPlayerMFCDlg::OnBnClickedButtonRelaxModel)
	ON_BN_CLICKED(IDC_BUTTON_GRADE_MODEL, &CConnectPlayerMFCDlg::OnBnClickedButtonGradeModel)
	ON_BN_CLICKED(IDC_BUTTON_RISK, &CConnectPlayerMFCDlg::OnBnClickedButtonRisk)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CConnectPlayerMFCDlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CConnectPlayerMFCDlg::OnBnClickedButtonQuit)
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CConnectPlayerMFCDlg)
	//EASYSIZE(control, left, top, right, bottom, options)
	//EASYSIZE(IDB_MAIN_BG, ES_BORDER, ES_BORDER, ES_BORDER, ES_BORDER, 0)
END_EASYSIZE_MAP


// CConnectPlayerMFCDlg ��Ϣ�������

BOOL CConnectPlayerMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	this->SetWindowTextW(_T("����������"));

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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//���������
	InitBackground();
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	CenterWindow();

	//�ؼ�����Ӧ��С
	INIT_EASYSIZE;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CConnectPlayerMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CConnectPlayerMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//����CPaintDC����
		CPaintDC dc(this);

		dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);


		/*		//��������
		CFont font;
		font.CreatePointFont(200, _T("Courier New"));

		//������ѡ��DC
		CFont * oldFont;
		oldFont = dc.SelectObject(&font);

		//����������ɫ
		dc.SetTextColor(RGB(0, 0, 255));
		dc.SetBkColor(RGB(255, 255, 255));

		CRect rect;
		GetClientRect(&rect);

		//���ƻ�ӭ��
		CString strText = _T("Welcome to Connection Plat!");
		CSize size;
		size = dc.GetTextExtent(strText, strText.GetLength());
		int x = (rect.Width() - size.cx) / 2;
		int y = (rect.Height() - size.cy) / 2;
		dc.TextOutW(x, y, strText);*/
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CConnectPlayerMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CConnectPlayerMFCDlg::InitBackground() {

	//����λͼ
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_MAIN_BG);
	//��������DC
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	//��λͼѡ��DC
	m_dcMem.SelectObject(&bmpMain);
	//
}


void CConnectPlayerMFCDlg::OnSize(UINT nType, int cx, int cy)
{
	CConnectPlayerMFCDlg::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	UPDATE_EASYSIZE;
}


void CConnectPlayerMFCDlg::OnBnClickedButtonBasicModel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_HIDE);

	CBasicGame* basic = new CBasicGame;
	FLAG basicFlag;
	basicFlag.bProp = false;
	basicFlag.bTimer = true;
	basicFlag.bScore = false;
	basicFlag.szTitle = _T("����������������������ģʽ");
	basic->SetGameFlag(basicFlag);
	CGameDig dlg;
	dlg.SetGameModel(basic);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);

}


void CConnectPlayerMFCDlg::OnBnClickedButtonRelaxModel()
{
	this->ShowWindow(SW_HIDE);
	CEasyGame* easy = new CEasyGame;
	FLAG easyFlag;
	easyFlag.bProp = true;
	easyFlag.bTimer = false;
	easyFlag.bScore = true;
	easyFlag.szTitle = _T("����������������������ģʽ");
	easy->SetGameFlag(easyFlag);
	CGameDig dlg;
	dlg.SetGameModel(easy);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void CConnectPlayerMFCDlg::OnBnClickedButtonGradeModel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CConnectPlayerMFCDlg::OnBnClickedButtonRisk()
{
	this->ShowWindow(SW_HIDE);
	CRankDlg dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void CConnectPlayerMFCDlg::OnBnClickedButtonHelp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CConnectPlayerMFCDlg::OnBnClickedButtonQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CAboutDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CDialogEx::OnNotify(wParam, lParam, pResult);
}
