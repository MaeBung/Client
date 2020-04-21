#pragma once
#include "CMainGame.h"
class CSystem
{
public:
	void OnInit();
	void OnCreateDevice();
	void OnUpdate();
	void OnRender();
	void OnDestroyDevice();
	void OnLostDevice();
	void OnResetDevice();
	void OnMsgProc(UINT _Msg,WPARAM _WParam, LPARAM _LParam);

private:
	CMainGame * m_pMainGame = nullptr;

	CFPSTimer * m_pSystemTimer = nullptr;
	CFPSLimiter * m_pGameFPSLimiter = nullptr;
};

