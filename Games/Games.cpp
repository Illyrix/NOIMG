// Games.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "gameClass.h"
int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleTitle(L"�еõ��۵���Ϸ");    //���ÿ���̨����ı���
	wchar_t inputWchar[256];          //���ֽڻ���
	bool load;		//�Ƿ��ȡ����
	while (1)
	{
		std::wcout << L">Continue Or Not [Y/N]:";
		std::wcin.getline(inputWchar, 256);
		CString input = inputWchar;
		if ((input == L"Y") || (input == L"y"))
		{
			load=true;
			break;
		}
		if ((input == L"N") || (input == L"n"))
		{
			load = false;
			break;
		}
		std::wcout<<L">Input Invalid!"<<std::endl;
	}
	gameClass &mainGame = *gameClass::createObj(load);
	while (gameClass::out)
	{
		std::wcout << L">";
		std::wcin.getline(inputWchar, 256);
		CString input = inputWchar;
		std::wcout << (LPCTSTR)mainGame.exe(input) << std::endl;
	}
	return 0;
}