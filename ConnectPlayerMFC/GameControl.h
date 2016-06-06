#pragma once
#include "global.h"
#include "GameLogic.h"
#include "Graph.h"
#include "Test.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();

	virtual void StartGame() = 0;

	virtual int IsWin(int nTime) {
		GameLogic logic;
		if (nTime <= 0) {
			m_graph.ClearGraph();
			return GAME_LOSE;
		}
		if (logic.IsBlank(m_graph)) {
			m_graph.ClearGraph();
			return GAME_SUCCESS;
		}
		return GAME_PALY;
	};

	virtual bool Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum) {
		GameLogic gameLogic;
		//�ж��Ƿ�Ϊ��
		if (gameLogic.IsBlank(m_graph))
			return false;
		//����һ����Ч����ʾ·��
		if (gameLogic.SearchValidPath(m_graph)) {
			//����·������
			nVexnum = gameLogic.GetVexPath(avPath);
			return true;
		}
		return false;
	};

	virtual void ResetGraph() {
		GameLogic gameLogic;
		gameLogic.ResetGraph(m_graph);
	};

	virtual void SetGrade(int nGrade) {
		m_nGrade = nGrade;
	}

	virtual int GetGrade() {
		return m_nGrade;
	}

	virtual void SetPropNum(int nProp) {
		m_nProp = nProp;
	}

	virtual int GetPropNum() {
		return m_nProp;
	}


	virtual bool PropLink() {
		return true;
	}

	//void StartGame();
	//int IsWin(int nTime);
	//bool Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum);
	//void ResetGraph();

	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	virtual bool Link(Vertex avPath[MAX_VERTEX_NUM], int &nVexNum) = 0;

	void SetGameFlag(FLAG flag);
	FLAG GetGameFlag();

protected:
	CGraph m_graph;//ͼ
	Vertex m_ptSelFirst;//ѡ�еĵ�һ����
	Vertex m_ptSelSec;//ѡ�еĵڶ�����
	CTest m_test;
	FLAG m_flag;

	int m_nGrade;
	int m_nProp;
};

