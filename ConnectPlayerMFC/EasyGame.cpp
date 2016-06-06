#include "stdafx.h"
#include "EasyGame.h"


CEasyGame::CEasyGame()
{
	m_nProp = 0;
}


CEasyGame::~CEasyGame()
{
}

void CEasyGame::StartGame() {
	GameLogic gameLogic;
	gameLogic.InitMap(m_graph);
	m_test.output(m_graph);
}

bool CEasyGame::Link(Vertex avPath[MAX_VERTEX_NUM], int &nVexNum) {
	//m_ptSelSec,m_ptFirstSec是否连通
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col) {
		return false;
	}

	int nInfo1 = m_graph.GetVertex(m_ptSelFirst.row * MAX_PIC_NUM + m_ptSelFirst.col);
	int nInfo2 = m_graph.GetVertex(m_ptSelSec.row * MAX_PIC_NUM + m_ptSelSec.col);

	int info1 = m_ptSelFirst.row * MAX_PIC_NUM + m_ptSelFirst.col;
	int info2 = m_ptSelSec.row * MAX_PIC_NUM + m_ptSelSec.col;
	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
		return false;
	}

	GameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec)) {
		m_nGrade += 10;
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);
		nVexNum = gameLogic.GetVexPath(avPath);
		return true;
	}
	return false;
}

int CEasyGame::IsWin(int nTime) {
	GameLogic logic;
	if (nTime <= 0) {
		m_graph.ClearGraph();
		return GAME_LOSE;
	}
	if (logic.IsBlank(m_graph)) {
		m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	/*GameLogic logic;
	if (logic.IsBlank(m_graph)) {
		m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	else {
		return GAME_SUCCESS;
	}*/
	return	GAME_PALY;
}

bool CEasyGame::Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum) {
	GameLogic gameLogic;
	//判断是否为空
	if (gameLogic.IsBlank(m_graph))
		return false;
	//查找一个有效的提示路径
	if (gameLogic.SearchValidPath(m_graph)) {
		//返回路径顶点
		nVexnum = gameLogic.GetVexPath(avPath);
		return true;
	}
	return false;
}
void CEasyGame::ResetGraph()
{
	GameLogic gameLogic;
	gameLogic.ResetGraph(m_graph);
}



int CEasyGame::GetPropNum() {
	return m_nProp;
}

void CEasyGame::SetPropNum(int nPropNum) {
	m_nProp = nPropNum;
}

bool CEasyGame::PropLink() {

	int nInfo1 = m_graph.GetVertex(m_ptSelFirst.row * MAX_PIC_NUM + m_ptSelFirst.col);
	int nInfo2 = m_graph.GetVertex(m_ptSelSec.row * MAX_PIC_NUM + m_ptSelSec.col);

	int info1 = m_ptSelFirst.row * MAX_PIC_NUM + m_ptSelFirst.col;
	int info2 = m_ptSelSec.row * MAX_PIC_NUM + m_ptSelSec.col;
	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
		return false;
	}
	else {
		GameLogic gameLogic;
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);
		m_nGrade += 10;
		return true;
	}
	return false;
}