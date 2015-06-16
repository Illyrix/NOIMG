#pragma once
#include "command.h"
#include "maptree.h"

class gameClass
{
private:

	std::deque<command> LIST_OF_COMMAND;
	maptree* findByname(CString treename)
	{
		for (auto i = all_trees.begin(); i != all_trees.end(); i++)
		{
			if (treename == i->name)
				return &(*i);
		}
		return NULL;
	}
	//在这里添加私有成员
	maptree* now_tree;
	std::list<maptree> all_trees;

	//在这里添加命令的实现

	CString cls(CString param)
	{
		system("cls");
		return L"";
	}

	CString exit(CString param)
	{
		//std::wcout << (LPCTSTR)L">exit running.param : "<< (LPCTSTR)param<<std::endl;
		out = 0;
		return L">Done!";
	}


	CString ls(CString param)
	{
		CString printout;
		std::list<maptree*> now_map=now_tree->getChildren();
		for (auto i = now_map.begin(); i != now_map.end(); i++)
		{
			printout += ((*i)->name+" ");
		}
		return printout;
	}
	CString cd(CString param)
	{
		int devidepos = param.FindOneOf(_T("\\\/"));
		while (devidepos != -1)
		{
			CString data = param.Left(devidepos);
			if (data == L"..")
			{
				now_tree = now_tree->getFather();
			}
			else
			{
				std::list<maptree*> now_map = now_tree->getChildren();
				maptree* goto_tree=now_tree;
				for (auto i = now_map.begin(); i != now_map.end(); i++)
				{
					if ((*i)->name == data)
						goto_tree = *i;
				}
				if (now_tree == goto_tree)
					return L"Invalid Param :" + data;
				else
					now_tree = goto_tree;
			}
			param = param.Right(param.GetLength() - devidepos - 1);
			devidepos = param.FindOneOf(_T("\\\/"));
		}
		CString data = param;
		if (data == L"..")
		{
			now_tree = now_tree->getFather();
			return L"You Haved Come To :" + now_tree->name;
		}
		else
			if (data==L"")
			{
				return L"You Haved Come To :" + now_tree->name;
			}
				else
				{
					std::list<maptree*> now_map = now_tree->getChildren();
					maptree* goto_tree = now_tree;
					for (auto i = now_map.begin(); i != now_map.end(); i++)
					{
						if ((*i)->name == data)
							goto_tree = *i;
					}
					if (now_tree == goto_tree)
						return L"Invalid Param :" + data;
					else
					{
						now_tree = goto_tree;
						return L"You Haved Come To :" + now_tree->name;
					}
				}

	}

	bool loadSetting()
	{
		wchar_t buffers[65535];
		int length = (GetPrivateProfileString(L"maps", L"lists", NULL, buffers, 65535, L".\\config.ini"));
		int lists = _ttoi(buffers);
		GetPrivateProfileString(L"maps", L"nowmap", NULL, buffers, 65535, L".\\config.ini");
		int nowmap = _ttoi(buffers);
		for (int i = 0; i < lists; i++)
		{
			CString mapname;
			mapname.Format(_T("%d"), i);
			mapname = L"map" + mapname;
			length = (GetPrivateProfileSection(mapname, buffers, 65535, L".\\config.ini"));
			if ((buffers[0] == '\0'))
			{
				return false;
			}
			else
			{
				int j = 0;
				int another_NULL = 1;
				std::map<CString, CString> keyValueMap;
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
				for (auto k = keyvalue.begin(); k != keyvalue.end(); k++)	//把键值对放入map里面
				{
					int devide_pos = k->Find(_T("="));
					CString key_str = k->Left(devide_pos);
					CString value_str = k->Right(k->GetLength() - devide_pos - 1);
					keyValueMap.insert(std::pair<CString, CString>(key_str, value_str));
				}
				maptree temp_maptree(keyValueMap);
				all_trees.push_back(temp_maptree);
				if (nowmap == i)
					now_tree = &(all_trees.back());
			}
		}

		GetPrivateProfileString(L"treeset", L"setting", NULL, buffers, 65535, L".\\config.ini");//读取tree的配置
		CString mapsetting(buffers);
		int spacepos = mapsetting.Find(_T(" "));
		while ((spacepos!=-1))
		{
			CString data = mapsetting.Left(spacepos);
			int dotpos = data.Find(_T("."));
			CString father=data.Left(dotpos);
			CString child = data.Right(data.GetLength()-dotpos-1);
			maptree* fatherpoint = findByname(father);
			maptree* childpoint = findByname(child);
			if (fatherpoint&&childpoint)
				fatherpoint->addChild(*childpoint);
			else
			{
				return false;
			}
			mapsetting = mapsetting.Right(mapsetting.GetLength()-spacepos-1);
			spacepos = mapsetting.Find(_T(" "));
		}
		int dotpos = mapsetting.Find(_T("."));
		CString father = mapsetting.Left(dotpos);
		CString child = mapsetting.Right(mapsetting.GetLength() - dotpos - 1);
		maptree* fatherpoint = findByname(father);
		maptree* childpoint = findByname(child);
		if (fatherpoint&&childpoint)
			fatherpoint->addChild(*childpoint);
		else
		{
			return false;
		}



		return true;
	}

	gameClass(bool load)
	{
		//新建命令从这里新建

		LIST_OF_COMMAND.push_back(*new command(L"exit", &gameClass::exit));
		LIST_OF_COMMAND.push_back(*new command(L"ls", &gameClass::ls));
		LIST_OF_COMMAND.push_back(*new command(L"cd", &gameClass::cd));
		LIST_OF_COMMAND.push_back(*new command(L"cls", &gameClass::cls));



		//这里添加希望游戏一开始处理的代码
		if (load)
		{
			//从存档中读取
			
			if (!loadSetting())
			{
				std::wcout << L"存档损坏" << std::endl;			//读取失败
				out = 0;
				return;
			}

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
	void mainGame()		//主游戏进程
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