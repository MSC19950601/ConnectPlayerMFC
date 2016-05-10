#pragma once
#include "global.h"
#include "GameLogic.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();

	void StartGame();
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	bool Link(Vertex avPath[2]);
private:
	int m_anMap[4][4];//初始游戏地图为4行4列
	Vertex m_ptSelFirst;//选中的第一个点
	Vertex m_ptSelSec;//选中的第二个点
};

