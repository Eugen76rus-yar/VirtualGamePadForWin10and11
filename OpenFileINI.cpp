#include "OpenFileINI.h"
#define test_true(object)((object==L"true") ? (TRUE) : (FALSE))

VOID OpenFileINI::OpenFile(std::string filesetting)
{
	std::locale l_utf8(std::locale(), new std::codecvt_utf8<wchar_t, 0x10ffffUL, std::codecvt_mode::consume_header>);
	std::wifstream  file_setting(filesetting);
	file_setting.imbue(l_utf8);
	std::wstring line;
	if (file_setting.is_open())
	{
		while (getline(file_setting, line))
		{
			//v_Line.push_back(line);
			//std::string string_temp (line.begin(), line.end());
			v_Line.push_back(line);
		}
	}
	else
	{
		int sleep = MessageBox(GetActiveWindow(), L"Error open setting.ini", L"Error", MB_ICONERROR);
		exit(0);
		return;
	}
	Cal_line();
	return;
}

VOID OpenFileINI::Cal_line()
{
	int size_struct = v_Line.size();
	BootonLoad tempStruct;
	std::vector<std::wstring> tempstre;
	for (int count = 0; count < size_struct; count++)
	{
		std::wstring line_count = v_Line[count];
		int count_char = line_count.size();
		if (count == 0)
		{
			std::size_t position_sim = line_count.find(L":",0);
			Height = std::stoi(line_count.substr(0, position_sim));
			int size = line_count.size();
			Widght = std::stoi(line_count.substr((position_sim+1), size));
			
		}
		else
		{
			std::size_t postiton_sim;
			std::size_t count_string = 0;
			int testcycle = 0;
			while (testcycle < 1000)
			{
				postiton_sim = line_count.find(L";", count_string);
					if (postiton_sim != std::string::npos)
					{
						tempstre.push_back(line_count.substr(count_string, (postiton_sim- count_string)));
					}
					else
					{
						tempstre.push_back(line_count.substr(count_string, (line_count.size()- count_string)));
						break;
					}
				testcycle++;
				count_string = postiton_sim+1;
				if (testcycle > 1000)
				{
					int sleep = MessageBox(GetActiveWindow(), L"ini parsing error if size > 1000", L"Error", MB_ICONERROR);
					exit(0);
					break;

				}

			}
			int size_tempstre = tempstre.size();
			if (size_tempstre == 9)
			{
				ButtonRun.push_back({ std::stof(tempstre[0]), std::stof(tempstre[1]), std::stof(tempstre[2]), std::stof(tempstre[3]), tempstre[4], StringToWord(std::string(tempstre[5].begin(),tempstre[5].end())),StringToDWord(std::string(tempstre[6].begin(),tempstre[6].end())),StringToIntToDWord(std::string(tempstre[7].begin(),tempstre[7].end())),test_true(tempstre[8]) });
					//StringToWord(tempstre[5]), StringToDWord(tempstre[6]), StringToIntToDWord(tempstre[7]), test_true(tempstre[8]) });
				tempstre.clear();
				//ButtonRun.push_back({ (float)110, (float)430, (float)100, (float)80, "UP", VK_UP, INPUT_KEYBOARD, 328, FALSE, (float)0.6, (float)0.5, (float)0.5, (float)150 / 255, TRUE });
			}
			else if (size_tempstre == 13)
			{
				ButtonRun.push_back({ std::stof(tempstre[0]), std::stof(tempstre[1]), std::stof(tempstre[2]), std::stof(tempstre[3]), tempstre[4],  StringToWord(std::string(tempstre[5].begin(),tempstre[5].end())),StringToDWord(std::string(tempstre[6].begin(),tempstre[6].end())),StringToIntToDWord(std::string(tempstre[7].begin(),tempstre[7].end())), test_true(tempstre[8]),D2D1::ColorF(std::stof(tempstre[9]), std::stof(tempstre[10]), std::stof(tempstre[11]), (std::stof(tempstre[12]))/255) });
				tempstre.clear();
			
			}
			else if (size_tempstre == 14)
			{
				ButtonRun.push_back({ std::stof(tempstre[0]), std::stof(tempstre[1]), std::stof(tempstre[2]), std::stof(tempstre[3]), tempstre[4],  StringToWord(std::string(tempstre[5].begin(),tempstre[5].end())),StringToDWord(std::string(tempstre[6].begin(),tempstre[6].end())),StringToIntToDWord(std::string(tempstre[7].begin(),tempstre[7].end())), test_true(tempstre[8]),D2D1::ColorF(std::stof(tempstre[9]), std::stof(tempstre[10]), std::stof(tempstre[11]), (std::stof(tempstre[12])) / 255), test_true(tempstre[13]) });
				tempstre.clear();
			}else
			{
			
				int sleep = MessageBox(GetActiveWindow(), L"ini parsing error", L"Error", MB_OK);
				exit(0);
				break;
			}
			


		}
		
	}
	int a = 0;
	return VOID();
}

WORD OpenFileINI::StringToWord(std::string stringw)
{
	WORD TempD;
	std::stringstream strings;
	strings << std::hex << stringw;
	strings >> TempD;

	return TempD;
}

DWORD OpenFileINI::StringToDWord(std::string stringw)
{
	DWORD TempD;
	std::stringstream strings;
	strings << std::hex << stringw;
	strings >> TempD;

	return TempD;
}

DWORD OpenFileINI::StringToIntToDWord(std::string stringw)
{
	DWORD TempD;
	int temp = std::stoi(stringw);
	TempD = temp;
	return TempD;
}

HRESULT OpenFileINI::setstructVectButton(VisualKaybord* Button)
{
	int size_ButtonRun = ButtonRun.size();
	for (int count = 0; count < size_ButtonRun; count++)
	{
		Button->ADD_Button(ButtonRun[count].x, ButtonRun[count].y, ButtonRun[count].height, ButtonRun[count].Widght, ButtonRun[count].text, ButtonRun[count].push_button, ButtonRun[count].Type_key, ButtonRun[count].scankey, ButtonRun[count].Move_button, ButtonRun[count].d2dColor, ButtonRun[count].ExtendKey);
		
	}
	return 0;
}





