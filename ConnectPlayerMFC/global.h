#pragma once
//定义顶点结构体
typedef struct tagVertex {
	int row;//行
	int col;//列
	int info;//信息类
	tagVertex() :row(-1), col(-1), info(-1) {};
}Vertex;

typedef struct tagFlag{
	bool bTimer;//计时进度条
	bool bProp;//道具
	bool bScore;//积分
	CString szTitle;//对话框标题栏文字
}FLAG;//true表示显示，false表示不显示

#define BLANK -1

#define MAX_ROW 10 // 游戏地图行数
#define MAX_COL 16 // 游戏地图列数
#define MAX_VERTEX_NUM 160 // 顶点数
#define MAX_PIC_NUM 16 // 图片花色
#define REPEAT_NUM 10 // 每种花色图片个数
#define MAP_TOP 50 // 游戏地图左上角纵坐标
#define MAP_LEFT 50 // 游戏地图左上角横坐标
#define PIC_WIDTH 40 // 游戏图片宽度
#define PIC_HEIGHT 40 // 游戏图片高度

#define PLAY_TIMER_ID 1

#define GAME_LOSE -1
#define GAME_SUCCESS 0
#define GAME_PALY 1