#pragma once

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
};

