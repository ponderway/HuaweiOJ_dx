#include <iostream>
#include <stdlib.h>
using namespace std;


#define null 0
#define MAXSIZE 50

struct strlnode
{
	int data;
	struct strlnode *plast;
	struct strlnode *pnext;
};

void create(struct strlnode **p, int x)  /*创建双链表(表头节点)*/
{
	struct strlnode *q;

	q = (struct strlnode *)malloc(sizeof(struct strlnode));
	q->data = x;
	q->plast = null;
	q->pnext = null;

	*p = q;

	return;
}

void insertnode(struct strlnode **p, int i, int x) /* 在链表第i个位置插入数据等于x的节点 */
{
	// 由于没有头节点，要分头插，尾插以及在中间插

	strlnode *newNode;
	create(&newNode, x);

	if (p == NULL)
		*p = newNode;

	// 头插
	if (i == 0)
	{
		newNode->pnext = *p;
		(*p)->plast = newNode;
		*p = newNode;
		return;
	}

	strlnode *p1 = *p;
	int j = 0;
	while (j < i - 1 && p1->pnext != NULL)
	{
		p1 = p1->pnext;
		++j;
	}

	if (j != i - 1) // 越界
		return;

	// 尾插
	if (p1->pnext == NULL)
	{
		p1->pnext = newNode;
		newNode->plast = p1;
		return;
	}
	// 中插
	strlnode *p2 = p1->pnext;

	newNode->pnext = p2;
	newNode->plast = p1;
	p2->plast = newNode;
	p1->pnext = newNode;
}

void deletenode(struct strlnode **p, int i) /* 删除链表中第i个节点 */
{
	strlnode *p1 = *p;

	// 删除头结点
	if (i == 0)
	{
		*p = p1->pnext;
		delete p1;
	}

	int j = 0;
	while (j < i && p1->pnext != NULL)
	{
		p1 = p1->pnext;
		++j;
	}

	if (j != i)
		return;

	strlnode *p2 = p1->plast;
	// 删除尾节点
	if (p1->pnext == NULL)
	{
		p2->pnext = NULL;
		delete p1;
	}

	// 删除中间节点
	p2->pnext = p1->pnext;
	p1->pnext->plast = p2;
	delete p1;
}

int getnodenum(struct strlnode **p)  /*获取链表中节点个数*/
{
	int nodenum = 0;

	strlnode *p1 = *p;
	while (p1 != NULL)
	{
		++nodenum;
		p1 = p1->pnext;
	}
	return nodenum;
}

void TwoArrayPlus(int *a1, int len1, int *a2, int len2, int *a3, int &len3)
{
	int p1 = len1 - 1;
	int p2 = len2 - 1;
	//int len3 = 0;
	int i = 0;
	int token = 0;
	while (p1 >= 0 && p2 >= 0)
	{
		int temp = a1[p1] + a2[p2] + token;
		a3[i] = temp % 10;
		token = temp / 10;
		--p1;
		--p2;
		++i;
	}

	while (p1 >= 0)
	{
		int temp = a1[p1] + token;
		a3[i] = temp % 10;
		token = temp / 10;
		--p1;
		++i;
	}

	while (p2 >= 0)
	{
		int temp = a2[p2] + token;
		a3[i] = temp % 10;
		token = temp / 10;
		--p2;
		++i;
	}

	if (token)
	{
		a3[i] = token;
		len3 = i + 1;
	}
	else
		len3 = i;

	//for (int i = 0; i < len3; ++i)
	//	cout << a3[i];

	for (int i = 0; i < len3 / 2; ++i)
	{
		int temp = a3[i];
		a3[i] = a3[len3 - 1 - i];
		a3[len3 - 1 - i] = temp;
	}

	//for (int i = 0; i < len3; ++i)
	//	cout << a3[i];
	//cout << endl;

}


void readtolnode(struct strlnode **p, int *a, int size)  /* 将数组写入链表中，链表中的数据的先后顺序和数组中的顺序要保持一致 */
{
	int j = 0;
	int data = 0;
	struct strlnode *s = *p;

	s->data = *(a + (size - 1));

	for (j = 2; j < (size + 1); j++)
	{
		data = *(a + (size - j));
		insertnode(p, 0, data);
	}

	return;
}


void writetosqlist(int *a, struct strlnode *p)  /* 将链表写入数组中，数组中的数据的先后顺序和链表中的顺序要保持一致 */
{
	int j = 0;
	struct strlnode *s = p;

	while (s != null)
	{
		*(a + j) = s->data;
		s = s->pnext;
		j++;
	}

	return;
}

void bignumberplus(struct strlnode **plus, struct strlnode **p, struct strlnode **q) /* 使用链表实现大整数相加 */
{
	int len1 = getnodenum(p);
	int len2 = getnodenum(q);
	int *a1 = new int[len1];
	int *a2 = new int[len2];
	writetosqlist(a1, *p);
	writetosqlist(a2, *q);
	int len3 = len1 > len2 ? len1 : len2;
	int *a3 = new int[len3 + 1];
	TwoArrayPlus(a1, len1, a2, len2, a3, len3);
	readtolnode(plus, a3, len3);

}
