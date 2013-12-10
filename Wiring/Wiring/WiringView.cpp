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
	CFont font;
	font.CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_SWISS, _T("Console"));
	pDC->SelectObject(&font);
	SwitchBox switchBox = this->GetDocument()->switchBox();
	int x = switchBox.x();
	int y = switchBox.y();
	int width = switchBox.width();
	int height = switchBox.height();
	const int PADDING = 3;
	pDC->Rectangle(x, y, x + width, y + height);
	pDC->Rectangle(x + PADDING, y + PADDING, x + width - PADDING, y + height - PADDING);
	const int PIN_SIZE = 20;
	for (unsigned int i = 0; i < switchBox.pin().size(); ++i)
	{
		int cx, cy;
		int px, py;
		switch (switchBox.pin()[i].orientation())
		{
		case Pin::ORI_TOP:
			cx = x + switchBox.pin()[i].shift();
			cy = y - (PIN_SIZE >> 1) + 1;
			px = cx;
			py = y + (PADDING << 1);
			break;
		case Pin::ORI_BOTTOM:
			cx = x + switchBox.pin()[i].shift();
			cy = y + height + (PIN_SIZE >> 1) - 1;
			px = cx;
			py = y + height - (PADDING << 1);
			break;
		case Pin::ORI_LEFT:
			cx = x - (PIN_SIZE >> 1) + 1;
			cy = y + switchBox.pin()[i].shift();
			px = x + (PADDING << 1);
			py = cy;
			break;
		case Pin::ORI_RIGHT:
			cx = x + width + (PIN_SIZE >> 1) - 1;
			cy = y + switchBox.pin()[i].shift();
			px = x + width - (PADDING << 1);
			py = cy;
			break;
		}
		CRect pinArea(cx - (PIN_SIZE >> 1), cy - (PIN_SIZE >> 1), cx + (PIN_SIZE >> 1), cy + (PIN_SIZE >> 1));
		pDC->Rectangle(pinArea);
		CString num;
		num.Format(L"%d", switchBox.pin()[i].id());
		CRect textArea(cx - 100, cy - 100, cx + 100, cy + 100);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(num, textArea, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		pDC->Ellipse(px - PADDING, py - PADDING, px + PADDING, py + PADDING);
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

void CWiringView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CView::OnLButtonUp(nFlags, point);
}


void CWiringView::OnMouseMove(UINT nFlags, CPoint point)
{
	CView::OnMouseMove(nFlags, point);
}


void CWiringView::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
}
