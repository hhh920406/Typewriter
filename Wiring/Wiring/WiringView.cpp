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
	this->_status = STATUS_IDLE;
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
	pDC->Rectangle(switchBox.getOuterBorder());
	pDC->Rectangle(switchBox.getInnerBorder());
	for (unsigned int i = 0; i < switchBox.pin().size(); ++i)
	{
		pDC->Rectangle(switchBox.getPinRect(i));
		CString num;
		num.Format(L"%d", switchBox.pin()[i].id());
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(num, switchBox.getPinTextRect(i), DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		pDC->Ellipse(switchBox.getPortRect(i));
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

/**
 * 对鼠标左键按下事件的处理。
 */
void CWiringView::OnLButtonDown(UINT nFlags, CPoint point)
{
	switch (this->_status)
	{
	case STATUS_IDLE:
		this->mouseLeftDownIdle(point);
		break;
	}
	this->_lastMousePos = point;
	this->_lastClickPos = point;
	this->Invalidate();
	CView::OnLButtonDown(nFlags, point);
}

/**
* 对鼠标移动事件的处理。
*/
void CWiringView::OnMouseMove(UINT nFlags, CPoint point)
{
	switch (this->_status)
	{
	case STATUS_IDLE:
		this->mouseMoveIdle(point);
		break;
	case STATUS_BORDER_RESIZING_LEFT:
	case STATUS_BORDER_RESIZING_RIGHT:
	case STATUS_BORDER_RESIZING_TOP:
	case STATUS_BORDER_RESIZING_BOTTOM:
		this->mouseMoveResize(point);
		break;
	case STATUS_MOVING:
		this->mouseMoveMoving(point);
		break;
	}
	this->_lastMousePos = point;
	this->Invalidate();
	CView::OnMouseMove(nFlags, point);
}

/**
 * 对鼠标左键抬起事件的处理。
 */
void CWiringView::OnLButtonUp(UINT nFlags, CPoint point)
{
	switch (this->_status)
	{
	case STATUS_BORDER_RESIZING_LEFT:
	case STATUS_BORDER_RESIZING_RIGHT:
	case STATUS_BORDER_RESIZING_TOP:
	case STATUS_BORDER_RESIZING_BOTTOM:
		this->mouseLeftUpResize(point);
		break;
	case STATUS_MOVING:
		this->mouseLeftUpMoving(point);
		break;
	}
	this->_lastMousePos = point;
	this->_lastClickPos = point;
	this->Invalidate();
	CView::OnLButtonUp(nFlags, point);
}

void CWiringView::restoreIdle()
{
	this->_status = STATUS_IDLE;
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

/**
 * 处于空闲状态时鼠标左键抬起，将会触发其它状态。
 * @param point 鼠标的相对位置。
 */
void CWiringView::mouseLeftDownIdle(CPoint point)
{
	SwitchBox switchBox = this->GetDocument()->switchBox();
	int pinIndex = switchBox.pinHoverIndex(point);
	if (pinIndex != -1)
	{
		this->_status = STATUS_PIN_MOVING;
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
		return;
	}
	int portIndex = switchBox.portHoverIndex(point);
	if (portIndex != -1)
	{
		this->_status = STATUS_WIRE_CONNECTING;
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		return;
	}
	if (switchBox.isOnTopBorder(point))
	{
		this->_status = STATUS_BORDER_RESIZING_TOP;
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));
		return;
	}
	if (switchBox.isOnBottomBorder(point))
	{
		this->_status = STATUS_BORDER_RESIZING_BOTTOM;
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));
		return;
	}
	if (switchBox.isOnLeftBorder(point))
	{
		this->_status = STATUS_BORDER_RESIZING_LEFT;
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
		return;
	}
	if (switchBox.isOnRightBorder(point))
	{
		this->_status = STATUS_BORDER_RESIZING_RIGHT;
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
		return;
	}
	if (switchBox.isOnInner(point))
	{
		this->_status = STATUS_MOVING;
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
		return;
	}
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

/**
 * 处于空闲状态时鼠标移动，根据鼠标区域改变鼠标的图标。
 * @param point 鼠标的相对位置。
 */
void CWiringView::mouseMoveIdle(CPoint point)
{
	SwitchBox switchBox = this->GetDocument()->switchBox();
	int pinIndex = switchBox.pinHoverIndex(point);
	if (pinIndex != -1)
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
		return;
	}
	int portIndex = switchBox.portHoverIndex(point);
	if (portIndex != -1)
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		return;
	}
	if (switchBox.isOnTopBorder(point) || switchBox.isOnBottomBorder(point))
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));
		return;
	}
	if (switchBox.isOnLeftBorder(point) || switchBox.isOnRightBorder(point))
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
		return;
	}
	if (switchBox.isOnInner(point))
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
		return;
	}
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

/**
 * 改变布线盒大小。
 * @param point 鼠标的相对位置。
 */
void CWiringView::mouseMoveResize(CPoint point)
{
	SwitchBox switchBox = this->GetDocument()->switchBox();
	switch (this->_status)
	{
	case STATUS_BORDER_RESIZING_LEFT:
		this->GetDocument()->switchBox().setPosition(switchBox.x() + point.x - this->_lastMousePos.x, switchBox.y());
		this->GetDocument()->switchBox().setSize(switchBox.width() - point.x + this->_lastMousePos.x, switchBox.height());
		break;
	case STATUS_BORDER_RESIZING_RIGHT:
		this->GetDocument()->switchBox().setSize(switchBox.width() + point.x - this->_lastMousePos.x, switchBox.height());
		break;
	case STATUS_BORDER_RESIZING_TOP:
		this->GetDocument()->switchBox().setPosition(switchBox.x(), switchBox.y() + point.y - this->_lastMousePos.y);
		this->GetDocument()->switchBox().setSize(switchBox.width(), switchBox.height() - point.y + this->_lastMousePos.y);
		break;
	case STATUS_BORDER_RESIZING_BOTTOM:
		this->GetDocument()->switchBox().setSize(switchBox.width(), switchBox.height() + point.y - this->_lastMousePos.y);
		break;
	}
}

/**
 * 移动布线盒。
 * @param point 鼠标的相对位置。
 */
void CWiringView::mouseMoveMoving(CPoint point)
{
	SwitchBox switchBox = this->GetDocument()->switchBox();
	this->GetDocument()->switchBox().setPosition(switchBox.x() + point.x - this->_lastMousePos.x, switchBox.y() + point.y - this->_lastMousePos.y);
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
}

/**
 * 改变大小完成，恢复常态。
 */
void CWiringView::mouseLeftUpResize(CPoint)
{
	this->restoreIdle();
}

/**
 * 移动完成，恢复常态。
 */
void CWiringView::mouseLeftUpMoving(CPoint)
{
	this->restoreIdle();
}