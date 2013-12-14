/**
 * 数据库管理。
 * @author ZHG <CyberZHG@gmail.com>
 */
#pragma once
#include "stdafx.h"
#include "SwitchBox.h"

class DataChip : public CRecordset
{
public:
	DataChip(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(DataChip)

	long	m_D_ChipID;
	CStringW	m_D_Name;
	long	m_D_Width;
	long	m_D_Height;
	long	m_D_X;
	long	m_D_Y;

	virtual CString GetDefaultConnect();
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);
};

class DataPin : public CRecordset
{
public:
	DataPin(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(DataPin)

	long	m_D_PinID;
	long	m_D_ChipID;
	long	m_D_No;
	long	m_D_Orientation;
	long	m_D_Shift;

	virtual CString GetDefaultConnect();
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);
};

class DataWire : public CRecordset
{
public:
	DataWire(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(DataWire)

	long	m_D_WireID;
	long	m_D_ChipID;
	long	m_D_No;
	long	m_D_U;
	long	m_D_V;

	virtual CString GetDefaultConnect();
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);
};

class DataWireSub : public CRecordset
{
public:
	DataWireSub(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(DataWireSub)

	long	m_D_WireSubID;
	long	m_D_WireID;
	long	m_D_No;
	long	m_D_X;
	long	m_D_Y;

	virtual CString GetDefaultConnect();
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);
};

class DataControl
{
public:
	static CDatabase* database();
	static void save(SwitchBox &switchBox);
	static void load(SwitchBox &switchBox, long chipID);
	static DataChip* list();
};