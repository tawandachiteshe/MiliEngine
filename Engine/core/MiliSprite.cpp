#include "MiliSprite.h"
#include "core.h"

MiliSprite::MiliSprite()
{

}

MiliSprite::MiliSprite(int w, int h):
nWidth(w), nHeight(h)
{

	Create(nWidth, nHeight);
}

MiliSprite::MiliSprite(std::wstring sFile) :
sFile(sFile)
{
	if (!Load(sFile))
		Create(8, 8);
}


void MiliSprite::SetGlyph(int x, int y, short c)
{
	if (x <0 || x >= nWidth || y < 0 || y >= nHeight)
		return;
	else
		m_Glyphs[y * nWidth + x] = c;
}

void MiliSprite::SetColour(int x, int y, short c)
{
	if (x <0 || x >= nWidth || y < 0 || y >= nHeight)
		return;
	else
		m_Colours[y * nWidth + x] = c;
}

short MiliSprite::GetGlyph(int x, int y)
{
	if (x <0 || x >= nWidth || y < 0 || y >= nHeight)
		return L' ';
	else
		return m_Glyphs[y * nWidth + x];
}

short MiliSprite::GetColour(int x, int y)
{
	if (x <0 || x >= nWidth || y < 0 || y >= nHeight)
		return FG_BLACK;
	else
		return m_Colours[y * nWidth + x];
}

short MiliSprite::SampleGlyph(float x, float y)
{
	int sx = (int)(x * (float)nWidth);
	int sy = (int)(y * (float)nHeight - 1.0f);
	if (sx <0 || sx >= nWidth || sy < 0 || sy >= nHeight)
		return L' ';
	else
		return m_Glyphs[sy * nWidth + sx];
}

short MiliSprite::SampleColour(float x, float y)
{
	int sx = (int)(x * (float)nWidth);
	int sy = (int)(y * (float)nHeight - 1.0f);
	if (sx <0 || sx >= nWidth || sy < 0 || sy >= nHeight)
		return FG_BLACK;
	else
		return m_Colours[sy * nWidth + sx];
}

bool MiliSprite::Save(std::wstring sFile)
{
	FILE *f = nullptr;
	_wfopen_s(&f, sFile.c_str(), L"wb");
	if (f == nullptr)
		return false;

	fwrite(&nWidth, sizeof(int), 1, f);
	fwrite(&nHeight, sizeof(int), 1, f);
	fwrite(m_Colours, sizeof(short), nWidth * nHeight, f);
	fwrite(m_Glyphs, sizeof(short), nWidth * nHeight, f);

	fclose(f);

	return true;
}

bool MiliSprite::Load(std::wstring sFile)
{
	delete[] m_Glyphs;
	delete[] m_Colours;
	nWidth = 0;
	nHeight = 0;

	FILE *f = nullptr;
	_wfopen_s(&f, sFile.c_str(), L"rb");
	if (f == nullptr)
		return false;

	std::fread(&nWidth, sizeof(int), 1, f);
	std::fread(&nHeight, sizeof(int), 1, f);

	Create(nWidth, nHeight);

	std::fread(m_Colours, sizeof(short), nWidth * nHeight, f);
	std::fread(m_Glyphs, sizeof(short), nWidth * nHeight, f);

	std::fclose(f);
	return true;
}
