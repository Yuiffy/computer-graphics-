
// ttView.cpp : CttView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "tt.h"
#endif

#include "ttDoc.h"
#include "ttView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CttView

IMPLEMENT_DYNCREATE(CttView, CView)

BEGIN_MESSAGE_MAP(CttView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CttView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MID, &CttView::OnMid)
	ON_COMMAND(ID_Bsm, &CttView::OnBsm)
	ON_COMMAND(ID_LINE, &CttView::OnLine)
	ON_COMMAND(ID_SEED, &CttView::OnSeed)
	ON_COMMAND(ID_SEEDLINE, &CttView::OnSeedline)
	ON_COMMAND(ID_ANIME, &CttView::OnAnime)
	ON_WM_TIMER()
	ON_COMMAND(ID_XDC, &CttView::OnXdc)
	ON_COMMAND(ID_YDC, &CttView::OnYdc)
	ON_COMMAND(ID_XYDC, &CttView::OnXydc)
	ON_COMMAND(ID_MOVE, &CttView::OnMove)
	ON_COMMAND(ID_XUANZHUAN, &CttView::OnXuanzhuan)
	ON_COMMAND(ID_SUOFANG, &CttView::OnSuofang)
	ON_COMMAND(ID_CLEARSCREEN, &CttView::OnClearscreen)
	ON_COMMAND(ID_COHEN, &CttView::OnCohen)
	ON_COMMAND(ID_ADT, &CttView::OnAdt)
	ON_COMMAND(ID_GAME, &CttView::OnGame)
END_MESSAGE_MAP()

// CttView 构造/析构

CttView::CttView()
{
	// TODO: 在此处添加构造代码
	m_point.clear();
	m_graphtype=0;
	m_cls = 0;
	m_x = 5;
	m_y = 5;
	m_stepX = 15;
	m_stepY = 1;
	m_animeON = 0;

	m_l = 100;
	m_r = 500;
	m_u = 100;
	m_d = 400;

	m_gameON = 0;
	srand(time(NULL));
	AfxMessageBox(_T("《画图and游戏最后的蓝球》\n欢迎使用本软件，本软件是一个集画图功能和游戏功能于一体的软件。\n要玩游戏请点击上面的游戏按钮。\nBy 1120310421董羽飞"));
}

CttView::~CttView()
{
}

BOOL CttView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CttView 绘制

void CttView::OnDraw(CDC* pDC)
{
	CttDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//pDC->MoveTo(10,10);
	//pDC->LineTo(10,400);
	//pDC->LineTo(1024,400);
	//pDC->LineTo(1024,10);
	//pDC->LineTo(10,10);
	if (m_animeON){
		CRect rect;
		GetClientRect(&rect);

		if (m_cls) pDC->FillRect(rect, RGB(0, 0, 0));
		double as = fabs(sin(m_x / 50.0));
		double ac = fabs(cos(m_y / 50.0));
		double as2 = sin(2 * 3.1415926 *m_x / rect.Width());
		double ac2 = sin(2 * 3.1415926 *m_y / rect.Height());
		int rc = min((int)(((as2 + 1.0) / 2.0) * 0xff), 0xff);
		int gc = min((int)(((ac2 + 1.0) / 2.0) * 0xff), 0xff);
		int bc = min(255, 512 - rc - gc);
		COLORREF color = RGB(rc, gc, bc);

		CPen pen(1, 5, color);
		CBrush brush(color);
		pDC->SelectObject(&pen);
		pDC->SelectObject(&brush);
		int bigx = abs(sin(m_x / 50.0)) * 50 + 1;
		int bigy = abs(cos(m_y / 50.0)) * 50 + 1;
		pDC->Ellipse(m_x - bigx, m_y - bigy, m_x + bigx, m_y + bigy);
	}
	if (m_gameON){
		CRect rect;
		GetClientRect(&rect);
		int &px = m_player_x;
		int &py = m_player_y;
		int bigx = 30;
		int bigy = 30;
		COLORREF color = RGB(23, 123, 123);
		COLORREF enemy_color = RGB(255, 0, 0);
		CPen pen(1, 5, color);
		CBrush brush(RGB(23,123,223));
		CPen pen2(1, 3, enemy_color);
		CBrush brush2(RGB(0,0,0));
		CPen pen3(1, 2, RGB(123,255,23));
		CBrush brush3(RGB(155, 225, 123));
		pDC->FillRect(rect, RGB(0, 0, 0));
		int cnt = m_enemy.size();
		pDC->SelectObject(&pen2);
		pDC->SelectObject(&brush2);
		for (int i = 0; i < cnt; i++){
			int ex = m_enemy[i].x;
			int ey = m_enemy[i].y;
			pDC->Ellipse(ex-10,ey-10,ex+10,ey+10);
		}
		pDC->SelectObject(&pen3);
		pDC->SelectObject(&brush3);
		cnt = m_bullet.size();
		for (int i = 0; i < cnt; i++){
			int ex = m_bullet[i].first.x;
			int ey = m_bullet[i].first.y;
			pDC->Ellipse(ex - 10, ey - 10, ex + 10, ey + 10);
		}
		pDC->SelectObject(&pen);
		pDC->SelectObject(&brush);
		pDC->Ellipse(px - bigx, py - bigy, px + bigx, py + bigy);
	}
	// TODO: 在此处为本机数据添加绘制代码
}


// CttView 打印


void CttView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CttView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CttView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CttView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CttView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CttView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CttView 诊断

#ifdef _DEBUG
void CttView::AssertValid() const
{
	CView::AssertValid();
}

void CttView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CttDoc* CttView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CttDoc)));
	return (CttDoc*)m_pDocument;
}
#endif //_DEBUG


// CttView 消息处理程序


void CttView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_gameON){
		MakeBullet(CPoint(m_player_x,m_player_y),point);
		return;
	}
	if(m_graphtype<=2)m_point.push_back(point);
	else if(m_graphtype==3){
		CDC* pDC = GetWindowDC();
		SeedFill(point.x , point.y , RGB(0,0,0),pDC);
	}else if(m_graphtype==4){
		CDC* pDC = GetWindowDC();
		SeedLine(point.x , point.y ,RGB(123,23,3), RGB(0,0,0),pDC);
	}
	else if (m_graphtype == 5){
		DuiChengX(point.x,point.y);
	}
	else if (m_graphtype == 6){
		DuiChengY(point.x, point.y);
	}
	else if (m_graphtype == 7){
		DuiChengXY(point.x, point.y);
	}
	else if (m_graphtype == 8){
		GraphMove(point.x, point.y);
	}
	else if (m_graphtype == 9){
		XuanZhuan(point.x, point.y);
	}
	else if (m_graphtype == 10){
		SuoFang(point.x, point.y);
	}
	else if (m_graphtype == 11){
		PointCai(point.x, point.y);
	}
	else if (m_graphtype == 12){
		m_point.push_back(point);
	}

	CView::OnLButtonDown(nFlags, point);
}


void CttView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	drawGraph();
	m_last_point = m_point;

	m_point.clear();

	CView::OnRButtonDown(nFlags, point);
}


void CttView::drawGraph(void)
{
	int i;
	int sz=m_point.size();
	if(sz==0)return;
	for(i=0; i<sz-1; i++){
		drawLine(m_point[i] , m_point[i+1]);
	}
	drawLine(m_point[sz-1] , m_point[0]);
	if (m_graphtype == 12) ADTFill(RGB(223,123,123));
}


void CttView::drawLine(CPoint st, CPoint ed)
{
	switch(m_graphtype){
		case 0:LineLine(st,ed);break;
		case 1:MidLine(st,ed);break;
		case 2:BsmLine(st,ed);break;
		default:LineLine(st,ed);
	}
}

void CttView::LineLine(CPoint st, CPoint ed)
{
	CDC* pDC = GetWindowDC();
	pDC->MoveTo(st);
	pDC->LineTo(ed);
}

void CttView::MidLine(CPoint st, CPoint ed)
{
	CDC* pDC = GetWindowDC();
	COLORREF color = RGB(0,0,0);
	int x,y;
	int dx=(((ed.x-st.x)>0)<<1)-1;
	int dy=(((ed.y-st.y)>0)<<1)-1;	//算y的增量是1还是-1
	//x若相等，则为竖着的直线
	if(ed.x==st.x){
		int x=st.x, y=st.y;
		while(y!=ed.y){
			pDC->SetPixel(x,y,color);
			y+=dy;
		}
		pDC->SetPixel(x,y,color);
		return;
	}

	//斜率小于等于1 / 大于1
	if(fabs((1.0*ed.y-st.y)/(1.0*ed.x-st.x)) <= 1.0){
		if(st.x > ed.x)swap(st,ed);		//将小的x放st、大的放ed
		dy=(((ed.y-st.y)>0)<<1)-1;
		x=st.x;
		y=st.y;
		int a=(st.y - ed.y)*dy;
		int b=(ed.x - st.x);
		int d=a+a+b;
		while(x!=ed.x || y!=ed.y){
			pDC->SetPixel(x,y,color);
			if(d>0){
				x++;
				d+=a+a;
			}else if(d<0){
				x++;
				y+=dy;
				d+=a+b+a+b;
			}else{
				x++;
				d+=a+a;
			}
		}
	}else{	//斜率大于1，则xy交换
		if(st.y > ed.y)swap(st,ed);		//将小的y放st、大的放ed
		dx=(((ed.x-st.x)>0)<<1)-1;
		x=st.x;
		y=st.y;
		int a=(st.x - ed.x)*dx;
		int b=(ed.y - st.y);
		int d=a+a+b;
		while(x!=ed.x || y!=ed.y){
			pDC->SetPixel(x,y,color);
			if(d>0){
				y++;
				d+=a+a;
			}else if(d<0){
				y++;
				x+=dx;
				d+=a+b+a+b;
			}else{
				y++;
				d+=a+a;
			}
		}
	}

	pDC->SetPixel(x,y,color);
}

void CttView::BsmLine(CPoint st, CPoint ed)
{
	CDC* pDC = GetWindowDC();
	COLORREF color = RGB(0,0,0);
	int x,y;
	int dx=(((ed.x-st.x)>0)<<1)-1;
	int dy=(((ed.y-st.y)>0)<<1)-1;	//算y的增量是1还是-1
	//x若相等，则为横着的直线
	if(ed.x==st.x){
		int x=st.x, y=st.y;
		while(y!=ed.y){
			pDC->SetPixel(x,y,color);
			y+=dy;
		}
		pDC->SetPixel(x,y,color);
		return;
	}

	//斜率小于等于1 / 大于1
	if(fabs((1.0*ed.y-st.y)/(1.0*ed.x-st.x)) <= 1.0){
		if(st.x > ed.x)swap(st,ed);		//将小的x放st、大的放ed
		dy=(((ed.y-st.y)>0)<<1)-1;
		x=st.x;
		y=st.y;
		int dtx=ed.x-st.x;
		int dty=(ed.y-st.y)*dy;
		int e=2*dty-dtx;
		while(x!=ed.x || y!=ed.y){
			pDC->SetPixel(x,y,color);
			if(e>=0){
				x++;
				y+=dy;
				e+=dty+dty-dtx-dtx;
			}else{
				x++;
				e+=dty+dty;
			}
		}
	}else{	//斜率大于1，则xy交换
		if(st.y > ed.y)swap(st,ed);		//将小的y放st、大的放ed
		dx=(((ed.x-st.x)>0)<<1)-1;
		x=st.x;
		y=st.y;
		int dtx=(ed.x-st.x)*dx;
		int dty=ed.y-st.y;
		int e=2*dtx-dty;
		while(x!=ed.x || y!=ed.y){
			pDC->SetPixel(x,y,color);
			if(e>=0){
				y++;
				x+=dx;
				e+=dtx+dtx-dty-dty;
			}else{
				y++;
				e+=dtx+dtx;
			}
		}
	}
	pDC->SetPixel(x,y,color);
}

void CttView::SeedFill(const int &x,const int &y,const COLORREF &color , CDC* pDC)
{
	pDC->SetPixel(x,y,color);
	if(pDC->GetPixel(x+1,y)!=color)SeedFill(x+1,y, color, pDC);
	if(pDC->GetPixel(x-1,y)!=color)SeedFill(x-1,y, color, pDC);
	if(pDC->GetPixel(x,y+1)!=color)SeedFill(x,y+1, color, pDC);
	if(pDC->GetPixel(x,y-1)!=color)SeedFill(x,y-1, color, pDC);
}

void CttView::SeedLine(const int &X,const int &Y,const COLORREF &color,const COLORREF &b_color , CDC* pDC)
{
	vector<CPoint> v;
	v.clear();
	v.push_back(CPoint(X,Y));
	while(!v.empty()){
		CPoint p=v.back();
		v.pop_back();
		int x=p.x;
		int y=p.y;
		int l,r;
		pDC->SetPixel(x,y,color);
		l=x;
		r=x;
		while(pDC->GetPixel(l-1,y)!=b_color){
			l--;
			pDC->SetPixel(l,y,color);
		}
		while(pDC->GetPixel(r+1,y)!=b_color){
			r++;
			pDC->SetPixel(r,y,color);
		}
		printf("%d,%d,%d,%d\n",x,y,l,r);
		SeedLineSearch(l,r,y-1,color,b_color,pDC,v);
		SeedLineSearch(l,r,y+1,color,b_color,pDC,v);
	}
}

void CttView::SeedLineSearch(const int &l, const int &r, const int &y,const COLORREF &color,const COLORREF &b_color , CDC* pDC, vector<CPoint> &v){
	int ready=0;
	for(int i=l; i<=r; i++){
		COLORREF t=pDC->GetPixel(i,y);
		if(t!=b_color && t!=color){
			ready=1;
		}else{
			if(ready==1){
				v.push_back(CPoint(i-1,y));
				ready=0;
			}
		}
	}
	if(ready==1){
		v.push_back(CPoint(r,y));
	}
}

void CttView::OnMid()
{
	// TODO: 在此添加命令处理程序代码
	m_graphtype=1;
}


void CttView::OnBsm()
{
	// TODO: 在此添加命令处理程序代码
	m_graphtype=2;
}


void CttView::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	m_graphtype=0;
}


void CttView::OnSeed()
{
	// TODO: 在此添加命令处理程序代码
	m_graphtype=3;
}


void CttView::OnSeedline()
{
	// TODO: 在此添加命令处理程序代码
	m_graphtype=4;
}



void CttView::OnXdc()
{
	// TODO: Add your command handler code here
	m_graphtype = 5;
}

void CttView::DuiChengX(const int &x, const int &y){
	int i;
	int sz = m_last_point.size();
	vector<CPoint> mlp = m_last_point;
	if (sz == 0)return;

	for (i = 0; i<sz - 1; i++){
		CPoint st, ed, fs,fe;
		fs = mlp[i];
		fe = mlp[i + 1];
		st.x = fs.x;
		st.y = -(fs.y - y) + y;
		ed.x = fe.x;
		ed.y = -(fe.y - y) + y;
		LineLine(st,ed);
	}
	CPoint st, ed, fs, fe;
	fs = mlp[sz-1];
	fe = mlp[0];
	st.x = fs.x;
	st.y = -(fs.y - y) + y;
	ed.x = fe.x;
	ed.y = -(fe.y - y) + y;
	LineLine(st,ed);
}

void CttView::DuiChengY(const int &x, const int &y){
	int i;
	int sz = m_last_point.size();
	vector<CPoint> mlp = m_last_point;
	if (sz == 0)return;

	for (i = 0; i<sz - 1; i++){
		CPoint st, ed, fs, fe;
		fs = mlp[i];
		fe = mlp[i + 1];
		st.x = -(fs.x-x)+x;
		st.y = fs.y;
		ed.x = -(fe.x - x) + x;
		ed.y = fe.y;
		LineLine(st, ed);
	}
	CPoint st, ed, fs, fe;
	fs = mlp[sz - 1];
	fe = mlp[0];
	st.x = -(fs.x - x) + x;
	st.y = fs.y;
	ed.x = -(fe.x - x) + x;
	ed.y = fe.y;
	LineLine(st, ed);
}

void CttView::DuiChengXY(const int &x, const int &y){
	int i;
	int sz = m_last_point.size();
	vector<CPoint> mlp = m_last_point;
	if (sz == 0)return;

	for (i = 0; i<sz - 1; i++){
		CPoint st, ed, fs, fe;
		fs = mlp[i];
		fe = mlp[i + 1];
		st.x = -(fs.x - x) + x;
		st.y = -(fs.y - y) + y;
		ed.x = -(fe.x - x) + x;
		ed.y = -(fe.y - y) + y;
		LineLine(st, ed);
	}
	CPoint st, ed, fs, fe;
	fs = mlp[sz - 1];
	fe = mlp[0];
	st.x = -(fs.x - x) + x;
	st.y = -(fs.y - y) + y;
	ed.x = -(fe.x - x) + x;
	ed.y = -(fe.y - y) + y;
	LineLine(st, ed);
}

void CttView::GraphMove(const int &x, const int &y){
	int i;
	int sz = m_last_point.size();
	vector<CPoint> mlp = m_last_point;
	if (sz == 0)return;
	int dx = x - mlp[0].x;
	int dy = y - mlp[0].y;
	for (i = 0; i < sz; i++){
		mlp[i].x += dx;
		mlp[i].y += dy;
	}
	for (i = 0; i<sz - 1; i++){
		LineLine(mlp[i], mlp[i + 1]);
	}
	LineLine(mlp[sz - 1], mlp[0]);
}

void CttView::XuanZhuan(const int &x, const int &y){
	int i;
	int sz = m_last_point.size();
	vector<CPoint> mlp = m_last_point;
	if (sz == 0)return;
	int dx = x - mlp[0].x;
	int dy = y - mlp[0].y;
	int x0 = mlp[0].x;
	int y0 = mlp[0].y;
	double dxy = sqrt(dx*dx + dy*dy);
	double sin = ((double)dx)/(dxy);
	double cos = ((double)dy)/(dxy);
	for (i = 0; i < sz; i++){
		int fx = m_last_point[i].x;
		int fy = m_last_point[i].y;
		mlp[i].x = (fx-x0)*cos - (fy-y0)*sin + x0;
		mlp[i].y = (fx-x0)*sin + (fy-y0)*cos + y0;
	}
	for (i = 0; i<sz - 1; i++){
		LineLine(mlp[i], mlp[i + 1]);
	}
	LineLine(mlp[sz - 1], mlp[0]);
}

void CttView::SuoFang(const int &x, const int &y){
	int i;
	int sz = m_last_point.size();
	vector<CPoint> mlp = m_last_point;
	if (sz < 2)return;
	int x0 = mlp[0].x;
	int y0 = mlp[0].y;
	int dx = x - mlp[0].x;
	int dy = y - mlp[0].y;
	int dx2 = mlp[1].x - mlp[0].x;
	int dy2 = mlp[1].y - mlp[0].y;
	double dxy = sqrt(dx*dx + dy*dy);
	double dxy2 = sqrt(dx2*dx2 + dy2*dy2);
	double rate = dxy / dxy2;
	for (i = 0; i < sz; i++){
		int fx = m_last_point[i].x;
		int fy = m_last_point[i].y;
		mlp[i].x = (fx - x0)*rate + x0;
		mlp[i].y = (fy - y0)*rate + y0;
	}
	for (i = 0; i<sz - 1; i++){
		LineLine(mlp[i], mlp[i + 1]);
	}
	LineLine(mlp[sz - 1], mlp[0]);
}

void CttView::OnYdc()
{
	// TODO: Add your command handler code here
	m_graphtype = 6;
}


void CttView::OnXydc()
{
	// TODO: Add your command handler code here
	m_graphtype = 7;
}


void CttView::OnMove()
{
	// TODO: Add your command handler code here
	m_graphtype = 8;
}


void CttView::OnXuanzhuan()
{
	// TODO: Add your command handler code here
	m_graphtype = 9;
}


void CttView::OnSuofang()
{
	// TODO: Add your command handler code here
	m_graphtype = 10;
}


void CttView::OnClearscreen()
{
	// TODO: Add your command handler code here
	m_cls = 1;
	Invalidate(FALSE);
}


void CttView::OnCohen()
{
	// TODO: Add your command handler code here
	CDC* pDC = GetWindowDC();
	pDC->MoveTo(m_l,m_u);
	pDC->LineTo(m_l,m_d);
	pDC->LineTo(m_r,m_d);
	pDC->LineTo(m_r,m_u);
	pDC->LineTo(m_l,m_u);
	m_point.clear();
	m_graphtype = 11;
}

void CttView::PointCai(const int &x, const int &y){
	CPoint p;
	p.x = x;
	p.y = y;
	m_point.push_back(p);
	if (m_point.size() == 2){
		LineCai(m_point[0], m_point[1]);
		m_point.clear();
	}
}

void CttView::LineCai(const CPoint &x, const CPoint &y){
	int c[2][4];
	int cnum[2];
	CDC* pDC = GetWindowDC();
	CPen pen1(0, 0, RGB(255, 0, 0));
	CPen pen2(0, 3, RGB(0, 0, 0));
	CPen pen3(0, 2, RGB(0, 0, 0));
	GetC(c[0],cnum[0],x);
	GetC(c[1],cnum[1],y);
	if (cnum[0] & cnum[1]){
		pDC->SelectObject(&pen1);
		pDC->MoveTo(x);
		pDC->LineTo(y);
		return;
	}
	if ((cnum[0] | cnum[1])==0){
		pDC->SelectObject(&pen2);
		pDC->MoveTo(x);
		pDC->LineTo(y);
		return;
	}
	pDC->SelectObject(&pen1);
	pDC->MoveTo(x);
	pDC->LineTo(y);
	CPoint a[2];
	int an = 0;
	if (c[0][0] != c[1][0])//与下边有交
	{
		int jx = x.x + (1.0*m_d - x.y) / (y.y - x.y)  *(y.x - x.x);
		if (jx > m_l && jx < m_r) a[an++] = CPoint(jx, m_d);
	}
	if (c[0][1] != c[1][1])//与上边有交
	{
		int jx = x.x + (1.0*m_u - x.y) / (y.y - x.y)  *(y.x - x.x);
		if (jx > m_l && jx < m_r) a[an++] = CPoint(jx, m_u);
	}
	if (c[0][2] != c[1][2])//与右边有交
	{
		int jy = x.y + (1.0*m_r - x.x) / (y.x - x.x)  *(y.y - x.y);
		if (jy < m_d && jy > m_u) a[an++] = CPoint(m_r, jy);
	}
	if (c[0][3] != c[1][3])//与左边有交
	{
		int jy = x.y + (1.0*m_l - x.x) / (y.x - x.x)  *(y.y - x.y);
		if (jy < m_d && jy > m_u) a[an++] = CPoint(m_l, jy);
	}
	if (an == 1){
		if (cnum[0] == 0)a[an++] = x;
		else a[an++] = y;
	}
	pDC->SelectObject(&pen2);
	pDC->MoveTo(a[0]);
	pDC->LineTo(a[1]);
}

void CttView::GetC(int c[],int &cnum, const CPoint p){
	int x = p.x, y = p.y;
	c[0] = 0;
	c[1] = 0;
	c[2] = 0;
	c[3] = 0;
	if (y > m_d) c[0] = 1;
	if (y < m_u) c[1] = 1;
	if (x > m_r) c[2] = 1;
	if (x < m_l) c[3] = 1;
	cnum = 0;
	for (int i = 0; i < 4; i++){
		cnum <<= 1;
		cnum |= c[i];
	}
}

void CttView::OnAdt()
{
	m_graphtype = 12;
}

void CttView::ADTFill(const COLORREF color){
	if (m_point.size() <= 2)return;
	CDC* pDC = GetWindowDC();
	CPen pen1(0, 0, color);
	pDC->SelectObject(&pen1);
	int start, end, msz=m_point.size();
	start = 10000;
	end = 0;
	for (int i = 0; i < msz; i++){
		start = min(start, m_point[i].y);
		end = max(end, m_point[i].y);
	}
	vector<EdgeTable> net(end+1);
	net.assign(end + 1, EdgeTable());
	Edge te;
	int miny;
	for (int i = 0; i < msz-1; i++){
		te = Edge(m_point[i], m_point[i + 1], miny);
		net[miny].Add(te);
	}
	te = Edge(m_point[msz-1], m_point[0], miny);
	net[miny].Add(te);
	
	EdgeTable adt = EdgeTable(start);
	for (int i = start; i <= end; i++){
		for (int j = 0; j < net[i].e.size(); j++)
			adt.Add(net[i].e[j]);
		for (int j = 1; j < adt.e.size(); j += 2){
			pDC->MoveTo((int)adt.e[j-1].x0, i);
			pDC->LineTo((int)adt.e[j].x0, i);
		}
		adt.Update();
	}
}

void CttView::OnGame()
{
	if (!m_gameON){
		if (m_animeON){
			KillTimer(1);
			m_animeON = 0;
		}
		AfxMessageBox(_T("《最后的蓝球》\n你扮演世界上最后一个蓝球，要尽力生存下去。\n敌人是红黑球，碰到你你就死了。\n你可以用鼠标左键发射飞弹攻击敌人。\n你也可以使用按键W/S/A/D移动。\n敌人会越来越多，尽力活下去吧！"));
		m_x = 0;
		m_y = 0;
		CRect rect;
		GetClientRect(&rect);
		m_player_x = rect.Width() / 2;
		m_player_y = rect.Height() / 2;
		m_cls = 1;
		m_enemy.clear();
		m_wait = 200;
		m_time = 0;
		m_bullet.clear();
		SetTimer(2, 0, NULL);
	}
	else KillTimer(2);
	m_gameON ^= 1;
}


void CttView::OnAnime()
{
	if (!m_animeON)
		SetTimer(1, 0, NULL);
	else KillTimer(1);
	m_animeON ^= 1;
	m_cls = 0;
	// TODO: Add your command handler code here
}


void CttView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1){

		CRect rect;
		GetClientRect(&rect);

		m_x = m_x + m_stepX;
		m_y = m_y + m_stepY;
		int dx = ((m_stepX >= 0) << 1) - 1;
		int dy = ((m_stepY > 0) << 1) - 1;
		m_stepX %= 30;
		m_stepY %= 30;
		m_stepX += dx;
		m_stepY += dy;

		if (m_x > rect.Width() - 5){
			m_x = rect.Width() - 5;
			m_stepX = -m_stepX;
		}
		if (m_x < 5){
			m_x = 5;
			m_stepX = -m_stepX;
		}
		if (m_y > rect.Height() - 5){
			m_y = rect.Height() - 5;
			m_stepY = -m_stepY;
		}
		if (m_y < 5){
			m_y = 5;
			m_stepY = -m_stepY;
		}
		Invalidate(FALSE);
	}
	if (nIDEvent == 2){
		m_time--;
		CRect rect;
		GetClientRect(&rect);
		int rw = rect.Width();
		int rh = rect.Width();
		if (m_time <= 0){
			m_time = m_wait;
			m_wait *=0.9;
			m_wait--;
			m_wait = max(20, m_wait);
			CPoint t;
			int ran = rand();
			double sita = ((double)ran) / 10000;
			double dis = rect.Width() + rect.Height();
			t.x = m_player_x + dis * cos(sita);
			t.y = m_player_y + dis * sin(sita);
			t.x = max(0, t.x);
			t.y = max(0, t.y);
			t.x = min(rect.Width(), t.x);
			t.y = min(rect.Height(), t.y);
			m_enemy.push_back(t);
		}
		int speed = 6;
		if (GetKeyState('A') < 0 && m_player_x>0){
			m_player_x -= speed;
		}
		if (GetKeyState('D') < 0 && m_player_x<rw){
			m_player_x += speed;
		}
		if (GetKeyState('W') < 0 && m_player_y>0){
			m_player_y -= speed;
		}
		if (GetKeyState('S') < 0 && m_player_y<rh){
			m_player_y += speed;
		}

		//Bullet
		for (vector<pair<CPoint, CPoint> >::iterator it = m_bullet.begin(); it != m_bullet.end();){
			if (it->first.x < 0 || it->first.x >rw || it->first.y<0 || it->first.y>rh){
				it = m_bullet.erase(it);
				continue;
			}
			bool del = 0;
			for (vector<CPoint>::iterator it2 = m_enemy.begin(); it2 != m_enemy.end();){
				int dx = it->first.x - it2->x;
				int dy = it->first.y - it2->y;
				int dis2 = dx*dx + dy*dy;
				if (dis2 <= 200){
					it2 = m_enemy.erase(it2);
					it = m_bullet.erase(it);
					del = 1;
					break;
				}
				else it2++;
			}
			if (del)continue;
			int sx = it->second.x - it->first.x;
			int sy = it->second.y - it->first.y;
			double ss2 = sqrt(sx*sx + sy*sy);
			double speed = 6;
			if (ss2 == 0)continue;
			int speedx = sx / (ss2 / speed);
			int speedy = sy / (ss2 / speed);
			it->first.x += speedx;
			it->first.y += speedy;
			it++;
		}

		//enemy
		int cnt = m_enemy.size();
		for (int i = 0; i < cnt; i++){
			int dx = m_enemy[i].x - m_player_x;
			int dy = m_enemy[i].y - m_player_y;
			int dis2 = dx*dx + dy*dy;
			if (dis2 <= 300){
				if (m_gameON == 0)return;
				KillTimer(2);
				m_gameON = 0;
				AfxMessageBox(_T("你被击中了，游戏结束！"));
				return;
			}
			int sx = m_player_x - m_enemy[i].x;
			int sy = m_player_y - m_enemy[i].y;
			double ss2 = sqrt(sx*sx + sy*sy);
			double speed = 3;
			if (ss2 == 0)continue;
			int speedx = sx / (ss2 / speed);
			int speedy = sy / (ss2 / speed);
			m_enemy[i].x += speedx;
			m_enemy[i].y += speedy;
		}
		Invalidate(FALSE);
	}
	CView::OnTimer(nIDEvent);
}

void CttView::MakeBullet(CPoint start, CPoint aim){
	int sx = aim.x - start.x;
	int sy = aim.y - start.y;
	double ss = sqrt(sx*sx + sy*sy);
	double dis = 2000;
	if (ss == 0)return;
	int qx = sx / ss*dis;
	int qy = sy / ss*dis;
	CPoint aim2(start.x + qx, start.y + qy);
	pair<CPoint, CPoint> t = make_pair(start, aim2);
	m_bullet.push_back(t);
}