
/******************************************************************************************************
Description     : 对输入的一元多项式，进行同类项合并，输出处理后的一元多项式 
Prototype       : void OrderPolynomial (char* InputString, char* OutputString)
Input Param     : char* InputString 输入多项式字符串
Output Param    : char* OutputString 输出多项式字符串
Return Value    : void

********************************************************************************************************/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// "7X^4-5X^3+3X^3+1X^0"
// 提取多项式的系数，数组第i个元素表示指数为i的系数
// 将字符串中的数字以空格隔开，然后分割
vector<int> GetFactor(char* Str)
{
	string s;
	vector<int> nums;
	int len = strlen(Str);
	for (int i = 0; i < len; ++i)
	{
		if (Str[i] >= '0' && Str[i] <= '9')
			s += Str[i];
		else if (Str[i] == '-')
			s += " -";
		else
			s += ' ';
	}

	string::size_type i = 0, j = 0;
	while (j != string::npos)
	{
		j = s.find(' ', i);

		if (i != j)
		{
			string temp = s.substr(i, j - i);
			int num = atoi(temp.c_str());
			nums.push_back(num);
		}
		i = j + 1;
	}
	// 获取最大指数
	int maxExp = 0;
	for (vector<int>::size_type i = 1; i < nums.size(); i += 2)
	{
		maxExp = nums[i] > maxExp ? nums[i] : maxExp;
	}

	vector<int> factor(maxExp + 1, 0);
	for (vector<int>::size_type i = 1; i < nums.size(); i += 2)
	{
		factor[nums[i]] += nums[i - 1];
	}

	return factor;
}

// 数字转字符串
string num2string(int num)
{
	char str[10];
	string s;
	sprintf(str, "%d", num);
	string res = str;
	return res;
}

// 将系数数组转化成多项式表达式形式
string GetPolynomial(vector<int> factor)
{

	string poly;
	for (int i = factor.size() - 1; i >= 0; --i)
	{
		if (factor[i] != 0)
		{
			if (poly.length() != 0 && factor[i] > 0)
				poly += '+';
			poly += num2string(factor[i]) + "X^" + num2string(i);
		}
	}

	//这行代码会使一个事例不通过
	//if (poly.length() == 0)
	//	return "0";
	return poly;
}

void OrderPolynomial(char* InputString, char* OutputString)
{
	/*在这里实现功能*/
	vector<int> factor = GetFactor(InputString);
	string poly = GetPolynomial(factor);

	strncpy(OutputString, poly.c_str(), poly.length());
	OutputString[poly.length()] = '\0';
	return;
}
