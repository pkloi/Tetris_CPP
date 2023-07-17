#include "Tetris.h"
#include <stdlib.h>
#include <time.h>
#include <conio.h> //输出
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <fstream>

#pragma comment(lib,"winmm.lib")

#define MAX_LEVEL 5//最大关卡数

// const int SPEED_NORMAL=500;//ms
const int SPEED_NORMAL[5]={500,300,150,100,80};//ms
const int SPEED_QUICK=50;//ms

#define BLOCK_TYPE_I 1 //I
#define BLOCK_TYPE_Z_1 2  //Z 1型
#define BLOCK_TYPE_Z_2 3  //Z 1型
#define BLOCK_TYPE_T 4  //T
#define BLOCK_TYPE_L 5  //L
#define BLOCK_TYPE_J 6  //J
#define BLOCK_TYPE_Tian 7  //田

#define READFILE_PATH "./score.txt"//分数文件路径

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
	//背景音乐
	mciSendString("play ./res/bg.mp3 repeat",0,0,0);
	m_nDelay=SPEED_NORMAL[0];

	//随机生成种子
	srand(time(NULL));

	//创建游戏窗口
	initgraph(938,896);

	//加载背景图片
	loadimage(&m_imgBg,"res/bg2.png");
	loadimage(&m_imgBG_Win,"res/win.png");
	loadimage(&m_imgBg_Over,"res/over.png");

	//初始化游戏中的区域
	for(int i=0;i<m_nRows;i++)
	{
		for(int j=0;j<m_nCols;j++)
		{
			m_mapData[i][j]=0;
		}
	}

	m_nScore=0;
	m_nLevel=1;
	m_nClearLineCount=0;
	m_nHighestScore=0;//如果文件中的数据为空，则还是需要赋值0

	m_bGameOver=false;

	//初始化最高分
	fstream file(READFILE_PATH);
	if(!file.is_open())
	{
		cout<<READFILE_PATH<<"打开失败！"<<endl;
		file.open(READFILE_PATH,ios::out);

	}
	else{
		file>>m_nHighestScore;
	}
	file.close();
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

		if(m_bGameOver)
		{
			//游戏结束，保存分数
			saveScore();

			//结束界面
			displayOver();

			system("pause");
			init();
		}
	}
}

void Tetris::keyEvent()
{
	//记录按下的键
	unsigned char ch;
	//是否旋转
	bool bRotateFlag=false;
	//左右移动
	int dx=0;

	//判断是否按下键盘
	if(_kbhit())
	{
		ch=_getch();//输出，免回车

		if(ch==224)
		{
			ch=_getch();//方向键会返回两个字符，所以需要再取一次ch

			switch(ch){
			case 72:
				//上
				bRotateFlag=true;
				break;
			case 80:
				//下 
				m_nDelay=SPEED_QUICK;
				break;
			case 75:
				//左
				dx=-1;
				break;
			case 77:
				//右
				dx=1;
				break;  
			default:
				break;
			} 
		}
		else{
			switch(ch){
				//如果是WASD，也可以作为方向键
			case 'w':
				//上
				break;
			case 's':
				//下 
				break;
			case 'a':
				//左
				dx=-1;
				break;
			case 'd':
				//右
				dx=1;
				break;
			}
		}
	}

	if(bRotateFlag)
	{
		//旋转
		rotate();
		m_bUpdate=true;
	}

	if(dx!=0)
	{
		//左右移动
		moveLeftRight(dx);
		m_bUpdate=true;
	}
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

	drawScore();//绘制分数

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
	//下降
	m_bakBlock=*m_pCurrBlock;
	m_pCurrBlock->drop();

	//固化
	if(!m_pCurrBlock->blockInMap(m_mapData))
	{
		*m_pCurrBlock=m_bakBlock;
		m_pCurrBlock->solidify(m_mapData);

		//固化方块不再使用
		delete m_pCurrBlock;
		m_pCurrBlock=m_pNextBlock;
		m_pNextBlock=new Block;

		//检查是否到顶，结束游戏
		checkOver();
	}

	m_nDelay=SPEED_NORMAL[m_nLevel-1];
}

void Tetris::clearLine()
{
	int nLines=0;//记录被清除的行数

	int k=m_nRows-1;//存储数据的行数 如果该行满，则删除，k仍然指向最后一行
	for(int i=m_nRows-1;i>=0;i--)//从最后一行扫描
	{
		//检查第i行是否满了
		int count=0;
		for(int j=0;j<m_nCols;j++)
		{
			if(m_mapData[i][j])//一个一个扫描过去，不为0则表示有数据
			{
				count++;
			}
			m_mapData[k][j]=m_mapData[i][j];//一边扫描一边存储
		}

		//一行扫描结束，count不等于m_nCols，则表示没有满行；反之，满行
		if(count<m_nCols)//不是满行
		{
			k--;//因为该行没有满，所以仍然存储该行
		}
		else{
			nLines++;

			//解释：
			//因为满行了，需要消除该行,所以k不变，仍然指向该行
			//下一次执行m_mapData[k][j]=m_mapData[i][j];会被覆盖
		}
	}

	if(nLines>0)
	{
		//消除一行动画
		mciSendString("play res/xiaochu1.mp3",0,0,0);
		 m_bUpdate=true;

		//得分
		 int addScore[4]={10,30,60,80};
		 m_nScore+=addScore[nLines-1];
		 if(m_nScore>m_nHighestScore)
		 {
			 m_nHighestScore=m_nScore;
		 }

		 //关卡
		 //每100分为一个级别，1-100 第一关 101-200 第二关 ...
		 m_nLevel=(m_nScore+99)/100;
		 if(m_nLevel)

		 //消除行数
		 m_nClearLineCount+=nLines;
	}
}

void Tetris::moveLeftRight(int offset)
{
	m_bakBlock=*m_pCurrBlock;
	m_pCurrBlock->moveLeftRight(offset);

	if(!m_pCurrBlock->blockInMap(m_mapData))
	{
		*m_pCurrBlock=m_bakBlock;
	}
}

void Tetris::rotate()
{
	//田字方块旋转没有意义，直接return
	if(m_pCurrBlock->getBlockType()==BLOCK_TYPE_Tian)
	{
		return;
	}
	m_bakBlock=*m_pCurrBlock;
	m_pCurrBlock->rotate();

	if(!m_pCurrBlock->blockInMap(m_mapData))
	{
		*m_pCurrBlock=m_bakBlock;
	}
}

void Tetris::drawScore()
{
	//用到了EasyX函数，具体查看帮助手册
	char ShowText[32];

	//分数
	sprintf_s(ShowText,sizeof(ShowText),"%d",m_nScore);
	setcolor(RGB(180,180,180));

	LOGFONT f;
	gettextstyle(&f);//获取当前字体
	f.lfHeight=60;
	f.lfWidth=30;
	f.lfQuality = ANTIALIASED_QUALITY;//抗锯齿
	_tcscpy_s(f.lfFaceName,sizeof(f.lfFaceName),_T("Segoe UI Black"));
	settextstyle(&f);

	setbkmode(TRANSPARENT);//字体背景设置为透明

	outtextxy(670,727,ShowText);

	//等级
	sprintf_s(ShowText,sizeof(ShowText),"%d",m_nLevel);
	gettextstyle(&f);
	//保证右对齐，宽度*位数得到第一位的位置
	int xPos=224-f.lfWidth*strlen(ShowText);
	//渲染
	outtextxy(xPos,727,ShowText);

	//消除行数
	sprintf_s(ShowText,sizeof(ShowText),"%d",m_nClearLineCount);
	gettextstyle(&f);
	//保证右对齐，宽度*位数得到第一位的位置
	xPos=224-f.lfWidth*strlen(ShowText);
	//渲染
	outtextxy(xPos,825,ShowText);

	//最高分
	sprintf_s(ShowText,sizeof(ShowText),"%d",m_nHighestScore);
	outtextxy(670,825,ShowText);
}

void Tetris::checkOver()
{
	m_bGameOver=(m_pCurrBlock->blockInMap(m_mapData)==false);
}

void Tetris::saveScore()
{
	if(m_nScore>=m_nHighestScore)
	{
		m_nHighestScore=m_nScore;

		ofstream file(READFILE_PATH);
		file<<m_nHighestScore;
		file.close();
	}
}

void Tetris::displayOver()
{
	//背景音乐停止
	mciSendString("stop ./res/bg.mp3",0,0,0);
	if(m_nLevel>=MAX_LEVEL)
	{
		mciSendString("play ./res/win.mp3",0,0,0);
		putimage(262,361,&m_imgBG_Win);
	}
	else{
		mciSendString("play ./res/over.mp3",0,0,0);
		putimage(262,361,&m_imgBg_Over);

	}
}
