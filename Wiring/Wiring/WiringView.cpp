
// WiringView.cpp : implementation of the CWiringView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Wiring.h"
#endif

#include "WiringDoc.h"
#include "WiringView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWiringView

IMPLEMENT_DYNCREATE(CWiringView, CView)

BEGIN_MESSAGE_MAP(CWiringView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CWiringView construction/destruction

CWiringView::CWiringView()
{
	// TODO: add construction code here

}

CWiringView::~CWiringView()
{
}

BOOL CWiringView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CWiringView drawing

void CWiringView::OnDraw(CDC* /*pDC*/)
{
	CWiringDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CWiringView printing

BOOL CWiringView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWiringView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWiringView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CWiringView diagnostics

#ifdef _DEBUG
void CWiringView::AssertValid() const
{
	CView::AssertValid();
}

void CWiringView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWiringDoc* CWiringView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWiringDoc)));
	return (CWiringDoc*)m_pDocument;
}
#endif //_DEBUG


// CWiringView message handlers
