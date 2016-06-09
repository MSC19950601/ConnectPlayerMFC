#include "stdafx.h"
#include "ConfigLogic.h"


CConfigLogic::CConfigLogic()
{
}


CConfigLogic::~CConfigLogic()
{
}

int CConfigLogic::GetStyle() {
	return CConfig::GetSingleInstance()->GetStyle();
}

CString CConfigLogic::GetElemPath() {
	return CConfig::GetSingleInstance()->GetElemPath();
}

CString CConfigLogic::GetMaskPath() {
	return CConfig::GetSingleInstance()->GetMaskPath();
}