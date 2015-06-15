#pragma once
#include "command.h"
#include "maptree.h"

class gameClass
{
private:

	std::deque<command> LIST_OF_COMMAND;
	//���������˽�г�Ա
	maptree now_tree;
	std::list<maptree> all_trees;

	//��������������ʵ��



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
		//�½�����������½�

		LIST_OF_COMMAND.push_back(*new command(L"exit", &gameClass::exit));
		LIST_OF_COMMAND.push_back(*new command(L"ls", &gameClass::ls));



		//�������ϣ����Ϸһ��ʼ����Ĵ���
		if (load)
		{
			//�Ӵ浵�ж�ȡ
			CString buffers;
			int length=(GetPrivateProfileStringW(L"maplist",L"lists",NULL, (LPWSTR)(LPCWSTR)buffers,65535,L".\\config.ini"));
			int lists = _ttoi(buffers);
			for (int i = 0; i < lists; i++)
			{
				CString mapname;
				mapname.Format(_T("%d"),i);
				mapname = L"map" + mapname;
				length= (GetPrivateProfileSectionW(mapname, (LPWSTR)(LPCWSTR)buffers, 65535, L".\\config.ini"));
				if (buffers == "\0\0")
				{
								//��ȡʧ��
				}
				else
				{
					int j=0;
					do 
					{
						Afx
					} while (true);
				}
			}
		}
		else
		{
			//�½���Ϸ
		}
	};	
public:
	static bool out;       //ѭ������
	static gameClass* createObj(bool load)	//����ģʽ
	{
		static gameClass m_Init(load);
		return &m_Init;
	}
	CString exe(CString);

	~gameClass()	//��������������������Զ�����ȹ���
	{
		
	}
};
bool gameClass::out = true;

CString gameClass::exe(CString input)
	{
		//��������Ͳ���
		int content_pos = input.Find(_T(" "));
		if (content_pos == -1)
			content_pos = input.GetLength();
		CString command_str = input.Left(content_pos);
		CString content_str = input.Right(input.GetLength() - content_pos - 1);
		content_str.TrimLeft(L" ");
		//������������
		for (auto i = LIST_OF_COMMAND.begin(); i != LIST_OF_COMMAND.end(); i++)
		{
			if (i->name == command_str)
				return (this->*(i->function))(content_str);  //�������н��
		}
		return L">Command Invalid:" + command_str;
	}