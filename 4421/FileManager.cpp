
//有一个测试用例不通过
#include <iostream>
#include <string>
#include <map>
#include "FileManager.h"
using namespace std;

class Dir
{
public:
	Dir()
	{}
	Dir(Dir *fath, string dirName)
	{
		father = fath;
		name = dirName;
	}

	Dir* father;
	string name;
};

class File
{
public:
	File()
	{}
	File(Dir *fath, string fileName)
	{
		father = fath;
		name = fileName;
	}

	Dir* father;
	string name;
};


map<string, Dir> dir;
map<string, File> file;

Dir root(NULL, "root");

void Init()
{
	dir["root"] = root;
}

int CreateDir(const char * ParentDirName, const char * DirName)
{
	if (dir.size() == 0)
		Init();

	if (ParentDirName == NULL || DirName == NULL)
		return -1;

	if (dir.count(ParentDirName) && !dir.count(DirName))
	{
		map<string, Dir>::iterator p;
		p = dir.find(ParentDirName);
		Dir newDir(&p->second, DirName);
		dir.insert(pair<string, Dir>(DirName, newDir));
		return 0;
	}
	else
		return -1;
}

void DeleteDir(const char * DirName)
{
	if (DirName == NULL)
		return;

	if (DirName == "root" || !dir.count(DirName))
		return;

	map<string, Dir>::iterator it = dir.begin(), p;
	map<string, File>::iterator	ip = file.begin();
	p = dir.find(DirName);

	while (it != dir.end())
	{
		if (it->first == "root")
		{
			++it;
			continue;
		}
		if (it->second.father->name == DirName)
		{
			DeleteDir(it->first.c_str());
			it = dir.begin();
			ip = file.begin();  // 二者都需要重置
		}
		else
			++it;
	}

	while (ip != file.end())
	{
		//if (ip->second.name == "root")
		//{
		//	++ip;
		//	continue;
		//}
		if (ip->second.father->name == DirName)
		{
			DeleteFile(ip->first.c_str());
			ip = file.begin();
		}
		else
			++ip;
	}
	dir.erase(p);
}

int MoveDir(const char * SrcDirName, const char * DestDirName)
{
	if (SrcDirName == NULL || DestDirName == NULL)
		return -1;
	if (!dir.count(SrcDirName) || !dir.count(DestDirName) || SrcDirName == DestDirName)
		return -1;
	if (SrcDirName == "root")
		return -1;
	map<string, Dir>::iterator ipSrc, ipDest, it;
	ipSrc = dir.find(SrcDirName);
	ipDest = dir.find(DestDirName);

	if (ipSrc->second.father->name == DestDirName) // 直接父目录
		return -1;

	it = ipDest;
	while (it->first != "root")// 子目录
	{
		if (it->second.father->name != SrcDirName)
			it = dir.find(it->second.father->name);
		else
			return -1;
	}

	ipSrc->second.father = &ipDest->second;
	return 0;
}

int CreateFile(const char * DirName, const char * FileName)
{
	if (dir.size() == 0)
		Init();

	if (!dir.count(DirName) || file.count(FileName))
		return -1;

	map<string, Dir>::iterator p = dir.find(DirName);
	File newFile(&p->second, FileName);
	file.insert(pair<string, File>(FileName, newFile));
	return 0;
}

void DeleteFile(const char * FileName)
{
	if (FileName == NULL)
		return;
	if (file.count(FileName))
	{
		map<string, File>::iterator ip;
		ip = file.find(FileName);
		file.erase(ip);
	}
	return;
}

unsigned int GetFileNum(const char * DirName)
{
	if (!dir.count(DirName))
		return 0;

	unsigned int num = 0;
	map<string, Dir>::iterator it;
	for (it = dir.begin(); it != dir.end(); ++it)
	{
		if (it->first == "root")
		{
			continue;
		}
		if (it->second.father->name == DirName)
			num += GetFileNum(it->first.c_str());
	}

	map<string, File>::iterator ip;
	for (ip = file.begin(); ip != file.end(); ++ip)
	{
		if (ip->second.father->name == DirName)
			++num;
	}
	return num;
}

void Clear(void)
{
	map<string, Dir>::iterator it = dir.begin();
	while (it != dir.end())
	{
		if (it->first == "root")
		{
			++it;
			continue;
		}
		if (it->second.father->name == "root")
		{
			DeleteDir(it->first.c_str());
			it = dir.begin();
		}
		else
			++it;
	}

	map<string, File>::iterator ip = file.begin();
	while (ip != file.end())
	{
		if (ip->second.father->name == "root")
		{
			DeleteFile(ip->first.c_str());
			ip = file.begin();
		}
		else
			++ip;
	}
	return;
}
