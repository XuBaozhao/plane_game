#pragma once
#include"GameObject.h"
class Enemy2 :public CGameObject
{
public:
	Enemy2(void);
	~Enemy2(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + ENEMY_HEIGHT, m_ptPos.y + ENEMY_HEIGHT));
	}

	int GetMontion()const
	{
		return m_nMotion;
	}
	BOOL Fired();
private:
	static const int ENEMY_HEIGHT = 80;
	static CImageList m_Images;
	int m_nMotion;//方向 1->向下 0 ->停止 -1->向上
	//图像索引
	int m_nImgIndex;
	//速度
	int m_V;
	int m_nWait;//发射延迟
};

