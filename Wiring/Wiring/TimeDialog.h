/**
 * 用来设置动画每一步的时间。
 * @author ZHG <CyberZHG@gmail.com>
 */
#pragma once
#include "afxdialogex.h"
#include "resource.h"

class TimeDialog : public CDialogEx
{
public:
    enum { IDD = IDD_TIMETICK };

    TimeDialog();
    virtual ~TimeDialog();
    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    virtual BOOL OnInitDialog();
};

