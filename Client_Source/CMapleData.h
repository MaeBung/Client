#pragma once
enum class MapleDataType
{
	NONE,
	IMG_0x00,
	SHORT,
	INT,
	FLOAT,
	DOUBLE,
	STRING,
	EXTENDED,
	PROPERTY,
	CANVAS,
	VECTOR,
	CONVEX,
	SOUND,
	UOL,
	UNKNOWN_TYPE,
	UNKNOWN_EXTENDED_TYPE
};

class CMapleData
{
public:
	CMapleData(MapleDataType _Type, char * _Data);
	~CMapleData();

private:
	MapleDataType m_Type;
	char * m_Data;

public:
	MapleDataType GetType() { return m_Type; }

	int GetInt(int _DefaultValue = 0)
	{
		if (m_Type == MapleDataType::INT) return *(int *)m_Data;
		return _DefaultValue;
	}
	float GetFloat(float _DefaultValue = 0.f)
	{
		if (m_Type == MapleDataType::FLOAT)
		{
			string floatStrData = *(string*)m_Data;
			return stof(floatStrData);
		}
		return _DefaultValue;
	}

	string GetString(string _DefaultValue = "(null)")
	{
		if (m_Type == MapleDataType::STRING) return *(string*)m_Data;
		return _DefaultValue;
	}

	Vector2 GetVector(Vector2 _DefaultValue = Vector2(0.f, 0.f))
	{
		if (m_Type == MapleDataType::INT) return *(Vector2*)m_Data;
		return _DefaultValue;
	}
};

