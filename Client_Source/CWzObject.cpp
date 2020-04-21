#include "DXUT.h"
#include "CWzObject.h"


CWzObject::CWzObject(string _Name)
	: m_Name(_Name)
{
}

CWzObject::~CWzObject()
{
	for (auto iter : m_mapProperties)
	{
		SAFE_DELETE(iter.second);
	}

	for (auto iter : m_mapChild)
	{
		SAFE_DELETE(iter.second);
	}
}
