
#include "OJ.h"
 
#include "OJ.h"
#include <stdio.h>
#include <string.h> 
#include <string>
#include <iostream>
using namespace std;
/*
功能:对输入的字符串进行处理，输出符合Jam记数法的字符串
    
输入参数：
	 	Char InMinSeq：输入最小的字母的序号
		char InMaxSeq: 输入最大的字母的序号
		int InNumbLen： 输入字符的位数
        char InChaStr: 输入具有InNumbLen个字符的字符串
输出参数（指针指向的内存区域保证有效）：
	 	char* pBufOutData：输出转换后的字符列表，以‘\n’区分
返回值
		void

*/

string alphabet = " abcdefghijilmnopqrstuvwxyz";

string GetNextNum(int InMinSeq, int InMaxSeq, int InNumbLen, string InChaStr)
{
	string nextNum = InChaStr;

	// 从最后一位开始遍历，当最后一位可以直接加1时，满足条件
	// 否则，向前进一位，寻找满足的字母，同时其后面的所有位依次以该位的字母开始递增

	for (int j = InNumbLen - 1; j >= 0; --j)
	{
		char tempNext = InChaStr[j] + 1;
		int flag = 1; // 找到合适的字母
		if (tempNext <= alphabet[InMaxSeq])
		{
			for (int i = 0; i < InNumbLen; ++i)
			{
				if (i != j && InChaStr[i] == tempNext)
				{
					flag = 0;
					break;
				}
			}
		}
		else
		{
			continue;
		}

		if (flag)
		{
			nextNum[j] = tempNext;
			if (j != InNumbLen - 1)
			{
				int k = j + 1;
				while (k < InNumbLen)
				{
					nextNum[k] = tempNext + (k - j);
					++k;
				}
			}
			return nextNum;
		}
	}
}

void GetResult(int InMinSeq, int InMaxSeq, int InNumbLen, char *InChaStr, char *pBufOutData)
{
	int num = 0;
	string maxData = alphabet.substr(InMaxSeq - InNumbLen + 1, InNumbLen);
	string res, tempNow = InChaStr;
	cout << res << endl;
	while (num < 5 && tempNow.compare(maxData) < 0)
	{
		if (num != 0)
			res += "\n";
		string tempNext = GetNextNum(InMinSeq, InMaxSeq, InNumbLen, tempNow);
		res += tempNext;
		tempNow = tempNext;
		++num;
	}

	strncpy(pBufOutData, res.c_str(), res.length());
	pBufOutData[res.length()] = '\0';
}