#pragma once

#include "CMapleData.h"
class CWzObjectChild;
class CWzObject
{
public:
	CWzObject(string _Name);
	~CWzObject();

protected:
	unordered_map<string, CMapleData * > m_mapProperties;
	unordered_map<string, CWzObjectChild *> m_mapChild;
	string m_Name;

public:
	string GetName() { return m_Name; }
	void SetName(string _Name) { m_Name = _Name; }
	
	void AddProperty(string _Key, CMapleData * _pData)
	{
		m_mapProperties.insert(make_pair(_Key, _pData));
	}

	CMapleData * GetProperty(string _Key)
	{
		auto find = m_mapProperties.find(_Key);
		if (find != m_mapProperties.end())
			return find->second;

		return nullptr;
	}
	unordered_map<string, CMapleData * > GetPropertiesMap()
	{
		return m_mapProperties;
	}

	void AddChild(string _Key, CWzObjectChild * _pChild)
	{
		m_mapChild.insert(make_pair(_Key, _pChild));
	}

	CWzObjectChild * GetChild(string _Key)
	{
		auto find = m_mapChild.find(_Key);
		if (find != m_mapChild.end())
		{
			return find->second;
		}
		return nullptr;
	}
	unordered_map<string, CWzObjectChild * > GetChildMap()
	{
		return m_mapChild;
	}


};

