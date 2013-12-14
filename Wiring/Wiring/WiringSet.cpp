
// WiringSet.cpp : CWiringSet 类的实现
//

#include "stdafx.h"
#include "Wiring.h"
#include "WiringSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWiringSet 实现

// 代码生成在 Saturday, December 14, 2013, 2:03 PM

IMPLEMENT_DYNAMIC(CWiringSet, CRecordset)

CWiringSet::CWiringSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_D_ChipID = 0;
	m_D_Name = L"";
	m_D_Width = 0;
	m_D_Height = 0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CWiringSet::GetDefaultConnect()
{
	return _T("DBQ=F:\\Homework\\MFC\\WData.mdb;DefaultDir=F:\\Homework\\MFC;Driver={Microsoft Access Driver (*.mdb)};DriverId=25;FIL=MS Access;FILEDSN=F:\\Homework\\MFC\\Data.dsn;MaxBufferSize=2048;MaxScanRows=8;PageTimeout=5;SafeTransactions=0;Threads=3;UID=admin;UserCommitSync=Yes;");
}

CString CWiringSet::GetDefaultSQL()
{
	return _T("[T_Chip]");
}

void CWiringSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Long(pFX, _T("[D_ChipID]"), m_D_ChipID);
	RFX_Text(pFX, _T("[D_Name]"), m_D_Name);
	RFX_Long(pFX, _T("[D_Width]"), m_D_Width);
	RFX_Long(pFX, _T("[D_Height]"), m_D_Height);

}
/////////////////////////////////////////////////////////////////////////////
// CWiringSet 诊断

#ifdef _DEBUG
void CWiringSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CWiringSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

