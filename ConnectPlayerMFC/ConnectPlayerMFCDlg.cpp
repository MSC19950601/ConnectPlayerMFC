
// ConnectPlayerMFCDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CConnectPlayerMFCDlg 对话框



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


// CConnectPlayerMFCDlg 消息处理程序

BOOL CConnectPlayerMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	this->SetWindowTextW(_T("欢乐连连看"));

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

	// TODO: 在此添加额外的初始化代码
	//主界面设计
	InitBackground();
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	CenterWindow();

	//控件自适应大小
	INIT_EASYSIZE;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CConnectPlayerMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//创建CPaintDC对象
		CPaintDC dc(this);

		dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);


		/*		//创建字体
		CFont font;
		font.CreatePointFont(200, _T("Courier New"));

		//将字体选进DC
		CFont * oldFont;
		oldFont = dc.SelectObject(&font);

		//设置字体颜色
		dc.SetTextColor(RGB(0, 0, 255));
		dc.SetBkColor(RGB(255, 255, 255));

		CRect rect;
		GetClientRect(&rect);

		//绘制欢迎语
		CString strText = _T("Welcome to Connection Plat!");
		CSize size;
		size = dc.GetTextExtent(strText, strText.GetLength());
		int x = (rect.Width() - size.cx) / 2;
		int y = (rect.Height() - size.cy) / 2;
		dc.TextOutW(x, y, strText);*/
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CConnectPlayerMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CConnectPlayerMFCDlg::InitBackground() {

	//加载位图
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_MAIN_BG);
	//创建兼容DC
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	//将位图选进DC
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
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);

	CBasicGame* basic = new CBasicGame;
	FLAG basicFlag;
	basicFlag.bProp = false;
	basicFlag.bTimer = true;
	basicFlag.bScore = false;
	basicFlag.szTitle = _T("欢乐连连看————基本模式");
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
	easyFlag.szTitle = _T("欢乐连连看————休闲模式");
	easy->SetGameFlag(easyFlag);
	CGameDig dlg;
	dlg.SetGameModel(easy);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void CConnectPlayerMFCDlg::OnBnClickedButtonGradeModel()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
}


void CConnectPlayerMFCDlg::OnBnClickedButtonQuit()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CAboutDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::OnNotify(wParam, lParam, pResult);
}
