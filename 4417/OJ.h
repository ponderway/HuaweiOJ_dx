#ifndef __OJ_H__
#define __OJ_H__

/*
功能:

输入:

输出:

返回:
*/

typedef struct strNode
{
	int data;
	strNode * pstrNext;
}strNode;


int iChanProcess(strNode * pstrIn, strNode * pstrOut);
void vFreeChan(strNode * pstrChan);

#endif
