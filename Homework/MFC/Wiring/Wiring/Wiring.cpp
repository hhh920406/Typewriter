#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Wiring.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "WiringDoc.h"
#include "WiringView.h"
#include "TimeDialog.h"
#include "OpenFileDialog.h"
#include "WiringSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CWiringApp, CWinApp)
    ON_COMMAND(ID_APP_ABOUT, &CWiringApp::OnAppAbout)
    ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
    ON_COMMAND(ID_EDIT_SETINTERVAL, &CWiringApp::OnEditSetinterval)
    ON_COMMAND(ID_FILE_OPEN32773, &CWiringApp::OnFileOpen)
END_MESSAGE_MAP()

CWiringApp::CWiringApp()
{
    m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
    System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif
    SetAppID(_T("Wiring.AppID.NoVersion"));
}

CWiringApp theApp;

BOOL CWiringApp::InitInstance()
{
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinApp::InitInstance();

    if (!AfxOleInit())
    {
        AfxMessageBox(IDP_OLE_INIT_FAILED);
        return FALSE;
    }

    AfxEnableControlContainer();

    EnableTaskbarInteraction(FALSE);

    SetRegistryKey(_T("Local AppWizard-Generated Applications"));
    LoadStdProfileSettings(4);

    CMultiDocTemplate* pDocTemplate;
    pDocTemplate = new CMultiDocTemplate(IDR_WiringTYPE,
        RUNTIME_CLASS(CWiringDoc),
        RUNTIME_CLASS(CChildFrame),
        RUNTIME_CLASS(CWiringView));
    if (!pDocTemplate)
        return FALSE;
    AddDocTemplate(pDocTemplate);

    CMainFrame* pMainFrame = new CMainFrame;
    if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
    {
        delete pMainFrame;
        return FALSE;
    }
    m_pMainWnd = pMainFrame;

    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    if (!ProcessShellCommand(cmdInfo))
        return FALSE;
    pMainFrame->ShowWindow(m_nCmdShow);
    pMainFrame->UpdateWindow();

    return TRUE;
}

int CWiringApp::ExitInstance()
{
    AfxOleTerm(FALSE);
    return CWinApp::ExitInstance();
}

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX); 

protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

void CWiringApp::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

void CWiringApp::OnEditSetinterval()
{
    TimeDialog dialog;
    dialog.DoModal();
}

/**
* 从数据库中打开文件。
* @author ZHG <CyberZHG@gmail.com>
*/
void CWiringApp::OnFileOpen()
{
    OpenFileDialog dialog;
    if (dialog.DoModal() == IDOK)
    {
        int chipID = dialog.selectedID();
        if (chipID != -1)
        {
            SwitchBox switchBox;
            DataControl::load(switchBox, chipID);
            this->OnFileNew(); 
            CWiringDoc *document = (CWiringDoc*)((CMainFrame*)AfxGetMainWnd())->MDIGetActive()->GetActiveView()->GetDocument();
            if (document != NULL)
            {
                document->setSwitchBox(switchBox);
                document->SetTitle(switchBox.name());
            }
        }
    }
}