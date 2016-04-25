// GameDig.cpp : 实现文件
//

#include "stdafx.h"
#include "ConnectPlayerMFC.h"
#include "GameDig.h"
#include "afxdialogex.h"


// CGameDig 对话框

IMPLEMENT_DYNAMIC(CGameDig, CDialogEx)

CGameDig::CGameDig(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_GAME_BASIC, pParent)
{

}

CGameDig::~CGameDig()
{
}

void CGameDig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDig, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CGameDig 消息处理程序


void CGameDig::InitBackground()
{
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\pic\\background_2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);

	m_dcMem.SelectObject(bmp);
	/*CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_MAIN_BG);
	//创建兼容DC
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	//将位图选进DC
	m_dcMem.SelectObject(&bmpMain);*/
}


BOOL CGameDig::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitBackground();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameDig::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}
