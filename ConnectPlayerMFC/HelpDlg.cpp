// HelpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ConnectPlayerMFC.h"
#include "HelpDlg.h"
#include "afxdialogex.h"


// CHelpDlg �Ի���

IMPLEMENT_DYNAMIC(CHelpDlg, CDialogEx)

CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
{
	//pos = 1;
	nMinPos = 1;
	nMaxPos = 1740;
}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialogEx)
	ON_WM_VSCROLL()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CHelpDlg ��Ϣ�������


void CHelpDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos = pScrollBar->GetScrollPos();

	switch (nSBCode)
	{
	case SB_LINEUP:
		pos -= 1;
		pScrollBar->SetScrollPos(pos, TRUE);
		UpdateHelp(pos);
		break;
	case SB_LINEDOWN:
		pos += 1;
		pScrollBar->SetScrollPos(pos, TRUE);
		UpdateHelp(pos);
		break;
	case SB_PAGEUP:
		pos -= 10;
		pScrollBar->SetScrollPos(pos, TRUE);
		UpdateHelp(pos);
		break;
	case SB_PAGEDOWN:
		pos += 10;
		pScrollBar->SetScrollPos(pos, TRUE);
		UpdateHelp(pos);
		break;
	case SB_TOP:
		pos = nMinPos;
		pScrollBar->SetScrollPos(pos, TRUE);
		UpdateHelp(pos);
		break;
	case SB_BOTTOM:
		pos = nMaxPos;
		pScrollBar->SetScrollPos(pos, TRUE);
		UpdateHelp(pos);
		break;
	case SB_THUMBPOSITION:
		pos = nPos;
		pScrollBar->SetScrollPos(pos, TRUE);
		UpdateHelp(pos);
		break;
	default:
		break;
	}

	

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL CHelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	this->GetClientRect(&rtClient);

	CClientDC dc(this);
	HANDLE hBmpBG = ::LoadImageW(NULL, _T("background\\help1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcHelp.CreateCompatibleDC(&dc);
	m_dcHelp.SelectObject(hBmpBG);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, rtClient.Width(), rtClient.Height());
	m_dcMem.SelectObject(&bmpMem);
	//m_dcMem.BitBlt(0, 0, 800, 1740, &m_dcHelp, 0, 0, SRCCOPY);

	//���ư�����Ϣ��ʾ����
	this->GetDlgItem(IDC_STATIC_HELP)->GetWindowRect(&m_rtHelp);
	this->ScreenToClient(&m_rtHelp);
	//���ư�����Ϣ
	UpdateHelp(0);

	//���ù�����Χ
	CBitmap bmpHelp;
	bmpHelp.Attach(hBmpBG);
	BITMAP bmpInfo;
	bmpHelp.GetBitmap(&bmpInfo);
	//���ù�������Χ
	((CScrollBar*)this->GetDlgItem(IDC_SCROLLBAR_HELP))->SetScrollRange(0, bmpInfo.bmHeight);
	((CScrollBar*)this->GetDlgItem(IDC_SCROLLBAR_HELP))->SetScrollPos(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CHelpDlg::OnPaint()
{

	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	dc.BitBlt(0, 0, rtClient.Width(), rtClient.Height(), &m_dcMem, 0, 0, SRCCOPY);
}


HBRUSH CHelpDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_COPYRIGHT) {
		COLORREF clr = RGB(255, 255, 255);
		pDC->SetBkColor(clr);
		HBRUSH bkBrush = ::CreateSolidBrush(clr);
		return bkBrush;
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CHelpDlg::UpdateHelp(int nPos)
{
	m_dcMem.BitBlt(0, 0, rtClient.Width(), rtClient.Height(), NULL, 0, 0, WHITENESS);
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(), m_rtHelp.Height(), NULL, 0, 0, WHITENESS);
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcHelp, 0, nPos, SRCCOPY);
	InvalidateRect(m_rtHelp, FALSE);
}



