#pragma once
//���嶥��ṹ��
typedef struct tagVertex {
	int row;//��
	int col;//��
	int info;//��Ϣ��
	tagVertex() :row(-1), col(-1), info(-1) {};
}Vertex;

#define BLANK -1