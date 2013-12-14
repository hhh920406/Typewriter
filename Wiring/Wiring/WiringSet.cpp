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


IMPLEMENT_DYNAMIC(DataPin, CRecordset)

DataPin::DataPin(CDatabase* pdb) : CRecordset(pdb)
{
	m_D_PinID = 0;
	m_D_ChipID = 0;
	m_D_No = 0;
	m_D_Orientation = 0;
	m_D_Shift = 0;
	m_nFields = 5;
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
	RFX_Long(pFX, _T("[D_Shift]"), m_D_Shift);
}


IMPLEMENT_DYNAMIC(DataWire, CRecordset)

DataWire::DataWire(CDatabase* pdb) : CRecordset(pdb)
{
	m_D_WireID = 0;
	m_D_ChipID = 0;
	m_D_No_Main = 0;
	m_D_No_Sub = 0;
	m_D_StartX = 0;
	m_D_StartY = 0;
	m_D_EndX = 0;
	m_D_EndY = 0;
	m_nFields = 8;
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
	RFX_Long(pFX, _T("[D_ChipID]"), m_D_ChipID);
	RFX_Long(pFX, _T("[D_No_Main]"), m_D_No_Main);
	RFX_Long(pFX, _T("[D_No_Sub]"), m_D_No_Sub);
	RFX_Long(pFX, _T("[D_StartX]"), m_D_StartX);
	RFX_Long(pFX, _T("[D_StartY]"), m_D_StartY);
	RFX_Long(pFX, _T("[D_EndX]"), m_D_EndX);
	RFX_Long(pFX, _T("[D_EndY]"), m_D_EndY);
}

CDatabase* DataControl::database()
{
	CDatabase *database = new CDatabase();
	if (!database->OpenEx(L"DBQ=data\\WData.mdb;DefaultDir=data;Driver={Microsoft Access Driver (*.mdb)};DriverId=25;FIL=MS Access;FILEDSN=data\\Data.dsn;MaxBufferSize=2048;MaxScanRows=8;PageTimeout=5;SafeTransactions=0;Threads=3;UID=admin;UserCommitSync=Yes;", CDatabase::noOdbcDialog))
	{
		delete database;
		return NULL;
	}
	return database;
}

void DataControl::save(SwitchBox &switchBox)
{
	CDatabase *database = DataControl::database();
	if (database != NULL)
	{
		DataChip dChip(database);
		dChip.Open();
		dChip.SetFieldNull(NULL);
		dChip.AddNew();
		dChip.m_D_Name = switchBox.name();
		dChip.m_D_Width = switchBox.width();
		dChip.m_D_Height = switchBox.height();
		dChip.Update();
		dChip.Close();
		CDBVariant ids;
		dChip.Open(0, _T("select @@identity as ids"));
		dChip.GetFieldValue(_T("ids"), ids);
		dChip.Close();
		long chipID = ids.m_lVal;
		for (unsigned int i = 0; i < switchBox.pin().size(); ++i)
		{
			Pin& pin = switchBox.pin()[i];
			DataPin dPin(database);
			dPin.Open();
			dPin.SetFieldNull(NULL);
			dPin.AddNew();
			dPin.m_D_ChipID = chipID;
			dPin.m_D_No = pin.id();
			dPin.m_D_Orientation = (int)pin.orientation();
			dPin.m_D_Shift = (double)pin.shift();
			dPin.Update();
			dPin.Close();
		}
		for (unsigned int i = 0; i < switchBox.wire().size(); ++i)
		{
			Wire& wire = switchBox.wire()[i];
			DataWire dWire(database);
			dWire.Open();
			dWire.SetFieldNull(NULL);
		}
		database->Close();
		delete database;
	}
}

void DataControl::load(SwitchBox &switchBox)
{
	CDatabase *database = DataControl::database();
	if (database != NULL)
	{

	}
}