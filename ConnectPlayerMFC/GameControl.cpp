#include "stdafx.h"
#include "GameControl.h"


CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}

void CGameControl::StartGame() {
	GameLogic gameLogic;
	gameLogic.InitMap(m_graph);
	m_test.output(m_graph);
}

int CGameControl::GetElement(int nRow, int nCol) {
	return m_graph.GetVertex(nRow * 4 + nCol);
}

void CGameControl::SetFirstPoint(int nRow, int nCol) {
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

void CGameControl::SetSecPoint(int nRow, int nCol) {
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

bool CGameControl::Link(Vertex avPath[16], int &nVexNum) {
	//m_ptSelSec,m_ptFirstSec是否连通
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col) {
		return false;
	}

	int nInfo1 = m_graph.GetVertex(m_ptSelFirst.row * 4 + m_ptSelFirst.col);
	int nInfo2 = m_graph.GetVertex(m_ptSelSec.row * 4 + m_ptSelSec.col);
	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
		return false;
	}

	GameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec)) {
		//nVexNum = gameLogic.GetVexPath(avPath);
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);
		m_test.output(m_graph);
		//avPath[0] = m_ptSelFirst;
		//avPath[nVexNum] = m_ptSelSec;//临时成功
		nVexNum = gameLogic.GetVexPath(avPath);
		if (gameLogic.IsOneLine(avPath, nVexNum)) {
			avPath[0] = m_ptSelFirst;
			avPath[1] = m_ptSelSec;
			nVexNum = 2;
			return true;
		}
		if (gameLogic.IsOneCorner(avPath, nVexNum)) {
			Vertex begin = avPath[0];
			Vertex end = avPath[nVexNum - 1];
			Vertex corner;
			for (int i = 1; i < nVexNum - 1; i++) {
				if ((avPath[i].row == begin.row && avPath[i].col == end.col) || (avPath[i].col == begin.col && avPath[i].row == end.row)) {
					corner = avPath[i];
				}
			}
			avPath[0] = m_ptSelFirst;
			avPath[1] = corner;
			avPath[2] = m_ptSelSec;
			nVexNum = 3;
			return true;
		}

		if (gameLogic.IsTwoCorner(avPath, nVexNum)) {
			Vertex begin = avPath[0];
			Vertex end = avPath[nVexNum - 1];
			Vertex c1;
			Vertex c2;
			for (int i = 1; i < nVexNum - 1; i++) {
				if (avPath[i].col == begin.col || avPath[i].row == begin.row) {
					c1 = avPath[i];
				}
				if (avPath[i].col == end.col || avPath[i].row == end.row) {
					c2 = avPath[i];
				}
			}
			if ((c1.row == c2.row || c1.col == c2.col) && c1.info != -1 && c2.info != -1) {
				avPath[0] = m_ptSelFirst;
				avPath[1] = c1;
				avPath[2] = c2;
				avPath[3] = m_ptSelSec;
				nVexNum = 4;
				return true;
			}
		}
		return true;
	}
	return false;
}

bool CGameControl::IsWin() {
	GameLogic logic;
	if (logic.IsBlank(m_graph)) {
		m_graph.ClearGraph();
		return true;
	}
	return false;
}
