#include "DXUT.h"
#include "CWzObjectChild.h"
#include "CWzObject.h"
CWzObjectChild::CWzObjectChild(string _Name, CWzObject * _pParent)
	:CWzObject(_Name)
{
	
	m_pParent = _pParent;
}

CWzObjectChild::~CWzObjectChild()
{
}
