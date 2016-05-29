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
	bool Link(Vertex avPath[16], int &nVexNum);
	bool IsWin();
	bool Help(Vertex avPath[16], int &nVexnum);
private:


	int m_anMap[4][4];//��ʼ��Ϸ��ͼΪ4��4��
	CGraph m_graph;//ͼ
	Vertex m_ptSelFirst;//ѡ�еĵ�һ����
	Vertex m_ptSelSec;//ѡ�еĵڶ�����

	CTest m_test;
};

