#include "Tetris.h"
#include <stdlib.h>
#include <time.h>

const int SPEED_NORMAL=500;//ms
const int SPEED_QUICK=50;//ms

Tetris::Tetris(int rows,int cols,int left,int top,int blockSize)
{
	m_nRows=rows;
	m_nCols=cols;
	m_nLeftMargin=left;
	m_nTopMargin=top;
	m_nBlockSize=blockSize;

	//初始化游戏数据
	for(int i=0;i<rows;i++)
	{
		vector<int> mapRow;
		for(int j=0;j<cols;j++)
		{
			mapRow.push_back(0);
		}
		m_mapData.push_back(mapRow);
	}
	m_bUpdate=false;
}

Tetris::~Tetris()
{
}

void Tetris::init()
{
	m_nDelay=SPEED_NORMAL;

	//随机生成种子
	srand(time(NULL));

	//创建游戏窗口
	initgraph(938,896);

	//加载背景图片
	loadimage(&m_imgBg,"res/bg2.png");

	//初始化游戏中的区域
	for(int i=0;i<m_nRows;i++)
	{
		for(int j=0;j<m_nCols;j++)
		{
			m_mapData[i][j]=0;
		}
	}
}

void Tetris::play()
{
	//初始化
	init();

	//第一次没有方块时，先预告方块
	m_pNextBlock=new Block;
	m_pCurrBlock=m_pNextBlock;

	m_pNextBlock=new Block;

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
	//绘制游戏背景图片
	putimage(0,0,&m_imgBg);

	//测试方块
// 	Block block;
// 	block.draw(m_nLeftMargin,m_nTopMargin);

	IMAGE** imgs=Block::getImages();

	//执行后，任何绘图操作都将暂时不输出到绘图窗口上
	//直到执行 FlushBatchDraw 或 EndBatchDraw 才将之前的绘图输出
	BeginBatchDraw();

	for(int i=0;i<m_nRows;i++)
	{
		for(int j=0;j<m_nCols;j++)
		{
			if(m_mapData[i][j]==0)
				continue;
			int x=j*m_nBlockSize+m_nLeftMargin;
			int y=i*m_nBlockSize+m_nTopMargin;
			
			putimage(x,y,imgs[m_mapData[i][j]-1]);
		}
	}

	m_pCurrBlock->draw(m_nLeftMargin,m_nTopMargin);
	m_pNextBlock->draw(689,150);

	EndBatchDraw();
}


int Tetris::getDelay()
{
	static unsigned long long ulLastTime=0;
	unsigned long long ulCurrentTime=GetTickCount();

	if(ulLastTime==0)
	{
		ulLastTime=ulCurrentTime;
		return 0;
	}
	else{
		int ret=ulCurrentTime-ulLastTime;
		ulLastTime=ulCurrentTime;
		return ret;
	}
	return 0;
}

void Tetris::drop()
{

}

void Tetris::clearLine()
{

}
