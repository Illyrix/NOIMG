#pragma once
#include <list>
#include <map>
#include <atlstr.h>
class maptree
{
private:
	std::list<maptree*>  children;
	maptree* father;
	std::map<CString,CString> feature;
public:
	CString name;
	maptree(std::map<CString,CString> featureInput)
	{
		father = NULL;
		for (auto i = featureInput.begin(); i != featureInput.end(); i++)
		{
			setFeature(i->first,i->second);
		}
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
		if (key == L"name")
		{
			name = value;
			return true;
		}
		auto i = feature.find(key);
		if (i != feature.end())
		{
			i->second = value;
			return true;
		}
		else
			return (feature.insert(std::pair<CString, CString>(key, value))).second;
	}
	void setFather(maptree* Fatherinput)
	{
		Fatherinput->addChild(*this);
	}

	void addChild(maptree &child)
	{
		child.father = this;
		if (this == &child)//自身赋值为自身，既根节点
		{
			return;
		}
		for (auto i = children.begin(); i != children.end(); i++)		//检测子节点是否已经存在
		{
			if (*i == &child)
				return;
		}
		//子节点不存在
		children.push_back(&child);
	}

	void deleteChild(maptree &child)
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

	std::list<maptree*> getChildren()
	{
		return children;
	}

	maptree* getFather()
	{
		return father;
	}
};