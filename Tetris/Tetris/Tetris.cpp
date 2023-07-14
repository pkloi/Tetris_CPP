#include "Tetris.h"




Tetris::Tetris(int rows,int cols,int left,int top,int blockSize)
{

}

Tetris::~Tetris()
{
}

void Tetris::init()
{
	m_nDelay=30;
}

void Tetris::play()
{
	//初始化
	init();

	int timer=0;

	//游戏循环
	while(1)
	{
		//接受用户输入（上下左右控制操作）
		keyEvent();

		//定时渲染画面
		timer+=getDelay();
		if(timer>m_nDelay)
		{
			timer=0;

			//下落
			drop();

			//渲染游戏画面
			m_bUpdate=true;
		}

		if(m_bUpdate)
		{
			m_bUpdate=false;
			//更新游戏画面
			updateWindow();

			//更新游戏信息（清行）
			clearLine();
		}
	}
}

void Tetris::keyEvent()
{

}

void Tetris::updateWindow()
{

}

int Tetris::getDelay()
{
	return 0;

}

void Tetris::drop()
{

}

void Tetris::clearLine()
{

}
