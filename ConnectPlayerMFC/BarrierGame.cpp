#include "stdafx.h"
#include "BarrierGame.h"


CBarrierGame::CBarrierGame()
{
	m_nBarrier = 1;
}


CBarrierGame::~CBarrierGame()
{
}

void CBarrierGame::StartGame() {
	GameLogic gameLogic;
	gameLogic.InitMap(m_graph);
	m_test.output(m_graph);
}

bool CBarrierGame::Link(Vertex avPath[MAX_VERTEX_NUM], int &nVexNum) {
	//m_ptSelSec,m_ptFirstSec «∑Ò¡¨Õ®
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

int CBarrierGame::IsWin(int nTime) {
	GameLogic logic;
	if (nTime <= 0) {
		m_graph.ClearGraph();
		return GAME_LOSE;
	}
	if (logic.IsBlank(m_graph)) {
		m_graph.ClearGraph();
		return GAME_NEXT;
	}
	return GAME_PALY;
}

bool CBarrierGame::SaveScore() {
	int finalScore = m_nGrade;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	int year = 1900 + ltm->tm_year;
	int month = 1 + ltm->tm_mon;
	int day = ltm->tm_mday;
	int hour = ltm->tm_hour;
	int minute = ltm->tm_min;
	int sec = ltm->tm_sec;
	SCORE newScore;
	newScore.nGrade = finalScore;
	newScore.nLevel = newScore.nGrade / 500 + 1;
	newScore.nNode = 2;
	newScore.strName.Format(_T("%d%02d%02d%02d%02d%02d"), year, month, day, hour, minute, sec);
	CScoreLogic scoreLogic;
	if (scoreLogic.SaveScore(newScore)) {

		return true;
	}
	return false;
}
