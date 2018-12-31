#include "StdAfx.h"
#include "prop.h"
#include "resource.h"

CImageList CProp::m_Images;

CProp::CProp(void)
{
	//随机确定X位置
	m_ptPos.x = rand() % (GAME_WIDTH - PROP_HEIGHT - 15);

	//随机确定图像索引
	m_nImgIndex = 0;

	//根据图像索引确定方向
	m_nMotion = 1;
	m_ptPos.y = -PROP_HEIGHT;
	if (m_nImgIndex % 2 != 0)//如果是图像索引是偶数
	{
		//	m_nMotion=-1;        //此时敌机从下方冒出
		m_ptPos.y = GAME_HEIGHT + PROP_HEIGHT;
	}
	//随机确定速度
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