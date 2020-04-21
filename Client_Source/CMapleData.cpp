#include "DXUT.h"
#include "CMapleData.h"

CMapleData::CMapleData(MapleDataType _Type, char * _Data)
{
	m_Type = _Type;
	m_Data = _Data;

}

CMapleData::~CMapleData()
{
}
