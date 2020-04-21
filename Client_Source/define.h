#pragma once

//�Ŵ��� ��� ��ó����
#define SCENE (*CSceneManager::GetInstance())
#define PHYSICS (*CPhysicsManager::GetInstance())
#define OBJECT (*CObjectManager::GetInstance())
#define INPUT (*CInputManager::GetInstance())
#define GRAPHICS (*CGraphicsManager::GetInstance())
#define DATA (*CDataManager::GetInstance())
#define TIME (*CTimeManager::GetInstance())

//�ڷ���
using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;


//����� ����ϰ�� ����׷α� Ȯ���� ���� �ܼ� �߰�
#if _DEBUG || DEBUG
#pragma comment (linker , "/entry:wWinMainCRTStartup /subsystem:console")
#define DEBUG_LOG printf("\n"); printf
#else 
#define DEBUG_LOG
#endif

#pragma comment (linker , "/entry:wWinMainCRTStartup /subsystem:console")
#define DEBUG_LOG printf("\n"); printf