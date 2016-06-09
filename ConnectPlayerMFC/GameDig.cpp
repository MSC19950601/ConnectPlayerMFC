// GameDig.cpp : 实现文件
//

#include "stdafx.h"
#include "ConnectPlayerMFC.h"
#include "GameDig.h"
#include "afxdialogex.h"
#include "SettingDlg.h"
#include "Config.h"
#include "ConfigLogic.h"

// CGameDig 对话框

IMPLEMENT_DYNAMIC(CGameDig, CDialogEx)

CGameDig::CGameDig(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_GAME, pParent)
{
	m_ptGameTop.x = MAP_LEFT;
	m_ptGameTop.y = MAP_TOP;

	//单个元素图片大小的设置
	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;
	//初始点的标识
	m_bFirstPoint = true;

	m_bPlaying = false;

	m_bPause = false;

	m_bProp = false;

	//what the fuck!
	//bSuc = false;
}

CGameDig::~CGameDig()
{
}

void CGameDig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_BASIC_GAME_MODEL, m_GameProgress);
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
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_TRICK, &CGameDig::OnBnClickedButtonTrick)
END_MESSAGE_MAP()


// CGameDig 消息处理程序


void CGameDig::InitBackground()
{
	CClientDC dc(this);
	HANDLE hBmpBG = ::LoadImageW(NULL, _T("background\\newBackground3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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
	this->GetDlgItem(IDC_PROGRESS_BASIC_GAME_MODEL)->ShowWindow(SW_HIDE);

	m_flag = m_pGameC->GetGameFlag();
	if (m_flag.bScore) {

		this->SetWindowTextW(m_flag.szTitle);

		this->GetDlgItem(IDC_BUTTON_BASIC_MODEL_PROMPT)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_BUTTON_BASIC_MODEL_REARANGEMENT)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_BUTTON_TRICK)->EnableWindow(FALSE);


	}
	else {

		this->SetWindowTextW(m_flag.szTitle);

		this->GetDlgItem(IDC_BUTTON_TRICK)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_STATIC_SCORE)->ShowWindow(SW_HIDE);
	}

	InitBackground();
	InitElement();
	UpdateWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameDig::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	dc.BitBlt(0, 0, 900, 600, &m_dcMem, 0, 0, SRCCOPY);

}

void CGameDig::InitElement() {
	CString elem = CConfig::GetSingleInstance()->GetElemPath();
	CString mask = CConfig::GetSingleInstance()->GetMaskPath();

	if (CConfig::GetSingleInstance()->GetStyle() == 1) {
		elem = _T("theme\\element1.bmp");
		mask = _T("theme\\elementMask1.bmp");
	}

	if (CConfig::GetSingleInstance()->GetStyle() == 2) {
		elem = _T("theme\\element2.bmp");
		mask = _T("theme\\elementMask2.bmp");
	}

	CClientDC dc(this);
	//HANDLE bmp = ::LoadImage(NULL, _T("theme\\element3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE bmp = ::LoadImage(NULL, elem, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(bmp);

	//HANDLE bmpMark = ::LoadImage(NULL, _T("theme\\elementMask3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE bmpMark = ::LoadImage(NULL, mask, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMark.CreateCompatibleDC(&dc);
	m_dcMark.SelectObject(bmpMark);



	HANDLE bmpPause = ::LoadImageW(NULL, _T("background\\background_4.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcPause.CreateCompatibleDC(&dc);
	m_dcPause.SelectObject(bmpPause);
	m_dcCache.CreateCompatibleDC(&dc);
	CBitmap bmpCache;
	bmpCache.CreateCompatibleBitmap(&dc, 640, 400);
	m_dcCache.SelectObject(bmpCache);
	m_dcCache.BitBlt(0, 0, 640, 400, &m_dcPause, 0, 0, SRCCOPY);
}


void CGameDig::OnBnClickedButtonBasicModelBeginGame()
{
	if(!m_flag.bScore)
		this->GetDlgItem(IDC_PROGRESS_BASIC_GAME_MODEL)->ShowWindow(SW_SHOW);

	//if (!m_bPause)	return;
	//初始化游戏地图
	m_pGameC->StartGame();
	//更新界面
	UpdateMap();
	//更新窗口
	InvalidateRect(m_rtGameRect, FALSE);
	//游戏标识设置
	m_bPlaying = true;
	//开始按钮禁止点击
	this->GetDlgItem(IDC_BUTTON_BASIC_MODEL_BEGIN_GAME)->EnableWindow(FALSE);

	if (!m_flag.bScore) {
		//初始化进度条
		m_GameProgress.SetRange(0, 300);//初始范围
		m_GameProgress.SetStep(-1);//初始步数值
		m_GameProgress.SetPos(300);//设置初始值
								   //启动定时器
		this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
		//绘制当前秒数
		DrawGameTime();
	}
}


void CGameDig::OnBnClickedButtonBasicModelPrompt()
{
	if (m_flag.bScore) {
		if (m_flag.bScore && m_pGameC->GetGrade() > 20) {
			int nGrade = m_pGameC->GetGrade();
			nGrade = nGrade - 20;
			m_pGameC->SetGrade(nGrade);
			DrawGameGrade();

			Vertex avPath[MAX_VERTEX_NUM];
			int nVexNum = 0;
			if (m_pGameC->Help(avPath, nVexNum)) {
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
		else {
			MessageBox(_T("积分不足!!!"));
			return;
		}
	}
	else {
		if (!m_bPlaying)	return;
		//if (m_bPause)	return;
		//连子判断
		Vertex avPath[MAX_VERTEX_NUM];
		int nVexNum = 0;
		if (m_pGameC->Help(avPath, nVexNum)) {
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
}


void CGameDig::OnBnClickedButtonBasicModelSuspendGame()
{
	CClientDC dc(this);

	if (!m_bPlaying)
		return;
	if (m_bPause) {
		KillTimer(PLAY_TIMER_ID);
		m_dcMem.BitBlt(MAP_LEFT, MAP_TOP, 640, 400, &m_dcCache, 0, 0, SRCCOPY);
		InvalidateRect(m_rtGameRect, FALSE);
		this->GetDlgItem(IDC_BUTTON_BASIC_MODEL_SUSPEND_GAME)->SetWindowTextW(_T("继续游戏"));
	}
	else {
		//休闲模式要修改
		if (!m_flag.bScore) {
			this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
			UpdateMap();
			InvalidateRect(m_rtGameRect, FALSE);
			this->GetDlgItem(IDC_BUTTON_BASIC_MODEL_SUSPEND_GAME)->SetWindowTextW(_T("暂停游戏"));
		}
		else 
		{
			UpdateMap();
			InvalidateRect(m_rtGameRect, FALSE);
			this->GetDlgItem(IDC_BUTTON_BASIC_MODEL_SUSPEND_GAME)->SetWindowTextW(_T("暂停游戏"));
		}
	}
	m_bPause = !m_bPause;
}


void CGameDig::OnBnClickedButtonBasicModelRearangement()
{
	if (m_flag.bScore) {
		if (m_flag.bScore && m_pGameC->GetGrade() > 50) {
			int nGrade = m_pGameC->GetGrade();
			nGrade = nGrade - 50;
			m_pGameC->SetGrade(nGrade);
			DrawGameGrade();

			m_pGameC->ResetGraph();
			//更新地图
			UpdateMap();
			//重绘界面
			InvalidateRect(m_rtGameRect, FALSE);

		}
		else {
			MessageBox(_T("积分不足!!!"));
			return;
		}
	}
	else {
		if (!m_bPlaying)
			return;
		//if (m_bPause)	return;
		//重排，调用CGameControl::ResetGraph
		m_pGameC->ResetGraph();
		//更新地图
		UpdateMap();
		//重绘界面
		InvalidateRect(m_rtGameRect, FALSE);
	}
}


void CGameDig::OnBnClickedButtonBasicModelSetting()
{
	CSettingDlg dlg;
	if (dlg.DoModal() == IDOK) {
		UpdateTheme();
	}
}


void CGameDig::OnBnClickedButtonBasicModelHelp()
{
	CHelpDlg dlg;
	dlg.DoModal();
}


void CGameDig::UpdateWindow()
{

	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(0, 0, 900 + nSpanWidth, 600 + nSpanHeight);
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
			int nElemVal = m_pGameC->GetElement(i, j);
			if (nElemVal == BLANK) {
				continue;
			}
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMark, 0, nElemVal * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal * nElemH, SRCAND);
			//m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal * nElemH, SRCCOPY);
		}
	}
	Invalidate(FALSE);
}


void CGameDig::OnLButtonUp(UINT nFlags, CPoint point)
{
	

	//基本实现
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
		m_pGameC->SetFirstPoint(nRow, nCol);
	}
	else {
		DrawTipFrame(nRow, nCol);
		m_pGameC->SetSecPoint(nRow, nCol);
		Vertex avPath[MAX_VERTEX_NUM];
		int nVexNum = 0;
		//判断是否是相同图片
		if (m_pGameC->Link(avPath, nVexNum)) {
			//画提示线
			DrawTipLine(avPath, nVexNum);
			//清除
			UpdateMap();
			//if(!m_flag.bScore)
				JudgeWin();
			if (m_flag.bScore) {
				DrawGameGrade();
				CalculateGameGrade();
			}
		}

		//使用道具实现
		if (m_bProp) {
			bool bSuc = m_pGameC->PropLink();
			UpdateMap();
			DrawGameGrade();
			m_bProp = false;
		}
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);
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

void CGameDig::OnTimer(UINT_PTR nIDEvent)
{
	DrawGameTime();
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying) {
		m_GameProgress.StepIt();
		JudgeWin();
	}
	
	CDialogEx::OnTimer(nIDEvent);
}


void CGameDig::DrawGameTime()
{
	//CPaintDC dc(this);
	CFont timeFont;
	timeFont.CreatePointFont(200, _T("Consolas"));
	CFont * oldFont;
	oldFont = m_dcMem.SelectObject(&timeFont);
	m_dcMem.SetTextColor(RGB(215, 202, 153));
	m_dcMem.SetBkColor(RGB(255, 0, 255));
	int time = m_GameProgress.GetPos();
	CString strTime;
	strTime.Format(_T("%d"), time);
	//dc.GetTextExtent(strTime);
	CRect rect;
	GetClientRect(&rect);
	CSize size;
	size = m_dcMem.GetTextExtent(strTime, strTime.GetLength());
	int x = ((rect.Width() - size.cx) / 2) + 340;
	int y = ((rect.Height() - size.cy) / 2) + 210;
	m_dcMem.TextOutW(x, y, strTime);

	m_dcMem.SelectObject(&timeFont);
	Invalidate(FALSE);
}


void CGameDig::JudgeWin()
{
	if (m_flag.bScore) {
		int	bGameStatus = m_pGameC->IsWin(1000000);
		if (bGameStatus == GAME_PALY) {
			return;
		}
		else {
			m_bPlaying = false;
			KillTimer(PLAY_TIMER_ID);

			CString strTitle;
			this->GetWindowTextW(strTitle);
			if (bGameStatus == GAME_SUCCESS) {
				MessageBox(_T("WIN!!!!"), strTitle);

				INT_PTR nRes;
				nRes = MessageBox(_T("您确定要将积分记入排行榜吗？"), _T("积分记录"), MB_OKCANCEL | MB_ICONQUESTION);
				if (IDCANCEL == nRes)
					return;
				else {
					m_pGameC->SaveScore();
				}
			}
			else
			{
				MessageBox(_T("oh, NO!!!! GAME OVER!!!"), strTitle);
			}
			this->GetDlgItem(IDC_BUTTON_BASIC_MODEL_BEGIN_GAME)->EnableWindow(TRUE);
		}
	}
	else {
		int	bGameStatus = m_pGameC->IsWin(m_GameProgress.GetPos());
		if (bGameStatus == GAME_PALY) {
			return;
		}
		else {
			m_bPlaying = false;
			KillTimer(PLAY_TIMER_ID);

			CString strTitle;
			this->GetWindowTextW(strTitle);
			if (bGameStatus == GAME_SUCCESS) {
				MessageBox(_T("WIN!!!!"), strTitle);
			}
			else
			{
				MessageBox(_T("oh, NO!!!! GAME OVER!!!"), strTitle);
			}
			this->GetDlgItem(IDC_BUTTON_BASIC_MODEL_BEGIN_GAME)->EnableWindow(TRUE);
		}
	}
}

void CGameDig::SetGameModel(CGameControl* pGameC) {
	m_pGameC = pGameC;
}

void CGameDig::DrawGameGrade() {
	int nGrade = m_pGameC->GetGrade();
	CFont scoreFont;
	scoreFont.CreatePointFont(200, _T("Consolas"));
	CFont * oldFont;
	oldFont = m_dcMem.SelectObject(&scoreFont);
	m_dcMem.SetTextColor(RGB(215, 202, 153));
	m_dcMem.SetBkColor(RGB(255, 0, 255));

	CString strScore;
	strScore.Format(_T("%d"), nGrade);
	CRect rect;
	GetClientRect(&rect);
	CSize size;
	size = m_dcMem.GetTextExtent(strScore, strScore.GetLength());
	int x = ((rect.Width() - size.cx) / 2) + 340;
	int y = ((rect.Height() - size.cy) / 2) + 210;
	m_dcMem.TextOutW(x, y, strScore);

	m_dcMem.SelectObject(&scoreFont);
	Invalidate(FALSE);
}

void CGameDig::CalculateGameGrade() {
	int nGrade = m_pGameC->GetGrade();
	if (nGrade >= 20 && !this->GetDlgItem(IDC_BUTTON_BASIC_MODEL_PROMPT)->IsWindowEnabled()) {
		this->GetDlgItem(IDC_BUTTON_BASIC_MODEL_PROMPT)->EnableWindow(TRUE);

	}


	if (nGrade >= 50 && !this->GetDlgItem(IDC_BUTTON_BASIC_MODEL_REARANGEMENT)->IsWindowEnabled()) {
		this->GetDlgItem(IDC_BUTTON_BASIC_MODEL_REARANGEMENT)->EnableWindow(TRUE);
		//nGrade = nGrade - 50;
		//m_pGameC->SetGrade(nGrade);
	}

	if (nGrade % 100 == 0) {
		if(!this->GetDlgItem(IDC_BUTTON_TRICK)->IsWindowEnabled())
			this->GetDlgItem(IDC_BUTTON_TRICK)->EnableWindow(TRUE);
		int nProp = m_pGameC->GetPropNum();
		nProp++;
		m_pGameC->SetPropNum(nProp);
	}

}

void CGameDig::OnBnClickedButtonTrick()
{
	if (m_pGameC->GetPropNum() < 1) {
		MessageBox(_T("道具不足!!!"));
		return;
	}
	m_bProp = true;
	//每使用一次道具，道具数量减少一个
	int nProp = m_pGameC->GetPropNum();
	nProp--;
	m_pGameC->SetPropNum(nProp);
}

void CGameDig::UpdateTheme() {

	CConfigLogic logic;

	int style = logic.GetStyle();
	CString elem = logic.GetElemPath();
	CString mask = logic.GetMaskPath();
	CClientDC dc(this);

	HANDLE bmp;
	HANDLE bmpMark;
	switch (style)
	{
	case 1:
		bmp = ::LoadImage(NULL, _T("theme\\element1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		m_dcElement.CreateCompatibleDC(&dc);
		m_dcElement.SelectObject(bmp);
		bmpMark = ::LoadImage(NULL, _T("theme\\elementMask1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		m_dcMark.CreateCompatibleDC(&dc);
		m_dcMark.SelectObject(bmpMark);
		UpdateMap();
		break;
	case 2:
		bmp = ::LoadImage(NULL, _T("theme\\element2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		m_dcElement.CreateCompatibleDC(&dc);
		m_dcElement.SelectObject(bmp);
		bmpMark = ::LoadImage(NULL, _T("theme\\elementMask2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		m_dcMark.CreateCompatibleDC(&dc);
		m_dcMark.SelectObject(bmpMark);
		UpdateMap();
		break;
	case 3:
		bmp = ::LoadImage(NULL, elem, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		m_dcElement.CreateCompatibleDC(&dc);
		m_dcElement.SelectObject(bmp);
		bmpMark = ::LoadImage(NULL, mask, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		m_dcMark.CreateCompatibleDC(&dc);
		m_dcMark.SelectObject(bmpMark);
		UpdateMap();
		break;
	default:
		break;
	}
}