/**
 * ²¼ÏßºÐ×ÓÈÝÆ÷¡£
 * @author ZHG <CyberZHG@gmail.com>
 */
#pragma once

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();
	virtual ~CChildFrame();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};
