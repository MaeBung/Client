#pragma once

//매니저 등록 전처리기
#define SCENE (*CSceneManager::GetInstance())
#define PHYSICS (*CPhysicsManager::GetInstance())
#define OBJECT (*CObjectManager::GetInstance())
#define INPUT (*CInputManager::GetInstance())
#define GRAPHICS (*CGraphicsManager::GetInstance())
#define DATA (*CDataManager::GetInstance())
#define TIME (*CTimeManager::GetInstance())

//자료형
using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;


//디버그 모드일경우 디버그로그 확인을 위한 콘솔 추가
#if _DEBUG || DEBUG
#pragma comment (linker , "/entry:wWinMainCRTStartup /subsystem:console")
#define DEBUG_LOG printf("\n"); printf
#else 
#define DEBUG_LOG
#endif

#pragma comment (linker , "/entry:wWinMainCRTStartup /subsystem:console")
#define DEBUG_LOG printf("\n"); printf