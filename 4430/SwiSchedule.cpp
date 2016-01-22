#include <iostream>
#include <queue>
#include <map>
using namespace std;

/******************************************************************************

Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

******************************************************************************
File Name     :
Version       :
Author        :
Created       : 2010/3
Last Modified :
Description   :
Function List :

History       :
1.Date        : 2010/3
Author      :
Modification: Created file

******************************************************************************/
typedef  void(*PROC_FUN)(void);
struct Node
{
	unsigned int swiId;
	unsigned int prio;
	PROC_FUN proc;

	friend bool operator <(Node node1, Node node2)
	{
		return node1.prio > node2.prio;
	}
};

class LessThan
{
public:
	bool operator ()()
	{
		return node1.prio > node2.prio;
	}

private:
	Node node1, node2;
};
priority_queue<Node> swiQueue; //优先级从小到大
map<unsigned int, Node> swiMap;
int runningId;

/*************************************************************************************************
函数说明：创建软中断
输入参数：
swiId： 创建软中断ID；
prio：  创建软中断优先级；
proc：  创建软中断处理函数。
输出参数：无
返回值  ：成功返回0， 其它情况返回-1
**************************************************************************************************/
int SwiCreate(unsigned int swiId, unsigned int prio, void(*proc)(void))
{
	//TODO: 添加代码...
	Node swiNode = { swiId, prio, proc };
	if (prio < 0 || prio > 31 || proc == NULL || swiMap.count(swiId))
		return -1;

	swiMap[swiId] = swiNode;
	return 0;
}

/*************************************************************************************************
函数说明：软中断激活
输入参数：swiId： 待激活软中断ID
输出参数：无
返回值  ：成功返回0， 其它情况返回-1
**************************************************************************************************/
int SwiActivate(unsigned int swiId)
{
	if (!swiMap.count(swiId))
		return -1;
	swiQueue.push(swiMap[swiId]);

	while (!swiQueue.empty())
	{
		Node tempNode = swiQueue.top();
		if (runningId != tempNode.swiId)
		{
			int oldRunningId = runningId;
			runningId = tempNode.swiId;
			tempNode.proc();
			runningId = oldRunningId;
			swiQueue.pop();
		}
		else
			break;

	}

	return 0;
}

/*************************************************************************************************
函数说明：清空所有的信息
输入参数：无
输出参数：无
返回值  ：无
**************************************************************************************************/
void Clear(void)
{
	//TODO: 添加代码...
	runningId = -1;
	swiMap.clear();
	while (!swiQueue.empty())
		swiQueue.pop();
}
