/**
 * 布线盒的文档。
 * @author ZHG <CyberZHG@gmail.com>
 */
#pragma once
#include "SwitchBox.h"

class CWiringDoc : public CDocument
{
public:
	CWiringDoc();
	virtual ~CWiringDoc();
	DECLARE_DYNCREATE(CWiringDoc)
	void setSwitchBox(SwitchBox &box);
	SwitchBox& switchBox();

private:
	SwitchBox _switchBox;

protected:
	DECLARE_MESSAGE_MAP()
};
