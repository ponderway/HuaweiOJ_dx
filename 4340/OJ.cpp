#include <iostream>
using namespace std;

/*

输入: nPapers表示试卷的数目(1≤Papers≤20)，nRemain表示剩余的时间(1≤nRemain≤10000)，paper[][2]是一个Papers*2的数组，

每一行的两个元素依次为做完这一份试卷所需的时间、做完这份试卷的价值

输出: *pMaxValue为获得的最大价值
返回:
0:异常
1:计算成功返回

*/

int GetMaxValue(int nPapers, int nRemain, int paper[][2], double* pMaxValue)
{
	if (nPapers < 0 || nRemain < 0 || pMaxValue == NULL)
		return 0;

	// 申请空间
	double **c;
	c = new double*[nPapers + 1];
	for (int i = 0; i <= nPapers; ++i)
		c[i] = new double[nRemain + 1];

	for (int i = 0; i <= nPapers; ++i)
		c[i][0] = 0;
	for (int j = 0; j <= nRemain; ++j)
		c[0][j] = 0;

	for (int i = 1; i <= nPapers; ++i)
	for (int w = 1; w <= nRemain; ++w)
	{
		int wi = paper[i - 1][0];
		int vi = paper[i - 1][1];
		if (wi > w)
			c[i][w] = c[i - 1][w];
		else
		{
			int temp = c[i - 1][w - wi] + vi;
			c[i][w] = c[i - 1][w] > temp ? c[i - 1][w] : temp;
		}
	}

	*pMaxValue = c[nPapers][nRemain];

	// 释放空间
	for (int i = 0; i <= nPapers; ++i)
		delete[] c[i];
	delete[] c;

	return 1;
}

void test_1()
{
	double Ret;
	int M = 4;
	int N = 20;
	int paper_type_value[][2] = { { 4, 10 }, { 5, 22 }, { 10, 3 }, { 1, 2 } };
	GetMaxValue(M, N, paper_type_value, &Ret);
	cout << Ret << endl;
}

int main()
{
	test_1();
}