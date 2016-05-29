#pragma once
#include "global.h"
#include "Graph.h"
class GameLogic
{
public:
	GameLogic();
	~GameLogic();

public:
	void InitMap(CGraph &graph);
	void Clear(CGraph &graph, Vertex v1, Vertex v2);
	bool IsLink(CGraph &graph, Vertex v1, Vertex v2);
	int GetVexPath(Vertex avPath[16]);
	void UpdateArc(CGraph &graph, int nRow, int nCol);
	bool SearchPath2(CGraph &graph, int nV0, int nV1);
	bool IsExist(int nVi);
	void PushVertex(int nV);
	void PopVertex();
	bool IsCorner();
	bool IsBlank(CGraph &graph);

	bool IsMoreTwoCorner(Vertex avPath[16]);

	void correctPath(Vertex avPath[16], int info1, int info2);

	bool IsNoCorner(Vertex avPath[16],int n);

	bool IsOneCorner(Vertex avPath[16], int n);

	bool IsTwoCorner(Vertex avPath[16], int n);


protected:
	int m_anPath[16] = { -1 };
	int m_nVexNum;
	int m_nCorner;
public:
	bool SearchValidPath(CGraph& graph);
};

