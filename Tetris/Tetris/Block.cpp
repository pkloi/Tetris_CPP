#include "Block.h"


Block::Block()
{
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

}
