#include "stdafx.h"
#include "ScoreLogic.h"
#include <string>

CScoreLogic::CScoreLogic()
{
}


CScoreLogic::~CScoreLogic()
{
}

bool CScoreLogic::SaveScore(SCORE &score) {
	CScoreDao scoreDAO;
	CString filePathFinal = _T("Score\\score.txt");
	if (scoreDAO.Save(filePathFinal, score)) {
		return true;
	}
	return false;
}

//int CScoreLogic::SearchRank(SCORE list[], int nMode) {
int CScoreLogic::SearchRank(std::vector<SCORE>& list, int nMode) {
	CScoreDao scoreDAO;
	CString filePathFinal = _T("Score\\score.txt");
	if (scoreDAO.Read(filePathFinal, list, nMode)) {
		//int res = 0;
		////while (list[res].nNode != -1)
		//while (list.at(res).nNode != -1) {
		//	res++;
		//}
		return list.size();
	}
	return 0;
}