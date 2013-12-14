#pragma once
#include "afxdialogex.h"
#include "resource.h"

class NameDialog : public CDialogEx
{
public:
    enum { IDD = IDD_SETNAME };

    NameDialog();
    virtual ~NameDialog();
    CStringW getName() const;

private:
    CStringW _name;
public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedOk();
};