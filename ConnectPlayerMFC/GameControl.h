#pragma once
#include "global.h"
#include "GameLogic.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();

	void StartGame();
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	bool Link(Vertex avPath[2]);
private:
	int m_anMap[4][4];//��ʼ��Ϸ��ͼΪ4��4��
	Vertex m_ptSelFirst;//ѡ�еĵ�һ����
	Vertex m_ptSelSec;//ѡ�еĵڶ�����
};

