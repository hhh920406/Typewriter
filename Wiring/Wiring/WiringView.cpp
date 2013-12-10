#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "Wiring.h"
#endif

#include "WiringDoc.h"
#include "WiringView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CWiringView, CView)

BEGIN_MESSAGE_MAP(CWiringView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

CWiringView::CWiringView()
{
}

CWiringView::~CWiringView()
{
}

BOOL CWiringView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CWiringView::OnDraw(CDC* pDC)
{
	CWiringDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}
	if (this->GetDocument()->initialized())
	{
		CFont font;
		font.CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_SWISS, _T("Console"));
		pDC->SelectObject(&font);
		double shiftX = 50;
		double shiftY = 50;
		SwitchBox switchBox = this->GetDocument()->switchBox();
		double width = switchBox.width();
		double height = switchBox.height();
		pDC->Rectangle(50, 50, (int)(50.0 + width), (int)(50.0 + height));
		for (unsigned int i = 0; i < switchBox.pin().size(); ++i)
		{
			switch (switchBox.pin()[i].orientation())
			{
			case Pin::ORI_TOP:
				
				break;
			case Pin::ORI_BOTTOM:
				break;
			case Pin::ORI_LEFT:
				break;
			case Pin::ORI_RIGHT:
				break;
			}
		}
	}
	else
	{
		CString str("Left click to set properties.");
		CRect rect(50, 50, 1000, 1000);
		CFont font;
		font.CreateFontW(30, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_SWISS, _T("Console"));
		pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(0, 0, 200));
		pDC->DrawText(str, rect, 0);
	}
}

#ifdef _DEBUG
void CWiringView::AssertValid() const
{
	CView::AssertValid();
}

void CWiringView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWiringDoc* CWiringView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWiringDoc)));
	return (CWiringDoc*)m_pDocument;
}
#endif

void CWiringView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CWiringView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CWiringView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CView::OnLButtonDown(nFlags, point);
}

/**
 * 鼠标按下的事件。
 * 当布线盒未初始化时，会弹出对话框设置布线盒基本参数。
 */
void CWiringView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (this->GetDocument()->initialized())
	{
	}
	else
	{
		this->GetDocument()->initSwitchBox();
	}
	this->Invalidate();
	CView::OnLButtonUp(nFlags, point);
}


void CWiringView::OnMouseMove(UINT nFlags, CPoint point)
{
	CView::OnMouseMove(nFlags, point);
}


void CWiringView::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
}
