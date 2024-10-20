#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <codecvt>
#include <windows.h>
#include <sstream>
#include <d2d1.h>
#include "VisualKaybord.h"



struct BootonLoad
{
	FLOAT x;
	FLOAT y;
	FLOAT height;
	FLOAT Widght;
	std::wstring text;
	WORD push_button;
	DWORD Type_key; 
	DWORD scankey; 
	BOOL Move_button;
	D2D1_COLOR_F d2dColor = D2D1::ColorF((float)0.6, (float)0.5, (float)0.5, (float)10 / 255);
	BOOL ExtendKey = FALSE;
};

class OpenFileINI
{
public:
	int Height;
	int Widght;
	VOID OpenFile(std::string filesetting = "setting.ini");
	VOID Cal_line();
	WORD StringToWord(std::string stringw);
	DWORD StringToDWord(std::string stringw);
	DWORD StringToIntToDWord(std::string stringw);
	HRESULT setstructVectButton(VisualKaybord* Button);
	std::vector<BootonLoad> ButtonRun;
private:
	std::vector<std::wstring> v_Line;
};

