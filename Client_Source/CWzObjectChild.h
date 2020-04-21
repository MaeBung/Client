#pragma once
#include "CWzObject.h"

class CWzObject;
class CWzObjectChild : public CWzObject
{
public:
	CWzObjectChild(string _Name, CWzObject * _pParent);
	virtual ~CWzObjectChild();

private:
	CWzObject * m_pParent;
public:
	CWzObject * GetParent()
	{
		return m_pParent;
	}
};

