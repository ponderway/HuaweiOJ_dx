/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : 
  Version       : 
  Author        : 
  Created       : 2009/10/10
  Last Modified :
  Description   : 
  Function List :
              
  History       :
  1.Date        : 2009/10/10
    Author      : 
    Modification: Created file

******************************************************************************/
#include <stdlib.h>



/*****************************************************************************
Description  : 两个任意长度的正数相减
Prototype    : int Decrease(const char *pMinuend, const char *pSubtrahend, char **ppResult)
Input Param  : const char *pMinuend     被减数，以\0表示字符串结束
               const char *pSubtrahend  减数，以\0表示字符串结束
Output       : char **ppResult          减法结果，必须以\0表示字符串结束
Return Value : 成功返回0   失败返回-1
*****************************************************************************/
#include <iostream>
#include <string>
using namespace std;

// 获取小数的位数 
int GetLengthOfDecimal(const string &str)
{
	int len = 0;
	int pos = str.find('.');
	if (pos == -1)
		len = 0;
	else
		len = str.length() - pos - 1;

	return len;
}

// 对小数位补零，使两个整数的小数位一样长
void Aligment(string &str, int maxDecimalLen)
{
	int decimalLen = GetLengthOfDecimal(str);
	if (decimalLen == 0)
		str += '.';
	string zeros(maxDecimalLen - decimalLen, '0');
	str += zeros;
}

// 小数位已经对齐
bool GreaterEqual(const string &str1, const string &str2)
{
	int len1 = str1.length();
	int len2 = str2.length();
	if (len1 > len2)
		return true;
	if (len1 < len2)
		return false;

	int i = 0;
	while (i < len1 && str1[i] == str2[i])
		++i;
	if (i == len1)
		return true;

	if (str1[i] > str2[i])
		return true;
	else
		return false;
}

// 移除多余的0，整数会以. 结束
string RemoveExtraZeros(const string &str)
{
	int dotPos = str.find('.');
	int first = str.find_first_not_of('0');
	int last = str.find_last_not_of('0');
	if (first == dotPos)
		--first;
	if (last == dotPos)
		--last;
	string result = str.substr(first, last - first + 1);
	return result;
}

// 被减数大于减数，小数位已对齐
string PositiveNumMinus(const string &str1, const string &str2)
{
	string result(str1.length(), '\0');
	int index1 = str1.length() - 1;
	int index2 = str2.length() - 1;

	int borrow = 0;
	for (; index2 >= 0; --index2, --index1)
	{
		if (str1[index1] == '.')
		{
			result[index1] = '.';
			continue;
		}

		if (str1[index1] - borrow < str2[index2])
		{
			result[index1] = str1[index1] - borrow + 10 - str2[index2] + '0';
			borrow = 1;
		}
		else
		{
			result[index1] = str1[index1] - borrow - str2[index2] + '0';
			borrow = 0;
		}
	}

	for (; index1 >= 0; --index1)
	{
		if (str1[index1] - borrow < '0')
		{
			result[index1] = str1[index1] - borrow + 10;
			borrow = 1;
		}
		else
		{
			result[index1] = str1[index1] - borrow;
			borrow = 0;
		}
	}

	return  RemoveExtraZeros(result);
}

int Decrease(const char *pMinuend, const char *pSubtrahend, char **ppResult)
{

	if (pMinuend == NULL || pSubtrahend == NULL)
		return -1;
	string str1 = pMinuend;
	string str2 = pSubtrahend;

	int len1 = GetLengthOfDecimal(str1);
	int len2 = GetLengthOfDecimal(str2);
	int lenOfDecimal = len1 > len2 ? len1 : len2;

	Aligment(str1, lenOfDecimal);
	Aligment(str2, lenOfDecimal);

	bool negtiveFlag = false;
	if (!GreaterEqual(str1, str2))
		negtiveFlag = true;

	string result;
	if (negtiveFlag)
	{
		result = PositiveNumMinus(str2, str1);
		result = '-' + result;
	}
	else
		result = PositiveNumMinus(str1, str2);

	char* pResult = new char[result.length() + 1];
	strncpy(pResult, result.c_str(), result.length());
	pResult[result.length()] = '\0';

	*ppResult = pResult;
	return 0;
}



