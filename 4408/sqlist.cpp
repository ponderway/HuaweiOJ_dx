/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : 
  Version       : 
  Author        : 
  Created       : 2013/08/10
  Last Modified :
  Description   : 
  Function List :
              
  History       :
  1.Date        : 2013/08/10
    Author      : 
    Modification: Created file

******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stack>
#include <queue>
#include <iostream>
using namespace std;
/*
详细描述：   
int JudgeTrainSequence (int maxNum, char *pOutSeq);
输入参数：
	 	int maxNum：进站的火车最大编号
	 	char* pOutSeq：使用字符串表示火车出站序列
输出参数（指针指向的内存区域保证有效）：
	 	无。
返回值：
		Int: 根据输入的进站序列判断，如果输入的出战序列是可能的，返回1，否则返回0；

*/


int JudgeTrainSequence(int maxNum, char *pOutSeq)
{
	if (pOutSeq == NULL)
		return 0;

	queue<int> inQueue;
	for (int i = 1; i <= maxNum; ++i)
	{
		inQueue.push(i);
	}

	stack<int> buff;
	while (*pOutSeq != NULL && !inQueue.empty())
	{
		if (buff.empty() || buff.top() != (*pOutSeq - '0'))
		{
			while (!inQueue.empty())
			{
				buff.push(inQueue.front());
				inQueue.pop();

				if (buff.top() == (*pOutSeq - '0'))
					break;
			}
		}

		while (!buff.empty() && *pOutSeq != '\0' && buff.top() == (*pOutSeq - '0'))
		{
			buff.pop();
			++pOutSeq;
		}
	}

	if (*pOutSeq == '\0' && inQueue.empty() && buff.empty())
		return 1;
	return 0;
}

