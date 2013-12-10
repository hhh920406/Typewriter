
// WiringView.h : interface of the CWiringView class
//

#pragma once
#include "SwitchBox.h"

class CWiringView : public CView
{
protected: // create from serialization only
	CWiringView();
	DECLARE_DYNCREATE(CWiringView)

// Attributes
public:
	CWiringDoc* GetDocument() const;

private:
	SwitchBox _switchBox;
	bool _initialized;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CWiringView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};

#ifndef _DEBUG  // debug version in WiringView.cpp
inline CWiringDoc* CWiringView::GetDocument() const
   { return reinterpret_cast<CWiringDoc*>(m_pDocument); }
#endif

