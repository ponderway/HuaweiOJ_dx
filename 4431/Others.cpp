
#include "IPAddressValid.h"
#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;

bool isIPAddressValid(const char* pszIPAddr)
{
	// 请在此处实现
	if (NULL == pszIPAddr) return false;
	int lenIPAddr = strlen(pszIPAddr);
	int startIndex, endIndex;
	//去掉前后空格
	for (startIndex = 0; startIndex<lenIPAddr; startIndex++)
	if (pszIPAddr[startIndex] != ' ')
		break;
	for (endIndex = lenIPAddr - 1; endIndex >= 0; endIndex--)
	if (pszIPAddr[endIndex] != ' ')
		break;
	if (endIndex <= startIndex) return false;
	char inputStr[200];
	int lenInputStr = endIndex - startIndex + 1;
	strncpy(inputStr, &pszIPAddr[startIndex], lenInputStr);
	inputStr[lenInputStr] = '\0';
	//查找点的合法性
	int countDot = 0;
	for (int i = 0; i<lenInputStr; i++)
	{
		if (inputStr[i] == '.')
		{
			countDot++;
			if (i == 0 || i == lenInputStr - 1) return false;
			if (inputStr[i - 1]<'0' || inputStr[i - 1]>'9')
				return false;
			if (inputStr[i + 1]<'0' || inputStr[i + 1]>'9')
				return false;
		}
	}
	if (countDot != 3) return false;
	char *pCut;
	pCut = strtok(inputStr, ".");
	while (NULL != pCut)
	{
		int num;
		sscanf(pCut, "%d", &num);
		if (num != 0 && pCut[0] == '0') return false;
		if (num>255) return false;
		pCut = strtok(NULL, ".");
	}
	return true;
}