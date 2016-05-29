#pragma once
#include "global.h"
typedef int Vertices[MAX_VERTEX_NUM];
typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
//图数据结构
class CGraph
{
public:
	CGraph();
	~CGraph();

protected:
	Vertices m_Vertices;
	AdjMatrix m_AdjMatrix;
	int m_nVexnum;
	int m_nArcnum;

public:
	void InitGraph();
	int AddVertex(int nInfo);
	void AddArc(int nV1Index, int nV2Index);
	int GetVertex(int nIndex);
	int GetVexnum();
	bool GetAdiMatrix(int i, int j);
	bool GetArc(int nV1Index, int nV2Index);
	void UpdateVertex(int nIndex, int info);
	void ClearGraph();
};

