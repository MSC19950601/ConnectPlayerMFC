#pragma once
//���嶥��ṹ��
typedef struct tagVertex {
	int row;//��
	int col;//��
	int info;//��Ϣ��
	tagVertex() :row(-1), col(-1), info(-1) {};
}Vertex;

typedef struct tagFlag{
	bool bTimer;//��ʱ������
	bool bProp;//����
	bool bScore;//����
	CString szTitle;//�Ի������������
}FLAG;//true��ʾ��ʾ��false��ʾ����ʾ

#define BLANK -1

#define MAX_ROW 10 // ��Ϸ��ͼ����
#define MAX_COL 16 // ��Ϸ��ͼ����
#define MAX_VERTEX_NUM 160 // ������
#define MAX_PIC_NUM 16 // ͼƬ��ɫ
#define REPEAT_NUM 10 // ÿ�ֻ�ɫͼƬ����
#define MAP_TOP 50 // ��Ϸ��ͼ���Ͻ�������
#define MAP_LEFT 50 // ��Ϸ��ͼ���ϽǺ�����
#define PIC_WIDTH 40 // ��ϷͼƬ���
#define PIC_HEIGHT 40 // ��ϷͼƬ�߶�

#define PLAY_TIMER_ID 1

#define GAME_LOSE -1
#define GAME_SUCCESS 0
#define GAME_PALY 1