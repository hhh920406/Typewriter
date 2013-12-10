#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "Wiring.h"
#endif

#include "WiringDoc.h"
#include "BoxPropertyDialog.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CWiringDoc, CDocument)

BEGIN_MESSAGE_MAP(CWiringDoc, CDocument)
END_MESSAGE_MAP()

CWiringDoc::CWiringDoc()
{
	this->_initialized = false;
}

CWiringDoc::~CWiringDoc()
{
}

/**
 * ÐòÁÐ»¯¡£
 * @param archive ¹éµµ¡£
 */
void CWiringDoc::Serialize(CArchive& archive)
{
	if (archive.IsStoring())
	{
		if (this->_initialized)
		{
			this->_switchBox.serialize(archive);
		}
	}
	else
	{
		this->_initialized = true;
		this->_switchBox.serialize(archive);
		this->SetTitle(this->_switchBox.title());
	}
}

void CWiringDoc::setInitialized(bool value)
{
	this->_initialized = value;
}

bool CWiringDoc::initialized() const
{
	return this->_initialized;
}

SwitchBox& CWiringDoc::switchBox()
{
	return this->_switchBox;
}

void CWiringDoc::initSwitchBox()
{
	BoxPropertyDialog dialog;
	dialog.setSwitchBox(&this->_switchBox);
	if (dialog.DoModal() == IDOK)
	{
		this->setInitialized(true);
		this->SetTitle(this->switchBox().title());
	}
}

#ifdef _DEBUG
void CWiringDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWiringDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
