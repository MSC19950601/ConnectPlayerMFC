// GameDig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ConnectPlayerMFC.h"
#include "GameDig.h"
#include "afxdialogex.h"


// CGameDig �Ի���

IMPLEMENT_DYNAMIC(CGameDig, CDialogEx)

CGameDig::CGameDig(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_GAME_BASIC, pParent)
{
	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;

	//����Ԫ��ͼƬ��С������
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	//��ʼ����Ϸ��������
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * 4;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * 4;
	//��ʼ��ı�ʶ
	m_bFirstPoint = true;
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
	//CClientDC dc(this);
	//HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\pic\\background_2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//m_dcMem.CreateCompatibleDC(&dc);
	//m_dcMem.SelectObject(hBmpBG);

	//m_dcMem.CreateCompatibleDC(&dc);
	//CBitmap bmpMem;
	//bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	//m_dcMem.SelectObject(&bmpMem);

	//dc.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	//CRect rtWin;
	//CRect rtClient;
	//this->GetWindowRect(rtWin);
	//this->GetClientRect(rtClient);
	//int nSpanWidth = rtWin.Width() - rtClient.Width();
	//int nSpanHeight = rtWin.Height() - rtClient.Height();
	//MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	//CenterWindow();

	CClientDC dc(this);
	HANDLE hBmpBG = ::LoadImageW(NULL, _T("theme\\pic\\background_2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(hBmpBG);

	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
	/*CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_MAIN_BG);
	//��������DC
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	//��λͼѡ��DC
	m_dcMem.SelectObject(&bmpMain);*/
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
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);

}

void CGameDig::InitElement() {
	CClientDC dc(this);
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\cellPic\\cell1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(bmp);

	HANDLE bmpMark = ::LoadImage(NULL, _T("theme\\cellPic\\cell2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMark.CreateCompatibleDC(&dc);
	m_dcMark.SelectObject(bmpMark);
}


void CGameDig::OnBnClickedButtonBasicModelBeginGame()
{
	//��ʼ����Ϸ��ͼ
	m_gameControl.StartGame();

	/*// TODO: �ڴ���ӿؼ�֪ͨ����������
	int anMap[4][4] = {
		2,0,1,3,
		2,2,1,3,
		2,1,0,0,
		1,3,0,3
	};
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			m_anMap[i][j] = anMap[i][j];
		}
	}

	//

	int nLeft = 50;
	int nTop = 50;
	int nElemW = 40;
	int nElemH = 40;
	for (int i = 0; i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			//m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, m_anMap[i][j] * nElemH, SRCCOPY);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMark, 0, m_anMap[i][j] * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, m_anMap[i][j] * nElemH, SRCAND);
		}
	}*/
    UpdateMap();
	InvalidateRect(m_rtGameRect,FALSE);
}


void CGameDig::OnBnClickedButtonBasicModelPrompt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CGameDig::OnBnClickedButtonBasicModelSuspendGame()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CGameDig::OnBnClickedButtonBasicModelRearangement()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	CenterWindow();
}

void CGameDig::UpdateMap()
{
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;

	//m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcMem, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			int nElemVal = m_gameControl.GetElement(i, j);
			if (nElemVal == BLANK)	continue;
			//m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, m_anMap[i][j] * nElemH, SRCCOPY);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMark, 0, nElemVal * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal * nElemH, SRCAND);
		}
	}
	//UpdateMap();
	Invalidate(FALSE);
}


void CGameDig::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y) {
		return CDialog::OnLButtonUp(nFlags, point);
	}

	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;

	if (nRow > 4/*3*/ || nCol > 4/*3*/) {
		return CDialog::OnLButtonUp(nFlags, point);
	}
	if (m_bFirstPoint) {
		DrawTipFrame(nRow, nCol);
		//m_ptSelFirst.col = nCol;
		//m_ptSelFirst.row = nRow;
		m_gameControl.SetFirstPoint(nRow, nCol);
	}
	else {
		DrawTipFrame(nRow, nCol);
		//m_ptSelSec.x = nCol;
		//m_ptSelSec.y = nRow;
		m_gameControl.SetSecPoint(nRow, nCol);
		Vertex avPath[2];
		//�ж��Ƿ�����ͬͼƬ
		if (/*IsLink()*/m_gameControl.Link(avPath)) {
			//����ʾ��
			DrawTipLine(avPath);
			//���
			//m_anMap[m_ptSelFirst.y][m_ptSelFirst.x] = -1;
			//m_anMap[m_ptSelSec.y][m_ptSelSec.x] = -1;
			
			UpdateMap();
		}
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);
		
	}
	m_bFirstPoint = !m_bFirstPoint;
	//CDialogEx::OnLButtonUp(nFlags, point);
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


/*bool CGameDig::IsLink() {
	if (m_anMap[m_ptSelFirst.y][m_ptSelFirst.x] == m_anMap[m_ptSelSec.y][m_ptSelSec.x]) {
		return true;
	}
	return false;
}*/

/*void CGameDig::DrawTipLine() {
	CClientDC dc(this);
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	CPen * pOldPen = dc.SelectObject(&penLine);
	dc.MoveTo(
		m_ptGameTop.x + m_ptSelFirst.x + m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + m_ptSelFirst.y + m_sizeElem.cy + m_sizeElem.cy / 2
		);
	dc.LineTo(
		m_ptGameTop.x + m_ptSelSec.x + m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + m_ptSelSec.y + m_sizeElem.cy + m_sizeElem.cy / 2
		);
	dc.SelectObject(pOldPen);
}*/

void CGameDig::DrawTipLine(Vertex asvPath[2]) {
	CClientDC dc(this);
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	CPen * pOldPen = dc.SelectObject(&penLine);
	dc.MoveTo(
		m_ptGameTop.x + asvPath[0].col + m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + asvPath[0].row + m_sizeElem.cy + m_sizeElem.cy / 2
		);
	dc.LineTo(
		m_ptGameTop.x + asvPath[1].col + m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + asvPath[1].row + m_sizeElem.cy + m_sizeElem.cy / 2
		);
	dc.SelectObject(pOldPen);
}