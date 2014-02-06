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

protected:
    DECLARE_MESSAGE_MAP()
};
