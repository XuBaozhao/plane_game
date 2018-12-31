#pragma once
#include "gameobject.h"

class CBoss :public CGameObject
{
public:
	CBoss(void);
	~CBoss(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BOSS_HEIGHT + 90, m_ptPos.y + BOSS_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
	//是否可以开火发射子弹
	BOOL Fired();
private:
	static const int BOSS_HEIGHT = 70;
	static CImageList m_Images;
	int    m_nMotion = 1;//方向 1->向下 0->停止 -1->向上
	//图像索引
	int m_nImgIndex;
	//速度
	int m_V;
	int    m_nWait;//发射延时
};
