#include "stdafx.h"
#include "ScoreDao.h"
#include <string>

#define  FUCK 0
CScoreDao::CScoreDao()
{
}


CScoreDao::~CScoreDao()
{
}

bool CScoreDao::Save(const CString& strPath, SCORE &score) {
	CStdioFile file;
	if (file.Open(strPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {

		CString node;
		node.Format(_T("0%d"), score.nNode);
		file.Seek(0, CFile::end);
		file.WriteString(node);

		file.Seek(CFile::begin, CFile::end);
		file.WriteString(score.strName);

		CString scoreS;
		if (score.nGrade < 1000)
		{
			scoreS.Format(_T("00%d"), score.nGrade);
		}
		else
		{
			scoreS.Format(_T("0%d"), score.nGrade);
		}
		file.Seek(CFile::begin, CFile::end);
		file.WriteString(scoreS);

		CString level;
		level.Format(_T("%d\r\n"), score.nLevel);
		file.Seek(CFile::begin, CFile::end);
		file.WriteString(level);

		file.Close();
		return true;
	}
	return false;
}

//bool CScoreDao::Read(const CString& strPath, SCORE list[], int nMode) {
bool CScoreDao::Read(const CString& strPath, std::vector<SCORE>& list, int nMode) {
	CStdioFile file;
	if (file.Open(strPath, CFile::modeRead)) {
		int i = 0;
		CString strScore;
		CString strTemp;
		while (file.ReadString(strTemp)) {
			strScore = strTemp;
			SCORE* pScore = new SCORE;
			if (Parse(strScore, pScore, nMode)) {
				list.push_back(*pScore);
				delete pScore;
			}else
				continue;
		}
		file.Close();
		return true;
	}
	return false;
}

bool CScoreDao::Parse(const CString& strScore, SCORE* pScore, int nMode) {
	CString modeTemp = strScore.Mid(1, 1);
	if (_wtoi(modeTemp) == nMode) {
		pScore->nNode = nMode;
		pScore->nLevel = _wtoi(strScore.Right(1));
		pScore->nGrade = _wtoi(strScore.Mid(16, 5));
		pScore->strName = strScore.Mid(2, 14);
		return true;
	}
	return false;
}