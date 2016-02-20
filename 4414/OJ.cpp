// 时间超时， 未找到原因

#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
using namespace std;


map<char, char> keyBoard;
map<string, int> phoneNumbers;
// 建立字母到数字的映射表
void Init()
{
	for (int i = 0; i < 15; ++i)
	{
		keyBoard['A' + i] = '2' + i / 3;
	}

	for (int i = 0; i < 4; ++i)
	{
		keyBoard['P' + i] = '7';
		keyBoard['W' + i] = '9';
	}

	for (int i = 0; i < 3; ++i)
	{
		keyBoard['T' + i] = '8';
	}
}

// 对个性化号码进行转化
string TransformPhoneNumbers(string OrigNums)
{
	int len = OrigNums.length();
	string res;
	for (int i = 0; i < len; ++i)
	{
		if (OrigNums[i] >= '0' && OrigNums[i] <= '9')
			res += OrigNums[i];
		else if (OrigNums[i] >= 'A' && OrigNums[i] <= 'Z')
			res += keyBoard[OrigNums[i]];
		else
			continue;
	}

	int pos = 0;
	while (pos < res.length() && res[pos] == '0')
	{
		++pos;
	}

	if (pos == res.length())
		res = "0";
	else
		res = res.substr(pos);

	return res;
}

// 获取号码, 并统计号码出现的次数
void GetPhoneNumbers(const char*inFileName)
{

	ifstream inFile(inFileName);
	string temp;
	getline(inFile, temp);
	//while (getline(inFile, temp))
	while (!inFile.eof())
	{
		getline(inFile, temp);
		//cout << temp << endl;
		string nums = TransformPhoneNumbers(temp);
		if (phoneNumbers.count(nums) == 0)
			phoneNumbers[nums] = 1;
		else
			++phoneNumbers[nums];
	}

	inFile.close();
}

/*
功能: 检查是否有两个或多个公司拥有相同的电话号码,并统计输出

输入参数: inFileName  - 包含个性电话号码个数与列表的源文件名      [格式请见题目说明PPT]
outFileName - 输出统计重复号码的结果的目标文件名                  [格式请见题目说明PPT]

输出参数: 无
返回: 0 - 成功
1 - 其它各种错误，如文件不存在
*/

int PhoneBookProcess(const char *inFileName, const char *outFileName)
{
	if (inFileName == NULL || outFileName == NULL)
		return 1;

	ofstream outFile(outFileName);
	bool flag = false;
	Init();
	GetPhoneNumbers(inFileName);
	string res;
	map<string, int>::iterator ip;
	for (ip = phoneNumbers.begin(); ip != phoneNumbers.end(); ++ip)
	{
		if (ip->second > 1)
		{
			flag = true;
			char count = ip->second + '0';
			if (outFile.is_open())
			{
				outFile << ip->first + " " + count + "\n";
				//cout << "Out1" << endl;
			}
		}
	}

	if (!flag)
	{
		outFile << "No duplicates.";
	} 

	outFile.close();
	return 0;
}


int main()
{
	//Init();	
	char in[] = "ME.dat";
	char out[] = "ME_2.out";
	PhoneBookProcess(in, out);

	//fileCompare("ME.out", "Me_2.out");
}
