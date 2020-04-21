#pragma once
class CFPSTimer
{
public:
	CFPSTimer();
	~CFPSTimer();

private:
	float m_fDeltaTime = 0.f;
	float m_fFPS = 0.f;


	DWORD m_iFrameCount = 0;            //������ ī��Ʈ��
	float m_fTimeElapsed = 0.0f;            //�帥 �ð�
	DWORD m_iLastTime = timeGetTime();   //������ �ð�(temp����)
public:
	void Update();

	float GetFPS() { return m_fFPS; }
	float GetDeltaTime() { return m_fDeltaTime; }
};

