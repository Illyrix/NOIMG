#pragma once
#include <Windows.h>
#include <atlstr.h>
#include <deque>
#include <iostream>
class gameClass;
class command
{
public:
	CString name;
	CString(gameClass::*function)(CString);
	command(CString name_in, CString(gameClass::*p)(CString))
	{
		name = name_in;
		function = p;
	}
};
