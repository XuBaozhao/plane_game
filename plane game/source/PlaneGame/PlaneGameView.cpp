#include "stdafx.h"
#include "PlaneGame.h"
#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Bomb.h"
#include "Ball.h"
#include"prop.h"
#include"boss.h"
#include"prop2.h"
#include "Explosion.h"
#include <atlimage.h>
#include <mmSystem.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPlaneGameView


IMPLEMENT_DYNCREATE(CPlaneGameView, CView)
BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	//ON_WM_DESTROY()//         
END_MESSAGE_MAP()

// CPlaneGameView ����/����
CPlaneGameView::CPlaneGameView() :m_pMe(NULL), grade(0), blood(5), is_Pass(0), score(0), p2(0)
{
	// TODO: �ڴ˴���ӹ������	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	return CView::PreCreateWindow(cs);

	
}

// CPlaneGameView ����
void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

// CPlaneGameView ��ӡ
BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

// CPlaneGameView ���
#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG

// CPlaneGameView ��Ϣ�������
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//��������
	
	//��ʼ����Ϸ
	InitGame();
}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}

BOOL CPlaneGameView::InitGame()
{
	
	CRect rc;
	GetClientRect(rc);
	//�������������
	srand( (unsigned)time( NULL ) );
	//�����豸DC
	m_pDC = new CClientDC(this);
	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);
	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);
	//��λͼѡ���ڴ�DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	Enemy2::LoadImage();
	CProp::LoadImage();
	CProp2::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CBoss::LoadImage();
	CExplosion::LoadImage();

	//��������(ս��)
	m_pMe = new CMyPlane;
	//������Ϸ
	if (AfxMessageBox(L"Are you ready��", MB_YESNO) == 6){
		SetTimer(1, 30, NULL);
		PlaySound((LPCTSTR)IDR_WAVE4, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
		return TRUE;
	}
	else
		exit(1);
}

void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	//�������
	//pMemDC->FillSolidRect(0,0,GAME_WIDTH,GAME_HEIGHT,RGB(84, 142, 239));
	if (pass_num == 1){
		CRect rctClient;
		GetClientRect(rctClient);
		CDC tDC;
		tDC.CreateCompatibleDC(m_pDC);
		CBitmap m_bmp;
		m_bmp.LoadBitmap(IDB_BITMAP18);
		BITMAP bitmap;
		m_bmp.GetBitmap(&bitmap);
		CBitmap *pbmpOld = tDC.SelectObject(&m_bmp);
		static int curr = GAME_HEIGHT;
		if (curr >=0)
			curr--;
		else
			curr = GAME_HEIGHT;
		//curr -= 1;
			pMemDC->BitBlt(0, curr, GAME_WIDTH, GAME_HEIGHT - curr, &tDC, 0, 0, SRCCOPY);
			pMemDC->BitBlt(0, 0, GAME_WIDTH, curr, &tDC, 0, GAME_HEIGHT - curr, SRCCOPY);
	}
	else if (pass_num == 2)
	{
		CRect rctClient;
		GetClientRect(rctClient);
		CDC tDC;
		tDC.CreateCompatibleDC(m_pDC);
		CBitmap m_bmp;
		m_bmp.LoadBitmap(IDB_BITMAP15);
		BITMAP bitmap;
		m_bmp.GetBitmap(&bitmap);
		CBitmap *pbmpOld = tDC.SelectObject(&m_bmp);
		static int curr = GAME_HEIGHT;
		if (curr >= 0)
			curr--;
		else
			curr = GAME_HEIGHT;
			pMemDC->BitBlt(0, curr, GAME_WIDTH, GAME_HEIGHT - curr, &tDC, 0, 0, SRCCOPY);
			pMemDC->BitBlt(0, 0, GAME_WIDTH, curr, &tDC, 0, GAME_HEIGHT - curr, SRCCOPY);
	}
	else
	{
		CRect rctClient;
		GetClientRect(rctClient);
		CDC tDC;
		tDC.CreateCompatibleDC(m_pDC);
		CBitmap m_bmp;                             
		m_bmp.LoadBitmap(IDB_BITMAP16);
		BITMAP bitmap;
		m_bmp.GetBitmap(&bitmap);
		CBitmap *pbmpOld = tDC.SelectObject(&m_bmp);
		static int curr = GAME_HEIGHT;
		if (curr >= 0)
			curr--;
		else
			curr = GAME_HEIGHT;
			pMemDC->BitBlt(0, curr, GAME_WIDTH, GAME_HEIGHT - curr, &tDC, 0, 0, SRCCOPY);
			pMemDC->BitBlt(0, 0, GAME_WIDTH, curr, &tDC, 0, GAME_HEIGHT - curr, SRCCOPY);
	}
	
	//===============�������=======================================================
	//����÷�
	CString strgrade;
	strgrade.Format(_T("��ǰ�÷� : %d"), grade);//��ʾ�÷�
	pMemDC->SetBkMode(TRANSPARENT);
	//TRANSPARENT��ʹ��͸���������Ҳ�������ֵı����ǲ��ı�ġ�
	//��ֹ������ɫ���ֳ�ͻ
	pMemDC->SetTextAlign(TA_CENTER);
	//�ú���Ϊָ���豸�����������ֶ����־��
	//TA_CENTER��׼�����޶����ε�����ˮƽ���롣
	pMemDC->SetTextColor(RGB(255, 0, 0));
	//��ɫ��Χ//����λ��50:��ʼ��x��y����
	pMemDC->TextOut(50, 0, strgrade);
	//�������
	CString strlife;
	strlife.Format(_T("ʣ��Ѫ��  : %d"), life);
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(50, 20, strlife);
	//����ؿ�
	CString strpass_num;
	strpass_num.Format(_T("��ǰ�ؿ�  : %d"), pass_num);
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(50, 40, strpass_num);
	//���BOSSѪ��
	CString strzz;
	strzz.Format(_T("BOSSѪ�� :%d"), bslife);
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(50, 60, strzz);

	CString strv;
	strv.Format(_T("��V�������޵�"));
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(76,196,222));
	pMemDC->TextOut(425, 0, strv);

	CString strc;
	strc.Format(_T("��C��ȡ���޵�"));
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(76, 196, 222));
	pMemDC->TextOut(425, 20, strc);
	CString strb;
	strb.Format(_T("��B����������"));
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(76, 196, 222));
	pMemDC->TextOut(425, 40, strb);
	CString strx;
	strx.Format(_T("��X����������"));
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(76, 196, 222));
	pMemDC->TextOut(425, 60, strx);
	CString strz;
	strz.Format(_T("��Z��ɢ������"));
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(76, 196, 222));
	pMemDC->TextOut(425, 80, strz);

	//�����ҷ�ս��
	if(m_pMe!=NULL&&life!=0)
	{
	   m_pMe->Draw(m_pMemDC,FALSE);
	}
	else
	{   //Game Over//����û��ʱ
		PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	}

	//����ս��Ѫ��
	if (m_pMe)
	{
		CPoint pt = m_pMe->GetPoint();
		if (life <= 3)
		{
			CTime t = CTime::GetCurrentTime();
			int s = t.GetSecond(); //��ȡ��
			if (s % 2 == 0)
			{
				CBrush blooW2(RGB(250, 0, 0));//����һ��ˢ�Ӷ���
				pMemDC->SelectObject(&blooW2);//ѡ����ˢ��
				pMemDC->Ellipse(pt.x + 26, pt.y + 70, pt.x + 46, pt.y + 90);//Բ�δ�С
			}
		}
		if (life <= 5)
		{
			CBrush blooW3(RGB(250, 0, 0));//����һ��ˢ�Ӷ���
			pMemDC->SelectObject(&blooW3);//ѡ����ˢ��
			pMemDC->Rectangle(pt.x, pt.y + 60, pt.x + (life * 14), pt.y + 66);
		}//���δ�С
		else
		{
			pMemDC->Rectangle(pt.x, pt.y + 60, pt.x + (5 * 14), pt.y + 66);//���δ�С
			CBrush blooW(RGB(250, 250, 0));//����һ��ˢ�Ӷ���
			pMemDC->SelectObject(&blooW);//ѡ����ˢ��
			pMemDC->Rectangle(pt.x, pt.y + 80, pt.x + ((life-5) * 14), pt.y + 86);//���δ�С
		}
	}

	//���� ��������ը���л����ӵ�
	for(int i=0;i<8;i++)
	{
		POSITION pos1,pos2;
		for( pos1 = m_ObjList[i].GetHeadPosition(); ( pos2 = pos1 ) != NULL; )
		{
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext( pos1 );
			if(!pObj->Draw(pMemDC,FALSE))
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}
	//::GetKeyState(VK_SHIFT) > 0 û����
	//::GetKeyState(VK_SHIFT) < 0������
	if (GetKeyState('V')<0)
	{
		wudi = 1;
	}
	if (wudi == 1)
	{
		CString strwudi;
		strwudi.Format(_T("�޵�ģʽ�ѿ���"));
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(240,255,255));
		pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, strwudi);
	}
	//����C��ȡ���޵�ģʽ
	if (GetKeyState('C')<0)
	{
		wudi = 0;
	}
	//�����ڴ�DC���豸DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	static int nCreator = 3;
	static int nCreator2 = 3;
	static int nCreator3 = 3;

	//��������л�
	if(nCreator<=0)
	{
		nCreator = 10;
		m_ObjList[enEnemy].AddTail(new CEnemy);
	}
	nCreator--;
	if(m_pMe==NULL)
		return;

	//��������л�2
	if (nCreator2 <= 0 && pass_num != 1)
	{
		nCreator2 = 10;
		m_ObjList[enEnemy2].AddTail(new Enemy2);
	}
	nCreator2--;
	if (m_pMe == NULL)
		return;
	//�������
	if (score == 10 && propsum == 0)
	{
		propsum++;
	}
	if (propsum == 1)
	{
		m_ObjList[prop].AddTail(new CProp);
		m_ObjList[prop2].AddTail(new CProp2);
		propsum++;
	}
	//�������2
	//����boss

	if (pass_num == 3 && grade == 0)
	{
		bssum++;
	}
	if ((bssum == 1))
	{
		m_ObjList[boss].AddTail(new CBoss);
		bssum++;
	}
	//����ĸ���������ƶ�ս��
	for(int i=0;i<4;i++)
	{
		int nMeMotion=0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		nMeMotion = GetKey(VK_UP);
		if(nMeMotion==1)
			m_pMe->SetVerMotion(1);
		    
		nMeMotion = GetKey(VK_DOWN);
		if(nMeMotion==1)
			m_pMe->SetVerMotion(-1);

		nMeMotion = GetKey(VK_RIGHT);
		if(nMeMotion==1)
			m_pMe->SetHorMotion(1);

		nMeMotion = GetKey(VK_LEFT);
		if(nMeMotion==1)
			m_pMe->SetHorMotion(-1);
	}
	
	//����ս������
	if(GetKey(VK_SPACE)==1)//�����˿ո��
	{
		if(m_pMe!=NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			if (p2 == 0)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 28, pt.y + 10, 0));
			}
			if (p2 == 1)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y + 10, 0));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 36, pt.y + 10, 0));
			}
			if (p2 == 2)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y + 10, 0));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 28, pt.y + 10, 0));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 36, pt.y + 10, 0));
			}
			if (p2 == 3)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 10, pt.y + 10, 4));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 10, pt.y + 10, 2));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 10, pt.y + 10, 0));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30, pt.y + 10, 0));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30, pt.y + 10, -2));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30, pt.y + 10, -4));
			}
		}
	}
	if (GetKeyState('X') < 0)
	{
		CPoint pt = m_pMe->GetPoint();
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y + 0, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 10, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 20, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 30, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 40, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 50, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 60, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 70, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 80, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 90, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 100, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 110, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 120, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 130, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 140, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 150, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 160, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 170, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 180, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 190, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 210, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 220, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 230, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 240, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 250, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y - 260, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y + 0, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 10, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 20, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 30, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 40, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 50, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 60, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 70, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 80, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 90, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 100, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 110, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 120, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 130, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 140, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 150, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 160, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 170, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 180, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 190, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 210, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 220, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 230, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 240, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 250, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y - 260, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y + 0, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 10, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 20, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 30, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 40, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 50, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 60, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 70, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 80, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 90, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 100, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 110, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 120, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 130, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 140, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 150, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 160, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 170, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 180, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 190, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 210, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 220, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 230, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 240, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 250, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y - 260, 0));
	}
	if (GetKeyState('Z') < 0 )
	{
		CPoint pt = m_pMe->GetPoint();
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 10, pt.y + 10, 6));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 10, pt.y + 10, 4));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 10, pt.y + 10, 2));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 10, pt.y + 10, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y + 10, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30, pt.y + 10, 0));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30, pt.y + 10, -2));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30, pt.y + 10, -4));
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30, pt.y + 10, -6));
	}
	//  ��B��һ������
	if ((GetKeyState('B')<0))
	{
		int k;
		CPoint pt = m_pMe->GetPoint();
		for (k = 0; k <= 800; k += 8)
		{
			m_ObjList[enBomb].AddTail(new CBomb(k, pt.y + 10, 0));
		}
	}

	//�л������ӵ�
	CPoint PlanePt = m_pMe->GetPoint();
	for(POSITION ePos=m_ObjList[enEnemy].GetHeadPosition();ePos!=NULL;)
	{
          CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		  if(!pEnemy->Fired())
			  continue;
		  CPoint  ePt = pEnemy->GetPoint();
		  BOOL by=FALSE;
		  //�л���ս��ǰ��
		  if(pEnemy->GetMontion()==1 && ePt.y<PlanePt.y)
		         by=  TRUE;
		  //�л���ս������
		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt.x+18,ePt.y+10,pEnemy->GetMontion()));
		  }
	}
	// �л�2�����ӵ�
	CPoint PlanePt2 = m_pMe->GetPoint();
	for (POSITION ePos = m_ObjList[enEnemy2].GetHeadPosition(); ePos != NULL;)
	{
		Enemy2* pEnemy2 = (Enemy2*)m_ObjList[enEnemy2].GetNext(ePos);
		if (!pEnemy2->Fired())
			continue;
		CPoint  ePt = pEnemy2->GetPoint();

		BOOL by = FALSE;
		m_ObjList[enBall].AddTail(new CBall(ePt.x + 20, ePt.y + 15, pEnemy2->GetMontion()));
		m_ObjList[enBall].AddTail(new CBall(ePt.x + 52, ePt.y + 10, pEnemy2->GetMontion()));

	}
	//boss �����ӵ�
	CPoint PlanePt3 = m_pMe->GetPoint();
	for (POSITION ePos3 = m_ObjList[boss].GetHeadPosition(); ePos3 != NULL;)
	{
		CBoss * pEnemy3 = (CBoss*)m_ObjList[boss].GetNext(ePos3);
		if (!pEnemy3->Fired())
			continue;
		CPoint  ePt = pEnemy3->GetPoint();

		BOOL by = FALSE;
		m_ObjList[enBall].AddTail(new CBall(ePt.x + 25, ePt.y + 15, pEnemy3->GetMontion()));
		m_ObjList[enBall].AddTail(new CBall(ePt.x + 70, ePt.y + 15, pEnemy3->GetMontion()));
		m_ObjList[enBall].AddTail(new CBall(ePt.x + 115, ePt.y + 15, pEnemy3->GetMontion()));
		m_ObjList[enBall].AddTail(new CBall(ePt.x + 25, ePt.y + 35, pEnemy3->GetMontion()));
		m_ObjList[enBall].AddTail(new CBall(ePt.x + 70, ePt.y + 35, pEnemy3->GetMontion()));
		m_ObjList[enBall].AddTail(new CBall(ePt.x + 115, ePt.y + 35, pEnemy3->GetMontion()));
		m_ObjList[enBall].AddTail(new CBall(ePt.x + 25, ePt.y + 55, pEnemy3->GetMontion()));
		m_ObjList[enBall].AddTail(new CBall(ePt.x + 70, ePt.y + 55, pEnemy3->GetMontion()));
		m_ObjList[enBall].AddTail(new CBall(ePt.x + 115, ePt.y + 55, pEnemy3->GetMontion()));
	}
	//�л��ӵ�ը��ս��
	POSITION bPos1=NULL,bPos2=NULL;
	CRect mRect = m_pMe->GetRect();
	for(bPos1=m_ObjList[enBall].GetHeadPosition();( bPos2 = bPos1 ) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		//�ж��Ƿ��ص�
		if(tmpRect.IntersectRect(&bRect,mRect))
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left,mRect.top)
				);
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;
			//ɾ��ս��
			if (wudi == 0)
			{
				if (life == 0)
				{
					delete m_pMe;
					m_pMe = NULL;
				}
				else
				{
					life=life-1;
				}
			}
			break;
		}
	}

	//�������ӵ��໥��ײ:�ڶ��ز��ܴ��ӵ�����������
	if (pass_num != 2)
	{
		POSITION mPos1 = NULL, mPos2 = NULL;
		for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
			CRect bRect = pBomb->GetRect();

			for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
			{
				CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
				CRect bRect1 = pBall->GetRect();
				CRect tmpRect;

				if (tmpRect.IntersectRect(&bRect1, bRect))   //�ж��������������Ƿ��н���
				{
				
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));
					//ɾ������

					m_ObjList[enBomb].RemoveAt(mPos2);
					delete pBomb;
					//ɾ���ӵ�
					m_ObjList[enBall].RemoveAt(bPos2);
					delete pBall;
					//grade++;
					break;
				}
			}
		}
	}
	//�л���ս����ײ
	POSITION bPos3 = NULL, bPos4 = NULL;
	CRect mRect3 = m_pMe->GetRect();
	for (bPos3 = m_ObjList[enEnemy].GetHeadPosition(); (bPos4 = bPos3) != NULL;)
	{
		CBall* enemy = (CBall*)m_ObjList[enEnemy].GetNext(bPos3);
		//��ȡ�л�
		CRect bRect2 = enemy->GetRect();
		//�ж��������������Ƿ��н���
		CRect tmpRect;
		//�ж��Ƿ��ص�
		if (tmpRect.IntersectRect(&bRect2, mRect3))
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(new CExplosion(mRect3.left, mRect3.top));
			//ɾ���л�
			m_ObjList[enEnemy].RemoveAt(bPos4);
			delete enemy;

			//ɾ��ս��
			if (wudi == 0)
			{
				if (life == 0)
				{
					delete m_pMe;
					m_pMe = NULL;
				}
				else
				{
					life--;
				}
			}
			break;
		}
	}
	//�Ե����������
	POSITION bPop = NULL, bPop1 = NULL;
	CRect mR = m_pMe->GetRect();
	for (bPop = m_ObjList[prop].GetHeadPosition(); (bPop1 = bPop) != NULL;)
	{
		CProp * en = (CProp*)m_ObjList[prop].GetNext(bPop);
		//��ȡ�����
		CRect bRe = en->GetRect();
		//�ж��������������Ƿ��н���
		CRect tmpRect;
		//�ж��Ƿ��ص�
		if (tmpRect.IntersectRect(&bRe, mR))
		{
			//ɾ�������
			m_ObjList[prop].RemoveAt(bPop1);
			delete en;
			life++;
			if (life > 10)
				life = 10;
			break;
		}
	}
	//�Ե����2
	POSITION bPop2 = NULL, bPop3 = NULL;
	CRect mR1 = m_pMe->GetRect();
	for (bPop2 = m_ObjList[prop2].GetHeadPosition(); (bPop3 = bPop2) != NULL;)
	{
		CProp * en1 = (CProp*)m_ObjList[prop2].GetNext(bPop2);
		//��ȡ�����
		CRect bRe1 = en1->GetRect();
		//�ж��������������Ƿ��н���
		CRect tmpRect;
		//�ж��Ƿ��ص�
		if (tmpRect.IntersectRect(&bRe1, mR1))
		{
			//ɾ�������
			m_ObjList[prop2].RemoveAt(bPop3);
			delete en1;
			p2++;
			if (p2 > 3)
				p2 = 3;
			break;
		}
	}
	//�л�2��ս����ײ
	POSITION bPos5 = NULL, bPos6 = NULL;
	CRect mRect4 = m_pMe->GetRect();
	for (bPos5 = m_ObjList[enEnemy2].GetHeadPosition(); (bPos6 = bPos5) != NULL;)
	{
		CBall* enemy2 = (CBall*)m_ObjList[enEnemy2].GetNext(bPos5);
		//��ȡ�л�
		CRect bRect3 = enemy2->GetRect();
		//�ж��������������Ƿ��н���
		CRect tmpRect;
		//�ж��Ƿ��ص�
		if (tmpRect.IntersectRect(&bRect3, mRect4))
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(new CExplosion(mRect4.left, mRect4.top));
			//ɾ���л�
			m_ObjList[enEnemy2].RemoveAt(bPos6);
			delete enemy2;
			//ɾ��ս��
			if (wudi == 0)
			{
				if (life == 0)
				{
					delete m_pMe;
					m_pMe = NULL;
				}
				else
				{
					life--;
				}
			}
			break;
		}
	}
	//ս������ը���л�
	POSITION mPos12 = NULL, mPos22 = NULL;
	for (mPos12 = m_ObjList[enBomb].GetHeadPosition(); (mPos22 = mPos12) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos12);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect1 = pEnemy->GetRect();
			CRect tmpRect;

			if (tmpRect.IntersectRect(&bRect, mRect1))   //�ж��������������Ƿ��н���
			{
			
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(new CExplosion(mRect1.left, mRect1.top));
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos22);
				delete pBomb;

				//ɾ���л�
				m_ObjList[enEnemy].RemoveAt(ePos2);
				delete pEnemy;
				score++;
				if (score > 10)
				{
					score = 0;
					propsum = 0;
				}
				grade++;
				break;
			}
		}
	}

	//ս������ը���л�2
	POSITION mPos7 = NULL, mPos8 = NULL;
	for (mPos7 = m_ObjList[enBomb].GetHeadPosition(); (mPos8 = mPos7) != NULL;)
	{
		CBomb* pBomb2 = (CBomb*)m_ObjList[enBomb].GetNext(mPos7);
		CRect bRect4 = pBomb2->GetRect();
		POSITION ePos7 = NULL, ePos8 = NULL;
		for (ePos7 = m_ObjList[enEnemy2].GetHeadPosition(); (ePos8 = ePos7) != NULL;)
		{
			Enemy2* pEnemy4 = (Enemy2*)m_ObjList[enEnemy2].GetNext(ePos7);
			CRect mRect11 = pEnemy4->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect4, mRect11))   //�ж��������������Ƿ��н���
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(new CExplosion(mRect11.left, mRect11.top));
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos8);
				delete pBomb2;
				//ɾ���л�
				m_ObjList[enEnemy2].RemoveAt(ePos8);
				delete pEnemy4;
				grade++;
				break;
			}
		}
	}
	//ս������ը��BOSS
	POSITION mPos9 = NULL, mPos10 = NULL;
	for (mPos9 = m_ObjList[enBomb].GetHeadPosition(); (mPos10 = mPos9) != NULL;)
	{
		CBomb* pBomb3 = (CBomb*)m_ObjList[enBomb].GetNext(mPos9);
		CRect bRect5 = pBomb3->GetRect();
		POSITION ePos9 = NULL, ePos10 = NULL;
		for (ePos9 = m_ObjList[boss].GetHeadPosition(); (ePos10 = ePos9) != NULL;)
		{
			CBoss* pboss = (CBoss*)m_ObjList[boss].GetNext(ePos9);
			CRect mRect0 = pboss->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&mRect0, bRect5))   //�ж��������������Ƿ��н���
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(new CExplosion(mRect0.left, mRect0.top));
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos10);
				delete pBomb3;
				bslife--;
				//ɾ���л�
				if (bslife == 0)
				{
					grade = grade + 150;
					m_ObjList[boss].RemoveAt(ePos10);
					delete pboss;
				}
				break;
			}
		}
	}

	//==========================������һ�ؽ���===============================================
	if (m_pMe != NULL && grade >= 50 * pass_num)
	{
		//���صı�־����
		m_pMe = NULL;
		delete m_pMe;
		is_Pass = 1;
	}
	if (is_Pass == 1)
	{
		if (pass_num == 3)
		{
			PlaySound((LPCTSTR)IDR_WAVE6, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
			KillTimer(1);
			if (AfxMessageBox(L"��ϲ����ͨ�أ��Ƿ����¿�ʼ��", MB_YESNO) == 6)
			{
				//��յл�����
				ListEnemy.RemoveAll();
				//���ս������
				ListMe.RemoveAll();
				//���ս���ӵ�����
				ListBomb.RemoveAll();
				//��յл�ը������
				ListBall.RemoveAll();
				//��ձ�ը����
				ListExplosion.RemoveAll();
				//����µ�ս������
				m_pMe = new CMyPlane;
				grade = 0;
				life = 5;
				bssum = 0;
				pass_num = 1;
				is_Pass = 0;
				bslife = 400;
				p2 = 0;
				PlaySound((LPCTSTR)IDR_WAVE4, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
				SetTimer(1, 30, NULL);
			}//if
			else
				exit(1);
		}//if
		else
		{
				KillTimer(1);
				if (AfxMessageBox(L"��ϲ��ɹ�����!�Ƿ������һ�أ�", MB_YESNO) == 6)
				{
					//��յл�����
					ListEnemy.RemoveAll();
					//���ս������
					ListMe.RemoveAll();
					//���ս���ӵ�����
					ListBomb.RemoveAll();
					//��յл�ը������
					ListBall.RemoveAll();
					//��ձ�ը����
					ListExplosion.RemoveAll();
					//����µ�ս������
					m_pMe = new CMyPlane;
					grade = 0;
					life += 1;
					pass_num++;
					is_Pass = 0;
					p2 = 0;
					bssum = 0;

					SetTimer(1, 30, NULL);
				}//if
				else
					exit(1);
			}//else
	}//if

	//====================������Ϸ����======================================================
	if (life == NULL)
	{
		PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		KillTimer(1);
		if (AfxMessageBox(L"GAME OVER��\n�Ƿ����¿�ʼ��", MB_YESNO) == 6)
		{
			//��յл�����
			ListEnemy.RemoveAll();
			//���ս������
			ListMe.RemoveAll();
			//���ս���ӵ�����
			ListBomb.RemoveAll();
			//��յл�ը������
			ListBall.RemoveAll();
			//��ձ�ը����
			ListExplosion.RemoveAll();
			//����µ�ս������
			m_pMe = new CMyPlane;
			grade = 0;
			life = 5;
			bssum = 0;
			pass_num = 1;
			bslife = 400;
			p2 = 0;
			PlaySound((LPCTSTR)IDR_WAVE4, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
			SetTimer(1, 30, NULL);
		}//if
		else
			exit(1);
	}//if
}//onTimer

void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
		//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
		UpdateFrame(m_pMemDC);
		AI();
	CView::OnTimer(nIDEvent);
}
void CPlaneGameView::OnDestroy()
{
	CView::OnDestroy();
	this->StopGame();
	// TODO: �ڴ˴������Ϣ����������
}

