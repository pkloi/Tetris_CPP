#pragma once
#include <graphics.h>		// ����ͼ�ο�ͷ�ļ�
#include <vector>

using namespace std;

//λ�ýṹ�壬��¼����ĵ�λ��
struct Point{
	int row;
	int col;
};

//������
class Block
{
public:
	Block();
	~Block();

	void drop();//����
	void moveLeftRight(int offset);//�����ƶ���ͨ��ƫ�������� offset>0 ����;offset<0 ����
	void rotate();//��ת
	void draw(int leftMargin,int topMargin);//�������飬ͨ�����ñ߾�ֵ��λ����λ��

	//int a[3] =>��ȡ int* getdata();
	//int* a[3] =>��ȡ int** getdata();
	static IMAGE** getImages();

	Block& operator=(const Block& other);

	//�жϷ����Ƿ��ڵ�ͼ��
	bool blockInMap(const vector<vector<int>>&map);

	//�̻����飬ʹ���鲻������
	void solidify(vector<vector<int>>&map);
	int getBlockType();

private:
	int m_nBlockType;//��������
	Point m_PointBlocks[4];//ÿ�ĸ����鹹��һ������˹���飬ʹ�������¼ĳ�����͵ķ����и��������λ��
	IMAGE *m_img;

	static IMAGE* m_imgs[7];
	static int m_nImgSize;

};

