#pragma once
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows
#include <windows.h>
#include <string>
#include <vector>
#include <winuser.h>
// Файлы заголовков среды выполнения C

#include <WinUser.h>
#include "d2d_draw.h"

#include <string>

#include <initguid.h>
//#include <Objbase.h>

#define Exit_program 10
#define Close_keybord 20
#define Keybord_em (DWORD)22

struct button_run {
	INPUT push_button[1];
	int x;
	int y;
	int x_2;
	int y_2;
	BOOL Move_Button;
};

struct buttons_visual {

	FLOAT x;
	FLOAT y;
	FLOAT height;
	FLOAT Widgth;
	std::wstring text;
	const int size_name_Button;
	D2D1_COLOR_F d2dColor;
};



struct clutch_button
{
	DWORD IDPoint;
	BOOL Move_button;
	BOOL Buttons;
	int x;
	int y;
	INPUT push_button[1];
	INPUT MOUSE_move[1] = {};
};


class VisualKaybord
{
public:
	HRESULT init();
	HRESULT ADD_Button(FLOAT x, FLOAT y, FLOAT height, FLOAT Width, std::wstring text, WORD push_button, DWORD Type_key, DWORD scankey, BOOL Move_button, D2D1_COLOR_F d2dColor = D2D1::ColorF((float)0.6, (float)0.5, (float)0.5, (float)10 / 255), BOOL ExtendKey = FALSE);
	HRESULT Ret_Button(int mouse_position_x, int mouse_position_y, DWORD IDTOCH);
	HRESULT RenderButton(D2D_DRAW & d2_draw_in);
	HRESULT UP_Button(DWORD IDTOCH);
	HRESULT MOVE_POINT(int mouse_position_x, int mouse_position_y, DWORD IDTOCH);
	BOOL Run_Buttons(int mouse_position_x, int mouse_position_y);
	VOID CLEAR();
	VOID HCLAPS();

	float Scale_x = 1;
	float Scale_y = 1;
	bool Push_RUN = FALSE;
	POINT positionbuttonrun;
	POINT EXITPROGRAM;
	int S_whell = 20;
	~VisualKaybord();
private:
	button_run* pointer_ButtonStruct_r;
	button_run* pointer_end_ButtonStruct_r;
	std::vector<clutch_button>::iterator it_clutch_buttons;
	std::vector<buttons_visual> AddButtonStruct_Visual;
	std::vector<button_run> ButtonStruct_r;
	std::vector<clutch_button> clutch_buttons;
	HWND WinFocus;
	DWORD idWinFocus;
	DWORD idProgram;
	POINT POINTCURSOR;
	INPUT buttonsM[1];
	INPUT TempbuttonsM[1];
	BOOL initilize = false;
	int size_struct_1 = 0;
	DWORD mousemovetemp_w;
	int mousemovetemp_i;
	INPUT inpustsMouse;
};


