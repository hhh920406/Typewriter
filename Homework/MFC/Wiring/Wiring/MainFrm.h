#pragma once

class CMainFrame : public CMDIFrameWnd
{
    DECLARE_DYNAMIC(CMainFrame)
public:
    CMainFrame();
    virtual ~CMainFrame();

    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected: 
    CToolBar          m_wndToolBar;
    CReBar            m_wndReBar;
    CDialogBar        m_wndDlgBar;
    CStatusBar        m_wndStatusBar;

protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnFileSave();
};


