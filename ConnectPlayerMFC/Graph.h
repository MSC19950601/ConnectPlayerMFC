#pragma once

//ͼ���ݽṹ
class CGraph
{
public:
	CGraph();
	~CGraph();

#define MAX_VEXTEX_NUM 16
	typedef int Vertices[MAX_VEXTEX_NUM];
	typedef bool AdjMatrix[MAX_VEXTEX_NUM][MAX_VEXTEX_NUM];
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

