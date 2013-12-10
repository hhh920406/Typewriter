/**
 * 用于初始化开关布线盒的参数。
 * @author ZHG <CyberZHG@gmail.com>
 */
#pragma once
#include "Resource.h"
#include "SwitchBox.h"

class BoxPropertyDialog : public CDialogEx
{
public:
	BoxPropertyDialog();
	virtual ~BoxPropertyDialog();
	enum { IDD = IDD_BOXPROPERTY };
	void setSwitchBox(SwitchBox *switchBox);

private:
	SwitchBox *_switchBox;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};