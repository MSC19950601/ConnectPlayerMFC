// ThemeOptionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ConnectPlayerMFC.h"
#include "ThemeOptionDlg.h"
#include "afxdialogex.h"


// CThemeOptionDlg 对话框

IMPLEMENT_DYNAMIC(CThemeOptionDlg, CDialogEx)

CThemeOptionDlg::CThemeOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONFIG_THEME, pParent)
	, m_strElemPath(_T(""))
{

}

CThemeOptionDlg::~CThemeOptionDlg()
{
}

void CThemeOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SELF_SETTING_ELEMENT_PATH, m_strElemPath);
}


BEGIN_MESSAGE_MAP(CThemeOptionDlg, CDialogEx)
	ON_COMMAND_RANGE(IDC_RADIO_ORIGINAL_METRO, IDC_RADIO_SELF_SETTING_MAKE_SURE, &CThemeOptionDlg::OnBnClickRadio)
	ON_BN_CLICKED(IDC_BUTTON_SELF_SETTING_ELEMENT_PATH_FILE, &CThemeOptionDlg::OnBnClickedButtonSelfSettingElementPathFile)
END_MESSAGE_MAP()


// CThemeOptionDlg 消息处理程序
void CThemeOptionDlg::OnBnClickRadio(UINT nID) {

}



void CThemeOptionDlg::OnBnClickedButtonSelfSettingElementPathFile()
{
	
}

void CThemeOptionDlg::Save() {
	CConfig::GetSingleInstance()->Save();
}
