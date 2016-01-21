/******************************************************************************

  Copyright (C), 2001-2013, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : 
  Version       : 
  Author        : 
  Created       : 2013/03/12
  Last Modified :
  Description   : 
  Function List :
              
  History       :
  1.Date        : 2013/03/12
    Author      : 
    Modification: Created file

******************************************************************************/
// 提交有四个实例未通过
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

int number[4];
int cnt = 0;
int flag = false;

void Find(int n)
{
	if (n == 1)
	{
		if (number[0] == 24)
		{
			++cnt;
			flag = true;
		}
		return;
	}

	for (int i = 0; i < n; ++i)
	for (int j = i + 1; j < n; ++j)
	{
		int a, b;
		a = number[i];
		b = number[j];
		number[j] = number[n - 1];

		number[i] = a + b;
		Find(n - 1);

		number[i] = a - b;
		Find(n - 1);

		number[i] = b - a;
		Find(n - 1);

		number[i] = a * b;
		Find(n - 1);

		if (b != 0)
		{
			number[i] = a / b;
			Find(n - 1);
		}

		if (a != 0)
		{
			number[i] = b / a;
			Find(n - 1);
		}

		number[i] = a;
		number[j] = b;
	}
}

bool Game24Points(int a, int b, int c, int d)
{
	number[0] = a;
	number[1] = b;
	number[2] = c;
	number[3] = d;

	Find(4);
	if (cnt == 0)
		return false;
	else
		return true;
}


