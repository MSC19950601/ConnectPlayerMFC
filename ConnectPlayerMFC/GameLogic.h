#pragma once
#include "global.h"
class GameLogic
{
public:
	GameLogic();
	~GameLogic();

public:
	void InitMap(int anMap[][4]);
	void Clear(int anMap[][4], Vertex v1, Vertex v2);
	bool IsLink(int anMap[][4], Vertex v1, Vertex v2);
};

