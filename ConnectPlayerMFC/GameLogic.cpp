#include "stdafx.h"
#include "GameLogic.h"
#include <iostream>

GameLogic::GameLogic()
{
	m_nVexNum = 0;
	m_nCorner = 0;
	for (int i = 0; i <  MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			m_anPath[MAX_PIC_NUM * i + j] = -1;
		}
	}
}


GameLogic::~GameLogic()
{
}

void GameLogic::InitMap(CGraph &graph) {
	/*int anTemp[4][4] = {
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
	}*/

	/*int anTemp[16];
	//
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			anTemp[i * 4 + j] = i;
		}
	}
	srand((int)time(NULL));



	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			graph.AddVertex(anTemp[i * 4 + j]);
			UpdateArc(graph, i, j);
		}
	}*/
	//////////////////////////////////////////////////////////////////////////
	//160的情况
	int anTemp[MAX_VERTEX_NUM];
	for (int i = 0; i < REPEAT_NUM; i++) {
		for (int j = 0; j < MAX_PIC_NUM; j++) {
			anTemp[i * MAX_PIC_NUM + j] = j;
		}
	}
	srand((int)time(NULL));

	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		int nTemp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = nTemp;
	}
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j <  MAX_COL; j++) {
			graph.AddVertex(anTemp[i * MAX_PIC_NUM + j]);
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
	m_anPath[m_nVexNum] = nV;
	m_nVexNum++;
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
		if ((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2 != m_anPath[m_nVexNum - 2]) {
			return true;
		}
	}
	return false;
}
bool GameLogic::SearchPath2(CGraph &graph, int nV0, int nV1) {
	//得到顶点数
	int nVexnum = graph.GetVexnum();
	//遍历图中nV0行，从0列到nVexnum列，值为true的点
	for (int nVi = 0; nVi < nVexnum; nVi++) {
		if (graph.GetArc(nV0, nVi) && !IsExist(nVi)) {
			//压入当前顶点。假设为路径的一个有效顶点
			PushVertex(nVi);
			if (m_nCorner > 2) {
				PopVertex();
				continue;
			}
			if (nVi != nV1) 
			{
				//当中间顶点为空时，表示该条路径不通
				if (graph.GetVertex(nVi) != BLANK) 
				{
					PopVertex();
					continue;
				}
				//如果nVi是一个已消除的点，则判断（nVi,nV1）是否连通
				if (SearchPath2(graph, nVi, nV1)) {
					return true;
				}
			}
			else
			{
				return true;
			}
			PopVertex();
		}
	}
	return false;
}

bool GameLogic::IsLink(CGraph &graph, Vertex v1, Vertex v2) {
	int nV1Index = v1.row * MAX_PIC_NUM + v1.col;
	int nV2Index = v2.row * MAX_PIC_NUM + v2.col;

	PushVertex(nV1Index);
	if (SearchPath2(graph, nV1Index, nV2Index)) {
		return true;
	}
	PopVertex();
	//采用线性结构判断方法来对非线性结构判断

	return false;
}

void GameLogic::Clear(CGraph &graph, Vertex v1, Vertex v2) {
	int nV1Index = v1.row * MAX_PIC_NUM + v1.col;
	int nV2Index = v2.row * MAX_PIC_NUM + v2.col;

	graph.UpdateVertex(nV1Index, BLANK);
	graph.UpdateVertex(nV2Index, BLANK);

	UpdateArc(graph, v1.row, v1.col);
	UpdateArc(graph, v2.row, v2.col);

}

void GameLogic::UpdateArc(CGraph &graph, int nRow, int nCol) {
	int nV1Index = nRow * MAX_PIC_NUM + nCol;
	if (nCol > 0) {
		int nV2Index = nV1Index - 1;
		int nInfo1 = graph.GetVertex(nV1Index);
		int nInfo2 = graph.GetVertex(nV2Index);
		//TODO：判断与左边相邻的是否有关系
		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
			graph.AddArc(nV1Index, nV2Index);
		}
	}

	if (nCol < MAX_COL - 1) {
		int nV2Index = nV1Index + 1;
		//TODO：判断与右边相邻的是否有关系
		int nInfo1 = graph.GetVertex(nV1Index);
		int nInfo2 = graph.GetVertex(nV2Index);
		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
			graph.AddArc(nV1Index, nV2Index);
		}
	}

	if (nRow > 0) {
		int nV2Index = nV1Index - MAX_PIC_NUM;
		//TODO：判断与正上方是否有关系
		int nInfo1 = graph.GetVertex(nV1Index);
		int nInfo2 = graph.GetVertex(nV2Index);
		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
			graph.AddArc(nV1Index, nV2Index);
		}
	}

	if (nRow < MAX_ROW - 1) {
		int nV2Index = nV1Index + MAX_PIC_NUM;
		//TODO：判断与正下方是否有关系
		int nInfo1 = graph.GetVertex(nV1Index);
		int nInfo2 = graph.GetVertex(nV2Index);
		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
			graph.AddArc(nV1Index, nV2Index);
		}
	}
}


int GameLogic::GetVexPath(Vertex avPath[MAX_VERTEX_NUM]) {
	for (int i = 0; i < m_nVexNum; i++) {
		Vertex v;
		int nIndex = m_anPath[i];
		v.row = nIndex / MAX_PIC_NUM;
		v.col = nIndex % MAX_PIC_NUM;
		v.info = nIndex;
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

bool GameLogic::IsMoreTwoCorner(Vertex avPath[MAX_VERTEX_NUM]) {
	if (m_nVexNum < 3) {
		return false;
	}
	else {
		int nCorner = 0;
		for (int i = 3; i < m_nVexNum; i++) {
			if ((m_anPath[i - 1] + m_anPath[i - 3]) / 2 == m_anPath[i - 2])
				nCorner++;
		}
		if (nCorner > 2)
			return true;
		else
			return false;
	}
}

void GameLogic::correctPath(Vertex avPath[MAX_VERTEX_NUM], int info1, int info2) {

	if (info1 == 0)
		return;

	int begin = 0;
	int beginNum = 0;
	int end = 0;
	int endNum = 0;
	for (int i = 0; i < m_nVexNum; i++) {
		if (avPath[i].info = info1) {
			begin = i;
			beginNum++;
		}
		if(beginNum == 1)	break;
	}
	for (int i = 0; i < m_nVexNum; i++){
		if (avPath[i].info == info2) {
			end = i;
			endNum++;
		}
		if(endNum == 1)
			break;
	}

	if (end - begin + 1 == m_nVexNum)
		return;

	//修正
	for (int i = end + 1; i < MAX_VERTEX_NUM; i++) {
		avPath[i].row = -1;
		avPath[i].col = -1;
		avPath[i].info = -1;

		m_anPath[i] = -1;
		m_nVexNum = end - begin + 1;
	}
}

bool GameLogic::IsNoCorner(Vertex avPath[MAX_VERTEX_NUM], int n) {
	/*if (avPath[0].row == avPath[n - 1].row || avPath[0].col == avPath[n - 1].col)
		return true;
	else
		return false;*/
	
	if (avPath[0].row == avPath[n - 1].row) {
		if (abs(avPath[0].info - avPath[n - 1].info) == 1) {
			return true;
		}
		int colDivition = 0;
		int tempRow = avPath[0].row;
		for (int i = 1; i < n - 1; i++) {
			if (avPath[i].row == tempRow) {
				colDivition++;
			}
		}
		if (colDivition == (abs(avPath[0].col - avPath[n - 1].col) - 1))
			return true;
		else
			return false;
	}

	if (avPath[0].col == avPath[n - 1].col) {
		if (abs(avPath[0].info - avPath[n - 1].info) % MAX_PIC_NUM == 0) {
			return true;
		}
		int rowDivition = 0;
		int tempCol = avPath[0].row;
		for (int i = 1; i < n - 1; i++) {
			if (avPath[i].row == tempCol) {
				rowDivition++;
			}
		}
		if (rowDivition == (abs(avPath[0].row - avPath[n - 1].row) - 1))
			return true;
		else
			return false;
	}

	return false;
}

bool GameLogic::IsOneCorner(Vertex avPath[MAX_VERTEX_NUM], int n) {
	Vertex begin = avPath[0];
	Vertex end = avPath[n - 1];
	for (int i = 1; i < n - 1; i++) {
		if ((avPath[i].row == begin.row && avPath[i].col == end.col) || (avPath[i].col == begin.col && avPath[i].row == end.row)) {
			return true;
		}
	}
	return false;
}

bool GameLogic::IsTwoCorner(Vertex avPath[MAX_VERTEX_NUM], int n) {
	Vertex begin = avPath[0];
	Vertex end = avPath[n - 1];
	Vertex c1;
	Vertex c2;
	for (int i = 1; i < n - 1; i++) {
		if (avPath[i].col == begin.col || avPath[i].row == begin.row) {
			c1 = avPath[i];
		}
		if (avPath[i].col == end.col || avPath[i].row == end.row) {
			c2 = avPath[i];
		}
	}
	if ((c1.row == c2.row || c1.col == c2.col) && c1.info != -1 && c2.info != -1) {
		return true;
	}
	return false;
}



bool GameLogic::SearchValidPath(CGraph& graph)
{
	//得到顶点数
	int nVexnum = graph.GetVexnum();
	for (int i = 0; i < nVexnum; i++) {
		//得到第一个非空顶点
		//遍历得到第二个同色顶点
		for (int j = 0; j < nVexnum; j++) {
			if (i != j) {
				//如果i和j同色
				int nInfo1 = graph.GetVertex(i);
				int nInfo2 = graph.GetVertex(j);
				if (nInfo1 == nInfo2 && nInfo1 != BLANK && nInfo2 != BLANK) {
					//压入第一个顶点
					PushVertex(i);
					//搜寻两个点之间的连通路径
					if (SearchPath2(graph, i, j)) {
						return true;
					}
					PopVertex();
				}
			}
		}
	}
	return false;
}

//需修改

void GameLogic::ResetGraph(CGraph& graph)
{
	//随机交换顶点数组中两个顶点的值
	srand((int)time(NULL));
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		graph.changeInfo(nIndex1, nIndex2);
	}

	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			UpdateArc(graph, i, j);
		}
	}

}
