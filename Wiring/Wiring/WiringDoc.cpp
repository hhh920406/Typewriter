#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "Wiring.h"
#endif

#include "WiringDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CWiringDoc, CDocument)

BEGIN_MESSAGE_MAP(CWiringDoc, CDocument)
END_MESSAGE_MAP()

CWiringDoc::CWiringDoc()
{
	this->_switchBox.setPosition(100, 100);
	this->_switchBox.setSize(200, 200);
	this->_switchBox.setPinNum(18);
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
	this->_switchBox.serialize(archive);
}

SwitchBox& CWiringDoc::switchBox()
{
	return this->_switchBox;
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
