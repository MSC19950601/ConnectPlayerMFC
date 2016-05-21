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

	bool IsOneLine(Vertex avPath[16],int n);

	bool IsOneCorner(Vertex avPath[16], int n);

	bool IsTwoCorner(Vertex avPath[16], int n);


protected:

	int m_anPath[16];
	int m_nVexNum;
	int m_nCorner;
};

