#pragma once
#include <graphics.h>		// 引用图形库头文件
#include <vector>

using namespace std;

//位置结构体，记录方块的的位置
struct Point{
	int row;
	int col;
};

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

	//int a[3] =>获取 int* getdata();
	//int* a[3] =>获取 int** getdata();
	static IMAGE** getImages();

	Block& operator=(const Block& other);

	//判断方块是否在地图内
	bool blockInMap(const vector<vector<int>>&map);

	//固化方块，使方块不再下落
	void solidify(vector<vector<int>>&map);
	int getBlockType();

private:
	int m_nBlockType;//方块类型
	Point m_PointBlocks[4];//每四个方块构成一个俄罗斯方块，使用数组记录某种类型的方块中各个方块的位置
	IMAGE *m_img;

	static IMAGE* m_imgs[7];
	static int m_nImgSize;

};

