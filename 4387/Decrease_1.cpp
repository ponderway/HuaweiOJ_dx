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
#include <vector>
using namespace std;


// 获取小数的位数 
int GetLengthOfDecimal(string str)
{
	int len = 0;
	int pos = str.find('.');
	if (pos == -1)
		len = 0;
	else
		len = str.length() - pos - 1;

	return len;
}

// 去除小数点，将其补齐， 反转输入到数组中
vector<int> Alignment(string str, int lengthOfDecimal)
{
	int len = GetLengthOfDecimal(str);
	if (len == -1)
		len = 0;

	int subZeors = lengthOfDecimal - len;
	vector<int> nums(subZeors, 0);
	for (int i = str.length() - 1; i >= 0; --i)
	{
		if (str[i] != '.')
			nums.push_back(str[i] - '0');
	}

	return nums;
}

// 比较整数大小
int Compare(vector<int> num1, vector<int> num2)
{
	int len1 = num1.size();
	int len2 = num2.size();
	if (len1 > len2)
		return 1;
	if (len1 < len2)
		return -1;

	if (len1 == len2)
	{
		int i = len1 - 1;
		while (i >= 0 && num1[i] == num2[i])
			--i;

		if (i == -1)
			return 0;

		if (num1[i] > num2[i])
			return 1;
		else
			return -1;
	}
}

vector<int> Minus(vector<int> num1, vector<int> num2)
{
	vector<int> res;
	int flag = Compare(num1, num2);
	if (flag == 0)
	{
		res.push_back(0);
		return res;
	}

	vector<int> bigNum, smallNum;
	if (flag == 1)
	{
		bigNum = num1;
		smallNum = num2;
	}
	else
	{
		bigNum = num2;
		smallNum = num1;
	}

	int i = 0;
	int borrow = 0;
	for (; i < smallNum.size(); ++i)
	{
		int temp = bigNum[i] - borrow - smallNum[i];
		if (temp < 0)
		{
			temp = temp + 10;
			borrow = 1;
		}
		else
			borrow = 0;
		res.push_back(temp);
	}

	for (; i < bigNum.size(); ++i)
	{
		int temp = bigNum[i] - borrow;
		if (temp < 0)
		{
			temp = temp + 10;
			borrow = 1;
		}
		res.push_back(temp);
	}
	return res;
}

string RemoveZeros(string str)
{
	int first = 0, last = 0;
	while (first < str.length() && str[first] == '0')
		++first;
	if (first == str.length())
		return "0";

	if (str[first] == '.')
		--first;

	int i = 0;
	while (i < str.length() && str[i] != '.')
		++i;

	if (i == str.length())
		last = str.length() - 1;
	else
	{
		last = str.length() - 1;
		while (last > i && str[last] == '0')
		{
			--last;
		}
		if (last == i)
			--last;
	}

	string res = str.substr(first, last - first + 1);
	return res;
}

string GetResult(vector<int> num, int lengthOfDecimal, bool negtiveFlag)
{
	if (num.size() == 1 && num[0] == 0)
		return "0";
	if (num.size() <= lengthOfDecimal)
	{
		int additionalZero = lengthOfDecimal - num.size() + 1;
		while (additionalZero > 0)
		{
			num.push_back(0);
			--additionalZero;
		}
	}
	string temp;
	for (int i = num.size() - 1; i >= 0; --i)
		temp.push_back(num[i] + '0');
	temp.insert(temp.length() - lengthOfDecimal, ".");

	string res = RemoveZeros(temp);
	if (negtiveFlag)
		res = '-' + res;

	return res;
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

	vector<int> num1 = Alignment(str1, lenOfDecimal);
	vector<int> num2 = Alignment(str2, lenOfDecimal);

	bool negtiveFlag = false;
	if (Compare(num1, num2) == -1)
		negtiveFlag = true;

	vector<int> minusResult = Minus(num1, num2);

	string result = GetResult(minusResult, lenOfDecimal, negtiveFlag);

	char* pResult = new char[result.length() + 1];
	strncpy(pResult, result.c_str(), result.length());
	pResult[result.length()] = '\0';

	*ppResult = pResult;
	return 0;

}


