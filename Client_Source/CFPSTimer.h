#pragma once
class CFPSTimer
{
public:
	CFPSTimer();
	~CFPSTimer();

private:
	float m_fDeltaTime = 0.f;
	float m_fFPS = 0.f;


	DWORD m_iFrameCount = 0;            //프레임 카운트수
	float m_fTimeElapsed = 0.0f;            //흐른 시간
	DWORD m_iLastTime = timeGetTime();   //마지막 시간(temp변수)
public:
	void Update();

	float GetFPS() { return m_fFPS; }
	float GetDeltaTime() { return m_fDeltaTime; }
};

