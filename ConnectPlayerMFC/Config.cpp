#include "stdafx.h"
#include "Config.h"

CConfig* CConfig::m_pConfig = NULL;

CConfig::CConfig()
{
}


CConfig::~CConfig()
{
}

CConfig* CConfig::GetSingleInstance() {
	if (CConfig::m_pConfig == NULL) {
		CConfig::m_pConfig = new CConfig();
		CConfig::m_pConfig->Load();
	}
	return CConfig::m_pConfig;
}

void CConfig::ReleaseInstance() {
	if (CConfig::m_pConfig != NULL) {
		delete CConfig::m_pConfig;
		CConfig::m_pConfig = NULL;
	}
}

void CConfig::Save() {

	CString style;
	style.Format(_T("%d"), m_nStyle);
	::WritePrivateProfileString(_T("Picture"), _T("style"), style, _T("settingTheme\\config.ini"));
	::WritePrivateProfileString(_T("Picture"), _T("Element"), m_strElemPath, _T("settingTheme\\config.ini"));
	::WritePrivateProfileString(_T("Picture"), _T("Mask"), m_strMaskPath, _T("settingTheme\\config.ini"));
}

void CConfig::Load() {
	::GetPrivateProfileString(_T("Picture"), _T("Element"), _T(""), m_strElemPath.GetBuffer(MAX_PATH), MAX_PATH, _T("settingTheme\\config.ini"));
	::GetPrivateProfileString(_T("Picture"), _T("Mask"), _T(""), m_strMaskPath.GetBuffer(MAX_PATH), MAX_PATH, _T("settingTheme\\config.ini"));
	m_nStyle = GetPrivateProfileInt(_T("Picture"), _T("style"), 0, _T("settingTheme\\config.ini"));
	
}
