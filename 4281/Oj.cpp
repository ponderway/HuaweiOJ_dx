// 配置文件恢复
// 有一个测试用例未通过
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

map<string, string> cmdData;
string keyWord[] = {"reset", "board", "add", "delet", "reboot",
					"backplane", "abort"};
void Init()
{
	cmdData["reset"] = "reset what";
	cmdData["reset board"] = "board fault";
	cmdData["board add"] = "where to add";
	cmdData["board delet"] = "no board at all";
	cmdData["reboot backplane"] = "impossible";
	cmdData["backplane abort"] = "install first";
}

string Error()
{
	return "unkown command";
}

string GetResult(char *inputStr)
{
	vector<string> key1;
	vector<string> key2;
	int num = 0;
	char *temp = strtok(inputStr, " ");
	while (temp != NULL)
	{
		for (int i = 0; i < 7; ++i)
		{
			if (!keyWord[i].compare(0, strlen(temp), temp))
			{
				if (num == 0)
					key1.push_back(keyWord[i]);
				else
					key2.push_back(keyWord[i]);
			}
		}
		++num;
		if (num > 2)
		{
			return Error();
		}
		temp = strtok(NULL, " ");
	}

	map<string, string>::iterator ip;
	if (num == 1)
	{
		vector<string> key;
		key = key1.size() ? key1 : key2;
		for (int i = 0; i < key.size(); ++i)
		{
			if (cmdData.count(key[i]))
			{
				ip = cmdData.find(key[i]);
				return ip->second;
			}
			else
				return Error();
		}
	}
	else
	{
		string temp, res;
		int cnt = 0;
		for (int i = 0; i < key1.size(); ++i)
		{
			for (int j = 0; j < key2.size(); ++j)
			{
				temp += key1[i] + " " + key2[j];
				//cout << temp << endl;
				if (cmdData.count(temp))
				{
					++cnt;
					ip = cmdData.find(temp);
					res = ip->second;
				}
				temp = "";
			}
		}
		if (cnt == 1)
		{
			return res;
		}
		else
			return Error();
	}
	return Error();
}

int main()
{
	Init();
	char inputStr[100];
	//cin.getline(inputStr, 100);
	//gets(inputStr);
	//cout << inputStr << endl;
	
	while (cin.getline(inputStr, 100))
	{
		cout << GetResult(inputStr) << endl;
	}
}