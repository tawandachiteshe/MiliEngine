#include "MiliAudio.h"


MiliAudio::MiliAudio()
{
}


MiliAudio::~MiliAudio()
{
}



MiliAudio::MiliAudio(std::wstring sWavFile) :
m_sWavFile(sWavFile)
{
	// Load Wav file and convert to float format
	FILE *f = nullptr;
	_wfopen_s(&f, m_sWavFile.c_str(), L"rb");
	if (f == nullptr)
		return;

	char dump[4];
	std::fread(&dump, sizeof(char), 4, f); // Read "RIFF"
	if (strncmp(dump, "RIFF", 4) != 0) return;
	std::fread(&dump, sizeof(char), 4, f); // Not Interested
	std::fread(&dump, sizeof(char), 4, f); // Read "WAVE"
	if (strncmp(dump, "WAVE", 4) != 0) return;

	// Read Wave description chunk
	std::fread(&dump, sizeof(char), 4, f); // Read "fmt "
	std::fread(&dump, sizeof(char), 4, f); // Not Interested
	std::fread(&wavHeader, sizeof(WAVEFORMATEX)-2, 1, f); // Read Wave Format Structure chunk
	// Note the -2, because the structure has 2 bytes to indicate its own size
	// which are not in the wav file

	// Just check if wave format is compatible with olcCGE
	if (wavHeader.wBitsPerSample != 16 || wavHeader.nSamplesPerSec != 44100)
	{
		std::fclose(f);
		return;
	}

	// Search for audio data chunk
	long nChunksize = 0;
	std::fread(&dump, sizeof(char), 4, f); // Read chunk header
	std::fread(&nChunksize, sizeof(long), 1, f); // Read chunk size
	while (strncmp(dump, "data", 4) != 0)
	{
		// Not audio data, so just skip it
		std::fseek(f, nChunksize, SEEK_CUR);
		std::fread(&dump, sizeof(char), 4, f);
		std::fread(&nChunksize, sizeof(long), 1, f);
	}

	// Finally got to data, so read it all in and convert to float samples
	nSamples = nChunksize / (wavHeader.nChannels * (wavHeader.wBitsPerSample >> 3));
	nChannels = wavHeader.nChannels;

	// Create floating point buffer to hold audio sample
	fSample = new float[nSamples * nChannels];
	float *pSample = fSample;

	// Read in audio data and normalise
	for (long i = 0; i < nSamples; i++)
	{
		for (int c = 0; c < nChannels; c++)
		{
			short s = 0;
			std::fread(&s, sizeof(short), 1, f);
			*pSample = (float)s / (float)(MAXSHORT);
			pSample++;
		}
	}

	// All done, flag sound as valid
	std::fclose(f);
	bSampleValid = true;
}

