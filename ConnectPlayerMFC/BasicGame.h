#pragma once
#include "GameControl.h"
class CBasicGame :
	public CGameControl
{
public:
	CBasicGame();
	~CBasicGame();
	void StartGame();
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int &nVexNum);
protected:
};

