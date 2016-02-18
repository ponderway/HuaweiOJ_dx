//#include <stdlib.h>
//#include "oj.h"
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include "OJ.h"
using namespace std;

/*
功能:   输入一个不带头节点的单向链表(链表的节点数小于100),
删除链表中内容重复的节点（重复的节点全部删除），剩余的节点逆序倒排。

输入:   pstrIn： 输入一个不带头节点的单向链表

输出:   pstrOut：删除内容重复的节点后，逆序排列的链表(不带头节点,链表第一个节点的内存已经申请)。

返回:

示例:
输入链表的内容依次为 6,7,8,8,9,10,6
则输出链表的内容依次应该是 10,9,7

*/

int iChanProcess(strNode * pstrIn, strNode * pstrOut)
{
	if (pstrIn == NULL)
		return -1;

	multiset<int> dataSet;
	vector<int> res;
	multiset<int>::iterator ip;
	strNode *pTemp = pstrIn;
	while (pTemp != NULL)
	{
		dataSet.insert(pTemp->data);
		pTemp = pTemp->pstrNext;
	}

	for (ip = dataSet.begin(); ip != dataSet.end(); ++ip)
	{
		if (dataSet.count(*ip) == 1)
		{
			res.push_back(*ip);
		}
	}
	sort(res.begin(), res.end());

	pTemp = pstrOut;
	for (int i = res.size() - 1; i >= 0; --i)
	{
		if (i == res.size() - 1)
		{
			pTemp->data = res[i];
			pTemp->pstrNext = NULL;
		}
		else
		{
			strNode* pNode = new strNode;
			pNode->data = res[i];
			pNode->pstrNext = NULL;

			pTemp->pstrNext = pNode;
			pTemp = pNode;
		}
	}

	return 0;
}

/* 释放链表 */
void vFreeChan(strNode * pstrChan)
{
	strNode* pTemp = NULL;
	while (pstrChan != NULL)
	{
		pTemp = pstrChan;
		pstrChan = pstrChan->pstrNext;
		delete pTemp;
	}
	return;
}

strNode *vCreatChan(int * piData, int iNum)
{
	int       iLoop = 0;
	strNode * pstrChanHead = NULL;
	strNode * pstrChanEnd = NULL;
	strNode * pstTemp = NULL;

	if ((NULL == piData) || (iNum < 1))
	{
		return NULL;
	}

	pstrChanHead = (strNode *)malloc(sizeof(strNode));
	pstrChanHead->data = *piData;
	pstrChanHead->pstrNext = NULL;

	pstrChanEnd = pstrChanHead;

	for (iLoop = 1; iLoop < iNum; iLoop++)
	{
		pstTemp = (strNode *)malloc(sizeof(strNode));
		pstTemp->data = piData[iLoop];
		pstTemp->pstrNext = NULL;

		pstrChanEnd->pstrNext = pstTemp;
		pstrChanEnd = pstrChanEnd->pstrNext;
	}

	return pstrChanHead;
}
int main()
{
	strNode * pstrIn = NULL;
	strNode * pstrOut = NULL;
	int  iLenth = 0;
	int  iaDataIn[7] = { 6, 7, 8, 8, 9, 10, 6 };
	int  iaDataOut[7] = { 10, 9, 7 };
	int  iaDataMyOut[7] = { 0 };

	pstrIn = vCreatChan(iaDataIn, 7);
	pstrOut = (strNode *)malloc(sizeof(strNode));
	pstrOut->pstrNext = NULL;

	iChanProcess(pstrIn, pstrOut);

	while (pstrOut != NULL)
	{
		cout << pstrOut->data << " ";
		pstrOut = pstrOut->pstrNext;
	}
}