#pragma once
#include "MiliSprite.h"
#include "core.h"
class Renderer
{
public:
	Renderer();
	Renderer(const Renderer& r);
	Renderer(const int& ScreenWidth, const int& ScreenHeight);
	~Renderer();
	virtual void Draw(int x, int y, short c = 0x2588, short col = 0x000F);
	void Fill(int x1, int y1, int x2, int y2, short c = 0x2588, short col = 0x000F);
	void DrawString(int x, int y, std::wstring c, short col = 0x000F);
	void DrawStringAlpha(int x, int y, std::wstring c, short col = 0x000F);
	void Clip(int &x, int &y);
	void DrawLine(int x1, int y1, int x2, int y2, short c = 0x2588, short col = 0x000F);
	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short, short);
	void FillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short c = 0x2588, short col = 0x000F);
	void DrawCircle(int xc, int yc, int r, short c = 0x2588, short col = 0x000F);
	void FillCircle(int xc, int yc, int r, short c = 0x2588, short col = 0x000F);
	void DrawSprite(int x, int y, MiliSprite *sprite);
	void DrawPartialSprite(int x, int y, MiliSprite *sprite, int ox, int oy, int w, int h);
	void DrawWireFrameModel(const std::vector<std::pair<float, float>> &vecModelCoordinates, float x, float y, float r = 0.0f, float s = 1.0f, short col = FG_WHITE, short c = PIXEL_SOLID);
	CHAR_INFO* GetBufScreen();

private:
	const int m_ScreenWidth = 0;
	const int m_ScreenHeight = 0;
	CHAR_INFO *m_bufScreen;
	
};

