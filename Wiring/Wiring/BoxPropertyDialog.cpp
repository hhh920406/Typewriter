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
 * �ṩһ��Ҫ����Ĳ��ߺе�ʵ����
 * @param switchBox �Ѿ���ʼ���Ĳ��ߺС�
 */
void BoxPropertyDialog::setSwitchBox(SwitchBox *switchBox)
{
	this->_switchBox = switchBox;
}

/**
 * ���ò��ߺеĲ���������������Ŀ�Զ�����λ�á�
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
 * �����½���
 */
void BoxPropertyDialog::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}
