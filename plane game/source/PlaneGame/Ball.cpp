#include "StdAfx.h"
#include "Ball.h"
#include "resource.h"

CImageList CBall::m_Images;

CBall::CBall(int x,int y,int nMontion):CGameObject(x,y),m_nMotion(nMontion)
{

}

CBall::~CBall(void)
{
}
BOOL CBall::Draw(CDC* pDC,BOOL bPause)
{
	if(!bPause)
	{
		//�����ӵ��ٶ�
		m_ptPos.y = m_ptPos.y + m_nMotion * 4;
	}

	if(m_ptPos.y > GAME_HEIGHT+BALL_HEIGHT )
		return FALSE;
	if(m_ptPos.y < -BALL_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}

BOOL CBall::LoadImage()
{//�о��ӵ�
	return CGameObject::LoadImage(m_Images, IDB_BITMAP13, RGB(0, 0, 0), 10, 20, 1);
}