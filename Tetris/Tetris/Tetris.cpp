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

	//��ʼ����Ϸ����
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

	//�����������
	srand(time(NULL));

	//������Ϸ����
	initgraph(938,896);

	//���ر���ͼƬ
	loadimage(&m_imgBg,"res/bg2.png");

	//��ʼ����Ϸ�е�����
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
	//��ʼ��
	init();

	//��һ��û�з���ʱ����Ԥ�淽��
	m_pNextBlock=new Block;
	m_pCurrBlock=m_pNextBlock;

	m_pNextBlock=new Block;

	int timer=0;

	//��Ϸѭ��
	while(1)
	{
		//�����û����루�������ҿ��Ʋ�����
		keyEvent();

		//��ʱ��Ⱦ����
		timer+=getDelay();
		if(timer>m_nDelay)
		{
			timer=0;

			//����
			drop();

			//��Ⱦ��Ϸ����
			m_bUpdate=true;
		}

		if(m_bUpdate)
		{
			m_bUpdate=false;
			//������Ϸ����
			updateWindow();

			//������Ϸ��Ϣ�����У�
			clearLine();
		}
	}
}

void Tetris::keyEvent()
{

}

void Tetris::updateWindow()
{
	//������Ϸ����ͼƬ
	putimage(0,0,&m_imgBg);

	//���Է���
// 	Block block;
// 	block.draw(m_nLeftMargin,m_nTopMargin);

	IMAGE** imgs=Block::getImages();

	//ִ�к��κλ�ͼ����������ʱ���������ͼ������
	//ֱ��ִ�� FlushBatchDraw �� EndBatchDraw �Ž�֮ǰ�Ļ�ͼ���
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
