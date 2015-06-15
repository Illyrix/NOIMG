#pragma once
#include "command.h"
#include "maptree.h"

class gameClass
{
private:

	std::deque<command> LIST_OF_COMMAND;
	//在这里添加命令的实现



	CString exit(CString param)
	{
		std::wcout << (LPCTSTR)L">exit running.param : "<< (LPCTSTR)param<<std::endl;
		out = 0;
		return L">Done!";
	}


	CString ls(CString param)
	{
		std::wcout << (LPCTSTR)L">ls running.param : " << (LPCTSTR)param << std::endl;
		return L">Done!";
	}







	gameClass(bool load)
	{
		//新建命令从这里新建

		LIST_OF_COMMAND.push_back(*new command(L"exit", &gameClass::exit));
		LIST_OF_COMMAND.push_back(*new command(L"ls", &gameClass::ls));
	};	
public:
	static bool out;       //循环控制
	static gameClass* createObj(bool load)
	{
		static gameClass m_Init(load);
		return &m_Init;
	}
	CString exe(CString);

	~gameClass()	//析构函数，在其中添加自动保存等功能
	{
		
	}
};
bool gameClass::out = true;

CString gameClass::exe(CString input)
	{
		//分离命令和参数
		int content_pos = input.Find(_T(" "));
		if (content_pos == -1)
			content_pos = input.GetLength();
		CString command_str = input.Left(content_pos);
		CString content_str = input.Right(input.GetLength() - content_pos - 1);
		content_str.TrimLeft(L" ");
		//遍历所有命令
		for (auto i = LIST_OF_COMMAND.begin(); i != LIST_OF_COMMAND.end(); i++)
		{
			if (i->name == command_str)
				return (this->*(i->function))(content_str);  //返回运行结果
		}
		return L">Command Invalid:" + command_str;
	}