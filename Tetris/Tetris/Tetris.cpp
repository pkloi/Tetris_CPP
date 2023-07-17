#include "Tetris.h"
#include <stdlib.h>
#include <time.h>
#include <conio.h> //���
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <fstream>

#pragma comment(lib,"winmm.lib")

#define MAX_LEVEL 5//���ؿ���

// const int SPEED_NORMAL=500;//ms
const int SPEED_NORMAL[5]={500,300,150,100,80};//ms
const int SPEED_QUICK=50;//ms

#define BLOCK_TYPE_I 1 //I
#define BLOCK_TYPE_Z_1 2  //Z 1��
#define BLOCK_TYPE_Z_2 3  //Z 1��
#define BLOCK_TYPE_T 4  //T
#define BLOCK_TYPE_L 5  //L
#define BLOCK_TYPE_J 6  //J
#define BLOCK_TYPE_Tian 7  //��

#define READFILE_PATH "./score.txt"//�����ļ�·��

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
	//��������
	mciSendString("play ./res/bg.mp3 repeat",0,0,0);
	m_nDelay=SPEED_NORMAL[0];

	//�����������
	srand(time(NULL));

	//������Ϸ����
	initgraph(938,896);

	//���ر���ͼƬ
	loadimage(&m_imgBg,"res/bg2.png");
	loadimage(&m_imgBG_Win,"res/win.png");
	loadimage(&m_imgBg_Over,"res/over.png");

	//��ʼ����Ϸ�е�����
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
	m_nHighestScore=0;//����ļ��е�����Ϊ�գ�������Ҫ��ֵ0

	m_bGameOver=false;

	//��ʼ����߷�
	fstream file(READFILE_PATH);
	if(!file.is_open())
	{
		cout<<READFILE_PATH<<"��ʧ�ܣ�"<<endl;
		file.open(READFILE_PATH,ios::out);

	}
	else{
		file>>m_nHighestScore;
	}
	file.close();
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

		if(m_bGameOver)
		{
			//��Ϸ�������������
			saveScore();

			//��������
			displayOver();

			system("pause");
			init();
		}
	}
}

void Tetris::keyEvent()
{
	//��¼���µļ�
	unsigned char ch;
	//�Ƿ���ת
	bool bRotateFlag=false;
	//�����ƶ�
	int dx=0;

	//�ж��Ƿ��¼���
	if(_kbhit())
	{
		ch=_getch();//�������س�

		if(ch==224)
		{
			ch=_getch();//������᷵�������ַ���������Ҫ��ȡһ��ch

			switch(ch){
			case 72:
				//��
				bRotateFlag=true;
				break;
			case 80:
				//�� 
				m_nDelay=SPEED_QUICK;
				break;
			case 75:
				//��
				dx=-1;
				break;
			case 77:
				//��
				dx=1;
				break;  
			default:
				break;
			} 
		}
		else{
			switch(ch){
				//�����WASD��Ҳ������Ϊ�����
			case 'w':
				//��
				break;
			case 's':
				//�� 
				break;
			case 'a':
				//��
				dx=-1;
				break;
			case 'd':
				//��
				dx=1;
				break;
			}
		}
	}

	if(bRotateFlag)
	{
		//��ת
		rotate();
		m_bUpdate=true;
	}

	if(dx!=0)
	{
		//�����ƶ�
		moveLeftRight(dx);
		m_bUpdate=true;
	}
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

	drawScore();//���Ʒ���

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
	//�½�
	m_bakBlock=*m_pCurrBlock;
	m_pCurrBlock->drop();

	//�̻�
	if(!m_pCurrBlock->blockInMap(m_mapData))
	{
		*m_pCurrBlock=m_bakBlock;
		m_pCurrBlock->solidify(m_mapData);

		//�̻����鲻��ʹ��
		delete m_pCurrBlock;
		m_pCurrBlock=m_pNextBlock;
		m_pNextBlock=new Block;

		//����Ƿ񵽶���������Ϸ
		checkOver();
	}

	m_nDelay=SPEED_NORMAL[m_nLevel-1];
}

void Tetris::clearLine()
{
	int nLines=0;//��¼�����������

	int k=m_nRows-1;//�洢���ݵ����� �������������ɾ����k��Ȼָ�����һ��
	for(int i=m_nRows-1;i>=0;i--)//�����һ��ɨ��
	{
		//����i���Ƿ�����
		int count=0;
		for(int j=0;j<m_nCols;j++)
		{
			if(m_mapData[i][j])//һ��һ��ɨ���ȥ����Ϊ0���ʾ������
			{
				count++;
			}
			m_mapData[k][j]=m_mapData[i][j];//һ��ɨ��һ�ߴ洢
		}

		//һ��ɨ�������count������m_nCols�����ʾû�����У���֮������
		if(count<m_nCols)//��������
		{
			k--;//��Ϊ����û������������Ȼ�洢����
		}
		else{
			nLines++;

			//���ͣ�
			//��Ϊ�����ˣ���Ҫ��������,����k���䣬��Ȼָ�����
			//��һ��ִ��m_mapData[k][j]=m_mapData[i][j];�ᱻ����
		}
	}

	if(nLines>0)
	{
		//����һ�ж���
		mciSendString("play res/xiaochu1.mp3",0,0,0);
		 m_bUpdate=true;

		//�÷�
		 int addScore[4]={10,30,60,80};
		 m_nScore+=addScore[nLines-1];
		 if(m_nScore>m_nHighestScore)
		 {
			 m_nHighestScore=m_nScore;
		 }

		 //�ؿ�
		 //ÿ100��Ϊһ������1-100 ��һ�� 101-200 �ڶ��� ...
		 m_nLevel=(m_nScore+99)/100;
		 if(m_nLevel)

		 //��������
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
	//���ַ�����תû�����壬ֱ��return
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
	//�õ���EasyX����������鿴�����ֲ�
	char ShowText[32];

	//����
	sprintf_s(ShowText,sizeof(ShowText),"%d",m_nScore);
	setcolor(RGB(180,180,180));

	LOGFONT f;
	gettextstyle(&f);//��ȡ��ǰ����
	f.lfHeight=60;
	f.lfWidth=30;
	f.lfQuality = ANTIALIASED_QUALITY;//�����
	_tcscpy_s(f.lfFaceName,sizeof(f.lfFaceName),_T("Segoe UI Black"));
	settextstyle(&f);

	setbkmode(TRANSPARENT);//���屳������Ϊ͸��

	outtextxy(670,727,ShowText);

	//�ȼ�
	sprintf_s(ShowText,sizeof(ShowText),"%d",m_nLevel);
	gettextstyle(&f);
	//��֤�Ҷ��룬���*λ���õ���һλ��λ��
	int xPos=224-f.lfWidth*strlen(ShowText);
	//��Ⱦ
	outtextxy(xPos,727,ShowText);

	//��������
	sprintf_s(ShowText,sizeof(ShowText),"%d",m_nClearLineCount);
	gettextstyle(&f);
	//��֤�Ҷ��룬���*λ���õ���һλ��λ��
	xPos=224-f.lfWidth*strlen(ShowText);
	//��Ⱦ
	outtextxy(xPos,825,ShowText);

	//��߷�
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
	//��������ֹͣ
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
