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
	//  DDX_Radio(pDX, IDC_RADIO_ORIGINAL_METRO, m_ThemeConfig);
}


BEGIN_MESSAGE_MAP(CThemeOptionDlg, CDialogEx)
	ON_COMMAND_RANGE(IDC_RADIO_ORIGINAL_METRO, IDC_RADIO_SELF_SETTING_MAKE_SURE, &CThemeOptionDlg::OnBnClickRadio)
	ON_BN_CLICKED(IDC_BUTTON_SELF_SETTING_ELEMENT_PATH_FILE, &CThemeOptionDlg::OnBnClickedButtonSelfSettingElementPathFile)
	ON_BN_CLICKED(IDC_BUTTON_SELF_SETTING_MASK_PATH_FILE, &CThemeOptionDlg::OnBnClickedButtonSelfSettingMaskPathFile)
END_MESSAGE_MAP()


// CThemeOptionDlg 消息处理程序
void CThemeOptionDlg::OnBnClickRadio(UINT nID) {
	switch (nID)
	{
	case IDC_RADIO_ORIGINAL_METRO:
		m_nThemeType = 1;
		m_strElemPath = "theme\\element1.bmp";
		((CButton *)GetDlgItem(IDC_RADIO_ORIGINAL_HERO))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO_SELF_SETTING_MAKE_SURE))->SetCheck(FALSE);
		break;
	case IDC_RADIO_ORIGINAL_HERO:
		m_nThemeType = 2;
		((CButton *)GetDlgItem(IDC_RADIO_ORIGINAL_METRO))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO_SELF_SETTING_MAKE_SURE))->SetCheck(FALSE);
		m_strElemPath = "theme\\element2.bmp";
		break;
	case IDC_RADIO_SELF_SETTING_MAKE_SURE:
		m_nThemeType = 3;
		((CButton *)GetDlgItem(IDC_RADIO_ORIGINAL_HERO))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO_ORIGINAL_METRO))->SetCheck(FALSE);
		break;
	default:
		break;
	}
}



void CThemeOptionDlg::OnBnClickedButtonSelfSettingElementPathFile()
{
	if (((CButton *)GetDlgItem(IDC_RADIO_SELF_SETTING_MAKE_SURE))->GetCheck()
		&& !((CButton *)GetDlgItem(IDC_RADIO_ORIGINAL_METRO))->GetCheck()
		&& !((CButton *)GetDlgItem(IDC_RADIO_ORIGINAL_HERO))->GetCheck()) {
		CString  FilePathName;//文件名参数定义
		CFileDialog Dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (LPCTSTR)_TEXT("BMP Files(*.bmp)|*.bmp|All Files(*.*)|*.*"), NULL);
		//打开文件
		if (Dlg.DoModal() == IDOK)//是否打开成功
		{
			FilePathName = Dlg.GetPathName();//取得文件路径及文件名
			FilePathName = FilePathName.Right(18);
			//SetDlgItemText(IDC_EDIT_SELF_SETTING_ELEMENT_PATH, FilePathName);//在一个地址为IDC_OutPutFile的editbox中显示文件名
			CString later = FilePathName.Right(12);
			CString front = FilePathName.Left(5);
			CString buttom("\\");
			CString newFilePathName = front + buttom + later;
			SetDlgItemText(IDC_EDIT_SELF_SETTING_ELEMENT_PATH, newFilePathName);
			m_strElemPath = newFilePathName;
		}
		else//打开失败处理
		{
			//打开失败处理
			MessageBox(_T("打开失败"), NULL, MB_OK);
		}
	}
	else {
		MessageBox(_T("请选定自定义按钮！"), NULL, MB_OK);
	}

}

void CThemeOptionDlg::Save() {
	//CConfig::GetSingleInstance()->Save();
	CConfig* config = CConfig::GetSingleInstance();
	config->SetStyle(m_nThemeType);
	config->SetElemPath(m_strElemPath);
	config->SetMaskPath(m_strMaskPath);
	config->Save();
}


BOOL CThemeOptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CButton *)GetDlgItem(IDC_RADIO_ORIGINAL_HERO))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_RADIO_ORIGINAL_METRO))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_RADIO_SELF_SETTING_MAKE_SURE))->SetCheck(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CThemeOptionDlg::OnBnClickedButtonSelfSettingMaskPathFile()
{
	if (((CButton *)GetDlgItem(IDC_RADIO_SELF_SETTING_MAKE_SURE))->GetCheck()
		&& !((CButton *)GetDlgItem(IDC_RADIO_ORIGINAL_METRO))->GetCheck()
		&& !((CButton *)GetDlgItem(IDC_RADIO_ORIGINAL_HERO))->GetCheck()) {
		CString  FilePathName;//文件名参数定义
		CFileDialog Dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (LPCTSTR)_TEXT("BMP Files(*.bmp)|*.bmp|All Files(*.*)|*.*"), NULL);
		//打开文件
		if (Dlg.DoModal() == IDOK)//是否打开成功
		{
			FilePathName = Dlg.GetPathName();//取得文件路径及文件名
			FilePathName = FilePathName.Right(22);
			//SetDlgItemText(IDC_EDIT_SELF_SETTING_ELEMENT_PATH, FilePathName);//在一个地址为IDC_OutPutFile的editbox中显示文件名
			CString later = FilePathName.Right(16);
			CString front = FilePathName.Left(5);
			CString buttom("\\");
			CString newFilePathName = front + buttom + later;
			SetDlgItemText(IDC_EDIT_SELF_SETTING_MASK_PATH, newFilePathName);
			m_strMaskPath = newFilePathName;
		}
		else//打开失败处理
		{
			//打开失败处理
			MessageBox(_T("打开失败"), NULL, MB_OK);
		}
	}
	else {
		MessageBox(_T("请选定自定义按钮！"), NULL, MB_OK);
	}
}
