#include "stdafx.h"
#include "Graph.h"


CGraph::CGraph()
{
	InitGraph();
}


CGraph::~CGraph()
{
}

void CGraph::InitGraph() {
	//初始化顶点
	for (int i = 0; i < MAX_VERTEX_NUM; i++){
		m_Vertices[i] = -1;
	}
	//初始化边
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		//
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			//
			m_AdjMatrix[i][j] = false;
		}
	}
	m_nVexnum = 0;
	m_nArcnum = 0;
}


int CGraph::AddVertex(int nInfo){
	if (m_nVexnum >= MAX_VERTEX_NUM) {
		return m_nVexnum;
	}
	m_Vertices[m_nVexnum++] = nInfo;
	return m_nVexnum;
}


void CGraph::AddArc(int nV1Index, int nV2Index){
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

int CGraph::GetVertex(int nIndex) {
	return m_Vertices[nIndex];
}

int CGraph::GetVexnum() {
	return m_nVexnum;
}

bool CGraph::GetAdiMatrix(int i, int j) {
	return m_AdjMatrix[i][j];
}

bool CGraph::GetArc(int nV1Index, int nV2Index) {
	return m_AdjMatrix[nV1Index][nV2Index];
}

void CGraph::UpdateVertex(int nIndex, int info) {
	m_Vertices[nIndex] = info;
}

void CGraph::ClearGraph() {
	InitGraph();
}

void CGraph::changeInfo(int info1, int info2) {
	int temp = m_Vertices[info1];
	m_Vertices[info1] = m_Vertices[info2];
	m_Vertices[info2] = temp;
}