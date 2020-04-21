#pragma once
#include "CSingleton.h"
#include "CWzObject.h"
#include "CMapleData.h"
enum WzType
{
	CHARACTOR,
	SKILL
};

class CWzObjectManager :
	public CSingleton< CWzObjectManager>
{
public:
	CWzObjectManager();
	~CWzObjectManager();

private:
	map< WzType, map<string,CWzObject*>> m_mapWzObject;

public:
	CWzObject* GetWzObject(WzType _Type, string _Name);
	ThreadPool thp;
	void ParseWzObject(WzType _Type, string _Path);
	void Parse(CWzObject * _pParent, tinyxml2::XMLNode * _pParentNode)
	{
		tinyxml2::XMLElement * pElement = _pParentNode->ToElement();
		auto pAttribute = pElement->FirstAttribute();
		string Type = _pParentNode->Value();
		string Log;

		if (Type == "imgdir")
		{
			Log += pAttribute->Value();
			CWzObjectChild * pObject = new CWzObjectChild(pAttribute->Value(), _pParent);
			_pParent->AddChild(pAttribute->Value(), pObject);

			if (pElement->FirstChild())
				Parse(pObject, pElement->FirstChild());
		}
		else if (Type == "int")
		{
			Log += "="s + pAttribute->Value();
			int * Data = new int(stoi(pAttribute->Next()->Value()));
			_pParent->AddProperty(pAttribute->Value(), new CMapleData(MapleDataType::INT, (char*)Data));
		}
		else if (Type == "float")
		{
			Log += "="s + pAttribute->Value();
			_pParent->AddProperty(pAttribute->Value(), new CMapleData(MapleDataType::FLOAT, (char*)new string(pAttribute->Next()->Value())));

		}
		else if (Type == "string")
		{
			if (pAttribute->Value() != "_hash")
			{
				Log += "="s + pAttribute->Value();
				_pParent->AddProperty(pAttribute->Value(), new CMapleData(MapleDataType::STRING, (char*)new string(pAttribute->Next()->Value())));
			}
		}
		else if (Type == "vector")
		{
			Log += pAttribute->Name() + " = "s + pAttribute->Value();
			float y = stoi(pAttribute->Next()->Value());
			float x = stoi(pAttribute->Next()->Next()->Value());

			_pParent->AddProperty(pAttribute->Value(), new CMapleData(MapleDataType::VECTOR, (char*)new Vector2(x, y)));
		}
		else if (Type == "canvas")
		{
			float Height = stof(pAttribute->Next()->Value());
			float Width = stof(pAttribute->Next()->Next()->Value());
			_pParent->AddProperty(pAttribute->Value(), new CMapleData(MapleDataType::CANVAS, (char*)new Vector2(Width, Height)));

		}
		//DEBUG_LOG("%s %s", Type.c_str(), Log.c_str());
		if (pElement->NextSibling())
			Parse(_pParent, pElement->NextSibling());

	}
	vector<string> GetFilesInFolder(string _Path);

	void AddWzObject(WzType _Type, string _Name, CWzObject * _pObject);
};

#define WZ (*CWzObjectManager::GetInstance())

