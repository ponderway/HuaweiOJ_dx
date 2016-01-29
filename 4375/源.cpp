#include <iostream>
#include <string>
#include <vector>
using namespace std;

//"7X^4-5X^3+3X^3+1X^0"
// 提取多项式的系数，数组第i个元素表示指数为i的系数
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

// 多项式系数相乘
vector<int> FactorMultiple(vector<int> factor1, vector<int> factor2)
{
	int resLen = factor1.size() + factor2.size() - 1;
	vector<int> res(resLen, 0);
	for (vector<int>::size_type i = 0; i < factor1.size(); ++i)
	for (vector<int>::size_type j = 0; j < factor2.size(); ++j)
	{
		res[i + j] += factor1[i] * factor2[j];
	}

	return res;
}

// 数字转字符串
string num2string(int num)
{
	if (num == 0)
		return "0";
	string res;
	bool negtiveFlag = false;
	if (num < 0)
	{
		negtiveFlag = true;
		num *= -1;
	}
	while (num != 0)
	{
		char temp = num % 10 + '0';
		res = temp + res;
		num /= 10;
	}
	if (negtiveFlag)
		res = '-' + res;
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
			//poly += _itoa_s(factor,)
	}
	
	// 这行代码会使一个事例不通过
	//if (poly.length() == 0)
	//	return "0";
	return poly;
}

/******************************************************************************************************
Description     : 对两个输入的一元多项式，进行多项式乘法运算，输出结果一元多项式
Prototype       : void PolynomialMultiple (char* InputString1, char* InputString2, char* OutputString)
Input Param     : char* InputString1 乘数1多项式字符串
                  char* InputString2 乘数2多项式字符串
Output Param    : char* OutputString 乘积多项式字符串
Return Value    : void

********************************************************************************************************/

void PolynomialMultiple(char* InputString1, char* InputString2, char* OutputString)
{
	/*在这里实现功能*/
	vector<int> factor1 = GetFactor(InputString1);
	vector<int> factor2 = GetFactor(InputString2);

	vector<int> res = FactorMultiple(factor1, factor2);
	
	string poly = GetPolynomial(res);
	
	strncpy(OutputString, poly.c_str(), poly.length());
	OutputString[poly.length()] = '\0';
	return;
}

int main()
{
	char str1[] = "-3X^3+3X^3";
	char str2[] = "-3X^3+3X^3";
	char outStr[1024];
	PolynomialMultiple(str1, str2, outStr);

	cout << outStr << endl;
}