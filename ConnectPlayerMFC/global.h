#pragma once
//定义顶点结构体
typedef struct tagVertex {
	int row;//行
	int col;//列
	int info;//信息类
	tagVertex() :row(-1), col(-1), info(-1) {};
}Vertex;

#define BLANK -1