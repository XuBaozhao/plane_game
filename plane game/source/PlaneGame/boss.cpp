#include "StdAfx.h"
#include "boss.h"
#include "resource.h"

CImageList CBoss::m_Images;

CBoss::CBoss(void)
{
	//���ȷ��Xλ��
	m_ptPos.x = 80;

	//���ȷ��ͼ������
	m_nImgIndex = 0;

	//����ͼ������ȷ������
	m_nMotion = 1;
	m_ptPos.y = 100;
	if (m_nImgIndex % 2 != 0)//�����ͼ��������ż��
	{
		m_ptPos.y = GAME_HEIGHT + BOSS_HEIGHT;
	}
	//���ȷ���ٶ�
	m_V = rand() % 6 + 2;

	m_nWait = 0;
}

CBoss::~CBoss(void)
{
}
BOOL CBoss::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP5, RGB(0, 0, 0), 150, 70, 1);
}
BOOL CBoss::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>40)
		m_nWait = 0;

	if (!bPause)
	{
		//m_nMotion = 1;
		m_ptPos.y = m_ptPos.y;

		if (m_ptPos.x <= GAME_WIDTH - BOSS_HEIGHT - 70 && m_nMotion == 1)
		{
			m_ptPos.x += 2;
			if (m_ptPos.x >= GAME_WIDTH - BOSS_HEIGHT - 70)
				m_nMotion = -1;
		}
		if (m_ptPos.x >= 0 && m_nMotion == -1)
		{
			m_ptPos.x -= 2;
			if (m_ptPos.x <10)
				m_nMotion = 1;
		}

	}

	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
BOOL CBoss::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}