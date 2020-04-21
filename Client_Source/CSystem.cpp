#include "DXUT.h"
#include "CSystem.h"

void CSystem::OnInit()
{
	m_pMainGame = nullptr;
}

void CSystem::OnCreateDevice()
{
	m_pSystemTimer = new CFPSTimer();

	m_pMainGame = new CMainGame();
	m_pMainGame->Init();
}

void CSystem::OnUpdate()
{
	m_pSystemTimer->Update();
	m_pMainGame->Update();
}

void CSystem::OnRender()
{
	//printf("%.f\n", m_pSystemTimer->GetFPS());
	m_pMainGame->Render();
}

void CSystem::OnDestroyDevice()
{
	SAFE_DELETE(m_pSystemTimer);

	m_pMainGame->Release();
	SAFE_DELETE(m_pMainGame);

	DATA.SaveFile();
}

void CSystem::OnLostDevice()
{
	m_pMainGame->OnLostDevice();
}

void CSystem::OnResetDevice()
{
	m_pMainGame->OnResetDevice();
}

void CSystem::OnMsgProc(UINT _Msg, WPARAM _WParam, LPARAM _LParam)
{
}
