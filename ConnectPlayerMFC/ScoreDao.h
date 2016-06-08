#pragma once
#include "global.h"
#include <vector>
class CScoreDao
{
public:
	CScoreDao();
	~CScoreDao();

	bool Save(const CString& strPath, SCORE & score);
	//bool Read(const CString& strPath, SCORE list[], int nMode);
	bool Read(const CString& strPath, std::vector<SCORE>& list, int nMode);
	bool Parse(const CString& strScore, SCORE* pScore, int nMode);
};

