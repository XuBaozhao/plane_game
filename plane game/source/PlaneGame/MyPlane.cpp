#include "StdAfx.h"
#include "MyPlane.h"
#include "resource.h"

CImageList CMyPlane::m_Images;

CMyPlane::~CMyPlane(void)
{
}
CMyPlane::CMyPlane(void):m_nHorMotion(0),m_nVerMotion(0)
{//��ʼ���ֵ�λ��
	m_nWait = 0;
	m_ptPos.x = 256;
	m_ptPos.y =400;
}

BOOL CMyPlane::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;

}
BOOL CMyPlane::LoadImage()
{
	//LoadImage��һ�ֺ�����������װ��ͼ�꣬��꣬��λͼ��
	//HINSTANCE-------- - ��������ҪͼƬ��ʵ���ľ����
	//	LPCSTR--------------ͼƬ����·�����ļ�����
	//	UINT------------------ - ͼƬ���͡�
	//	int---------------------- - ͼƬ��ȡ�
	//	int---------------------- - ͼƬ�߶ȡ�
	//	UINT------------------ - load flags
	//�ɻ�ͼƬ
	return CGameObject::LoadImage(m_Images,IDB_BITMAP1, RGB(0, 0, 0), 71, 60, 1);
}
BOOL CMyPlane::Draw(CDC* pDC,BOOL bPause)
{
	m_nWait++;
	if(m_nWait>3)
		m_nWait=0;

	if(!bPause)
	{
		m_ptPos.x = m_ptPos.x + m_nHorMotion*6;
		m_ptPos.y = m_ptPos.y - m_nVerMotion*6;
	}

	if(m_ptPos.x>=GAME_WIDTH-90)
		m_ptPos.x =GAME_WIDTH-90;
	if(m_ptPos.x<=0)
		m_ptPos.x=0;

	if(m_ptPos.y<=0)
		m_ptPos.y =0;

	if(m_ptPos.y>=GAME_HEIGHT-120)
		m_ptPos.y=GAME_HEIGHT-120;


	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);
	return TRUE;
}