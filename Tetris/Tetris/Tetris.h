#pragma once

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

private:
	int m_nDelay;//刷新时间
	bool m_bUpdate;//是否刷新游戏界面
};

