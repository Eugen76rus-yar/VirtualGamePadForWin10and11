#pragma once
#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <string>




struct Vector2D
{
	float x;
	float y;
};
class D2D_DRAW
{
public:
	ID2D1Factory* pFactory;
	ID2D1PathGeometry* pGeometry;
	ID2D1SolidColorBrush* pBrush;
	ID2D1GeometrySink* pSink;
	ID2D1RenderTarget* pRenderTarget;
	ID2D1HwndRenderTarget* pHwndRenderTarget;
	IDWriteFactory* pIDWFactory;
	IDWriteTextFormat* pTextFormat;
	IDWriteTextLayout* pTextLayout;


	D2D1_ELLIPSE ellipse;

	D2D1_SIZE_U WndSize;
	virtual ~D2D_DRAW();

	HRESULT Initialize(HWND hWnd);
	HRESULT BeginDraw(FLOAT r, FLOAT g, FLOAT b, FLOAT a = 1.0f);
	HRESULT CreateGraphicsResources();
	HRESULT EndDraw();
	VOID Rectangle(float Pos_y, float pos_x, FLOAT width, FLOAT height, D2D1_COLOR_F d2dColor, LPCWSTR  text, int text_size_int);
	VOID GETSTRING(float Pos_y, float pos_x, FLOAT width, FLOAT height, LPCWSTR  text);

	VOID DiscardGraphicsResources();
private:
	HWND d2d_hwnd; //обьект окна
	PAINTSTRUCT struct_Visual;
};



