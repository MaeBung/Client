#include "DXUT.h"
#include "CWzObjectManager.h"

CWzObjectManager::CWzObjectManager()
	: thp(thread::hardware_concurrency())
{
	m_mapWzObject[WzType::CHARACTOR];
}

CWzObjectManager::~CWzObjectManager()
{
}

CWzObject * CWzObjectManager::GetWzObject(WzType _Type, string _Name)
{
	return  m_mapWzObject[_Type][_Name];
}

void CWzObjectManager::ParseWzObject(WzType _Type, string _Path)
{
	tinyxml2::XMLDocument m_xmlDoc;
	tinyxml2::XMLNode * m_pNode;
	tinyxml2::XMLElement * m_pElement;

	vector<string> files = GetFilesInFolder(_Path);

	for (auto iter : files)
	{
		if (iter.length() > 8 && iter.substr(iter.length() - 8, 8) == ".img.xml")
		{

			m_xmlDoc.LoadFile((_Path + iter).c_str());
			CWzObject * ParentsObject = new CWzObject(iter);
			WZ.AddWzObject(_Type, iter, ParentsObject);

			m_pNode = m_xmlDoc.FirstChild()->NextSibling();
			m_pElement = m_pNode->ToElement();

			Parse(ParentsObject, m_pNode->FirstChild());
		}
		else
		{
			auto f = [&]() { ParseWzObject(_Type, _Path + iter + "/"); };
			thp.EnqueueJob(f);
		}

	}
}
vector<string> CWzObjectManager::GetFilesInFolder(string _Path)
{
	vector<string> names;
	char search_path[200];
	sprintf(search_path, "%s/*.*", _Path.c_str());
	WIN32_FIND_DATAA fd;
	HANDLE hFind = ::FindFirstFileA(search_path, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
		//	if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			if (fd.cFileName[0] != '.')
				names.push_back(fd.cFileName);
			//	}
		} while (::FindNextFileA(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

void CWzObjectManager::AddWzObject(WzType _Type, string _Name, CWzObject * _pObject)
{
	m_mapWzObject[_Type].insert(make_pair(_Name, _pObject));
}
