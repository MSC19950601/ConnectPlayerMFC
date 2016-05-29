// GameDig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ConnectPlayerMFC.h"
#include "GameDig.h"
#include "afxdialogex.h"
#include <iostream>


// CGameDig �Ի���

IMPLEMENT_DYNAMIC(CGameDig, CDialogEx)

CGameDig::CGameDig(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_GAME_BASIC, pParent)
{
	m_ptGameTop.x = MAP_LEFT;
	m_ptGameTop.y = MAP_TOP;

	//����Ԫ��ͼƬ��С������
	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;

	//��ʼ����Ϸ��������
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;
	//��ʼ��ı�ʶ
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


// CGameDig ��Ϣ�������


void CGameDig::InitBackground()
{
	CClientDC dc(this);
	HANDLE hBmpBG = ::LoadImageW(NULL, _T("theme\\pic\\newBackground3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(hBmpBG);

	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 900, 600);
	m_dcMem.SelectObject(&bmpMem);
	m_dcMem.BitBlt(0, 0, 900, 600, &m_dcBG, 0, 0, SRCCOPY);
}


BOOL CGameDig::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitBackground();
	InitElement();
	UpdateWindow();
	//Invalidate();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CGameDig::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 900, 600, &m_dcMem, 0, 0, SRCCOPY);

}

void CGameDig::InitElement() {
	CClientDC dc(this);
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\cellPic\\newCellCollection2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(bmp);

	//HANDLE bmpMark = ::LoadImage(NULL, _T("theme\\cellPic\\animal_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//m_dcMark.CreateCompatibleDC(&dc);
	//m_dcMark.SelectObject(bmpMark);
}


void CGameDig::OnBnClickedButtonBasicModelBeginGame()
{
	//��ʼ����Ϸ��ͼ
	m_gameControl.StartGame();
	m_bPlaying = true;
	this->GetDlgItem(IDC_BUTTON_BASIC_MODEL_BEGIN_GAME)->EnableWindow(FALSE);
	
    UpdateMap();
	InvalidateRect(m_rtGameRect,FALSE);
}


void CGameDig::OnBnClickedButtonBasicModelPrompt()
{
	if (!m_bPlaying)	return;
	//�����ж�
	Vertex avPath[MAX_VERTEX_NUM];
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CGameDig::OnBnClickedButtonBasicModelRearangement()
{

	if (!m_bPlaying)
		return;
	//���ţ�����CGameControl::ResetGraph
	m_gameControl.ResetGraph();
	//���µ�ͼ
	UpdateMap();
	//�ػ����
	InvalidateRect(m_rtGameRect, FALSE);
}


void CGameDig::OnBnClickedButtonBasicModelSetting()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CGameDig::OnBnClickedButtonBasicModelHelp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CGameDig::UpdateWindow()
{
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(0, 0,900 + nSpanWidth, 600 + nSpanHeight);
	CenterWindow();
}

void CGameDig::UpdateMap()
{
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;

	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i < MAX_ROW;i++) {
		for (int j = 0;j < MAX_COL;j++) {
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

	if (nRow > MAX_ROW - 1/*3*/ || nCol > MAX_COL - 1/*3*/) {
		return CDialog::OnLButtonUp(nFlags, point);
	}
	if (m_bFirstPoint) {
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);
	}
	else {
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetSecPoint(nRow, nCol);
		Vertex avPath[MAX_VERTEX_NUM];
		int nVexNum = 0;
		//�ж��Ƿ�����ͬͼƬ
		if (m_gameControl.Link(avPath, nVexNum)) {
			//����ʾ��
			DrawTipLine(avPath, nVexNum);
			//���
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


void CGameDig::DrawTipLine(Vertex asvPath[MAX_VERTEX_NUM], int nVexNum) {
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