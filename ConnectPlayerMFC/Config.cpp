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
		//CConfig::m_pConfig->Load();
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

}
