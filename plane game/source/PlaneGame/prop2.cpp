#include "StdAfx.h"
#include "prop2.h"
#include "resource.h"

CImageList CProp2::m_Images;

CProp2::CProp2(void)
{
	//随机确定X位置
	m_ptPos.x = rand() % (GAME_WIDTH - PROP2_HEIGHT - 15);

	//随机确定图像索引
	m_nImgIndex = 0;

	//根据图像索引确定方向
	m_nMotion = 1;
	m_ptPos.y = -PROP2_HEIGHT;
	if (m_nImgIndex % 2 != 0)//如果是图像索引是偶数
	{
		m_ptPos.y = GAME_HEIGHT + PROP2_HEIGHT;
	}
	//随机确定速度
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