#pragma once

#include "core.h"

class MiliAudio
{
public:
	MiliAudio();
	MiliAudio(std::wstring sWavFile);
	~MiliAudio();

public:
	WAVEFORMATEX wavHeader;
	std::wstring m_sWavFile;
	float *fSample = nullptr;
	long nSamples = 0;
	int nChannels = 0;
	bool bSampleValid = false;
};

