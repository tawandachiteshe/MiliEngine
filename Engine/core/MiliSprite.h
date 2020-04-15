#pragma once

#include "core.h"

class MiliSprite
{

private:
	short *m_Glyphs = nullptr;
	short *m_Colours = nullptr;
	void Create(int w, int h)
	{
		nWidth = w;
		nHeight = h;
		m_Glyphs = new short[w*h];
		m_Colours = new short[w*h];
		for (int i = 0; i < w*h; i++)
		{
			m_Glyphs[i] = L' ';
			m_Colours[i] = FG_BLACK;
		}
	}

public:
	MiliSprite();
	MiliSprite(int w, int h);
	MiliSprite(std::wstring sFile);
	std::wstring sFile;


	int nWidth = 0;
	int nHeight = 0;
	~MiliSprite();
	void SetGlyph(int x, int y, short c);
	void SetColour(int x, int y, short c);
	short GetGlyph(int x, int y);
	short GetColour(int x, int y);
	short SampleGlyph(float x, float y);
	short SampleColour(float x, float y);
	bool Save(std::wstring sFile);
	bool Load(std::wstring sFile);
};

