#pragma once
#include <graphics.h>
#include <vector>

#include "Block.h"

using namespace std;

//游戏类
class Tetris
{
public:
	//构造函数
	//游戏区域的参数：rows-行;cols-列;left-游戏区域离左边框的距离;top-方块从顶部掉落的距离;blockSize-方块大小
	Tetris(int rows,int cols,int left,int top,int blockSize);
	~Tetris();

	void init();//初始化
	void play();//开始游戏

private:
	void keyEvent();//键盘输入事件
	void updateWindow();//渲染游戏界面

	//第一调用返回0
	int getDelay();//返回距离上一次调用该函数，间隔了多少时间（ms）
	void drop();//下落
	void clearLine();//清行
	void moveLeftRight(int offset);//左右移动
	void rotate();//旋转
	void drawScore();//绘制分数
	void checkOver();//游戏结束

	void saveScore();//保存分数
	void displayOver();//渲染结束界面

private:
	int m_nDelay;//刷新时间
	bool m_bUpdate;//是否刷新游戏界面

	int m_nScore;//得分
	int m_nLevel;//当前关卡
	int m_nClearLineCount;//消除的行数
	int m_nHighestScore;//最高分

	bool m_bGameOver;//游戏结束

	//0：空白，没有任何方块
	//5：表示第5种俄罗斯方块（一共七种）
	vector<vector<int>> m_mapData;//存游戏数据 地图的划分 行 列
	
	int m_nRows;//行
	int m_nCols;//列

	int m_nLeftMargin;
	int m_nTopMargin;

	int m_nBlockSize;//俄罗斯方块的大小

	IMAGE m_imgBg;//背景图片
	IMAGE m_imgBG_Win;//胜利背景
	IMAGE m_imgBg_Over;//失败背景

	Block* m_pCurrBlock;//当前方块
	Block* m_pNextBlock;//预告方块

	Block m_bakBlock;//当前方块降落过程中，用来备份上一个合法位置
};

