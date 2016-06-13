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

	virtual int IsWin(int nTime) = 0; 

	virtual bool Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum) {
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

	void SetBarrierNum(int nBarrierNum) {
		m_nBarrier = nBarrierNum;
	}
	int GetBarrierNum() {
		return m_nBarrier;
	}

	//排行榜
	virtual bool SaveScore() {
		return false;
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
	CGraph m_graph;//图
	Vertex m_ptSelFirst;//选中的第一个点
	Vertex m_ptSelSec;//选中的第二个点
	CTest m_test;
	FLAG m_flag;

	int m_nGrade = 0;
	int m_nProp;
	int m_nBarrier;
};

