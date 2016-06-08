#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include "GameControl.h"
#include "ScoreLogic.h"
class CEasyGame :
	public CGameControl
{
public:
	CEasyGame();
	~CEasyGame();

	void StartGame();
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int &nVexNum);
	int IsWin(int nTime);
	bool Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum);
	void ResetGraph();
	bool PropLink();
	void SetPropNum(int nPropNum);
	int GetPropNum();
	bool SaveScore();
protected:
	int m_nProp;
};

