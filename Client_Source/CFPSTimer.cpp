#include "DXUT.h"
#include "CFPSTimer.h"


CFPSTimer::CFPSTimer()
{
}


CFPSTimer::~CFPSTimer()
{
}

void CFPSTimer::Update()
{
	DWORD iCurTime = timeGetTime();      //현재 시간
	float fTimeDelta = (iCurTime - m_iLastTime)*0.001f;        //timeDelta(1번생성후 흐른 시간) 1초단위로 바꿔준다.

	m_fTimeElapsed += fTimeDelta;

	m_iFrameCount++;

	m_fFPS = (float)m_iFrameCount / m_fTimeElapsed;
	m_fDeltaTime = 1.0f / m_fFPS;

	if (m_fTimeElapsed >= 1.0f)         //흐른시간이 1초이상이면 내가 하고싶은것 처리
	{


		m_iFrameCount = 0;
		m_fTimeElapsed = 0.0f;
	}





	m_iLastTime = iCurTime;
}
