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
		for (auto i = children.begin(); i != children.end();i++)		//检测子节点是否已经存在
		{
			if (*i == &child)			
				return;
		}
		//子节点不存在
		child.father = this;
		children.push_back(&child);
	}

	void deletechild(tree &child)
	{
		for (auto i = children.begin(); i != children.end();)		//检测子节点是否已经存在
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
public:
	maptree(std::map<CString,CString> featureInput)
	{
		feature = featureInput;
	}

	CString getFeature(CString key)
	{
		auto i = feature.find(key);
		if (i != feature.end())
		{
			return i->second;
		}
		else
			return L"";
	}

	bool setFeature(CString key, CString value)
	{
		auto i = feature.find(key);
		if (i != feature.end())
		{
			i->second = value;
			return true;
		}
		else
			return (feature.insert(std::pair<CString, CString>(key, value))).second;
	}

};