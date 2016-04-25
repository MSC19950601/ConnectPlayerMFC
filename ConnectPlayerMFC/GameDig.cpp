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


// CGameDig ��Ϣ�������


void CGameDig::InitBackground()
{
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\pic\\background_2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);

	m_dcMem.SelectObject(bmp);
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
