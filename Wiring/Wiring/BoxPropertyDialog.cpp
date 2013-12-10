#include "stdafx.h"
#include "BoxPropertyDialog.h"

BEGIN_MESSAGE_MAP(BoxPropertyDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &BoxPropertyDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &BoxPropertyDialog::OnBnClickedCancel)
END_MESSAGE_MAP()

BoxPropertyDialog::BoxPropertyDialog() : CDialogEx(BoxPropertyDialog::IDD)
{
	AfxInitRichEdit2();
	this->_switchBox = 0L;
}


BoxPropertyDialog::~BoxPropertyDialog()
{
}

/**
 * 提供一个要变更的布线盒的实例。
 * @param switchBox 已经初始化的布线盒。
 */
void BoxPropertyDialog::setSwitchBox(SwitchBox *switchBox)
{
	this->_switchBox = switchBox;
}

/**
 * 设置布线盒的参数，根据引脚数目自动分配位置。
 */
void BoxPropertyDialog::OnBnClickedOk()
{
	CStringW title;
	this->GetDlgItem(IDC_EDIT_TITLE)->GetWindowTextW(title);
	this->_switchBox->setTitle(title);
	CString width, height;
	this->GetDlgItem(IDC_RICHEDIT2_WIDTH)->GetWindowText(width);
	this->GetDlgItem(IDC_RICHEDIT2_HEIGHT)->GetWindowText(height);
	this->_switchBox->setSize(_tstof(width), _tstof(height));
	CString pinNum;
	this->GetDlgItem(IDC_RICHEDIT2_PINNUM)->GetWindowText(pinNum);
	this->_switchBox->setPinNum(_tstoi(pinNum));
	CDialogEx::OnOK();
}

/**
 * 放弃新建。
 */
void BoxPropertyDialog::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}
