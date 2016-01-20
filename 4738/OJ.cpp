
#include "OJ.h"
#include <iostream>
#include <cmath>
/*
功能: 求解放置8皇后方案的个数。
输入：
    无
返回：
    int：放置8皇后方案的个数
*/

int *QueenPos = NULL; // 用来保存每一行皇后的所在的列

bool isAvailable(int k, int N)
{
	for (int i = 0; i < k; ++i)
	{
		if (QueenPos[i] == QueenPos[k] || abs(i - k) == abs(QueenPos[i] - QueenPos[k]))
			return false;
	}
	return true;
}

void queue(int k, int N, int &num)
{
	if (k == N)
		++num;
	else
	{
		for (int i = 0; i < N; ++i)
		{
			QueenPos[k] = i;
			if (isAvailable(k, N))
				queue(k + 1, N, num);
		}
	}
}

int PlaceQueenMethodNum(int N)
{
	QueenPos = new int[N];
	for (int i = 0; i < N; ++i)
		QueenPos[i] = -1;
	int num = 0;
	queue(0, N, num);

	return num;
}

// 参考：http://blog.csdn.net/hackbuteer1/article/details/6657109
// http://blog.csdn.net/cxllyg/article/details/8055596
