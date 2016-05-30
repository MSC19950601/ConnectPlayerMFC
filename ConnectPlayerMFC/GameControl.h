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

	CGraph m_graph;//ͼ
	Vertex m_ptSelFirst;//ѡ�еĵ�һ����
	Vertex m_ptSelSec;//ѡ�еĵڶ�����

	CTest m_test;
public:
	void ResetGraph();
};

