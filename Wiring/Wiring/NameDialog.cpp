#include "stdafx.h"
#include "NameDialog.h"

BEGIN_MESSAGE_MAP(NameDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &NameDialog::OnBnClickedOk)
END_MESSAGE_MAP()

NameDialog::NameDialog() : CDialogEx(NameDialog::IDD)
{
}


NameDialog::~NameDialog()
{
}

CStringW NameDialog::getName() const
{
	return this->_name;
}

void NameDialog::OnBnClickedOk()
{
	GetDlgItem(IDC_EDIT_NAME)->GetWindowTextW(this->_name);
	CDialogEx::OnOK();
}
