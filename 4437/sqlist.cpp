#include <stdlib.h>

#include <iostream>
using namespace std;

#define MAXSIZE 5

struct strmatrix
{
	int rownum; /* 二维数组行数 */
	int columnnum; /* 二维数组行数 */
	int matrix[MAXSIZE][MAXSIZE];
};

void setnull(struct strmatrix *p)  /*表置空*/
{
	for (int i = 0; i < p->rownum; ++i)
	for (int j = 0; j < p->columnnum; ++j)
		p->matrix[i][j] = 0;

	p->rownum = 0;
	p->columnnum = 0;
}

int getelementnum(struct strmatrix *p)  /*获取表中元素个数*/
{
	if (p == NULL)
		return 0;
	else
		return p->rownum * p->columnnum;
}


int getxnum(struct strmatrix *p, int x) /*获得数组中等于某个值的元素的个数*/
{
	int num = 0;
	for (int i = 0; i < p->rownum; ++i)
	for (int j = 0; j < p->columnnum; ++j)
	{
		if (p->matrix[i][j] == x)
			++num;
	}
	return num;
}

void insertrow(struct strmatrix *p, int i, int *x) /* 插入1行 */
{
	if (i < 0 || i > p->rownum || p->rownum == MAXSIZE)
		return;

	for (int row = p->rownum - 1; row >= i; --row)
	for (int col = 0; col < p->columnnum; ++col)
		p->matrix[row + 1][col] = p->matrix[row][col];

	for (int col = 0; col < p->columnnum; ++col)
		p->matrix[i][col] = x[col];

	++p->rownum;
}

void insertcolumn(struct strmatrix *p, int i, int *x) /* 插入1列 */
{
	if (i < 0 || i > p->columnnum || p->columnnum == MAXSIZE)
		return;

	for (int col = p->columnnum - 1; col >= i; --col)
	for (int row = 0; row < p->rownum; ++row)
		p->matrix[row][col + 1] = p->matrix[row][col];

	for (int row = 0; row < p->rownum; ++row)
		p->matrix[row][i] = x[row];

	++p->columnnum;
}


void matrixtrans(struct strmatrix *p) /* 方矩阵置换 */
{
	for (int row = 0; row < p->rownum; ++row)
	for (int col = 0; col < row; ++col)
	{
		int temp = p->matrix[row][col];
		p->matrix[row][col] = p->matrix[col][row];
		p->matrix[col][row] = temp;
	}
}

void matrixwhirl(struct strmatrix *p) /* 方矩阵顺时针旋转90度 */
{
	// 原矩阵a,新矩阵b, b(i,j) = a(j, M - i);M为方矩阵的的行减1
	int a[MAXSIZE][MAXSIZE];
	int size = p->rownum;
	for (int row = 0; row < size; ++row)
	for (int col = 0; col < size; ++col)
		a[col][size - 1 - row] = p->matrix[row][col];

	for (int row = 0; row < size; ++row)
	for (int col = 0; col < size; ++col)
		p->matrix[row][col] = a[row][col];
}

void matrixplus(struct strmatrix *plu, struct strmatrix *p, struct strmatrix *q) /* 两个矩阵相加 */
{
	plu->rownum = p->rownum;
	plu->columnnum = p->columnnum;

	for (int i = 0; i < plu->rownum; ++i)
	for (int j = 0; j < plu->columnnum; ++j)
	{
		plu->matrix[i][j] = p->matrix[i][j] + q->matrix[i][j];
	}
}

void matrixmultiply(struct strmatrix *mul, struct strmatrix *p, struct strmatrix *q) /* 两个矩阵相乘 */
{
	mul->rownum = p->rownum;
	mul->columnnum = q->columnnum;
	for (int i = 0; i < mul->rownum; ++i)
	for (int j = 0; j < mul->columnnum; ++j)
	{
		int temp = 0;
		for (int k = 0; k < p->columnnum; ++k)
			temp += p->matrix[i][k] * q->matrix[k][j];
		mul->matrix[i][j] = temp;
	}
}