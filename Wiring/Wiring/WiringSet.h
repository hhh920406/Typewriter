/**
 * 数据库管理。
 * @author ZHG <CyberZHG@gmail.com>
 */
#pragma once
#include "stdafx.h"

class DataChip : public CRecordset
{
public:
	DataChip(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(DataChip)

	long	m_D_ChipID;
	CStringW	m_D_Name;
	long	m_D_Width;
	long	m_D_Height;

	virtual CString GetDefaultConnect();
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);

	void addNewChip(CStringW name, int width, int height);
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
	double	m_D_Shift;

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
	long	m_D_PinID;
	long	m_D_No;
	double	m_D_StartX;
	double	m_D_StartY;
	double	m_D_EndX;
	double	m_D_EndY;

	virtual CString GetDefaultConnect();
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);
};