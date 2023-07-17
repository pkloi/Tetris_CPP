#include "Block.h"
#include <stdlib.h>

IMAGE* Block::m_imgs[7]={NULL,};//������������Ϊ��(�еı��������Բ�д��,��)
int Block::m_nImgSize=36;


Block::Block()
{
	//��ʼ������ͼƬ
	if(m_imgs[0]==NULL)
	{
		IMAGE imgTmp;
		loadimage(&imgTmp,"res/tiles.png");

		//ͨ���и�ͼƬ�õ���ͬ��С����
		SetWorkingImage(&imgTmp);
		for(int i=0;i<7;i++)
		{
			m_imgs[i]=new IMAGE;
			getimage(m_imgs[i],i*m_nImgSize,0,m_nImgSize,m_nImgSize);
		}
		SetWorkingImage();//�ָ�������

	}
	int blocks[7][4]={
		1,3,5,7,//I
		2,4,5,7,//Z 1��
		3,5,4,6,//Z 2��
		3,5,4,7,//T
		2,3,5,7,//L
		3,5,7,6,//J
		2,3,4,5,//��
	};

	//�������һ�ֶ���˹����
	m_nBlockType=1+rand()%7;//1+ 0...6 => 0...7

	//��ʼ�� m_PointBlocks
	for(int i=0;i<4;i++)
	{
		int nValue=blocks[m_nBlockType-1][i];
		m_PointBlocks[i].row=nValue/2;
		m_PointBlocks[i].col=nValue%2;
	}

	//��ǰ����
	m_img=m_imgs[m_nBlockType-1];
}


Block::~Block()
{
}

void Block::drop()
{
	//���µ��䣬ֻ�ı���
	for(int i=0;i<4;i++)
	{
		m_PointBlocks[i].row++;
	}
}

void Block::moveLeftRight(int offset)
{
	for(int i=0;i<4;i++)
	{
		m_PointBlocks[i].col+=offset;
	}
}

void Block::rotate()
{
	Point p=m_PointBlocks[1];
	for(int i=0;i<4;i++)
	{
		Point tmp=m_PointBlocks[i];
		m_PointBlocks[i].row=p.row+tmp.col-p.col;
		m_PointBlocks[i].col=p.col-tmp.row+p.row;
	}
}

void Block::draw(int leftMargin,int topMargin)
{
	for(int i=0;i<4;i++)
	{
		int x=leftMargin+m_PointBlocks[i].col*m_nImgSize;
		int y=topMargin+m_PointBlocks[i].row*m_nImgSize;
		putimage(x,y,m_img);
	}
}

IMAGE** Block::getImages()
{
	return m_imgs;
}

bool Block::blockInMap(const vector<vector<int>>& map)
{
	int nRows=map.size();
	int nCols=map[0].size();

	for(int i=0;i<4;i++)
	{
		if(m_PointBlocks[i].col<0 || m_PointBlocks[i].col>=nCols || //�г�����Χ
			m_PointBlocks[i].row<0 || m_PointBlocks[i].row>=nRows || //�г�����Χ
			map[m_PointBlocks[i].row][m_PointBlocks[i].col] != 0) //��ǰλ���Ѿ��з��飨�з���ʱ��ֵ��Ϊ0)
		{
			return false;
		}
	}
	return true;
}

void Block::solidify(vector<vector<int>>& map)
{
	for(int i=0;i<4;i++)
	{
		//���ñ�ǣ����̻�����Ӧλ��
		int nCurRow=m_PointBlocks[i].row;
		int nCurCol=m_PointBlocks[i].col;
		map[nCurRow][nCurCol]=m_nBlockType;
	}
}

int Block::getBlockType()
{
	return m_nBlockType;
}

Block& Block::operator=(const Block& other)
{
	if(this==&other)
		return *this;

	this->m_nBlockType=other.m_nBlockType;

	for(int i=0;i<4;i++)
	{
		this->m_PointBlocks[i]=other.m_PointBlocks[i];
	}

	return *this;
}
