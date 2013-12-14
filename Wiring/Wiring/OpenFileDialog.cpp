#include "stdafx.h"
#include "OpenFileDialog.h"
#include "WiringSet.h"

BEGIN_MESSAGE_MAP(OpenFileDialog, CDialogEx)
    ON_BN_CLICKED(IDOK, &OpenFileDialog::OnBnClickedOk)
END_MESSAGE_MAP()

OpenFileDialog::OpenFileDialog() : CDialogEx(OpenFileDialog::IDD)
{
    this->_selectedID = -1;
}


OpenFileDialog::~OpenFileDialog()
{
}


BOOL OpenFileDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    CListCtrl *listCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_FILE);
    listCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT);
    listCtrl->InsertColumn(1, _T("ID"), LVCFMT_LEFT, 100);
    listCtrl->InsertColumn(2, _T("Name"), LVCFMT_LEFT, 300);
    DataChip *dChip = DataControl::list();
    if (dChip != NULL)
    {
        dChip->MoveFirst();
        while (!dChip->IsEOF())
        {
            this->_chipID.push_back(dChip->m_D_ChipID);
            CString id;
            id.Format(L"%d", dChip->m_D_ChipID);
            int num = listCtrl->GetItemCount();
            listCtrl->InsertItem(num, id);
            listCtrl->SetItemText(num, 1, dChip->m_D_Name);
            dChip->MoveNext();
        }
        dChip->Close();
    }
    return TRUE;
}

void OpenFileDialog::OnBnClickedOk()
{
    CListCtrl *listCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_FILE);
    POSITION pos = listCtrl->GetFirstSelectedItemPosition();
    if (pos != NULL)
    {
        int index = listCtrl->GetNextSelectedItem(pos);
        this->_selectedID = this->_chipID[index];
    }
    CDialogEx::OnOK();
}

int OpenFileDialog::selectedID() const
{
    return this->_selectedID;
}