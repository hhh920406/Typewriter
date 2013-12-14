#include "stdafx.h"
#include "Wiring.h"
#include "WiringSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(DataChip, CRecordset)

DataChip::DataChip(CDatabase* pdb) : CRecordset(pdb)
{
	m_D_ChipID = 0;
	m_D_Name = L"";
	m_D_Width = 0;
	m_D_Height = 0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString DataChip::GetDefaultConnect()
{
	return _T("DBQ=data\\WData.mdb;DefaultDir=data;Driver={Microsoft Access Driver (*.mdb)};DriverId=25;FIL=MS Access;FILEDSN=data\\Data.dsn;MaxBufferSize=2048;MaxScanRows=8;PageTimeout=5;SafeTransactions=0;Threads=3;UID=admin;UserCommitSync=Yes;");
}

CString DataChip::GetDefaultSQL()
{
	return _T("[T_Chip]");
}

void DataChip::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[D_ChipID]"), m_D_ChipID);
	RFX_Text(pFX, _T("[D_Name]"), m_D_Name);
	RFX_Long(pFX, _T("[D_Width]"), m_D_Width);
	RFX_Long(pFX, _T("[D_Height]"), m_D_Height);
}

void DataChip::addNewChip(CStringW name, int width, int height)
{
	this->AddNew();
	this->m_D_Name = name;
	this->m_D_Width = width;
	this->m_D_Height = height;
	this->Update();
}


IMPLEMENT_DYNAMIC(DataPin, CRecordset)

DataPin::DataPin(CDatabase* pdb) : CRecordset(pdb)
{
	m_D_PinID = 0;
	m_D_ChipID = 0;
	m_D_No = 0;
	m_D_Orientation = 0;
	m_D_Shift = 0.0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString DataPin::GetDefaultConnect()
{
	return _T("DBQ=data\\WData.mdb;DefaultDir=data;Driver={Microsoft Access Driver (*.mdb)};DriverId=25;FIL=MS Access;FILEDSN=data\\Data.dsn;MaxBufferSize=2048;MaxScanRows=8;PageTimeout=5;SafeTransactions=0;Threads=3;UID=admin;UserCommitSync=Yes;");
}

CString DataPin::GetDefaultSQL()
{
	return _T("[T_Pin]");
}

void DataPin::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[D_PinID]"), m_D_PinID);
	RFX_Long(pFX, _T("[D_ChipID]"), m_D_ChipID);
	RFX_Long(pFX, _T("[D_No]"), m_D_No);
	RFX_Long(pFX, _T("[D_Orientation]"), m_D_Orientation);
	RFX_Double(pFX, _T("[D_Shift]"), m_D_Shift);
}


IMPLEMENT_DYNAMIC(DataWire, CRecordset)

DataWire::DataWire(CDatabase* pdb) : CRecordset(pdb)
{
	m_D_WireID = 0;
	m_D_PinID = 0;
	m_D_No = 0;
	m_D_StartX = 0.0;
	m_D_StartY = 0.0;
	m_D_EndX = 0.0;
	m_D_EndY = 0.0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString DataWire::GetDefaultConnect()
{
	return _T("DBQ=data\\WData.mdb;DefaultDir=data;Driver={Microsoft Access Driver (*.mdb)};DriverId=25;FIL=MS Access;FILEDSN=data\\Data.dsn;MaxBufferSize=2048;MaxScanRows=8;PageTimeout=5;SafeTransactions=0;Threads=3;UID=admin;UserCommitSync=Yes;");
}

CString DataWire::GetDefaultSQL()
{
	return _T("[T_Wire]");
}

void DataWire::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[D_WireID]"), m_D_WireID);
	RFX_Long(pFX, _T("[D_PinID]"), m_D_PinID);
	RFX_Long(pFX, _T("[D_No]"), m_D_No);
	RFX_Double(pFX, _T("[D_StartX]"), m_D_StartX);
	RFX_Double(pFX, _T("[D_StartY]"), m_D_StartY);
	RFX_Double(pFX, _T("[D_EndX]"), m_D_EndX);
	RFX_Double(pFX, _T("[D_EndY]"), m_D_EndY);
}