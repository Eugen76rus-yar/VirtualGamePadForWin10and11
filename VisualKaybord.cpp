#include "VisualKaybord.h"              
DEFINE_GUID(CLSID_UIHostNoLaunch,
	0x4CE576FA, 0x83DC, 0x4f88, 0x95, 0x1C, 0x9D, 0x07, 0x82, 0xB4, 0xE3, 0x76);

// 37c994e7_432b_4834_a2f7_dce1f13b834b
DEFINE_GUID(IID_ITipInvocation,
	0x37c994e7, 0x432b, 0x4834, 0xa2, 0xf7, 0xdc, 0xe1, 0xf1, 0x3b, 0x83, 0x4b);

struct ITipInvocation : IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE Toggle(HWND wnd) = 0;
};

int runkeybordwon()//клавиатура win 
{
	HRESULT hr;
	hr = CoInitialize(0);

	ITipInvocation* tip;
	hr = CoCreateInstance(CLSID_UIHostNoLaunch, 0, CLSCTX_INPROC_HANDLER | CLSCTX_LOCAL_SERVER, IID_ITipInvocation, (void**)&tip);
	tip->Toggle(GetDesktopWindow());
	tip->Release();
	return 0;
}



void PUSH_BUTTON()
{
	keybd_event(VK_UP, 0, 0, 0);
}





HRESULT VisualKaybord::init()
{
	return S_OK;
}

HRESULT VisualKaybord::ADD_Button(FLOAT x, FLOAT y, FLOAT height, FLOAT Width, std::wstring text, WORD push_button, DWORD Type_key, DWORD scankey, BOOL Move_button, D2D1_COLOR_F d2dColor, BOOL ExtendKey)
{
	INPUT Key[1];
	Key[0].type = Type_key;
	if (Type_key == INPUT_KEYBOARD)
	{
		if (ExtendKey)
		{
			Key[0].ki.dwFlags =  KEYEVENTF_EXTENDEDKEY |
				KEYEVENTF_SCANCODE;
		}
		else
		{
			Key[0].ki.dwFlags = // KEYEVENTF_EXTENDEDKEY |
				KEYEVENTF_SCANCODE;
		}
		Key[0].ki.wVk = push_button;
		Key[0].ki.wScan = scankey;
	}
	if (Type_key == INPUT_MOUSE)
	{
		Key[0].mi.dwFlags = push_button;
		Key[0].mi.time = 0;
		Key[0].mi.dwExtraInfo = 0;
		Key[0].mi.mouseData = 0;
		Key[0].mi.dx = 0;
		Key[0].mi.dy = 0;
	}

	int size_text = text.length();
	AddButtonStruct_Visual.push_back({ (x*Scale_x) , (y * Scale_y) , (height * Scale_y) , (Width * Scale_x) , text , size_text ,d2dColor });
	int ix = x * Scale_x;
	int iy = y * Scale_y;
	int ix2 = (x + Width) * Scale_x;
	int iy2 = (y + height) * Scale_y;
	ButtonStruct_r.push_back({ Key[0], ix, iy, ix2, iy2,Move_button });
	pointer_end_ButtonStruct_r = &ButtonStruct_r[0] + ButtonStruct_r.size();
	return S_OK;
}

HRESULT VisualKaybord::Ret_Button(int mouse_position_x, int mouse_position_y, DWORD IDTOCH)
{
	pointer_ButtonStruct_r = &ButtonStruct_r[0]; 
	while(pointer_ButtonStruct_r != pointer_end_ButtonStruct_r)
	{
		if (mouse_position_x > pointer_ButtonStruct_r->x and mouse_position_y > pointer_ButtonStruct_r->y and mouse_position_y < pointer_ButtonStruct_r->y_2 and mouse_position_x < pointer_ButtonStruct_r->x_2)

		{

			
			if (pointer_ButtonStruct_r->push_button[0].type == Exit_program)
			{
				exit(0);
			}
			else if (pointer_ButtonStruct_r->push_button[0].type == Close_keybord)
			{
				Scale_x = 1;
				Scale_y = 1;
				Push_RUN = FALSE;

				//size_struct_1 = 0;
				return Close_keybord;
			}if (//ButtonStruct_r[count].push_button[0].type == INPUT_MOUSE and 
				pointer_ButtonStruct_r->push_button[0].mi.dwFlags == MOUSEEVENTF_WHEEL)
			{
				clutch_buttons.push_back({ IDTOCH,pointer_ButtonStruct_r->Move_Button , TRUE, mouse_position_x,mouse_position_y,pointer_ButtonStruct_r->push_button[0] });

				//size_struct_1++;
				return 0;
			}
			if (pointer_ButtonStruct_r->push_button[0].type == (DWORD)21)
			{
				runkeybordwon();
				return 0;
			}
			if (pointer_ButtonStruct_r->push_button[0].type == Keybord_em)
			{
				return Keybord_em;
			}
			
			clutch_buttons.push_back({ IDTOCH,pointer_ButtonStruct_r->Move_Button, TRUE, mouse_position_x,mouse_position_y,pointer_ButtonStruct_r->push_button[0],inpustsMouse });
				SendInput(1, pointer_ButtonStruct_r->push_button, sizeof(pointer_ButtonStruct_r->push_button));
				//size_struct_1++;
				return(0);
	
		}
		++pointer_ButtonStruct_r;
				
	};
	//size_struct_1++;
	clutch_buttons.push_back({ IDTOCH,TRUE, TRUE, mouse_position_x,mouse_position_y,{},inpustsMouse });

	return 0;
}




HRESULT VisualKaybord::RenderButton(D2D_DRAW& d2_draw_in)
{
	if (Push_RUN)
	{
		int size_struct = AddButtonStruct_Visual.size();
		for (int count = 0; count < size_struct; count++)
		{

			d2_draw_in.Rectangle(AddButtonStruct_Visual[count].x, AddButtonStruct_Visual[count].y, AddButtonStruct_Visual[count].height, AddButtonStruct_Visual[count].Widgth, D2D1::ColorF((float)0.5, (float)0.5, (float)0.5, (float)200 / 255), AddButtonStruct_Visual[count].text.c_str(), AddButtonStruct_Visual[count].size_name_Button);
		}
		return S_OK;
	}
	else
	{
		EXITPROGRAM.x = 300;
		EXITPROGRAM.y = 0;
		d2_draw_in.Rectangle(EXITPROGRAM.x, EXITPROGRAM.y, 100, 200, D2D1::ColorF((float)0.6, (float)0.5, (float)0.5, (float)150 / 255), L"EXIT", 4);
		d2_draw_in.Rectangle(positionbuttonrun.x, positionbuttonrun.y, 100, 200, D2D1::ColorF((float)0.5, (float)0.5, (float)0.8, (float)150 / 255), L"RUN", 3);
	}
	if (!initilize)
	{
		inpustsMouse.type = INPUT_MOUSE;
		inpustsMouse.mi.dwFlags = MOUSEEVENTF_MOVE;
		inpustsMouse.mi.time = 0;
		inpustsMouse.mi.dwExtraInfo = 0;
		inpustsMouse.mi.mouseData = 0;

		TempbuttonsM[0].type = INPUT_MOUSE;
		TempbuttonsM[0].mi.dwFlags = MOUSEEVENTF_WHEEL;
		TempbuttonsM[0].mi.time = NULL;
		TempbuttonsM[0].mi.dwExtraInfo = 0;
		TempbuttonsM[0].mi.mouseData = 0;
		initilize = TRUE;
	}

	return S_OK;
}

HRESULT VisualKaybord::UP_Button(DWORD IDTOCH)
{
	std::vector<clutch_button>::iterator it_clutch_buttons_Del;
	it_clutch_buttons_Del = std::find_if(clutch_buttons.begin(), clutch_buttons.end(), [&](clutch_button s) { return s.IDPoint == IDTOCH; });
	if (it_clutch_buttons_Del == clutch_buttons.end())
	{
		return 0;
	}

			if (it_clutch_buttons_Del->push_button[0].type == INPUT_MOUSE and it_clutch_buttons_Del->push_button[0].mi.dwFlags != MOUSEEVENTF_MOVE and it_clutch_buttons_Del->push_button[0].mi.dwFlags != MOUSEEVENTF_WHEEL)
			{
				//DWORD test = 0x0002;
				it_clutch_buttons_Del->push_button[0].mi.dwFlags = it_clutch_buttons_Del->push_button[0].mi.dwFlags *2;
				SendInput(1, it_clutch_buttons_Del->push_button, sizeof(it_clutch_buttons_Del->push_button));
			}
			else  
			{        
				if (it_clutch_buttons_Del->push_button[0].type == INPUT_KEYBOARD)
				{
					it_clutch_buttons_Del->push_button[0].ki.dwFlags = it_clutch_buttons_Del->push_button[0].ki.dwFlags | KEYEVENTF_KEYUP;
						//| KEYEVENTF_EXTENDEDKEY 
						//| KEYEVENTF_SCANCODE;
					SendInput(1, it_clutch_buttons_Del->push_button, sizeof(it_clutch_buttons_Del->push_button));
				}
				else
				{

				}
			}
			size_struct_1--;
			clutch_buttons.erase(it_clutch_buttons_Del);

	return E_NOTIMPL;
}

HRESULT VisualKaybord::MOVE_POINT(int mouse_position_x, int mouse_position_y, DWORD IDTOCH)
{
	if (it_clutch_buttons->IDPoint == IDTOCH)
	{
		if (it_clutch_buttons->Move_button)
		{
			it_clutch_buttons->MOUSE_move[0].mi.dx = mouse_position_x - it_clutch_buttons->x;
			it_clutch_buttons->MOUSE_move[0].mi.dy = mouse_position_y - it_clutch_buttons->y;
			//			if (clutch_buttons[count].MOUSE_move[0].mi.dx < 80)
			//			{
			SendInput(1, it_clutch_buttons->MOUSE_move, sizeof(it_clutch_buttons->MOUSE_move));

			it_clutch_buttons->x = mouse_position_x;
			it_clutch_buttons->y = mouse_position_y;
			//			}
						//mouse_event(MOUSEEVENTF_MOVE, (mouse_position_x - clutch_buttons[count].x), (mouse_position_y - clutch_buttons[count].y), NULL, NULL);
					//	SendInput(1, clutch_buttons[count].MOUSE_move, sizeof(clutch_buttons[count].MOUSE_move));

			return 0;
		}
		else if (it_clutch_buttons->push_button[0].mi.dwFlags == MOUSEEVENTF_WHEEL)
		{
			if ((mouse_position_y - it_clutch_buttons->y) > S_whell)
			{

				TempbuttonsM[0].mi.mouseData = (DWORD)120;
				SendInput(1, TempbuttonsM, sizeof(TempbuttonsM));


				it_clutch_buttons->y = mouse_position_y;

				return 0;
			}
			else if ((mouse_position_y - it_clutch_buttons->y) < -S_whell)
			{
				TempbuttonsM[0].mi.mouseData = (DWORD)-120;
				SendInput(1, TempbuttonsM, sizeof(TempbuttonsM));
				it_clutch_buttons->y = mouse_position_y;
				return 0;
			}
			return 0;
		}

		return 0;

	}
	it_clutch_buttons = std::find_if(clutch_buttons.begin(), clutch_buttons.end(), [&](clutch_button s) { return s.IDPoint == IDTOCH; });
	if (it_clutch_buttons == clutch_buttons.end())
	{
		return 0;
	}
		if (it_clutch_buttons->Move_button)
		{
			it_clutch_buttons->MOUSE_move[0].mi.dx = mouse_position_x - it_clutch_buttons->x;
			it_clutch_buttons->MOUSE_move[0].mi.dy = mouse_position_y - it_clutch_buttons->y;
			//			if (clutch_buttons[count].MOUSE_move[0].mi.dx < 80)
			//			{
			SendInput(1, it_clutch_buttons->MOUSE_move, sizeof(it_clutch_buttons->MOUSE_move));

			it_clutch_buttons->x = mouse_position_x;
			it_clutch_buttons->y = mouse_position_y;
			//			}
						//mouse_event(MOUSEEVENTF_MOVE, (mouse_position_x - clutch_buttons[count].x), (mouse_position_y - clutch_buttons[count].y), NULL, NULL);
					//	SendInput(1, clutch_buttons[count].MOUSE_move, sizeof(clutch_buttons[count].MOUSE_move));

			return 0;
		}
		else if (it_clutch_buttons->push_button[0].mi.dwFlags == MOUSEEVENTF_WHEEL)
		{
			if ((mouse_position_y - it_clutch_buttons->y) > S_whell)
			{

				//TempbuttonsM[0].mi.dx = 0;
				//TempbuttonsM[0].mi.dy = 0;
				TempbuttonsM[0].mi.mouseData = (DWORD)120;
				SendInput(1, TempbuttonsM, sizeof(TempbuttonsM));
				//
				//mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 120, 0);

				it_clutch_buttons->y = mouse_position_y;

				return 0;
			}
			else if ((mouse_position_y - it_clutch_buttons->y) < -S_whell)
			{
				TempbuttonsM[0].mi.mouseData = (DWORD)-120;
				SendInput(1, TempbuttonsM, sizeof(TempbuttonsM));
				//mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -120, 0);
				it_clutch_buttons->y = mouse_position_y;
				return 0;
			}
			return 0;
		}

		return 0;


}

BOOL VisualKaybord::Run_Buttons(int mouse_position_x, int mouse_position_y)
{
	if (positionbuttonrun.x < mouse_position_x and positionbuttonrun.y < mouse_position_y and (positionbuttonrun.x + 200) > mouse_position_x and (positionbuttonrun.y + 100) > mouse_position_y)
	{
		Push_RUN = TRUE;
		return TRUE;
	};
	if (EXITPROGRAM.x < mouse_position_x and EXITPROGRAM.y < mouse_position_y and (EXITPROGRAM.x + 200) > mouse_position_x and (EXITPROGRAM.y + 100) > mouse_position_y)
	{
		exit(0);
	}
	return false;
}

VOID VisualKaybord::CLEAR()
{
	AddButtonStruct_Visual.clear();
	ButtonStruct_r.clear();
	return VOID();
}

VOID VisualKaybord::HCLAPS()
{
	int size_struct = clutch_buttons.size();
	for (int count = 0; count < size_struct; count++)
	{
		if (clutch_buttons[count].push_button[0].type == INPUT_KEYBOARD)
		{
			clutch_buttons[count].push_button[0].ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
			SendInput(ARRAYSIZE(clutch_buttons[count].push_button), clutch_buttons[count].push_button, sizeof(clutch_buttons[count].push_button));
		}
		else
		{
			//mouse_event(clutch_buttons[count].push_button[0].type, 0, 0, NULL, NULL);
		};
	};
}




VisualKaybord::~VisualKaybord()
{
	//keybd_event(VK_UP, 0, 0, 0);
}

//x;
//FLOAT y;
//FLOAT height;
//FLOAT Width;
//std::string text;
//INPUT push_button;


