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

}

void Block::moveLeftRight(int offset)
{

}

void Block::rotate()
{

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
