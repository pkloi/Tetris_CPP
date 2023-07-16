#include "Block.h"
#include <stdlib.h>

IMAGE* Block::m_imgs[7]={NULL,};//设置整个数组为空(有的编译器可以不写‘,’)
int Block::m_nImgSize=36;


Block::Block()
{
	//初始化方块图片
	if(m_imgs[0]==NULL)
	{
		IMAGE imgTmp;
		loadimage(&imgTmp,"res/tiles.png");

		//通过切割图片得到不同的小方块
		SetWorkingImage(&imgTmp);
		for(int i=0;i<7;i++)
		{
			m_imgs[i]=new IMAGE;
			getimage(m_imgs[i],i*m_nImgSize,0,m_nImgSize,m_nImgSize);
		}
		SetWorkingImage();//恢复工作区
			
	}
	int blocks[7][4]={
		1,3,5,7,//I
		2,4,5,7,//Z 1型
		3,5,4,6,//Z 2型
		3,5,4,7,//T
		2,3,5,7,//L
		3,5,7,6,//J
		2,3,4,5,//田
	};

	//随机生成一种俄罗斯方块
	m_nBlockType=1+rand()%7;//1+ 0...6 => 0...7

	//初始化 m_PointBlocks
	for(int i=0;i<4;i++)
	{
		int nValue=blocks[m_nBlockType-1][i];
		m_PointBlocks[i].row=nValue/2;
		m_PointBlocks[i].col=nValue%2;
	}

	//当前方块
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
