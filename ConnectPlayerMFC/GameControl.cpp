#include "stdafx.h"
#include "GameControl.h"


CGameControl::CGameControl()
{
	m_nGrade = 0;
	m_nBarrier = 1;
}


CGameControl::~CGameControl()
{
}

int CGameControl::GetElement(int nRow, int nCol) {
	return m_graph.GetVertex(nRow * MAX_PIC_NUM + nCol);
}

void CGameControl::SetFirstPoint(int nRow, int nCol) {
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
	m_ptSelFirst.info = MAX_PIC_NUM * nRow + nCol;
}

void CGameControl::SetSecPoint(int nRow, int nCol) {
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
	m_ptSelSec.info = MAX_PIC_NUM * nRow + nCol;
}

//bool CGameControl::Link(Vertex avPath[MAX_VERTEX_NUM], int &nVexNum) {
//	//m_ptSelSec,m_ptFirstSec是否连通
//	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col) {
//		return false;
//	}
//
//	int nInfo1 = m_graph.GetVertex(m_ptSelFirst.row * MAX_PIC_NUM + m_ptSelFirst.col);
//	int nInfo2 = m_graph.GetVertex(m_ptSelSec.row * MAX_PIC_NUM + m_ptSelSec.col);
//
//	int info1 = m_ptSelFirst.row * MAX_PIC_NUM + m_ptSelFirst.col;
//	int info2 = m_ptSelSec.row * MAX_PIC_NUM + m_ptSelSec.col;
//	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
//		return false;
//	}
//
//	GameLogic gameLogic;
//	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec)) {
//		//nVexNum = gameLogic.GetVexPath(avPath);
//		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);
//		//m_test.output(m_graph);
//		//avPath[0] = m_ptSelFirst;
//		//avPath[nVexNum] = m_ptSelSec;//临时成功
//		nVexNum = gameLogic.GetVexPath(avPath);
//
//		//对生成的路径尽心预判
//		/*if (gameLogic.IsMoreTwoCorner(avPath)) {
//			return false;
//		}*/
//
//		//对搜索路径进行修正
//		/*gameLogic.correctPath(avPath,info1,info2);
//		if (gameLogic.IsNoCorner(avPath, nVexNum)) {
//			avPath[0] = m_ptSelFirst;
//			avPath[1] = m_ptSelSec;
//			nVexNum = 2;
//			return true;
//		}
//		if (gameLogic.IsOneCorner(avPath, nVexNum)) {
//			Vertex begin = avPath[0];
//			Vertex end = avPath[nVexNum - 1];
//			Vertex corner;
//			for (int i = 1; i < nVexNum - 1; i++) {
//				if ((avPath[i].row == begin.row && avPath[i].col == end.col) || (avPath[i].col == begin.col && avPath[i].row == end.row)) {
//					corner = avPath[i];
//				}
//			}
//			avPath[0] = m_ptSelFirst;
//			avPath[1] = corner;
//			avPath[2] = m_ptSelSec;
//			nVexNum = 3;
//			return true;
//		}
//
//		if (gameLogic.IsTwoCorner(avPath, nVexNum)) {
//			Vertex begin = avPath[0];
//			Vertex end = avPath[nVexNum - 1];
//			Vertex c1;
//			Vertex c2;
//			for (int i = 1; i < nVexNum - 1; i++) {
//				if (avPath[i].col == begin.col || avPath[i].row == begin.row) {
//					c1 = avPath[i];
//				}
//				if (avPath[i].col == end.col || avPath[i].row == end.row) {
//					c2 = avPath[i];
//				}
//			}
//			if ((c1.row == c2.row || c1.col == c2.col) && c1.info != -1 && c2.info != -1) {
//				avPath[0] = m_ptSelFirst;
//				avPath[1] = c1;
//				avPath[2] = c2;
//				avPath[3] = m_ptSelSec;
//				nVexNum = 4;
//				return true;
//			}
//		}*/
//
//		return true;
//	}
//	return false;
//}

void CGameControl::SetGameFlag(FLAG flag) {
	m_flag = flag;
}

FLAG CGameControl::GetGameFlag() {
	return m_flag;
}
//int CGameControl::IsWin(int nTime) {
//	GameLogic logic;
//	if (nTime <= 0) {
//		m_graph.ClearGraph();
//		return GAME_LOSE;
//	}
//	if (logic.IsBlank(m_graph)) {
//		m_graph.ClearGraph();
//		return GAME_SUCCESS;
//	}
//	return GAME_PALY;
//}
//bool CGameControl::Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum) {
//	GameLogic gameLogic;
//	//判断是否为空
//	if (gameLogic.IsBlank(m_graph))
//		return false;
//	//查找一个有效的提示路径
//	if (gameLogic.SearchValidPath(m_graph)) {
//		//返回路径顶点
//		nVexnum = gameLogic.GetVexPath(avPath);
//		return true;
//	}
//	return false;
//}
//void CGameControl::ResetGraph()
//{
//	GameLogic gameLogic;
//	gameLogic.ResetGraph(m_graph);
//}
//
//void CGameControl::StartGame() {
//	GameLogic gameLogic;
//	gameLogic.InitMap(m_graph);
//	m_test.output(m_graph);
//}