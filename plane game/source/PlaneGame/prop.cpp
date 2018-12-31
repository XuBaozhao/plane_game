#include "StdAfx.h"
#include "prop.h"
#include "resource.h"

CImageList CProp::m_Images;

CProp::CProp(void)
{
	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - PROP_HEIGHT - 15);

	//���ȷ��ͼ������
	m_nImgIndex = 0;

	//����ͼ������ȷ������
	m_nMotion = 1;
	m_ptPos.y = -PROP_HEIGHT;
	if (m_nImgIndex % 2 != 0)//�����ͼ��������ż��
	{
		//	m_nMotion=-1;        //��ʱ�л����·�ð��
		m_ptPos.y = GAME_HEIGHT + PROP_HEIGHT;
	}
	//���ȷ���ٶ�
	m_V = rand() % 6 + 2;

	m_nWait = 0;
}

CProp::~CProp(void)
{
}
BOOL CProp::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP8, RGB(0, 0, 0), 29, 28, 2);
}
BOOL CProp::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>20)
		m_nWait = 0;

	if (!bPause)
	{

		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT + PROP_HEIGHT)
		return FALSE;
	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
BOOL CProp::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}