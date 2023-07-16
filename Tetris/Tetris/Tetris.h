#pragma once
#include <graphics.h>
#include <vector>

#include "Block.h"

using namespace std;

//��Ϸ��
class Tetris
{
public:
	//���캯��
	//��Ϸ����Ĳ�����rows-��;cols-��;left-��Ϸ��������߿�ľ���;top-����Ӷ�������ľ���;blockSize-�����С
	Tetris(int rows,int cols,int left,int top,int blockSize);
	~Tetris();

	void init();//��ʼ��
	void play();//��ʼ��Ϸ

private:
	void keyEvent();//���������¼�
	void updateWindow();//��Ⱦ��Ϸ����

	//��һ���÷���0
	int getDelay();//���ؾ�����һ�ε��øú���������˶���ʱ�䣨ms��
	void drop();//����
	void clearLine();//����

private:
	int m_nDelay;//ˢ��ʱ��
	bool m_bUpdate;//�Ƿ�ˢ����Ϸ����

	//0���հף�û���κη���
	//5����ʾ��5�ֶ���˹���飨һ�����֣�
	vector<vector<int>> m_mapData;//����Ϸ����
	
	int m_nRows;//��
	int m_nCols;//��

	int m_nLeftMargin;
	int m_nTopMargin;

	int m_nBlockSize;//����˹����Ĵ�С

	IMAGE m_imgBg;//����ͼƬ

	Block* m_pCurrBlock;//��ǰ����
	Block* m_pNextBlock;//Ԥ�淽��
};

