#pragma once

class CDataManager :
	public CSingleton< CDataManager>
{
public:
	CDataManager();
	~CDataManager();


public:
	void LoadFile();
	void SaveFile();

private:
	string m_FileName;

	map<string, int>	m_mapInt;
	map<string, float>	m_mapFloat;
	map<string, bool>	m_mapBool;
	map<string, string> m_mapString;


	string PropertyFilePath;
	string PropertyFileName;
private:
	template<class T>
	void SaveContainor(ofstream& _FileSteam, map<string, T>& _mapContainor)
	{
		int ContainorSize = _mapContainor.size();
		_FileSteam.write((char*)&ContainorSize, sizeof(int));

		for (auto iter : _mapContainor)
		{
			int size = sizeof(iter);
			_FileSteam.write((char*)&size, sizeof(int));
			_FileSteam.write((char*)&iter, size);
		}
	}
	template<class T>
	void LoadContainor(ifstream& _FileSteam, map<string, T>& _mapContainor)
	{
		int ContainorSize;
		_FileSteam.read((char*)&ContainorSize, sizeof(int));
		for (int i = 0; i < ContainorSize; i++)
		{
			int size;
			_FileSteam.read((char*)&size, sizeof(int));
			char* Buffer = new char[size];
			_FileSteam.read(Buffer, size);
			_mapContainor.insert(*(pair<string, T>*)Buffer);
			delete[] Buffer;
		}
	}


public:
	int GetInt(string _Key, int _iDefaultValue = 0);
	float GetFloat(string _Key, float _fDefaultValue = 0.f);
	bool GetBool(string _Key, bool _bDefaultValue = 0.f);
	string GetString(string _Key, string _DefaultValue = "");

	void SetInt(string _Key, int _iValue);
	void SetFloat(string _Key, float _fValue);
	void SetBool(string _Key, bool _bValue);
	void SetString(string _Key, string _sValue);

	void DeleteKey(string _Key);
	void DeleteAllKey(string _Key);
	bool HasData(string _Key);
};


