#pragma once
#include "GameControl.h"
#include "ScoreLogic.h"
class CBarrierGame :
	public CGameControl
{
public:
	CBarrierGame();
	~CBarrierGame();

	void StartGame();
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int &nVexNum);
	int IsWin(int nTime);
	bool SaveScore();
protected:
	int m_nBarrier;
};

