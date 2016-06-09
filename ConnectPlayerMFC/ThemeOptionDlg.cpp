// ThemeOptionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ConnectPlayerMFC.h"
#include "ThemeOptionDlg.h"
#include "afxdialogex.h"


// CThemeOptionDlg �Ի���

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


// CThemeOptionDlg ��Ϣ�������
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
		CString  FilePathName;//�ļ�����������
		CFileDialog Dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (LPCTSTR)_TEXT("BMP Files(*.bmp)|*.bmp|All Files(*.*)|*.*"), NULL);
		//���ļ�
		if (Dlg.DoModal() == IDOK)//�Ƿ�򿪳ɹ�
		{
			FilePathName = Dlg.GetPathName();//ȡ���ļ�·�����ļ���
			FilePathName = FilePathName.Right(18);
			//SetDlgItemText(IDC_EDIT_SELF_SETTING_ELEMENT_PATH, FilePathName);//��һ����ַΪIDC_OutPutFile��editbox����ʾ�ļ���
			CString later = FilePathName.Right(12);
			CString front = FilePathName.Left(5);
			CString buttom("\\");
			CString newFilePathName = front + buttom + later;
			SetDlgItemText(IDC_EDIT_SELF_SETTING_ELEMENT_PATH, newFilePathName);
			m_strElemPath = newFilePathName;
		}
		else//��ʧ�ܴ���
		{
			//��ʧ�ܴ���
			MessageBox(_T("��ʧ��"), NULL, MB_OK);
		}
	}
	else {
		MessageBox(_T("��ѡ���Զ��尴ť��"), NULL, MB_OK);
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
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CThemeOptionDlg::OnBnClickedButtonSelfSettingMaskPathFile()
{
	if (((CButton *)GetDlgItem(IDC_RADIO_SELF_SETTING_MAKE_SURE))->GetCheck()
		&& !((CButton *)GetDlgItem(IDC_RADIO_ORIGINAL_METRO))->GetCheck()
		&& !((CButton *)GetDlgItem(IDC_RADIO_ORIGINAL_HERO))->GetCheck()) {
		CString  FilePathName;//�ļ�����������
		CFileDialog Dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (LPCTSTR)_TEXT("BMP Files(*.bmp)|*.bmp|All Files(*.*)|*.*"), NULL);
		//���ļ�
		if (Dlg.DoModal() == IDOK)//�Ƿ�򿪳ɹ�
		{
			FilePathName = Dlg.GetPathName();//ȡ���ļ�·�����ļ���
			FilePathName = FilePathName.Right(22);
			//SetDlgItemText(IDC_EDIT_SELF_SETTING_ELEMENT_PATH, FilePathName);//��һ����ַΪIDC_OutPutFile��editbox����ʾ�ļ���
			CString later = FilePathName.Right(16);
			CString front = FilePathName.Left(5);
			CString buttom("\\");
			CString newFilePathName = front + buttom + later;
			SetDlgItemText(IDC_EDIT_SELF_SETTING_MASK_PATH, newFilePathName);
			m_strMaskPath = newFilePathName;
		}
		else//��ʧ�ܴ���
		{
			//��ʧ�ܴ���
			MessageBox(_T("��ʧ��"), NULL, MB_OK);
		}
	}
	else {
		MessageBox(_T("��ѡ���Զ��尴ť��"), NULL, MB_OK);
	}
}
