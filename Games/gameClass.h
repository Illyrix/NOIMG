#pragma once
#include "command.h"
#include "maptree.h"

class gameClass
{
private:

	std::deque<command> LIST_OF_COMMAND;
	//在这里添加私有成员
	maptree* now_tree;
	std::list<maptree> all_trees;

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



		//这里添加希望游戏一开始处理的代码
		if (load)
		{
			//从存档中读取
			CString buffers;
			int length=(GetPrivateProfileString(L"maps",L"lists",NULL, (LPWSTR)(LPCWSTR)buffers,65535,L".\\config.ini"));
			int lists = _ttoi(buffers);
			GetPrivateProfileString(L"maps", L"nowmap", NULL, (LPWSTR)(LPCWSTR)buffers, 65535, L".\\config.ini");
			int nowmap = _ttoi(buffers);
			for (int i = 0; i < lists; i++)
			{
				CString mapname;
				mapname.Format(_T("%d"),i);
				mapname = L"map" + mapname;
				std::wcout << (LPCTSTR)mapname<<std::endl;
				length= (GetPrivateProfileSection(mapname, (LPWSTR)(LPCWSTR)buffers, 65535, L".\\config.ini"));
				if ((buffers[0]=='\0'))
				{
					std::wcout << L"存档损坏"<<std::endl;			//读取失败
					out = 0;
				}
				else
				{
					int j=0;
					int another_NULL = 1;
					std::map<CString,CString> keyValueMap;
					std::deque<CString> keyvalue;
					CString temp;
					do {
						if (buffers[j] != L'\0')
							temp += buffers[j];
						else
						{
							keyvalue.push_back(temp);
							temp.Empty();
						}
						j++;
					} while ((buffers[j - 1] != L'\0') || (buffers[j] != L'\0'));//分割成键/值对的队列
					for (auto k = keyvalue.begin(); k != keyvalue.end(); k++)
					{
						int devide_pos = k->Find(_T(" "));
						CString key_str = k->Left(devide_pos);
						CString value_str = k->Right(k->GetLength() - devide_pos - 1);
						keyValueMap.insert(std::pair<CString,CString>(key_str,value_str));
					}
					maptree temp_maptree(keyValueMap);
					all_trees.push_back(temp_maptree);
					if (nowmap == i)
						now_tree = &(*(all_trees.rend()));
				}
			}
			std::wcout<<(LPCTSTR)now_tree->getFeature(L"name");
		}
		else
		{
			//新建游戏
		}
	};	
public:
	static bool out;       //循环控制
	static gameClass* createObj(bool load)	//单例模式
	{
		static gameClass m_Init(load);
		return &m_Init;
	}
	CString exe(CString);

	/*~gameClass()	//析构函数，在其中添加自动保存等功能
	{
		
	}*/
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