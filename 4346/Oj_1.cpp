// 实现了功能，但有一些复杂
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*****************************************************************************
Prototype    : multiply
Description  : 两个任意长度的长整数相乘, 输出结果
Input Param  :
const std::string strMultiplierA  乘数A
const std::string strMultiplierB  乘数B
Output       :
std::string strRst            乘法结果
Return Value :
int                       0  正确
-1  异常
*****************************************************************************/
vector<int> ArrayAdd(vector<int>& vec1, vector<int>& vec2)
{

	int len1 = vec1.size();
	int len2 = vec2.size();

	if (len1 == 0)
		return vec2;
	if (len2 == 0)
		return vec1;

	vector<int> res;
	int i = 0;
	int carry = 0;
	while (i < len1 && i < len2)
	{
		int temp = vec1[i] + vec2[i] + carry;
		res.push_back(temp % 10);
		carry = temp / 10;
		++i;
	}

	while (i < len1)
	{
		int temp = vec1[i] + carry;
		res.push_back(temp % 10);
		carry = temp / 10;
		++i;
	}

	while (i < len2)
	{
		int temp = vec2[i] + carry;
		res.push_back(temp % 10);
		carry = temp / 10;
		++i;
	}

	if (carry)
		res.push_back(carry);

	return res;

}
int multiply(const std::string strMultiplierA, const std::string strMultiplierB, std::string &strRst)
{

	/* 在这里实现功能 */
	if (strMultiplierA.length() == 0 || strMultiplierB.length() == 0)
		return -1;

	vector<int> multiA, multiB, result;
	for (int i = strMultiplierA.length() - 1; i >= 0; --i)
		multiA.push_back(strMultiplierA[i] - '0');
	for (int i = strMultiplierB.length() - 1; i >= 0; --i)
		multiB.push_back(strMultiplierB[i] - '0');

	for (int i = 0; i < multiB.size(); ++i)
	{

		vector<int> tempMulti;
		for (int k = 0; k < i; ++k)
			tempMulti.push_back(0);

		int carry = 0;
		for (int j = 0; j < multiA.size(); ++j)
		{
			int temp = multiB[i] * multiA[j] + carry;
			tempMulti.push_back(temp % 10);
			carry = temp / 10;
		}

		if (carry)
			tempMulti.push_back(carry);

		vector<int> tempResult = result;
		result = ArrayAdd(tempMulti, tempResult);
	}

	int pos = -1;
	for (int i = result.size() - 1; i >= 0; --i)
	{
		if (result[i] != 0)
		{
			pos = i;
			break;
		}
	}

	if (pos == -1)
		strRst = "0";

	for (int i = pos; i >= 0; --i)
		strRst.push_back(result[i] + '0');

	return 0;
}

int main()
{
	string b = "123";
	string a = "522525";
	string c;
	multiply(a, b, c);
	cout << a << " * " << b << " = " << c << endl;
}