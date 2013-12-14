#include "stdafx.h"
#include <fstream>
#include "TimeDialog.h"
#include "TimeControl.h"
using namespace std;

BEGIN_MESSAGE_MAP(TimeDialog, CDialogEx)
    ON_BN_CLICKED(IDOK, &TimeDialog::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &TimeDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


TimeDialog::TimeDialog() : CDialogEx(TimeDialog::IDD)
{
}

TimeDialog::~TimeDialog()
{
}

void TimeDialog::OnBnClickedOk()
{
    CSliderCtrl *slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIME);
    TimeControl::saveTime(slider->GetPos());
    CDialogEx::OnOK();
}


void TimeDialog::OnBnClickedCancel()
{
    CDialogEx::OnCancel();
}


BOOL TimeDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    CSliderCtrl *slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIME);
    slider->SetRange(0, 50);
    slider->SetLineSize(5);
    slider->SetTicFreq(5);
    slider->SetPos(TimeControl::getTime());
    return TRUE;
}
