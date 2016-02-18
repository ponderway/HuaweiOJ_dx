// 本题的思路相当于另类的排序算法
// 依次对相邻的两个数进行组合比较， 使其组合的数达到最小
// 经过几轮的比较就可以得到最小的数字组合
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 10;
// 功能：将输入的数组排成最小的数
// 输入： int a[]:整型数组
//        int nCount:数组长度
//        char * strRst 返回值
// 输出：
// 返回：成功返回0  异常返回-1

int myCmp(string str1, string str2)
{
	string stra = str1 + str2;
	string strb = str2 + str1;
	if (stra.compare(strb) == -1)
		return true;

	if (str1.compare(strb) == 1)
		return false;

	return false;
}

int  smallestDigit(int a[], int nCount, char * strRst)
{
	if (a == NULL || nCount <= 0)
		return 1;

	vector<string> nums;
	for (int i = 0; i < nCount; ++i)
	{
		char temp[MAX];
		sprintf(temp, "%d", a[i]);
		nums.push_back(temp);
	}

	sort(nums.begin(), nums.end(), myCmp);
	
	string res;
	for (int i = 0; i < nCount; ++i)
	{
		res += nums[i];
	}
	
	strncpy(strRst, res.c_str(), res.length());
	strRst[res.length()] = '\0';
	return 0;
}


int main()
{
	int a[] = { 4589, 101, 41425, 9999 };
	char *pp = new char[100];
	smallestDigit(a, 4, pp);
	cout << pp << endl;

}