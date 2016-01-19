#include <stdlib.h>
#include "oj.h"
#include <string.h>

/* 功能：在字符串中找出连续最长的数字串，并把这个串的长度返回
函数原型：
   unsigned int Continumax(char** pOutputstr,  char* intputstr)
输入参数：
   char* intputstr  输入字符串
输出参数：
   char** pOutputstr: 连续最长的数字串，如果连续最长的数字串的长度为0，应该返回空字符串
   pOutputstr 指向的内存应该在函数内用malloc函数申请，由调用处负责释放

返回值：
  连续最长的数字串的长度

 */
unsigned int Continumax(char** pOutputstr,  char* inputstr)
{
	if (inputstr == NULL)
	{
		*pOutputstr = (char*)malloc(sizeof(char));
		**pOutputstr = '\0';
		return 0;
	}

	int len = strlen(inputstr);
	int maxLen = 0;
	int tempLen = 0;
	int startPos = 0;
	char* initStr = inputstr;

	while (*inputstr != '\0')
	{
		if (*inputstr >= '0' && *inputstr <= '9')
		{
			++tempLen;
		}
		else
		{
			if (tempLen >= maxLen)
			{
				maxLen = tempLen;
				startPos = inputstr - initStr - maxLen;
			}
			tempLen = 0;
		}
		++inputstr;
	}

	if (tempLen >= maxLen)
	{
		maxLen = tempLen;
		startPos = len - maxLen;
	}

	*pOutputstr = (char*)malloc(maxLen + 1);
	strncpy(*pOutputstr, initStr + startPos, maxLen);
	(*pOutputstr)[maxLen] = '\0';

	return maxLen;
}