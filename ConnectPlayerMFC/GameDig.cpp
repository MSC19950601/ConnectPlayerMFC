// GameDig.cpp : 实现文件
//

#include "stdafx.h"
#include "ConnectPlayerMFC.h"
#include "GameDig.h"
#include "afxdialogex.h"
#include <iostream>


// CGameDig 对话框

IMPLEMENT_DYNAMIC(CGameDig, CDialogEx)

CGameDig::CGameDig(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_GAME_BASIC, pParent)
{
	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;

	//单个元素图片大小的设置
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * 4;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * 4;
	//初始点的标识
	m_bFirstPoint = true;

	m_bPlaying = false;
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
	ON_BN_CLICKED(IDC_BUTTON_BASIC_MODEL_BEGIN_GAME, &CGameDig::OnBnClickedButtonBasicModelBeginGame)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_MODEL_PROMPT, &CGameDig::OnBnClickedButtonBasicModelPrompt)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_MODEL_SUSPEND_GAME, &CGameDig::OnBnClickedButtonBasicModelSuspendGame)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_MODEL_REARANGEMENT, &CGameDig::OnBnClickedButtonBasicModelRearangement)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_MODEL_SETTING, &CGameDig::OnBnClickedButtonBasicModelSetting)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_MODEL_HELP, &CGameDig::OnBnClickedButtonBasicModelHelp)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CGameDig 消息处理程序


void CGameDig::InitBackground()
{
	CClientDC dc(this);
	HANDLE hBmpBG = ::LoadImageW(NULL, _T("theme\\pic\\newBackground2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(hBmpBG);

	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
}


BOOL CGameDig::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitBackground();
	InitElement();
	UpdateWindow();
	//Invalidate();
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

void CGameDig::InitElement() {
	CClientDC dc(this);
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\cellPic\\newCellCollection1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(bmp);

	//HANDLE bmpMark = ::LoadImage(NULL, _T("theme\\cellPic\\animal_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//m_dcMark.CreateCompatibleDC(&dc);
	//m_dcMark.SelectObject(bmpMark);
}


void CGameDig::OnBnClickedButtonBasicModelBeginGame()
{
	//初始化游戏地图
	m_gameControl.StartGame();
	m_bPlaying = true;
	this->GetDlgItem(IDC_BUTTON_BASIC_MODEL_BEGIN_GAME)->EnableWindow(FALSE);
	
    UpdateMap();
	InvalidateRect(m_rtGameRect,FALSE);
}


void CGameDig::OnBnClickedButtonBasicModelPrompt()
{
	if (!m_bPlaying)	return;
	//连子判断
	Vertex avPath[16];
	int nVexNum = 0;
	if (m_gameControl.Help(avPath, nVexNum)) {
		m_ptSelFirst = avPath[0];
		m_ptSelSec = avPath[nVexNum - 1];
		DrawTipFrame(m_ptSelFirst.row, m_ptSelFirst.col);
		DrawTipFrame(m_ptSelSec.row, m_ptSelSec.col);
		DrawTipLine(avPath, nVexNum);
		UpdateMap();
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);
	}
}


void CGameDig::OnBnClickedButtonBasicModelSuspendGame()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CGameDig::OnBnClickedButtonBasicModelRearangement()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CGameDig::OnBnClickedButtonBasicModelSetting()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CGameDig::OnBnClickedButtonBasicModelHelp()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CGameDig::UpdateWindow()
{
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	CenterWindow();
}

void CGameDig::UpdateMap()
{
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;

	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			int nElemVal = m_gameControl.GetElement(i, j);
			if (nElemVal == BLANK) {
				continue;
			}
			//m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMark, 0, nElemVal * nElemH, SRCPAINT);
			//m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal * nElemH, SRCAND);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal * nElemH, SRCCOPY);
		}
	}
	Invalidate(FALSE);
}


void CGameDig::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y) {
		return CDialog::OnLButtonUp(nFlags, point);
	}

	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;

	if (nRow > 3/*3*/ || nCol > 3/*3*/) {
		return CDialog::OnLButtonUp(nFlags, point);
	}
	if (m_bFirstPoint) {
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);
	}
	else {
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetSecPoint(nRow, nCol);
		Vertex avPath[16];
		int nVexNum = 0;
		//判断是否是相同图片
		if (m_gameControl.Link(avPath, nVexNum)) {
			//画提示线
			DrawTipLine(avPath, nVexNum);
			//清除
			UpdateMap();

		}
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);
		if (m_gameControl.IsWin()) {
			MessageBox(_T("win"));
			return;
		}
	}
	m_bFirstPoint = !m_bFirstPoint;
}

void CGameDig::DrawTipFrame(int nRow, int nCol) {
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}


void CGameDig::DrawTipLine(Vertex asvPath[4], int nVexNum) {
	CClientDC dc(this);
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	CPen * pOldPen = dc.SelectObject(&penLine);
	
	dc.MoveTo(
		m_ptGameTop.x + asvPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + asvPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2
	);
	for (int i = 1; i < nVexNum; i++) {

		dc.LineTo(
			m_ptGameTop.x + asvPath[i].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + asvPath[i].row * m_sizeElem.cy + m_sizeElem.cy / 2
			);
	}
	dc.SelectObject(pOldPen);
}