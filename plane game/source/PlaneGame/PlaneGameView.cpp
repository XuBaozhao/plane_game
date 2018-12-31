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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	//ON_WM_DESTROY()//         
END_MESSAGE_MAP()

// CPlaneGameView 构造/析构
CPlaneGameView::CPlaneGameView() :m_pMe(NULL), grade(0), blood(5), is_Pass(0), score(0), p2(0)
{
	// TODO: 在此处添加构造代码	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	return CView::PreCreateWindow(cs);

	
}

// CPlaneGameView 绘制
void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
}

// CPlaneGameView 打印
BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

// CPlaneGameView 诊断
#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG

// CPlaneGameView 消息处理程序
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	//背景音乐
	
	//初始化游戏
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
	//产生随机数种子
	srand( (unsigned)time( NULL ) );
	//建立设备DC
	m_pDC = new CClientDC(this);
	//建立内存DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);
	//建立内存位图
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);
	//将位图选入内存DC
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

	//产生主角(战机)
	m_pMe = new CMyPlane;
	//启动游戏
	if (AfxMessageBox(L"Are you ready？", MB_YESNO) == 6){
		SetTimer(1, 30, NULL);
		PlaySound((LPCTSTR)IDR_WAVE4, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
		return TRUE;
	}
	else
		exit(1);
}

void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	//绘制天空
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
	
	//===============内容输出=======================================================
	//输出得分
	CString strgrade;
	strgrade.Format(_T("当前得分 : %d"), grade);//显示得分
	pMemDC->SetBkMode(TRANSPARENT);
	//TRANSPARENT是使用透明的输出，也就是文字的背景是不改变的。
	//防止两种颜色出现冲突
	pMemDC->SetTextAlign(TA_CENTER);
	//该函数为指定设备环境设置文字对齐标志。
	//TA_CENTER基准点与限定矩形的中心水平对齐。
	pMemDC->SetTextColor(RGB(255, 0, 0));
	//颜色范围//设置位置50:开始的x，y坐标
	pMemDC->TextOut(50, 0, strgrade);
	//输出生命
	CString strlife;
	strlife.Format(_T("剩余血量  : %d"), life);
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(50, 20, strlife);
	//输出关卡
	CString strpass_num;
	strpass_num.Format(_T("当前关卡  : %d"), pass_num);
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(50, 40, strpass_num);
	//输出BOSS血量
	CString strzz;
	strzz.Format(_T("BOSS血量 :%d"), bslife);
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(50, 60, strzz);

	CString strv;
	strv.Format(_T("‘V’开启无敌"));
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(76,196,222));
	pMemDC->TextOut(425, 0, strv);

	CString strc;
	strc.Format(_T("‘C’取消无敌"));
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(76, 196, 222));
	pMemDC->TextOut(425, 20, strc);
	CString strb;
	strb.Format(_T("‘B’清屏武器"));
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(76, 196, 222));
	pMemDC->TextOut(425, 40, strb);
	CString strx;
	strx.Format(_T("‘X’激光武器"));
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(76, 196, 222));
	pMemDC->TextOut(425, 60, strx);
	CString strz;
	strz.Format(_T("‘Z’散弹武器"));
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(76, 196, 222));
	pMemDC->TextOut(425, 80, strz);

	//绘制我方战机
	if(m_pMe!=NULL&&life!=0)
	{
	   m_pMe->Draw(m_pMemDC,FALSE);
	}
	else
	{   //Game Over//生命没有时
		PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	}

	//绘制战机血条
	if (m_pMe)
	{
		CPoint pt = m_pMe->GetPoint();
		if (life <= 3)
		{
			CTime t = CTime::GetCurrentTime();
			int s = t.GetSecond(); //获取秒
			if (s % 2 == 0)
			{
				CBrush blooW2(RGB(250, 0, 0));//定义一个刷子对象
				pMemDC->SelectObject(&blooW2);//选定该刷子
				pMemDC->Ellipse(pt.x + 26, pt.y + 70, pt.x + 46, pt.y + 90);//圆形大小
			}
		}
		if (life <= 5)
		{
			CBrush blooW3(RGB(250, 0, 0));//定义一个刷子对象
			pMemDC->SelectObject(&blooW3);//选定该刷子
			pMemDC->Rectangle(pt.x, pt.y + 60, pt.x + (life * 14), pt.y + 66);
		}//矩形大小
		else
		{
			pMemDC->Rectangle(pt.x, pt.y + 60, pt.x + (5 * 14), pt.y + 66);//矩形大小
			CBrush blooW(RGB(250, 250, 0));//定义一个刷子对象
			pMemDC->SelectObject(&blooW);//选定该刷子
			pMemDC->Rectangle(pt.x, pt.y + 80, pt.x + ((life-5) * 14), pt.y + 86);//矩形大小
		}
	}

	//绘制 导弹、爆炸、敌机、子弹
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
	//::GetKeyState(VK_SHIFT) > 0 没按下
	//::GetKeyState(VK_SHIFT) < 0被按下
	if (GetKeyState('V')<0)
	{
		wudi = 1;
	}
	if (wudi == 1)
	{
		CString strwudi;
		strwudi.Format(_T("无敌模式已开启"));
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(240,255,255));
		pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, strwudi);
	}
	//按“C”取消无敌模式
	if (GetKeyState('C')<0)
	{
		wudi = 0;
	}
	//复制内存DC到设备DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	static int nCreator = 3;
	static int nCreator2 = 3;
	static int nCreator3 = 3;

	//随机产生敌机
	if(nCreator<=0)
	{
		nCreator = 10;
		m_ObjList[enEnemy].AddTail(new CEnemy);
	}
	nCreator--;
	if(m_pMe==NULL)
		return;

	//随机产生敌机2
	if (nCreator2 <= 0 && pass_num != 1)
	{
		nCreator2 = 10;
		m_ObjList[enEnemy2].AddTail(new Enemy2);
	}
	nCreator2--;
	if (m_pMe == NULL)
		return;
	//掉落道具
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
	//掉落道具2
	//产生boss

	if (pass_num == 3 && grade == 0)
	{
		bssum++;
	}
	if ((bssum == 1))
	{
		m_ObjList[boss].AddTail(new CBoss);
		bssum++;
	}
	//检测四个方向键，移动战机
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
	
	//产生战机导弹
	if(GetKey(VK_SPACE)==1)//按下了空格键
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
	//  按B键一键清屏
	if ((GetKeyState('B')<0))
	{
		int k;
		CPoint pt = m_pMe->GetPoint();
		for (k = 0; k <= 800; k += 8)
		{
			m_ObjList[enBomb].AddTail(new CBomb(k, pt.y + 10, 0));
		}
	}

	//敌机发射子弹
	CPoint PlanePt = m_pMe->GetPoint();
	for(POSITION ePos=m_ObjList[enEnemy].GetHeadPosition();ePos!=NULL;)
	{
          CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		  if(!pEnemy->Fired())
			  continue;
		  CPoint  ePt = pEnemy->GetPoint();
		  BOOL by=FALSE;
		  //敌机在战机前面
		  if(pEnemy->GetMontion()==1 && ePt.y<PlanePt.y)
		         by=  TRUE;
		  //敌机在战机后面
		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt.x+18,ePt.y+10,pEnemy->GetMontion()));
		  }
	}
	// 敌机2发射子弹
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
	//boss 发射子弹
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
	//敌机子弹炸掉战机
	POSITION bPos1=NULL,bPos2=NULL;
	CRect mRect = m_pMe->GetRect();
	for(bPos1=m_ObjList[enBall].GetHeadPosition();( bPos2 = bPos1 ) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		//判断是否重叠
		if(tmpRect.IntersectRect(&bRect,mRect))
		{
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left,mRect.top)
				);
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;
			//删除战机
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

	//导弹与子弹相互碰撞:第二关不能打子弹其他都可以
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

				if (tmpRect.IntersectRect(&bRect1, bRect))   //判断两个矩形区域是否有交接
				{
				
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));
					//删除导弹

					m_ObjList[enBomb].RemoveAt(mPos2);
					delete pBomb;
					//删除子弹
					m_ObjList[enBall].RemoveAt(bPos2);
					delete pBall;
					//grade++;
					break;
				}
			}
		}
	}
	//敌机与战机碰撞
	POSITION bPos3 = NULL, bPos4 = NULL;
	CRect mRect3 = m_pMe->GetRect();
	for (bPos3 = m_ObjList[enEnemy].GetHeadPosition(); (bPos4 = bPos3) != NULL;)
	{
		CBall* enemy = (CBall*)m_ObjList[enEnemy].GetNext(bPos3);
		//获取敌机
		CRect bRect2 = enemy->GetRect();
		//判断两个矩形区域是否有交接
		CRect tmpRect;
		//判断是否重叠
		if (tmpRect.IntersectRect(&bRect2, mRect3))
		{
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(new CExplosion(mRect3.left, mRect3.top));
			//删除敌机
			m_ObjList[enEnemy].RemoveAt(bPos4);
			delete enemy;

			//删除战机
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
	//吃掉落包加生命
	POSITION bPop = NULL, bPop1 = NULL;
	CRect mR = m_pMe->GetRect();
	for (bPop = m_ObjList[prop].GetHeadPosition(); (bPop1 = bPop) != NULL;)
	{
		CProp * en = (CProp*)m_ObjList[prop].GetNext(bPop);
		//获取掉落包
		CRect bRe = en->GetRect();
		//判断两个矩形区域是否有交接
		CRect tmpRect;
		//判断是否重叠
		if (tmpRect.IntersectRect(&bRe, mR))
		{
			//删除掉落包
			m_ObjList[prop].RemoveAt(bPop1);
			delete en;
			life++;
			if (life > 10)
				life = 10;
			break;
		}
	}
	//吃掉落包2
	POSITION bPop2 = NULL, bPop3 = NULL;
	CRect mR1 = m_pMe->GetRect();
	for (bPop2 = m_ObjList[prop2].GetHeadPosition(); (bPop3 = bPop2) != NULL;)
	{
		CProp * en1 = (CProp*)m_ObjList[prop2].GetNext(bPop2);
		//获取掉落包
		CRect bRe1 = en1->GetRect();
		//判断两个矩形区域是否有交接
		CRect tmpRect;
		//判断是否重叠
		if (tmpRect.IntersectRect(&bRe1, mR1))
		{
			//删除掉落包
			m_ObjList[prop2].RemoveAt(bPop3);
			delete en1;
			p2++;
			if (p2 > 3)
				p2 = 3;
			break;
		}
	}
	//敌机2与战机碰撞
	POSITION bPos5 = NULL, bPos6 = NULL;
	CRect mRect4 = m_pMe->GetRect();
	for (bPos5 = m_ObjList[enEnemy2].GetHeadPosition(); (bPos6 = bPos5) != NULL;)
	{
		CBall* enemy2 = (CBall*)m_ObjList[enEnemy2].GetNext(bPos5);
		//获取敌机
		CRect bRect3 = enemy2->GetRect();
		//判断两个矩形区域是否有交接
		CRect tmpRect;
		//判断是否重叠
		if (tmpRect.IntersectRect(&bRect3, mRect4))
		{
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(new CExplosion(mRect4.left, mRect4.top));
			//删除敌机
			m_ObjList[enEnemy2].RemoveAt(bPos6);
			delete enemy2;
			//删除战机
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
	//战机导弹炸掉敌机
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

			if (tmpRect.IntersectRect(&bRect, mRect1))   //判断两个矩形区域是否有交接
			{
			
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(new CExplosion(mRect1.left, mRect1.top));
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPos22);
				delete pBomb;

				//删除敌机
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

	//战机导弹炸掉敌机2
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
			if (tmpRect.IntersectRect(&bRect4, mRect11))   //判断两个矩形区域是否有交接
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(new CExplosion(mRect11.left, mRect11.top));
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPos8);
				delete pBomb2;
				//删除敌机
				m_ObjList[enEnemy2].RemoveAt(ePos8);
				delete pEnemy4;
				grade++;
				break;
			}
		}
	}
	//战机导弹炸掉BOSS
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
			if (tmpRect.IntersectRect(&mRect0, bRect5))   //判断两个矩形区域是否有交接
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(new CExplosion(mRect0.left, mRect0.top));
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPos10);
				delete pBomb3;
				bslife--;
				//删除敌机
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

	//==========================进入下一关界面===============================================
	if (m_pMe != NULL && grade >= 50 * pass_num)
	{
		//过关的标志变量
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
			if (AfxMessageBox(L"恭喜！已通关！是否重新开始？", MB_YESNO) == 6)
			{
				//清空敌机链表
				ListEnemy.RemoveAll();
				//清空战机链表
				ListMe.RemoveAll();
				//清空战机子弹链表
				ListBomb.RemoveAll();
				//清空敌机炸弹链表
				ListBall.RemoveAll();
				//清空爆炸链表
				ListExplosion.RemoveAll();
				//添加新的战机对象
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
				if (AfxMessageBox(L"恭喜你成功过关!是否进入下一关？", MB_YESNO) == 6)
				{
					//清空敌机链表
					ListEnemy.RemoveAll();
					//清空战机链表
					ListMe.RemoveAll();
					//清空战机子弹链表
					ListBomb.RemoveAll();
					//清空敌机炸弹链表
					ListBall.RemoveAll();
					//清空爆炸链表
					ListExplosion.RemoveAll();
					//添加新的战机对象
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

	//====================结束游戏界面======================================================
	if (life == NULL)
	{
		PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		KillTimer(1);
		if (AfxMessageBox(L"GAME OVER！\n是否重新开始？", MB_YESNO) == 6)
		{
			//清空敌机链表
			ListEnemy.RemoveAll();
			//清空战机链表
			ListMe.RemoveAll();
			//清空战机子弹链表
			ListBomb.RemoveAll();
			//清空敌机炸弹链表
			ListBall.RemoveAll();
			//清空爆炸链表
			ListExplosion.RemoveAll();
			//添加新的战机对象
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
		//刷新游戏帧画面: 在内存DC上绘图
		UpdateFrame(m_pMemDC);
		AI();
	CView::OnTimer(nIDEvent);
}
void CPlaneGameView::OnDestroy()
{
	CView::OnDestroy();
	this->StopGame();
	// TODO: 在此处添加消息处理程序代码
}

