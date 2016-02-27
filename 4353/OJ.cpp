#include "oj.h"
/*
功能: 矩阵相乘
    
输入: MatrixA,MatrixB
    
输出: MatrixC

返回: 0
     
*/

// 二维指针的转化是关键
int matrix(int **MatrixA, int **MatrixB, int **MatrixC, int N)
{

	for (int i = 0; i < N; ++i)
	for (int j = 0; j < N; ++j)
	{
		int temp = 0;
		for (int k = 0; k < N; ++k)
		{
			int a_ik = *((int*)MatrixA + i * N + k);
			int b_kj = *((int*)MatrixB + k * N + j);
			temp += a_ik * b_kj;
		}
		*((int*)MatrixC + i * N + j) = temp;
	}

	return 0;
}
