/**
 * ²¼ÏßºÐ¡£
 * @author ZHG <CyberZHG@gmail.com>
 */
#pragma once

#ifndef __AFXWIN_H__
    #error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"

class CWiringApp : public CWinApp
{
public:
    CWiringApp();

    virtual BOOL InitInstance();
    virtual int ExitInstance();

    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
    afx_msg void OnEditSetinterval();
    afx_msg void OnFileOpen();
};

extern CWiringApp theApp;
