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
#include <iostream>
using namespace std;

char alphabet[] = " abcdefghijilmnopqrstuvwxyz";



void GetNextNum(int InMinSeq, int InMaxSeq, int InNumbLen, char *InChaStr, char *pBufOutData)
{
	if (InMinSeq < 1 || InMinSeq > 26 || InMaxSeq < 1 || InMaxSeq > 26 || InMinSeq >= InMaxSeq ||
		InNumbLen > InMaxSeq - InMinSeq || InChaStr == NULL)
		return;
	strncpy(pBufOutData, InChaStr, InNumbLen);
	pBufOutData[InNumbLen] = '\0';

	for (int j = InNumbLen - 1; j >= 0; --j)
	{
		char tempNext = InChaStr[j] + 1;
		int flag = 1;
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
			if (flag)
			{
				pBufOutData[j] = tempNext;
				if (j != InNumbLen - 1)
				{
					int k = j + 1;
					while (k < InNumbLen)
					{
						pBufOutData[k] = tempNext + (k - j);
						++k;
					}		
				}
				return;
			}
		}	
	}
}

void GetResult(int InMinSeq, int InMaxSeq, int InNumbLen, char *InChaStr, char *pBufOutData)
{
	int num = 1;
	char maxData[30];
	int p = InMaxSeq;
	for (int i = InNumbLen - 1; i >= 0; --i)
	{
		maxData[i] = alphabet[p];
		--p;		
	}
	maxData[InNumbLen] = '\0';
	char temp[30];
	GetNextNum(InMinSeq, InMaxSeq, InNumbLen, InChaStr, temp);
	strncpy(pBufOutData, temp, InNumbLen);
	pBufOutData[InNumbLen] = '\0';
	while (num < 5 && (strncmp(temp, maxData, InNumbLen) <= 0))
	{
		char input[30];
		strncpy(input, temp, InNumbLen);
		input[InNumbLen] = '\0';
		GetNextNum(InMinSeq, InMaxSeq, InNumbLen, input, temp);
		pBufOutData[(InNumbLen + 1) * num - 1] = '\n';
		strncpy(pBufOutData + (InNumbLen + 1) * num, temp, InNumbLen);
		++num;
		pBufOutData[(InNumbLen + 1) * num - 1] = '\0';
	}
	
}

int main()
{
	char res[200];
	cout << alphabet[10] << endl;
	GetResult(2, 10, 5, "bdfij", res);
	cout << res << endl;
}