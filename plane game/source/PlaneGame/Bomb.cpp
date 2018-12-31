#include "StdAfx.h"
#include "Bomb.h"
#include "resource.h"


CImageList CBomb::m_Images;


CBomb::CBomb(int x, int y, int xx) :CGameObject(x, y), dx(xx)
{

}

CBomb::~CBomb(void)
{
}
BOOL CBomb::LoadImage()
{
	//我方战机子弹图片
	return CGameObject::LoadImage(m_Images, IDB_BITMAP10, RGB(0, 0, 0), 10, 20, 1);
}
BOOL CBomb::Draw(CDC* pDC,BOOL bPause)
{
	if(!bPause)
	{
		m_ptPos.y = m_ptPos.y - 8;
		m_ptPos.x = m_ptPos.x + dx;
	}

	if(m_ptPos.y < -BOMB_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}