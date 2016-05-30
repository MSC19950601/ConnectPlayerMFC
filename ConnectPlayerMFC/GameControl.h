#pragma once
#include "global.h"
#include "GameLogic.h"
#include "Graph.h"
#include "Test.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();

	void StartGame();
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int &nVexNum);
	int IsWin(int nTime);
	bool Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum);
private:

	CGraph m_graph;//图
	Vertex m_ptSelFirst;//选中的第一个点
	Vertex m_ptSelSec;//选中的第二个点

	CTest m_test;
public:
	void ResetGraph();
};

