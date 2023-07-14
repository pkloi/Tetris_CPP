#pragma once

//方块类
class Block
{
public:
	Block();
	~Block();

	void drop();//下落
	void moveLeftRight(int offset);//左右移动，通过偏移量控制 offset>0 右移;offset<0 左移
	void rotate();//旋转
	void draw(int leftMargin,int topMargin);//画出方块，通过设置边距值定位画出位置
};

