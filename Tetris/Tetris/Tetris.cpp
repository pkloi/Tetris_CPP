#include "Tetris.h"




Tetris::Tetris(int rows,int cols,int left,int top,int blockSize)
{

}

Tetris::~Tetris()
{
}

void Tetris::init()
{
	m_nDelay=30;
}

void Tetris::play()
{
	//��ʼ��
	init();

	int timer=0;

	//��Ϸѭ��
	while(1)
	{
		//�����û����루�������ҿ��Ʋ�����
		keyEvent();

		//��ʱ��Ⱦ����
		timer+=getDelay();
		if(timer>m_nDelay)
		{
			timer=0;

			//����
			drop();

			//��Ⱦ��Ϸ����
			m_bUpdate=true;
		}

		if(m_bUpdate)
		{
			m_bUpdate=false;
			//������Ϸ����
			updateWindow();

			//������Ϸ��Ϣ�����У�
			clearLine();
		}
	}
}

void Tetris::keyEvent()
{

}

void Tetris::updateWindow()
{

}

int Tetris::getDelay()
{
	return 0;

}

void Tetris::drop()
{

}

void Tetris::clearLine()
{

}
