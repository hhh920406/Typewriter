#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "Wiring.h"
#endif

#include <cmath>
#include "WiringDoc.h"
#include "WiringView.h"
const double PI = acos(-1.0);

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
	ON_WM_ERASEBKGND()
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
	CDC memDC;
	CBitmap memBitmap;
	CRect windowRect;
	this->GetWindowRect(windowRect);
	memDC.CreateCompatibleDC(NULL);
	memBitmap.CreateCompatibleBitmap(pDC, windowRect.Width(), windowRect.Height());
	CBitmap *pOldBit = memDC.SelectObject(&memBitmap);
	memDC.FillSolidRect(0, 0, windowRect.Width(), windowRect.Height(), RGB(255, 255, 255));

	CFont font;
	font.CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_SWISS, _T("Console"));
	memDC.SelectObject(&font);
	SwitchBox& switchBox = this->GetDocument()->switchBox();
	memDC.Rectangle(switchBox.getOuterBorder());
	memDC.Rectangle(switchBox.getInnerBorder());
	for (unsigned int i = 0; i < switchBox.pin().size(); ++i)
	{
		memDC.Rectangle(switchBox.getPinRect(i));
		CString num;
		num.Format(L"%d", switchBox.pin()[i].id());
		memDC.SetBkMode(TRANSPARENT);
		memDC.DrawText(num, switchBox.getPinTextRect(i), DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		memDC.Ellipse(switchBox.getPortRect(i));
	}
	for (unsigned int i = 0; i < switchBox.wire().size(); ++i)
	{
		if (switchBox.wire()[i].count() > 0)
		{
			memDC.MoveTo(switchBox.x() + switchBox.wire()[i].x(0), switchBox.y() + switchBox.wire()[i].y(0));
		}
		for (int j = 1; j < switchBox.wire()[i].count(); ++j)
		{
			memDC.LineTo(switchBox.x() + switchBox.wire()[i].x(j), switchBox.y() + switchBox.wire()[i].y(j));
		}
	}
	if (this->_status == STATUS_WIRE_CONNECTING)
	{
		memDC.MoveTo(this->_lastClickPos);
		memDC.LineTo(this->_lastMousePos);
	}

	pDC->BitBlt(0, 0, windowRect.Width(), windowRect.Height(), &memDC, 0, 0, SRCCOPY);
	memBitmap.DeleteObject();
	memDC.DeleteDC();
}

BOOL CWiringView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
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
	case STATUS_PIN_MOVING:
		this->mouseMovePin(point);
		break;
	case STATUS_WIRE_CONNECTING:
		this->mouseMoveConnect(point);
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
}

/**
 * 对鼠标左键抬起事件的处理。
 */
void CWiringView::OnLButtonUp(UINT nFlags, CPoint point)
{
	switch (this->_status)
	{
	case STATUS_PIN_MOVING:
		this->mouseLeftUpPin(point);
		break;
	case STATUS_WIRE_CONNECTING:
		this->mouseLeftUpConnect(point);
		break;
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
	SwitchBox& switchBox = this->GetDocument()->switchBox();
	int pinIndex = switchBox.pinHoverIndex(point);
	if (pinIndex != -1)
	{
		this->_status = STATUS_PIN_MOVING;
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
		this->_lastIndex = pinIndex;
		return;
	}
	int portIndex = switchBox.portHoverIndex(point);
	if (portIndex != -1)
	{
		this->_status = STATUS_WIRE_CONNECTING;
		this->_lastIndex = portIndex;
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
	SwitchBox& switchBox = this->GetDocument()->switchBox();
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
 * 改变引脚的位置。
 * @param point 鼠标的相对位置。
 */
void CWiringView::mouseMovePin(CPoint point)
{
	SwitchBox& switchBox = this->GetDocument()->switchBox();
	double cx = (switchBox.left() + switchBox.right()) * 0.5;
	double cy = (switchBox.top() + switchBox.bottom()) * 0.5;
	double hw = switchBox.width() * 0.5;
	double hh = switchBox.height() * 0.5;
	double angle = atan2(cy - point.y, point.x - cx);
	double divideAngle = atan2(hh, hw);
	if (angle < 0.0)
	{
		angle += PI * 2.0;
	}
	if (angle < divideAngle)
	{
		switchBox.pin()[this->_lastIndex].setOrientation(Pin::ORI_RIGHT);
		switchBox.pin()[this->_lastIndex].setShift(hh - hw * tan(angle));
	}
	else if (angle < PI / 2)
	{
		switchBox.pin()[this->_lastIndex].setOrientation(Pin::ORI_TOP);
		switchBox.pin()[this->_lastIndex].setShift(hw + hh * tan(PI / 2 - angle));
	}
	else if (angle < PI - divideAngle)
	{
		switchBox.pin()[this->_lastIndex].setOrientation(Pin::ORI_TOP);
		switchBox.pin()[this->_lastIndex].setShift(hw - hh * tan(angle - PI / 2));
	}
	else if (angle < PI)
	{
		switchBox.pin()[this->_lastIndex].setOrientation(Pin::ORI_LEFT);
		switchBox.pin()[this->_lastIndex].setShift(hh - hw * tan(PI - angle));
	}
	else if (angle < PI + divideAngle)
	{
		switchBox.pin()[this->_lastIndex].setOrientation(Pin::ORI_LEFT);
		switchBox.pin()[this->_lastIndex].setShift(hh + hw * tan(angle - PI));
	}
	else if (angle < PI * 3 / 2)
	{
		switchBox.pin()[this->_lastIndex].setOrientation(Pin::ORI_BOTTOM);
		switchBox.pin()[this->_lastIndex].setShift(hw - hh * tan(PI * 3 / 2 - angle));
	}
	else if (angle < PI * 2 - divideAngle)
	{
		switchBox.pin()[this->_lastIndex].setOrientation(Pin::ORI_BOTTOM);
		switchBox.pin()[this->_lastIndex].setShift(hw + hh * tan(angle - PI * 3 / 2));
	}
	else
	{
		switchBox.pin()[this->_lastIndex].setOrientation(Pin::ORI_RIGHT);
		switchBox.pin()[this->_lastIndex].setShift(hh + hw * tan(PI * 2 - angle));
	}
	for (unsigned i = 0; i < switchBox.wire().size(); ++i)
	{
		if (switchBox.wire()[i].u() == this->_lastIndex)
		{
			switchBox.wire()[i].set(0,
				switchBox.getPortCenter(this->_lastIndex).x - switchBox.x(),
				switchBox.getPortCenter(this->_lastIndex).y - switchBox.y());
		}
		else if (switchBox.wire()[i].v() == this->_lastIndex)
		{
			switchBox.wire()[i].set(switchBox.wire()[i].count() - 1,
				switchBox.getPortCenter(this->_lastIndex).x - switchBox.x(),
				switchBox.getPortCenter(this->_lastIndex).y - switchBox.y());
		}
	}
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
}

/**
 * 进行基本的连线。
 * @param point 鼠标的相对位置。
 */
void CWiringView::mouseMoveConnect(CPoint point)
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
}

/**
 * 改变布线盒大小。
 * @param point 鼠标的相对位置。
 */
void CWiringView::mouseMoveResize(CPoint point)
{
	SwitchBox& switchBox = this->GetDocument()->switchBox();
	switch (this->_status)
	{
	case STATUS_BORDER_RESIZING_LEFT:
		switchBox.setPosition(switchBox.x() + point.x - this->_lastMousePos.x, switchBox.y());
		switchBox.setSize(switchBox.width() - point.x + this->_lastMousePos.x, switchBox.height());
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
		break;
	case STATUS_BORDER_RESIZING_RIGHT:
		switchBox.setSize(switchBox.width() + point.x - this->_lastMousePos.x, switchBox.height());
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
		break;
	case STATUS_BORDER_RESIZING_TOP:
		switchBox.setPosition(switchBox.x(), switchBox.y() + point.y - this->_lastMousePos.y);
		switchBox.setSize(switchBox.width(), switchBox.height() - point.y + this->_lastMousePos.y);
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));
		break;
	case STATUS_BORDER_RESIZING_BOTTOM:
		switchBox.setSize(switchBox.width(), switchBox.height() + point.y - this->_lastMousePos.y);
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));
		break;
	}
}

/**
 * 移动布线盒。
 * @param point 鼠标的相对位置。
 */
void CWiringView::mouseMoveMoving(CPoint point)
{
	SwitchBox& switchBox = this->GetDocument()->switchBox();
	switchBox.setPosition(switchBox.x() + point.x - this->_lastMousePos.x, switchBox.y() + point.y - this->_lastMousePos.y);
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
}

/**
 * 移动引脚位置完成，恢复常态。
 */
void CWiringView::mouseLeftUpPin(CPoint)
{
	this->restoreIdle();
}

/**
 * 连线完成，恢复常态。
 */
void CWiringView::mouseLeftUpConnect(CPoint point)
{
	SwitchBox& switchBox = this->GetDocument()->switchBox();
	int index = switchBox.portHoverIndex(point);
	if (index != -1 && index != this->_lastIndex)
	{
		switchBox.addWire(this->_lastIndex, index);
	}
	this->restoreIdle();
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
