// Project6TextDX2d.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Project6TextDX2d.h"
#include "CreateWindowInBandimpl.h"




#define MAX_LOADSTRING 100
HWND hWnd; //глобальная перменная окна 
ATOM WndClass; //объект класса
constexpr auto NameWnd = L"testWindow";

int a;

//Directx
ID3D11Device* IDXDiveced_3d; 
IDXGIDevice4* IDXDevece4_GDI;
IDXGISurface2* surface_GDI;
ID2D1DeviceContext* diveceContext;
ID2D1Device* Device_d2d1;
//композиция окна
IDCompositionVisual* Compositionvisual;
IDCompositionDesktopDevice* CompositionDesktop;
//Фабрика DX
IDXGIFactory5* factory_dx3d;
ID2D1Factory2* factory_d2d;

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна



IDCompositionTarget* m_target;
IDCompositionVisual2* m_visual;
IDCompositionSurface* m_surface;


D2D_SIZE_F            m_size;
D2D_POINT_2F          m_dpi;



// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int ID_timers;

UINT cInputs;//мультитач
PTOUCHINPUT pInputs;
POINT ptInput;

bool Run_KEYBORD = false;

bool Run_KEYBORD_EM = false;

//удаление ненужной обработки

int Height = 800;
int Widght = 1280;

POINTER_INFO pointerInfo = {};







HRESULT DrawDX2D()
{

    //VisualRender.ADD_Button((float)110, (float)430, (float)100, (float)80, "UP", VK_UP, INPUT_KEYBOARD, 328, FALSE, D2D1::ColorF((float)0.6, (float)0.5, (float)0.5, (float)150 / 255), TRUE);
   // VisualRender.ADD_Button((float)110, (float)550, (float)100, (float)80, "DOWN", 0x28, INPUT_KEYBOARD, 336, FALSE, D2D1::ColorF((float)0.6, (float)0.5, (float)0.5, (float)150 / 255), TRUE);
   // VisualRender.ADD_Button((float)20, (float)550, (float)100, (float)80, "LEFT", VK_LEFT, INPUT_KEYBOARD, 331, FALSE, D2D1::ColorF((float)0.6, (float)0.5, (float)0.5, (float)150 / 255), TRUE);
   // VisualRender.ADD_Button((float)200, (float)550, (float)100, (float)80, "Right", VK_RIGHT, INPUT_KEYBOARD, 333, FALSE, D2D1::ColorF((float)0.6, (float)0.5, (float)0.5, (float)150 / 255), TRUE);
   // VisualRender.ADD_Button((float)1150, (float)300, (float)100, (float)100, "Return", VK_RETURN, INPUT_KEYBOARD, 28, FALSE);
   // VisualRender.ADD_Button((float)50, (float)50, (float)100, (float)100, "ESC", VK_ESCAPE, INPUT_KEYBOARD, 1, FALSE);
   // VisualRender.ADD_Button((float)900, (float)680, (float)100, (float)200, "SPASE", VK_SPACE, INPUT_KEYBOARD, 57, FALSE);
   // VisualRender.ADD_Button((float)1120, (float)150, (float)100, (float)100, "A", 0x41, INPUT_KEYBOARD, 30, FALSE);
   // VisualRender.ADD_Button((float)980, (float)150, (float)100, (float)100, "D", 0x44, INPUT_KEYBOARD, 32, FALSE);
   // VisualRender.ADD_Button((float)1050, (float)20, (float)100, (float)100, "I", 0x49, INPUT_KEYBOARD, 23, FALSE);

   // VisualRender.ADD_Button((float)50, (float)180, (float)100, (float)100, "TAB", VK_TAB, INPUT_KEYBOARD, 15, FALSE);
   // VisualRender.ADD_Button((float)1040, (float)300, (float)100, (float)100, "F", 0x46, INPUT_KEYBOARD, 33, FALSE);
   // VisualRender.ADD_Button((float)930, (float)300, (float)100, (float)100, "H", 0x48, INPUT_KEYBOARD, 35, FALSE);
   // VisualRender.ADD_Button((float)50, (float)680, (float)100, (float)150, "Crtl", VK_LCONTROL, INPUT_KEYBOARD, 29, FALSE, D2D1::ColorF((float)0.6, (float)0.5, (float)0.5, (float)150 / 255), TRUE);


 
   // VisualRender.ADD_Button((float)950, (float)450, (float)100, (float)100, "MLeft", MOUSEEVENTF_LEFTDOWN, INPUT_MOUSE, 0, TRUE );
   // VisualRender.ADD_Button((float)1120, (float)450, (float)100, (float)100, "MRight", MOUSEEVENTF_RIGHTDOWN, INPUT_MOUSE, 0, TRUE);

   // OpenIniFile.setstructVectButton(&VisualRender);

    HRESULT hr = S_OK;
    POINT offset = {};
    if (diveceContext != NULL)
    {
        hr = m_surface->BeginDraw(nullptr,
            __uuidof(diveceContext),
            reinterpret_cast<void**>(&diveceContext),
            &offset);
        d2_draw.pRenderTarget = diveceContext;
        diveceContext->SetDpi(m_dpi.x,
            m_dpi.y);

        diveceContext->SetTransform(D2D1::Matrix3x2F::Translation(offset.x * 96 / m_dpi.x,
            offset.y * 96 / m_dpi.y));

        diveceContext->Clear();


        VisualRender.RenderButton(d2_draw);
        //d2_draw.Rectangle((float)0, (float)0, (float)100, (float)100, D2D1::ColorF((float)70 / 255, (float)50 / 255, (float)50 / 255, (float)255 / 255));

        hr = m_surface->EndDraw();
        hr = CompositionDesktop->Commit();
    }
    return hr;
}

void Gampad()
{
    OpenIniFile.setstructVectButton(&VisualRender);
    VisualRender.ADD_Button((float)300, (float)0, (float)100, (float)100, L"Close", 0, Close_keybord, 0, FALSE);
    //DrawDX2D();


    return;
}


//Инициализация directx, создание буферов 
HRESULT Initialize()
{
    RECT rect;
    HRESULT hr;
    unsigned x;
    unsigned y;
    HMONITOR monitor;

    try
    {
        hr = D3D11CreateDevice(nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            D3D11_CREATE_DEVICE_BGRA_SUPPORT,
            nullptr, 0,
            D3D11_SDK_VERSION,
            &IDXDiveced_3d,
            nullptr,
            nullptr);
        if (FAILED(hr)) throw std::exception("Unable to D3D11CreateDevice");

        hr = IDXDiveced_3d->QueryInterface(&IDXDevece4_GDI);
        if (FAILED(hr)) throw std::exception("Unable to g_pd3dDevice->QueryInterface");

        hr = D2D1CreateDevice(IDXDevece4_GDI,
            nullptr,
            &Device_d2d1);
        if (FAILED(hr)) throw std::exception("Unable to D2D1CreateDevice");

        hr = DCompositionCreateDevice3(
            Device_d2d1,
            __uuidof(CompositionDesktop),
            reinterpret_cast<void**>(&CompositionDesktop));
        if (FAILED(hr)) throw std::exception("Unable to DCompositionCreateDevice3");

        hr = CompositionDesktop->CreateTargetForHwnd(hWnd,
            false,
            &m_target);
        if (FAILED(hr)) throw std::exception("Unable to m_device->CreateTargetForHwnd");

        hr = CompositionDesktop->CreateVisual(&m_visual);
        if (FAILED(hr)) throw std::exception("Unable to m_device->CreateVisual");

        if (!GetClientRect(hWnd, &rect))
            throw std::exception("Unable to GetClientRect");

        hr = CompositionDesktop->CreateSurface(rect.right - rect.left,
            rect.bottom - rect.top,
            DXGI_FORMAT_B8G8R8A8_UNORM,
            DXGI_ALPHA_MODE_PREMULTIPLIED,
            &m_surface);
        if (FAILED(hr)) throw std::exception("Unable to m_device->CreateSurface");

        hr = m_visual->SetContent(m_surface);
        if (FAILED(hr)) throw std::exception("Unable to m_visual->SetContent");

        hr = m_target->SetRoot(m_visual);
        if (FAILED(hr)) throw std::exception("Unable to target->SetRoot");

        hr = Device_d2d1->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
            &diveceContext);
        if (FAILED(hr)) throw std::exception("Unable to d2Device->CreateDeviceContext");

        monitor = MonitorFromWindow(hWnd,
            MONITOR_DEFAULTTONEAREST);

        hr = GetDpiForMonitor(monitor,
            MDT_EFFECTIVE_DPI,
            &x,
            &y);
        if (FAILED(hr))
        {
            int sleep = MessageBox(GetActiveWindow(), L"Error initilize d2d", L"Error", MB_ICONERROR);
            exit(0);
        }

        m_dpi.x = static_cast<float>(x);
        m_dpi.y = static_cast<float>(y);
        m_size.width = (rect.right - rect.left) * 96 / m_dpi.x;
        m_size.height = (rect.bottom - rect.top) * 96 / m_dpi.y;
    }
    catch (const std::exception& e)
    {
        throw std::exception("Ошибка инициализации dx");
    }

    return hr;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJECT6TEXTDX2D, szWindowClass, MAX_LOADSTRING);
    WndClass = MyRegisterClass(hInstance);

    

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT6TEXTDX2D));
    DrawDX2D();//в WM_PAINT жрет ресурсы ЦП, постоянным обновлением экрана
    MSG msg;
    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
          //SetCursor(GetCursor());
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT6TEXTDX2D));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PROJECT6TEXTDX2D);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   const auto hpath = LoadLibraryW(L"user32.dll");//проучаем адрес DLL
   
   CreateWindowInBandEx pCreateWindowInBandEx = CreateWindowInBandEx(GetProcAddress(hpath, "CreateWindowInBandEx"));
   if (!pCreateWindowInBandEx)  MessageBox(GetActiveWindow(), L"Ошибка создания окна CreateWindowInBandEx/ возможно недостаточно прав", L"Title", MB_ICONERROR); //throw std::exception("Ошибка создания объекта CreateWindowInBandEx");


   //hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
   //        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   int iWidth = GetSystemMetrics(SM_CXSCREEN);
   int iHeight = GetSystemMetrics(SM_CYSCREEN);

   hWnd = pCreateWindowInBandEx(WS_EX_NOACTIVATE |
       WS_EX_NOREDIRECTIONBITMAP
       // | WS_EX_LAYERED  
       // | WS_EX_TRANSPARENT, 
       , WndClass, NameWnd, WS_POPUP,
       0, 0, iWidth, iHeight, nullptr, nullptr, hInstance, LPVOID(WndClass), ZBID_UIACCESS, 0);

   if (!hWnd)
   {
      MessageBox(GetActiveWindow(), L"Ошибка создания окна CreateWindowInBandEx/ возможно недостаточно прав или проверте настройки UAC", L"Title", MB_ICONERROR);
     // throw std::exception("Ошибка создания окна CreateWindowInBandEx/недостаточно прав");
      return FALSE;
   }
   Initialize();
   d2_draw.Initialize(hWnd);    
   OpenIniFile.OpenFile("setting.ini");
   Height = OpenIniFile.Height;
   Widght = OpenIniFile.Widght;
   RegisterTouchWindow(hWnd, TWF_WANTPALM);
   SetTabletpenserviceProperties(hWnd);
   UpdateWindow(hWnd);
   ShowWindow(hWnd, nCmdShow);
   SetWindowPos(hWnd, NULL, 0, 0, 500, 120, NULL);
   SetWindowLongW(hWnd, WS_POPUP, WS_EX_NOACTIVATE | //WS_EX_NOREDIRECTIONBITMAP|
      //| WS_EX_LAYERED  
       WS_EX_TRANSPARENT);
   ShowCursor(false);
   return TRUE;
}



//Отображение клавиатуры
void Keybord_em_open()
{
    VisualRender.CLEAR();
    VisualRender.ADD_Button((float)300, (float)0, (float)100, (float)100, L"Close", 0, Keybord_em, 0, FALSE);

    VisualRender.ADD_Button((float)3, (float)336, (float)90, (float)90, L"~", 0xC0, INPUT_KEYBOARD, 41, FALSE);
    VisualRender.ADD_Button((float)94, (float)336, (float)90, (float)90, L"1", 0x31, INPUT_KEYBOARD, 2, FALSE);
    VisualRender.ADD_Button((float)185, (float)336, (float)90, (float)90, L"2", 0x32, INPUT_KEYBOARD, 3, FALSE);
    VisualRender.ADD_Button((float)276, (float)336, (float)90, (float)90, L"3", 0x33, INPUT_KEYBOARD, 4, FALSE);
    VisualRender.ADD_Button((float)367, (float)336, (float)90, (float)90, L"4", 0x34, INPUT_KEYBOARD, 5, FALSE);
    VisualRender.ADD_Button((float)458, (float)336, (float)90, (float)90, L"5", 0x35, INPUT_KEYBOARD, 6, FALSE);
    VisualRender.ADD_Button((float)549, (float)336, (float)90, (float)90, L"6", 0x36, INPUT_KEYBOARD, 7, FALSE);
    VisualRender.ADD_Button((float)640, (float)336, (float)90, (float)90, L"7", 0x37, INPUT_KEYBOARD, 8, FALSE);
    VisualRender.ADD_Button((float)731, (float)336, (float)90, (float)90, L"8", 0x38, INPUT_KEYBOARD, 9, FALSE);
    VisualRender.ADD_Button((float)822, (float)336, (float)90, (float)90, L"9", 0x39, INPUT_KEYBOARD, 10, FALSE);
    VisualRender.ADD_Button((float)913, (float)336, (float)90, (float)90, L"0", 0x30, INPUT_KEYBOARD, 11, FALSE);
    VisualRender.ADD_Button((float)1004, (float)336, (float)90, (float)90, L"-/_", 0xBD, INPUT_KEYBOARD, 12, FALSE);
    VisualRender.ADD_Button((float)1095, (float)336, (float)90, (float)90, L"+/=", 0xBB, INPUT_KEYBOARD, 13, FALSE);
    VisualRender.ADD_Button((float)1186, (float)336, (float)90, (float)90, L"←", 0x08, INPUT_KEYBOARD, 14, FALSE);


    VisualRender.ADD_Button((float)3, (float)427, (float)90, (float)90, L"TAB", 0x09, INPUT_KEYBOARD, 15, FALSE);
    VisualRender.ADD_Button((float)94, (float)427, (float)90, (float)90, L"Q", 0x51, INPUT_KEYBOARD, 16, FALSE);
    VisualRender.ADD_Button((float)185, (float)427, (float)90, (float)90, L"W", 0x57, INPUT_KEYBOARD, 17, FALSE);
    VisualRender.ADD_Button((float)276, (float)427, (float)90, (float)90, L"E", 0x45, INPUT_KEYBOARD, 18, FALSE);
    VisualRender.ADD_Button((float)367, (float)427, (float)90, (float)90, L"R", 0x52, INPUT_KEYBOARD, 19, FALSE);
    VisualRender.ADD_Button((float)458, (float)427, (float)90, (float)90, L"T", 0x54, INPUT_KEYBOARD, 20, FALSE);
    VisualRender.ADD_Button((float)549, (float)427, (float)90, (float)90, L"Y", 0x59, INPUT_KEYBOARD, 21, FALSE);
    VisualRender.ADD_Button((float)640, (float)427, (float)90, (float)90, L"U", 0x55, INPUT_KEYBOARD, 22, FALSE);
    VisualRender.ADD_Button((float)731, (float)427, (float)90, (float)90, L"I", 0x49, INPUT_KEYBOARD, 23, FALSE);
    VisualRender.ADD_Button((float)822, (float)427, (float)90, (float)90, L"O", 0x4F, INPUT_KEYBOARD, 24, FALSE);
    VisualRender.ADD_Button((float)913, (float)427, (float)90, (float)90, L"P", 0x50, INPUT_KEYBOARD, 25, FALSE);
    VisualRender.ADD_Button((float)1004, (float)427, (float)90, (float)90, L"[/{", 0xDB, INPUT_KEYBOARD, 26, FALSE);
    VisualRender.ADD_Button((float)1095, (float)427, (float)90, (float)90, L"]/}", 0xDD, INPUT_KEYBOARD, 27, FALSE);
    VisualRender.ADD_Button((float)1186, (float)427, (float)90, (float)90, L"|", 0xDC, INPUT_KEYBOARD, 43, FALSE);


    VisualRender.ADD_Button((float)3, (float)518, (float)90, (float)90, L"CAPS", 0x14, INPUT_KEYBOARD, 58, FALSE);
    VisualRender.ADD_Button((float)94, (float)518, (float)90, (float)90, L"A", 0x51, INPUT_KEYBOARD, 30, FALSE);
    VisualRender.ADD_Button((float)185, (float)518, (float)90, (float)90, L"S", 0x53, INPUT_KEYBOARD, 31, FALSE);
    VisualRender.ADD_Button((float)276, (float)518, (float)90, (float)90, L"D", 0x44, INPUT_KEYBOARD, 32, FALSE);
    VisualRender.ADD_Button((float)367, (float)518, (float)90, (float)90, L"F", 0x46, INPUT_KEYBOARD, 33, FALSE);
    VisualRender.ADD_Button((float)458, (float)518, (float)90, (float)90, L"G", 0x47, INPUT_KEYBOARD, 34, FALSE);
    VisualRender.ADD_Button((float)549, (float)518, (float)90, (float)90, L"H", 0x48, INPUT_KEYBOARD, 35, FALSE);
    VisualRender.ADD_Button((float)640, (float)518, (float)90, (float)90, L"J", 0x4A, INPUT_KEYBOARD, 36, FALSE);
    VisualRender.ADD_Button((float)731, (float)518, (float)90, (float)90, L"K", 0x4B, INPUT_KEYBOARD, 37, FALSE);
    VisualRender.ADD_Button((float)822, (float)518, (float)90, (float)90, L"L", 0x4C, INPUT_KEYBOARD, 38, FALSE);
    VisualRender.ADD_Button((float)913, (float)518, (float)90, (float)90, L";/:", 0x50, INPUT_KEYBOARD, 39, FALSE);
    VisualRender.ADD_Button((float)1004, (float)518, (float)90, (float)90, L"'", 0xDB, INPUT_KEYBOARD, 40, FALSE);
    VisualRender.ADD_Button((float)1095, (float)518, (float)181, (float)90, L"Enter", 0x0D, INPUT_KEYBOARD, 28, FALSE);


    VisualRender.ADD_Button((float)3, (float)609, (float)90, (float)90, L"Shift", 0x09, INPUT_KEYBOARD, 42, FALSE, D2D1::ColorF((float)0.6, (float)0.5, (float)0.5, (float)10 / 255), TRUE);
    VisualRender.ADD_Button((float)94, (float)609, (float)90, (float)90, L"Z", 0x5A, INPUT_KEYBOARD, 44, FALSE);
    VisualRender.ADD_Button((float)185, (float)609, (float)90, (float)90, L"X", 0x58, INPUT_KEYBOARD, 45, FALSE);
    VisualRender.ADD_Button((float)276, (float)609, (float)90, (float)90, L"C", 0x43, INPUT_KEYBOARD, 46, FALSE);
    VisualRender.ADD_Button((float)367, (float)609, (float)90, (float)90, L"V", 0x56, INPUT_KEYBOARD, 47, FALSE);
    VisualRender.ADD_Button((float)458, (float)609, (float)90, (float)90, L"B", 0x42, INPUT_KEYBOARD, 48, FALSE);
    VisualRender.ADD_Button((float)549, (float)609, (float)90, (float)90, L"N", 0x4E, INPUT_KEYBOARD, 49, FALSE);
    VisualRender.ADD_Button((float)640, (float)609, (float)90, (float)90, L"M", 0x4D, INPUT_KEYBOARD, 50, FALSE);
    VisualRender.ADD_Button((float)731, (float)609, (float)90, (float)90, L"</,", 0xBC, INPUT_KEYBOARD, 51, FALSE);
    VisualRender.ADD_Button((float)822, (float)609, (float)90, (float)90, L">/.", 0xBE, INPUT_KEYBOARD, 52, FALSE);
    VisualRender.ADD_Button((float)913, (float)609, (float)90, (float)90, L"? /", 0xBF, INPUT_KEYBOARD, 53, FALSE);

    VisualRender.ADD_Button((float)3, (float)700, (float)90, (float)90, L"Crtl", 0xA2, INPUT_KEYBOARD, 29, FALSE, D2D1::ColorF((float)0.6, (float)0.5, (float)0.5, (float)10 / 255), TRUE);
    VisualRender.ADD_Button((float)94, (float)700, (float)90, (float)90, L"Win", 0x5B, INPUT_KEYBOARD, 347, FALSE);
    VisualRender.ADD_Button((float)185, (float)700, (float)90, (float)90, L"ALT", 0x12, INPUT_KEYBOARD, 56, FALSE);
    VisualRender.ADD_Button((float)276, (float)700, (float)636, (float)90, L"SPACE", 0x20, INPUT_KEYBOARD, 51, FALSE);
    VisualRender.ADD_Button((float)913, (float)700, (float)90, (float)90, L"DEL", 0x2E, INPUT_KEYBOARD, 339, FALSE);


    VisualRender.ADD_Button((float)1095, (float)609, (float)100, (float)80, L"UP", VK_UP, INPUT_KEYBOARD, 328, FALSE, D2D1::ColorF((float)0.6, (float)0.5, (float)0.5, (float)10 / 255), TRUE);
    VisualRender.ADD_Button((float)1095, (float)700, (float)100, (float)80, L"DOWN", 0x28, INPUT_KEYBOARD, 336, FALSE, D2D1::ColorF((float)0.6, (float)0.5, (float)0.5, (float)10 / 255), TRUE);
    VisualRender.ADD_Button((float)1004, (float)700, (float)100, (float)80, L"LEFT", VK_LEFT, INPUT_KEYBOARD, 331, FALSE, D2D1::ColorF((float)0.6, (float)0.5, (float)0.5, (float)10 / 255), TRUE);
    VisualRender.ADD_Button((float)1186, (float)700, (float)100, (float)80, L"Right", VK_RIGHT, INPUT_KEYBOARD, 333, FALSE, D2D1::ColorF((float)0.6, (float)0.5, (float)0.5, (float)10 / 255), TRUE);

    DrawDX2D();

       // VisualRender.ADD_Button((float)1150, (float)300, (float)100, (float)100, "Return", VK_RETURN, INPUT_KEYBOARD, 28, FALSE);
       // VisualRender.ADD_Button((float)50, (float)50, (float)100, (float)100, "ESC", VK_ESCAPE, INPUT_KEYBOARD, 1, FALSE);
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
//VisualRender.HCLAPS();
    switch (message)
    {

    case WM_POINTERUPDATE:
    {
        GetPointerInfo(GET_POINTERID_WPARAM(wParam), &pointerInfo);
        POINT p = pointerInfo.ptPixelLocation;
        VisualRender.MOVE_POINT(p.x, p.y, pointerInfo.pointerId);
        return 0;
    }
    case WM_GESTURE:
        return 0;
    case WM_POINTERDOWN:
    {
        GetPointerInfo(GET_POINTERID_WPARAM(wParam), &pointerInfo);
        POINT p = pointerInfo.ptPixelLocation;
        if (Run_KEYBORD)
        {
            DWORD Result = VisualRender.Ret_Button(p.x, p.y, pointerInfo.pointerId);
            if (Result == Close_keybord)
            {
                SetWindowPos(hWnd, NULL, 0, 0, 500, 120, NULL);
                Run_KEYBORD = FALSE;
            }
            else if (Result == Keybord_em)
            {
                if (Run_KEYBORD_EM)
                {
                    Run_KEYBORD_EM = false;
                    Gampad();
                    return 0;
                }
                else
                {
                    Run_KEYBORD_EM = true;
                    Keybord_em_open();
                    return 0;
                }
            }else
            {
                return 0;
            }
        }
        else
        {
            Run_KEYBORD = VisualRender.Run_Buttons(p.x, p.y);
            if (Run_KEYBORD)
            {
                Gampad();
                int iWidth = GetSystemMetrics(SM_CXSCREEN);
                int iHeight = GetSystemMetrics(SM_CYSCREEN);
                SetWindowPos(hWnd, NULL, 0, 0, iWidth+20, iHeight+20, NULL);
            }
        }
                            



        return 0;
    }
    case WM_POINTERUP:
    {
    GetPointerInfo(GET_POINTERID_WPARAM(wParam), &pointerInfo);
    POINT p = pointerInfo.ptPixelLocation;
    VisualRender.UP_Button(pointerInfo.pointerId);

    return 0;
    }
    case WM_POINTERLEAVE:
        return 0;
    case WM_SETCURSOR:
        return 0;
    case WM_SETFOCUS:
        return 0;
    case WM_POINTERENTER:
        return 0;
    case WM_INPUT:
        return 0;
    case WM_POINTERCAPTURECHANGED:
        return 0;
    case WM_LBUTTONDOWN:
        return 0;
    case WM_LBUTTONUP:
        return 0;
    case WM_MOUSEMOVE:
        return 0;
    case WM_MOUSEHOVER:
        return 0;
    case WM_MOUSELEAVE:
        return 0;
    case WM_NCMOUSEMOVE:
        return 0;
    case WM_NCMOUSEHOVER:
        return 0;
    case WM_LBUTTONDBLCLK:
        return 0;
    case WM_MBUTTONDBLCLK:
        return 0;
    case WM_MBUTTONDOWN:
        return 0;
    case WM_MBUTTONUP:
        return 0;
    case WM_RBUTTONDBLCLK:
        return 0;
    case WM_RBUTTONDOWN:
        return 0;
    case WM_RBUTTONUP:
        return 0;

    case WM_TABLET_QUERYSYSTEMGESTURESTATUS:
    {
        return TABLET_DISABLE_PRESSANDHOLD;
    }
 

    case WM_SIZE:
    {
        int iWidth = GetSystemMetrics(SM_CXSCREEN);
        int iHeight = GetSystemMetrics(SM_CYSCREEN);
        VisualRender.CLEAR();
        float  temp_x = (float)iHeight / (float)Height;
        float  temp_y = (float)iWidth / (float)Widght;
        VisualRender.Scale_x = temp_y;
        VisualRender.Scale_y = temp_x;
        
        DrawDX2D();
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


