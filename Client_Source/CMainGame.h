#pragma once

class CMainGame
{

public:
	void Init();
	void Update();
	void Render();
	void Release();
	
	void OnLostDevice();
	void OnResetDevice();
};

