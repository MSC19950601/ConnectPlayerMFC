#pragma once
#include "global.h"
#include "ScoreDao.h"
#include <vector>
class CScoreLogic
{
public:
	CScoreLogic();
	~CScoreLogic();

	bool SaveScore(SCORE &score);
	//int SearchRank(SCORE list[], int nMode);
	int SearchRank(std::vector<SCORE>& list, int nMode);
};

