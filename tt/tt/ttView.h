
// ttView.h : CttView 类的接口
//

#pragma once
#pragma comment(linker, "/STACK:102400000,102400000")
#include<vector>
using namespace std;

class Edge{
public:
	Edge(){
		x0 = dx = ymax = 0;
	}
	Edge(int _x0, int _dx, int _ymax){
		x0 = _x0;
		dx = _dx;
		ymax = _ymax;
	}
	Edge(CPoint st, CPoint ed, int &miny){
		if (st.y > ed.y)swap(st, ed);
		x0 = (double)st.x;
		dx = ((double)(ed.x - st.x)) / (ed.y - st.y);
		ymax = ed.y;
		miny = st.y;
	}
	double x0, dx;
	int ymax;
};

class EdgeTable{
public:
	EdgeTable(){
		e.clear();
		now = 0;
	}
	EdgeTable(int _now){
		e.clear();
		now = _now;
	}
	void Add(Edge ed){
		int sz = e.size();
		vector<Edge>::iterator it;
		for (it = e.begin(); it != e.end(); it++){
			if (it->x0 > ed.x0 || (fabs(it->x0 - ed.x0)<=0.01 && it->dx > ed.dx)) break;
		}
		e.insert(it, ed);
	}
	void Update(){
		now++;
		vector<Edge>::iterator it;
		for (it = e.begin(); it != e.end();){
			it->x0 += it->dx;
			if (it->ymax <= now){
				it = e.erase(it);
			}
			else it++;
		}
	}
	vector<Edge> e;
	int now;
};

class CttView : public CView
{
protected: // 仅从序列化创建
	CttView();
	DECLARE_DYNCREATE(CttView)

// 特性
public:
	CttDoc* GetDocument() const;

	vector<CPoint> m_point;
	vector<CPoint> m_last_point;
	int m_graphtype;
	int m_cls;

	int m_l, m_r, m_u, m_d;

	int m_x, m_y;
	int m_stepX, m_stepY;
	int m_animeON;

	CPoint go[4];

	int m_gameON;
	int m_player_x;
	int m_player_y;
	vector<CPoint> m_enemy;
	vector<pair<CPoint,CPoint> > m_bullet;
	int m_time;
	int m_wait;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CttView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	void drawGraph(void);
	void drawLine(CPoint st, CPoint ed);
	void LineLine(CPoint st, CPoint ed);
	void MidLine(CPoint st, CPoint ed);
	void BsmLine(CPoint st, CPoint ed);
	void SeedFill(const int &x, const int &y,const COLORREF &color , CDC* pDC);
	void SeedLine(const int &x,const int &y,const COLORREF &color,const COLORREF &b_color , CDC* pDC);
	void SeedLineSearch(const int &l, const int &r, const int &y,const COLORREF &color,const COLORREF &b_color , CDC* pDC, vector<CPoint> &v);
	void DuiChengX(const int &x, const int &y);
	void DuiChengY(const int &x, const int &y);
	void DuiChengXY(const int &x, const int &y);
	void GraphMove(const int &x, const int &y);
	void XuanZhuan(const int &x, const int &y);
	void SuoFang(const int &x, const int &y);
	void PointCai(const int &x, const int &y);
	void LineCai(const CPoint &x, const CPoint &y);
	void GetC(int c[], int &cnum, const CPoint p);
	void ADTFill(const COLORREF color);
	void MakeBullet(CPoint start, CPoint aim);
	afx_msg void OnMid();
	afx_msg void OnBsm();
	afx_msg void OnLine();
	afx_msg void OnSeed();
	afx_msg void OnSeedline();
	afx_msg void OnAnime();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnXdc();
	afx_msg void OnYdc();
	afx_msg void OnXydc();
	afx_msg void OnMove();
	afx_msg void OnXuanzhuan();
	afx_msg void OnSuofang();
	afx_msg void OnClearscreen();
	afx_msg void OnCohen();
	afx_msg void OnAdt();
	afx_msg void OnGame();
};

#ifndef _DEBUG  // ttView.cpp 中的调试版本
inline CttDoc* CttView::GetDocument() const
   { return reinterpret_cast<CttDoc*>(m_pDocument); }
#endif

