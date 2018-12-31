#include "StdAfx.h"
#include "Enemy2.h"
#include "resource.h"

CImageList Enemy2::m_Images;

Enemy2::Enemy2(void)
{
	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - ENEMY_HEIGHT);

	//���ȷ��ͼ������
	m_nImgIndex = rand() % 2;

	//����ͼ������ȷ������
	m_nMotion = 1;
	m_ptPos.y = -ENEMY_HEIGHT;
	if (m_nImgIndex % 2 != 0)//�����ͼ��������ż��
	{
		//	m_nMotion=-1;        //��ʱ�л����·�ð��
		m_ptPos.y = GAME_HEIGHT + ENEMY_HEIGHT;
	}
	//ȷ���ٶ�
	m_V = 10;

	m_nWait = 0;
}

Enemy2::~Enemy2(void)
{
}
BOOL Enemy2::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP9, RGB(0, 0, 0), 50, 40, 2);
}
BOOL Enemy2::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>20)
		m_nWait = 0;

	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT)
		return FALSE;
	if (m_ptPos.x > GAME_WIDTH)
		return FALSE;
	//if(m_ptPos.y < -ENEMY_HEIGHT)
	//return FALSE;
	//
	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
BOOL Enemy2::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}