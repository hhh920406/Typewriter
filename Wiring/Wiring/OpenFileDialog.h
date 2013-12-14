/**
 * 选择数据库中的文件。
 * @author ZHG <CyberZHG@gmail.com>
 */

#pragma once
#include <vector>
#include "afxdialogex.h"
#include "resource.h"

class OpenFileDialog : public CDialogEx
{
public:
	enum { IDD = IDD_OPENFILE };

	OpenFileDialog();
	virtual ~OpenFileDialog();
	virtual BOOL OnInitDialog();
	int selectedID() const;
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();

private:
	long _selectedID;
	std::vector<long> _chipID;
};

