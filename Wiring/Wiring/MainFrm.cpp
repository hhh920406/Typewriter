#include "stdafx.h"
#include "Wiring.h"
#include "WiringDoc.h"
#include "WiringSet.h"
#include "NameDialog.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_SAVE32772, &CMainFrame::OnFileSave)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,         
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

/**
* 保存文件到数据库中。
* @author ZHG <CyberZHG@gmail.com>
*/
void CMainFrame::OnFileSave()
{
	CMDIChildWnd *wnd = MDIGetActive();
	if (wnd != NULL)
	{
		CWiringDoc *document = (CWiringDoc*)wnd->GetActiveView()->GetDocument();
		if (document->switchBox().name().IsEmpty())
		{
			NameDialog dialog;
			if (dialog.DoModal() == IDOK)
			{
				CStringW name = dialog.getName();
				document->switchBox().setName(name);
			}
			else
			{
				return;
			}
		}
		CStringW name = document->switchBox().name();
		int width = document->switchBox().width();
		int height = document->switchBox().height();
		DataChip set;
		set.addNewChip(name, width, height);
	}
}
