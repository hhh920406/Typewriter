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
	m_D_No = 0;
	m_D_U = 0;
	m_D_V = 0;
	m_nFields = 5;
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
	RFX_Long(pFX, _T("[D_No]"), m_D_No);
	RFX_Long(pFX, _T("[D_U]"), m_D_U);
	RFX_Long(pFX, _T("[D_V]"), m_D_V);
}


IMPLEMENT_DYNAMIC(DataWireSub, CRecordset)

DataWireSub::DataWireSub(CDatabase* pdb) : CRecordset(pdb)
{
	m_D_WireSubID = 0;
	m_D_WireID = 0;
	m_D_No = 0;
	m_D_X = 0;
	m_D_Y = 0;
	m_nFields = 5;
	m_nDefaultType = dynaset;
}

CString DataWireSub::GetDefaultConnect()
{
	return _T("DBQ=data\\WData.mdb;DefaultDir=data;Driver={Microsoft Access Driver (*.mdb)};DriverId=25;FIL=MS Access;FILEDSN=data\\Data.dsn;MaxBufferSize=2048;MaxScanRows=8;PageTimeout=5;SafeTransactions=0;Threads=3;UID=admin;UserCommitSync=Yes;");
}

CString DataWireSub::GetDefaultSQL()
{
	return _T("[T_WireSub]");
}

void DataWireSub::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[D_WireSubID]"), m_D_WireSubID);
	RFX_Long(pFX, _T("[D_WireID]"), m_D_WireID);
	RFX_Long(pFX, _T("[D_No]"), m_D_No);
	RFX_Long(pFX, _T("[D_X]"), m_D_X);
	RFX_Long(pFX, _T("[D_Y]"), m_D_Y);
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
			dPin.m_D_Shift = (long)(pin.shift() * 100);
			dPin.Update();
			dPin.Close();
		}
		for (unsigned int i = 0; i < switchBox.wire().size(); ++i)
		{
			Wire& wire = switchBox.wire()[i];
			DataWire dWire(database);
			dWire.Open();
			dWire.SetFieldNull(NULL);
			dWire.AddNew();
			dWire.m_D_ChipID = chipID;
			dWire.m_D_No = (long)i;
			dWire.m_D_U = wire.u();
			dWire.m_D_V = wire.v();
			dWire.Update();
			dWire.Close();
			dWire.Open(0, _T("select @@identity as ids"));
			dWire.GetFieldValue(_T("ids"), ids);
			dWire.Close();
			long wireID = ids.m_lVal;
			for (int j = 0; j < wire.count(); ++j)
			{
				DataWireSub dWireSub(database);
				dWireSub.Open();
				dWireSub.SetFieldNull(NULL);
				dWireSub.AddNew();
				dWireSub.m_D_WireID = wireID;
				dWireSub.m_D_No = j;
				dWireSub.m_D_X = (long)(wire.x(j) * 100);
				dWireSub.m_D_Y = (long)(wire.y(j) * 100);
				dWireSub.Update();
				dWireSub.Close();
			}
		}
		database->Close();
	}
}

void DataControl::load(SwitchBox &switchBox, long chipID)
{
	CDatabase *database = DataControl::database();
	if (database != NULL)
	{
		DataChip dChip(database);
		CString sql;
		sql.Format(L"SELECT * WHERE D_ChipID = %d", chipID);
		dChip.MoveFirst();
		switchBox.setName(dChip.m_D_Name);
		switchBox.setSize(dChip.m_D_Width, dChip.m_D_Height);
		dChip.Close();
		DataPin dPin(database);
		dPin.Open(0, sql);
		dPin.MoveFirst();
		while (!dPin.IsEOF())
		{
			Pin pin;
			pin.setId(dPin.m_D_PinID);
			pin.setOrientation(Pin::Orientation(dPin.m_D_Orientation));
			pin.setShift(dPin.m_D_Shift / 100.0);
			switchBox.pin().push_back(pin);
			dPin.MoveNext();
		}
		dPin.Close();
		DataWire dWire(database);
		dWire.Open(0, sql);
		dWire.MoveFirst();
		for (long i = 0; i < dWire.GetRecordCount(); ++i)
		{
			switchBox.wire().push_back(Wire());
		}
		dWire.Close();
		database->Close();
	}
}

DataChip* DataControl::list()
{
	CDatabase *database = DataControl::database();
	if (database != NULL)
	{
		DataChip *dChip = new DataChip(database);
		dChip->Open(0, _T("SELECT *"));
		return dChip;
	}
	return NULL;
}