#include "D2D_DRAW.h"

template <class T> void  SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

D2D_DRAW::~D2D_DRAW()//удаление обьекта класса
{
}

HRESULT D2D_DRAW::Initialize(HWND hWnd)
{

	HRESULT hr = S_OK;

	d2d_hwnd = hWnd;

	// Create a DirectWrite factory.
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(pIDWFactory),
		reinterpret_cast<IUnknown**>(&pIDWFactory)
	);
	//CreateGraphicsResources();
	
	return hr;
}

HRESULT D2D_DRAW::BeginDraw(FLOAT r, FLOAT g, FLOAT b, FLOAT a) //не особо нужен 
{
	HRESULT hr = CreateGraphicsResources();
	if (FAILED(hr))
		return hr;

	BeginPaint(d2d_hwnd, &struct_Visual);

	pRenderTarget->BeginDraw();

	pRenderTarget->SetTransform(D2D1::IdentityMatrix());

	pRenderTarget->Clear(D2D1::ColorF(r, g, b, a));

	return hr;

}

HRESULT D2D_DRAW::CreateGraphicsResources()
{
	bool Test = TRUE == FALSE;

	HRESULT hr = S_OK;
	if (pRenderTarget != NULL and Test)
		return hr;
	
	D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&pFactory);

	if (pFactory == NULL)
		return E_FAIL;

	RECT rc;
	if (GetClientRect(d2d_hwnd, &rc) == NULL)
		return E_FAIL;

	D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

	hr = pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)),
		D2D1::HwndRenderTargetProperties(d2d_hwnd, size), // D2D1_PRESENT_OPTIONS_IMMEDIATELY
		&pHwndRenderTarget);

	pRenderTarget = pHwndRenderTarget;

	if (FAILED(hr))
		return hr;

	return hr;
}

HRESULT D2D_DRAW::EndDraw() //не особо нужен 
{
	HRESULT hr = S_OK;
	hr = pRenderTarget->EndDraw();
	if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
	{
		DiscardGraphicsResources();
	}

	EndPaint(d2d_hwnd, &struct_Visual);

	return hr;
}

VOID D2D_DRAW::Rectangle(float pos_x, float pos_y, FLOAT height, FLOAT width, D2D1_COLOR_F d2dColor, LPCWSTR  text, int text_size_int)
{
	HRESULT hr; 

	// Draw two rectangles.
	D2D1_RECT_F rectangle = D2D1::RectF(
		pos_x,
		pos_y,
		pos_x + width,
		pos_y + height
	);
	D2D1_ROUNDED_RECT R_Rectangle = D2D1::RoundedRect
	(
		rectangle,
		width/20,
		width/20

	);

	hr = pRenderTarget->CreateSolidColorBrush(d2dColor, &pBrush);

	if (FAILED(hr))
		return;

	pRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);

	// Draw a filled rectangle.
	//pRenderTarget->FillRectangle(&rectangle1, pBrush);
	pRenderTarget->FillRoundedRectangle(R_Rectangle, pBrush);


	SafeRelease(&pBrush);
	pIDWFactory->CreateTextFormat(L"Plantagenet Cherokee", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, (FLOAT)16, L"", &pTextFormat);
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);
	D2D1_RECT_F rectangle_string = D2D1::RectF(
		pos_x,
		pos_y,
		pos_x + width,
		pos_y + height
	);
	pIDWFactory->CreateTextLayout(
		text, text_size_int,  // The length of the string.
		pTextFormat,  // The text format to apply to the string (contains font information, etc).
		width,         // The width of the layout box.
		height,// The height of the layout box.
		&pTextLayout  // The IDWriteTextLayout interface pointer.
	);
	pRenderTarget->DrawTextLayout({ pos_x, pos_y }, pTextLayout, pBrush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	SafeRelease(&pBrush);
	SafeRelease(&pTextFormat);
	SafeRelease(&pTextLayout);
	return;

	
}

VOID D2D_DRAW::GETSTRING(float Pos_y, float pos_x, FLOAT width, FLOAT height, LPCWSTR  text) //вывод текста тест
{
	pIDWFactory->CreateTextFormat(L"Plantagenet Cherokee",NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, (FLOAT)16, L"",&pTextFormat);
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);
	D2D1_RECT_F rectangle_string = D2D1::RectF(
		pos_x,
		Pos_y,
		pos_x + width,
		Pos_y + height
	);
	pIDWFactory->CreateTextLayout(
		text, 1,  // The length of the string.
		pTextFormat,  // The text format to apply to the string (contains font information, etc).
		width,         // The width of the layout box.
		height,// The height of the layout box.
		&pTextLayout  // The IDWriteTextLayout interface pointer.
	);
	pRenderTarget->DrawTextLayout({ pos_x, Pos_y }, pTextLayout, pBrush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	SafeRelease(&pBrush);
	SafeRelease(&pTextFormat);
	SafeRelease(&pTextLayout);
	return VOID();
}



VOID D2D_DRAW::DiscardGraphicsResources()
{
	SafeRelease(&pRenderTarget);
}
