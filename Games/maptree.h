#pragma once
#include <list>
#include <map>
#include <atlstr.h>
class tree
{
protected:
	std::list<tree*>  children;
	tree* father;
public:
	tree()
	{
		father = NULL;
	}

	void addchild(tree &child)
	{
		for (auto i = children.begin(); i != children.end();i++)		//����ӽڵ��Ƿ��Ѿ�����
		{
			if (*i == &child)			
				return;
		}
		//�ӽڵ㲻����
		child.father = this;
		children.push_back(&child);
	}

	void deletechild(tree &child)
	{
		for (auto i = children.begin(); i != children.end();)		//����ӽڵ��Ƿ��Ѿ�����
		{
			if (*i == &child)
			{
				child.father = NULL;
				children.erase(i);
			}
			else
				i++;
		}
	}

	std::list<tree*> getChildren()
	{
		return children;
	}

	tree* getFather()
	{
		return father;
	}
};

class maptree :public tree
{
private:
	std::map<CString,CString> feature;
	CString name;
public:

};