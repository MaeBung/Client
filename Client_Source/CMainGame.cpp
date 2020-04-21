#include "DXUT.h"
#include "CMainGame.h"
void Parse(CWzObject * _pParent, tinyxml2::XMLNode * _pParentNode);
void Print(CWzObject * _pObj)
{
	DEBUG_LOG("%s 의 정보를 추출합니다.", _pObj->GetName().c_str());
	for (auto iter : _pObj->GetPropertiesMap())
	{
		switch (iter.second->GetType())
		{
		case MapleDataType::INT:
			DEBUG_LOG("%s 프로퍼티 의 정보: Type : Int , Value : %d\n", iter.first.c_str(), iter.second->GetInt());
			break;
		case MapleDataType::FLOAT:
			DEBUG_LOG("%s 프로퍼티 의 정보: Type : Float , Value : %f\n", iter.first.c_str(), iter.second->GetFloat());
			break;
		case MapleDataType::STRING:
			DEBUG_LOG("%s 프로퍼티 의 정보: Type : String , Value : %s\n", iter.first.c_str(), iter.second->GetString().c_str());
			break;
		case MapleDataType::VECTOR:
			DEBUG_LOG("%s 프로퍼티 의 정보: Type : Vector , x : %.f y : %.f\n", iter.first.c_str(), iter.second->GetVector().x, iter.second->GetVector().y);
			break;
		case MapleDataType::CANVAS:
			DEBUG_LOG("%s 프로퍼티 의 정보: Type : Canvas , width : %.f height : %.f\n", iter.first.c_str(), iter.second->GetVector().x, iter.second->GetVector().y);
			break;
		}
	}

	for (auto iter : _pObj->GetChildMap())
	{
		Print(iter.second);
	}
}
void CMainGame::Init()
{

	//DATA.LoadFile();
	//DATA.SetString("TestString", "432432");
	//DATA.SetFloat("TestFloat", 4.432423);
	WZ.ParseWzObject(WzType::CHARACTOR, "./Resource/WZ/Character.wz/");
	

	//printf("Test Int Data : %d\n", DATA.GetInt("TestInt"));
	//printf("Test Float Data : %f\n", DATA.GetFloat("TestFloat"));
	//printf("Test bool Data : %d\n", DATA.GetBool("TestBool"));
	//printf("Test String Data : %s\n", DATA.GetString("TestString").c_str());
	DEBUG_LOG("파싱완료");
//	auto a = WZ.GetWzObject(WzType::CHARACTOR, "00002000.img.xml");
//	Print(a);
}

void CMainGame::Update()
{

}

void CMainGame::Render()
{
}

void CMainGame::Release()
{
}

void CMainGame::OnLostDevice()
{
}

void CMainGame::OnResetDevice()
{
}
