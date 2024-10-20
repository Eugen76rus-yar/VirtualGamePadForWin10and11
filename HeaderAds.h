#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <string>
#include <d2d1_2.h>
#include <dxgi1_3.h>
#include <dcomp.h>
#include <ddraw.h>
#include <d3d9.h>
#include <d3d11_2.h>
#include <dwmapi.h>
#include <vector>
#include <chrono>
#include <thread>
#include <wtsapi32.h>
#include <winapifamily.h>
#include <hidusage.h>
#include <shellscalingapi.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <strsafe.h>
#include <Psapi.h>
#include <sddl.h>
#include <WinUser.h>
#include <Mmsystem.h>
#pragma comment(lib, "Shcore.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "dcomp.lib")
#pragma comment(lib, "Imm32.lib")
#pragma comment(lib,"Winmm.lib")
#include "D2D_DRAW.h"
#include "VisualKaybord.h"
#include <WinUser.h>
#include <tpcshrd.h>
#include "OpenFileINI.h"



#define TABLET_DISABLE_PRESSANDHOLD        0x00000001
#define TABLET_DISABLE_PENTAPFEEDBACK      0x00000008
#define TABLET_DISABLE_PENBARRELFEEDBACK   0x00000010
#define TABLET_DISABLE_TOUCHUIFORCEON      0x00000100
#define TABLET_DISABLE_TOUCHUIFORCEOFF     0x00000200
#define TABLET_DISABLE_TOUCHSWITCH         0x00008000
#define TABLET_DISABLE_FLICKS              0x00010000
#define TABLET_ENABLE_FLICKSONCONTEXT      0x00020000
#define TABLET_ENABLE_FLICKLEARNINGMODE    0x00040000
#define TABLET_DISABLE_SMOOTHSCROLLING     0x00080000
#define TABLET_DISABLE_FLICKFALLBACKKEYS   0x00100000
#define TABLET_ENABLE_MULTITOUCHDATA       0x01000000


VisualKaybord VisualRender;
D2D_DRAW d2_draw;
//D2D_DRAW d2_draw;
int nTimerID;
OpenFileINI OpenIniFile;

template <class T> void  SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}


const DWORD dwHwndTabletProperty =
TABLET_DISABLE_PRESSANDHOLD | // disables press and hold (right-click) gesture
TABLET_DISABLE_PENTAPFEEDBACK | // disables UI feedback on pen up (waves)
TABLET_DISABLE_PENBARRELFEEDBACK | // disables UI feedback on pen button down (circle)
TABLET_DISABLE_TOUCHUIFORCEON |
TABLET_DISABLE_TOUCHSWITCH |
TABLET_DISABLE_SMOOTHSCROLLING |
TABLET_DISABLE_FLICKFALLBACKKEYS |
TABLET_DISABLE_FLICKS; // disables pen flicks (back, forward, drag down, drag up)

void SetTabletpenserviceProperties(HWND hWnd) {
    ATOM atom = ::GlobalAddAtom(MICROSOFT_TABLETPENSERVICE_PROPERTY);
    ::SetProp(hWnd, MICROSOFT_TABLETPENSERVICE_PROPERTY, reinterpret_cast<HANDLE>(dwHwndTabletProperty));
    ::GlobalDeleteAtom(atom);
}



