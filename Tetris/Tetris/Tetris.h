#pragma once

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
};

