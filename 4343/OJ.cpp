
#include "OJ.h"
/*
功能: 求n(n ≤ 65536)以内的所有阿姆斯特朗数
原型：
    int CalcArmstrongNumber(int n);

输入参数：
    int n: n ≤ 65536

返回值：
    n以内的阿姆斯特朗数的数量。
*/

int CalcArmstrongNumber(int n)
{
	if (n == 1 && n > 65536)
		return -1;

	int m = 0; // 个数
	for (int i = 2; i <= n; ++i)
	{
		int k = i, j = 0, sum = 0;
		while (k > 0)
		{
			j = k % 10;
			k /= 10;
			sum += j * j * j;
		}

		if (sum == i)
			++m;
	}

	return m;
}
