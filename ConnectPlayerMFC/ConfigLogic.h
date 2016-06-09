#pragma once
#include "Config.h"
class CConfigLogic
{
public:
	CConfigLogic();
	~CConfigLogic();

public:
	int GetStyle();
	CString GetElemPath();
	CString GetMaskPath();
};

