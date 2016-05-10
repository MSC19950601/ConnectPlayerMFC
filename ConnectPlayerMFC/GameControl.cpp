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
	gameLogic.InitMap(m_anMap);
}

int CGameControl::GetElement(int nRow, int nCol) {
	return m_anMap[nRow][nCol];
}

void CGameControl::SetFirstPoint(int nRow, int nCol) {
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

void CGameControl::SetSecPoint(int nRow, int nCol) {
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

bool CGameControl::Link(Vertex avPath[2]) {
	//m_ptSelSec,m_ptFirstSec «∑Ò¡¨Õ®
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col) {
		return false;
	}

	if (m_anMap[m_ptSelFirst.row][m_ptSelFirst.col] != m_anMap[m_ptSelSec.row][m_ptSelSec.col]) {
		return false;
	}

	GameLogic gameLogic;
	if (gameLogic.IsLink(m_anMap, m_ptSelFirst, m_ptSelSec)) {
		gameLogic.Clear(m_anMap, m_ptSelFirst, m_ptSelSec);
		avPath[0] = m_ptSelFirst;
		avPath[1] = m_ptSelSec;
		return true;
	}
	return false;
}
