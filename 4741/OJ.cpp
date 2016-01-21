// 可怕的阶乘
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include "oj.h"

const int MaxLen = 200;

void MultiLess10(int n, char *pOut)
{
	int len = strlen(pOut);
	int add = 0;
	for (int i = 0; i < len; ++i)
	{
		int temp = pOut[i] - '0';
		temp = n * temp + add;
		pOut[i] = temp % 10 + '0';
		add = temp / 10;
	}
	if (add)
		pOut[len] = add + '0';
}

void Add(char* str1, char* str2, char* sum)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);

	int add = 0;
	int i = 0;
	while (i < len1 && i < len2)
	{
		int temp = str1[i] - '0' + str2[i] - '0' + add;
		sum[i] = temp % 10 + '0';
		add = temp / 10;
		++i;
	}

	while (i < len1)
	{
		int temp = str1[i] - '0' + add;
		sum[i] = temp % 10 + '0';
		add = temp / 10;
		++i;
	}

	while (i < len2)
	{
		int temp = str2[i] - '0' + add;
		sum[i] = temp % 10 + '0';
		add = temp / 10;
		++i;
	}

	if (add)
		sum[i] = add + '0';

}

void Multi(int n, char *pOut)
{
	if (n < 10)
		MultiLess10(n, pOut);
	else
	{
		int k = n % 10;
		int j = n / 10;

		int len = strlen(pOut);
		char* temp1 = new char[MaxLen];
		char* temp2 = new char[MaxLen];
		memset(temp1, '\0', MaxLen);
		memset(temp2, '\0', MaxLen);
		strncpy(temp1, pOut, len);
		strncpy(temp2 + 1, pOut, len);
		temp2[0] = '0';
		//cout << temp1 << endl;
		//cout << temp2 << endl;

		MultiLess10(k, temp1);
		MultiLess10(j, temp2);

		//cout << temp1 << endl;
		//cout << temp2 << endl;

		Add(temp1, temp2, pOut);
	}
}

void Reverse(char *str)
{
	int len = strlen(str);
	int i = 0;
	int j = len - 1;
	while (i < j)
	{
		char temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		++i;
		--j;
	}
}

void CalcNN(int n, char *pOut)
{

	//int len = strlen(pOut);
	//memset(pOut, '\0', len);

	if (n == 0)
	{
		pOut[0] = '0';
		pOut[1] = '\0';
		return;
	}
	pOut[0] = '1';
	pOut[1] = '\0';
	if (n == 1)
		return;

	char ch[MaxLen];
	memset(ch, '\0', MaxLen);
	ch[0] = '1';
	for (int i = 2; i <= n; ++i)
	{
		Multi(i, ch);
	}

	Reverse(ch);

	int len = strlen(ch);
	strncpy(pOut, ch, len);
	pOut[len] = '\0';
}