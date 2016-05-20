#include "stdafx.h"
#include "GameLogic.h"
#include <iostream>

GameLogic::GameLogic()
{
	m_nVexNum = 0;
	m_nCorner = 0;
}


GameLogic::~GameLogic()
{
}

void GameLogic::InitMap(CGraph &graph) {
	int anTemp[4][4] = {
		2,0,1,3,
		2,2,1,3,
		2,1,0,0,
		1,3,0,3
	};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++){
			graph.AddVertex(anTemp[i][j]);
			UpdateArc(graph, i, j);
		}
	}
	
}

bool GameLogic::IsExist(int nVi) {
	for (int i = 0; i < m_nVexNum; i++) {
		if (m_anPath[i] == nVi)	return true;
	}
	return false;
}

void GameLogic::PushVertex(int nV) {
	m_anPath[m_nVexNum++] = nV;
	if (IsCorner()) {
		m_nCorner++;
	}

}

void GameLogic::PopVertex() {
	if (IsCorner()) {
		m_nCorner--;
	}
	m_nVexNum--;
}
bool GameLogic::IsCorner() {
	if (m_nVexNum >= 3) {
		if ((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2 == m_anPath[m_nVexNum - 2]) {
			return true;
		}
	}
	return false;
}
bool GameLogic::SearchPath(CGraph &graph, int nV0, int nV1) {
	//�õ�������
	int nVexnum = graph.GetVexnum();

	//����ͼ��nV0�У���0�е�nVexnum�У�ֵΪtrue�ĵ�
	for (int nVi = 0; nVi < nVexnum; nVi++) {
		if (graph.GetArc(nV0, nVi) && !IsExist(nVi)) {
			//ѹ�뵱ǰ���㡣����Ϊ·����һ����Ч����
			PushVertex(nVi);
			if (m_nCorner > 2) {
				PopVertex();
				continue;
			}
			if (nVi != nV1) {
				//���м䶥��Ϊ��ʱ����ʾ����·����ͬ
				if (graph.GetVertex(nVi) != BLANK) {
					PopVertex();
					continue;
				}
				//���nVi��һ���������ĵ㣬���жϣ�nVi,nV1���Ƿ���ͨ
				if (SearchPath(graph, nVi, nV1)) {
					return true;
				}
			}
			else{
				return true;
			}
			PopVertex();
		}
	}
	return false;
}

bool GameLogic::IsLink(CGraph &graph, Vertex v1, Vertex v2) {
	int nV1Index = v1.row * 4 + v1.col;
	int nV2Index = v2.row * 4 + v2.col;

	//AddVertex(v1);
	PushVertex(nV1Index);
	if (SearchPath(graph, nV1Index, nV2Index)) {
		return true;
	}
	PopVertex();
	//DeleteVertex();

	return false;
}

void GameLogic::Clear(CGraph &graph, Vertex v1, Vertex v2) {
	int nV1Index = v1.row * 4 + v1.col;
	int nV2Index = v2.row * 4 + v2.col;

	graph.UpdateVertex(nV1Index, BLANK);
	graph.UpdateVertex(nV2Index, BLANK);

	UpdateArc(graph, v1.row, v1.col);
	UpdateArc(graph, v2.row, v2.col);

}

void GameLogic::UpdateArc(CGraph &graph, int nRow, int nCol) {
	int nV1Index = nRow * 4 + nCol;
	if (nCol > 0) {
		int nV2Index = nV1Index - 1;
		int nInfo1 = graph.GetVertex(nV1Index);
		int nInfo2 = graph.GetVertex(nV2Index);
		//TODO���ж���������ڵ��Ƿ��й�ϵ
		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
			graph.AddArc(nV1Index, nV2Index);
		}
	}

	if (nCol < 3) {
		int nV2Index = nV1Index + 1;
		//TODO���ж����ұ����ڵ��Ƿ��й�ϵ
		int nInfo1 = graph.GetVertex(nV1Index);
		int nInfo2 = graph.GetVertex(nV2Index);
		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
			graph.AddArc(nV1Index, nV2Index);
		}
	}

	if (nRow > 0) {
		int nV2Index = nV1Index - 4;
		//TODO���ж������Ϸ��Ƿ��й�ϵ
		int nInfo1 = graph.GetVertex(nV1Index);
		int nInfo2 = graph.GetVertex(nV2Index);
		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
			graph.AddArc(nV1Index, nV2Index);
		}
	}

	if (nRow < 3) {
		int nV2Index = nV1Index + 4;
		//TODO���ж������·��Ƿ��й�ϵ
		int nInfo1 = graph.GetVertex(nV1Index);
		int nInfo2 = graph.GetVertex(nV2Index);
		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
			graph.AddArc(nV1Index, nV2Index);
		}
	}
}


/*void GameLogic::AddVertex(Vertex v) {
	m_avPath[m_nVexNum] = v;
	m_nVexNum++;
}

void GameLogic::DeleteVertex() {
	m_nVexNum--;
}*/

int GameLogic::GetVexPath(Vertex avPath[16]) {
	for (int i = 0; i < m_nVexNum; i++) {
		Vertex v;
		int nIndex = m_anPath[i];
		v.row = nIndex / 4;
		v.col = nIndex % 4;
		avPath[i] = v;
	}
	return m_nVexNum;
}

bool GameLogic::IsBlank(CGraph &graph) {
	for (int i = 0; i < graph.GetVexnum(); i++) {
		if (graph.GetVertex(i) != BLANK) {
			
			return false;
		}
	}
	return true;
}


