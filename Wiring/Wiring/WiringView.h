/**
* ���ߺе���ͼ��
* @author ZHG <CyberZHG@gmail.com>
*/
#pragma once
#include "resource.h"
#include "SwitchBox.h"
#include "SwitchBoxSolver.h"

class CWiringView : public CView
{
protected:
	CWiringView();
	virtual ~CWiringView();
	DECLARE_DYNCREATE(CWiringView)
	CWiringDoc* GetDocument() const;
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	enum Status
	{
		STATUS_IDLE, /** ����״̬�� */
		STATUS_PIN_MOVING, /** �ƶ����š� */
		STATUS_WIRE_CONNECTING, /** ���ߡ� */
		STATUS_BORDER_RESIZING_LEFT, /** �ı䲼�ߺе���߽硣 */
		STATUS_BORDER_RESIZING_RIGHT, /** �ı䲼�ߺе��ұ߽硣 */
		STATUS_BORDER_RESIZING_TOP, /** �ı䲼�ߺе��ϱ߽硣 */
		STATUS_BORDER_RESIZING_BOTTOM, /** �ı䲼�ߺе��±߽硣 */
		STATUS_MOVING, /** �ƶ����ߺС� */
		STATUS_SOLVE_GREEDY /** ̰�����׶Ρ� */
	} _status;
	CPoint _lastMousePos;
	CPoint _lastClickPos;
	int _lastIndex;
	int _lastPos;
	int _tick;
	int _removeIndex;
	SwitchBoxSolver _solver;
	std::vector<Wire> _wire;
	bool _timer;

	void restoreIdle();
	void mouseLeftDownIdle(CPoint point);

	void mouseMoveIdle(CPoint point);
	void mouseMovePin(CPoint point);
	void mouseMoveResize(CPoint point);
	void mouseMoveMoving(CPoint point);

	void mouseLeftUpPin(CPoint point);
	void mouseLeftUpConnect(CPoint point);
	void mouseLeftUpResize(CPoint point);
	void mouseLeftUpMoving(CPoint point);

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG
inline CWiringDoc* CWiringView::GetDocument() const
   { return reinterpret_cast<CWiringDoc*>(m_pDocument); }
#endif

