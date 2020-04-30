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
	vector<string> files = GetFilesInFolder(_Path);

	for (auto iter : files)
	{
		if (iter.length() > 8 && iter.substr(iter.length() - 8, 8) == ".img.xml")
		{
			if (HasWzObject(_Type, iter))
				continue;
			auto f = [=]()
			{
				tinyxml2::XMLDocument m_xmlDoc;
				tinyxml2::XMLNode* m_pNode;
				tinyxml2::XMLElement* m_pElement;
				
				m_xmlDoc.LoadFile((_Path + iter).c_str());
				if (!m_xmlDoc.FirstChild())
					return;

				CWzObject * ParentsObject = new CWzObject(iter);
				WZ.AddWzObject(_Type, iter, ParentsObject);

				m_pNode = m_xmlDoc.FirstChild()->NextSibling();
				m_pElement = m_pNode->ToElement();

				Parse(ParentsObject, m_pNode->FirstChild());
			};

			thp.EnqueueJob(f);
		}
		else
		{
			auto f = [=]() { ParseWzObject(_Type, _Path + iter + "/"); };
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
	std::scoped_lock lock(m_mutex);
	//현재 로딩상황 확인해보기
	//std::cout << m_mapWzObject[_Type].size() << std::endl;

	m_mapWzObject[_Type].insert(make_pair(_Name, _pObject));
}

bool CWzObjectManager::HasWzObject(WzType _Type, string _Name)
{
	return m_mapWzObject[_Type].find(_Name) != m_mapWzObject[_Type].end();
}