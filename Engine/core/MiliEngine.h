#pragma once

#include "MiliAudio.h"
#include "Renderer.h"

class MiliEngine
{

protected:	

	int m_mousePosX;
	int m_mousePosY;
public:
	struct sKeyState
	{
		bool bPressed;
		bool bReleased;
		bool bHeld;
	} m_keys[256], m_mouse[5];

	MiliEngine();
	~MiliEngine();
	void EnableSound();
	int ConstructConsole(int width, int height, int fontw, int fonth);
	
	int ScreenWidth();
	int ScreenHeight();
	void Start();
	sKeyState GetKey(int nKeyID);
	int GetMouseX();
	int GetMouseY();
	sKeyState GetMouse(int nMouseButtonID);
	bool IsFocused();
private:
	void GameThread();

public:
	// User MUST OVERRIDE THESE!!
	virtual bool OnUserCreate() = 0;
	virtual bool OnUserUpdate(float fElapsedTime) = 0;
	Renderer* renderer;
	// Optional for clean up 
	virtual bool OnUserDestroy()						{ return true; }


protected:

	int Error(const wchar_t *msg);
	static BOOL CloseHandler(DWORD evt);
	





protected:
	int m_nScreenWidth;
	int m_nScreenHeight;

	std::wstring m_sAppName;
	HANDLE m_hOriginalConsole;
	CONSOLE_SCREEN_BUFFER_INFO m_OriginalConsoleInfo;
	HANDLE m_hConsole;
	HANDLE m_hConsoleIn;
	SMALL_RECT m_rectWindow;
	short m_keyOldState[256];
	short m_keyNewState[256];
	bool m_mouseOldState[5];
	bool m_mouseNewState[5];
	bool m_bConsoleInFocus = true;
	bool m_bEnableSound = false;

	// These need to be static because of the OnDestroy call the OS may make. The OS
	// spawns a special thread just for that
	static std::atomic<bool> m_bAtomActive;
	static std::condition_variable m_cvGameFinished;
	static std::mutex m_muxGame;


	///////////// audio engine fields //////////////
protected:

	unsigned int LoadAudioSample(std::wstring sWavFile);
	void PlaySample(int id, bool bLoop);
	void StopSample(int id);
	bool CreateAudio(unsigned int nSampleRate = 44100, unsigned int nChannels = 1,
		unsigned int nBlocks = 8, unsigned int nBlockSamples = 512);
	bool DestroyAudio();
	void waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwParam1, DWORD dwParam2);
	static void CALLBACK waveOutProcWrap(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
	void AudioThread();
	virtual float onUserSoundSample(int nChannel, float fGlobalTime, float fTimeStep);
	virtual float onUserSoundFilter(int nChannel, float fGlobalTime, float fSample);
	float GetMixerOutput(int nChannel, float fGlobalTime, float fTimeStep);
	struct sCurrentlyPlayingSample
	{
		int nAudioSampleID = 0;
		long nSamplePosition = 0;
		bool bFinished = false;
		bool bLoop = false;
	};

	std::list<sCurrentlyPlayingSample> listActiveSamples;

	unsigned int m_nSampleRate;
	unsigned int m_nChannels;
	unsigned int m_nBlockCount;
	unsigned int m_nBlockSamples;
	unsigned int m_nBlockCurrent;
	/////////// engine fields ////////
	std::vector<MiliAudio> vecAudioSamples;

	short* m_pBlockMemory = nullptr;
	WAVEHDR *m_pWaveHeaders = nullptr;
	HWAVEOUT m_hwDevice = nullptr;

	std::thread m_AudioThread;
	std::atomic<bool> m_bAudioThreadActive = false;
	std::atomic<unsigned int> m_nBlockFree = 0;
	std::condition_variable m_cvBlockNotZero;
	std::mutex m_muxBlockNotZero;
	std::atomic<float> m_fGlobalTime = 0.0f;

};

