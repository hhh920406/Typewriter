
// WiringSet.cpp : CWiringSet ���ʵ��
//

#include "stdafx.h"
#include "Wiring.h"
#include "WiringSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWiringSet ʵ��

// ���������� Saturday, December 14, 2013, 2:03 PM

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
#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[D_ChipID]"), m_D_ChipID);
	RFX_Text(pFX, _T("[D_Name]"), m_D_Name);
	RFX_Long(pFX, _T("[D_Width]"), m_D_Width);
	RFX_Long(pFX, _T("[D_Height]"), m_D_Height);

}
/////////////////////////////////////////////////////////////////////////////
// CWiringSet ���

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

