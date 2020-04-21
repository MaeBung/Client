#include "DXUT.h"
#include "CDataManager.h"


CDataManager::CDataManager()
{
	PropertyFilePath = "./";
	PropertyFileName = "UserProperty.Property";
}


CDataManager::~CDataManager()
{

}

void CDataManager::LoadFile()
{
	string FilePath = PropertyFilePath + PropertyFileName;
	ifstream readFile;

	readFile.open(FilePath.c_str(), ios::binary | ios::in);
	if (readFile.is_open() == false)
	{
		SaveFile();
	}
	else
	{
		LoadContainor(readFile, this->m_mapInt);
		LoadContainor(readFile, this->m_mapBool);
		LoadContainor(readFile, this->m_mapFloat);
		LoadContainor(readFile, this->m_mapString);
	}
	readFile.close();
}

void CDataManager::SaveFile()
{
	string FilePath = PropertyFilePath + PropertyFileName;

	ofstream writeFile;
	writeFile.open(FilePath.c_str(), ios::binary | ios::out);

	if (writeFile.eof() == false)
		writeFile.clear();

	SaveContainor(writeFile, this->m_mapInt);
	SaveContainor(writeFile, this->m_mapBool);
	SaveContainor(writeFile, this->m_mapFloat);
	SaveContainor(writeFile, this->m_mapString);

	writeFile.close();
}



int CDataManager::GetInt(string _Key, int _iDefaultValue)
{
	auto find = m_mapInt.find(_Key);
	if (find == m_mapInt.end())
	{
		return _iDefaultValue;
	}
	return find->second;
}

float CDataManager::GetFloat(string _Key, float _fDefaultValue)
{
	auto find = m_mapFloat.find(_Key);
	if (find == m_mapFloat.end())
	{
		return _fDefaultValue;
	}
	return find->second;
}

bool CDataManager::GetBool(string _Key, bool _bDefaultValue)
{
	auto find = m_mapBool.find(_Key);
	if (find == m_mapBool.end())
	{
		return _bDefaultValue;
	}
	return find->second;
}

string CDataManager::GetString(string _Key, string _DefaultValue)
{
	auto find = m_mapString.find(_Key);
	if (find == m_mapString.end())
	{
		return _DefaultValue;
	}
	return find->second;
}


void CDataManager::SetInt(string _Key, int _iValue)
{
	auto find = m_mapInt.find(_Key);
	if (find == m_mapInt.end())
	{
		m_mapInt.insert(make_pair(_Key, _iValue));
	}
	else find->second = _iValue;
}

void CDataManager::SetFloat(string _Key, float _fValue)
{
	auto find = m_mapFloat.find(_Key);
	if (find == m_mapFloat.end())
	{
		m_mapFloat.insert(make_pair(_Key, _fValue));
	}
	else find->second = _fValue;
}

void CDataManager::SetBool(string _Key, bool _bValue)
{
	auto find = m_mapBool.find(_Key);
	if (find == m_mapBool.end())
	{
		m_mapBool.insert(make_pair(_Key, _bValue));
	}
	else find->second = _bValue;
}

void CDataManager::SetString(string _Key, string _Value)
{
	auto find = m_mapString.find(_Key);
	if (find == m_mapString.end())
	{
		m_mapString.insert(make_pair(_Key, _Value));
	}
	else find->second = _Value;
}

void CDataManager::DeleteKey(string _Key)
{
	m_mapBool.erase(_Key);
	m_mapFloat.erase(_Key);
	m_mapInt.erase(_Key);
	m_mapString.erase(_Key);
}

void CDataManager::DeleteAllKey(string _Key)
{
	m_mapBool.clear();
	m_mapFloat.clear();
	m_mapInt.clear();
	m_mapString.clear();
}

bool CDataManager::HasData(string _Key)
{
	auto find1 = m_mapBool.find(_Key);
	if (find1 != m_mapBool.end()) return true;

	auto find2 = m_mapFloat.find(_Key);
	if (find2 != m_mapFloat.end()) return true;

	auto find3 = m_mapInt.find(_Key);
	if (find3 != m_mapInt.end()) return true;

	auto find4 = m_mapString.find(_Key);
	if (find4 != m_mapString.end()) return true;

	return false;
}

