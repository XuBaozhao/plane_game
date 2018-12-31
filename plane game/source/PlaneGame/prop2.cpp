#include "StdAfx.h"
#include "prop2.h"
#include "resource.h"

CImageList CProp2::m_Images;

CProp2::CProp2(void)
{
	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - PROP2_HEIGHT - 15);

	//���ȷ��ͼ������
	m_nImgIndex = 0;

	//����ͼ������ȷ������
	m_nMotion = 1;
	m_ptPos.y = -PROP2_HEIGHT;
	if (m_nImgIndex % 2 != 0)//�����ͼ��������ż��
	{
		m_ptPos.y = GAME_HEIGHT + PROP2_HEIGHT;
	}
	//���ȷ���ٶ�
	m_V = rand() % 6 + 2;

	m_nWait = 0;
}

CProp2::~CProp2(void)
{
}
BOOL CProp2::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP11, RGB(0, 0, 0), 50, 40, 3);
}
BOOL CProp2::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>20)
		m_nWait = 0;

	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT + PROP2_HEIGHT)
		return FALSE;
	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
BOOL CProp2::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}