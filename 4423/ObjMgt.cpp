
#include "ObjMgt.h"
#include <list>
using namespace std;

struct KEY
{
	unsigned int key1;
	unsigned int key2;
	unsigned int key3;
};

list<KEY> allKey;
/*************************************************************************
功能：增加单个对象
输入：
key1  外部关键字 KEY1
key2  外部关键字KEY2
key3  外部关键字KEY3
输出：无
返回：
-1 :失败(对象已经存在或者其它异常)
0 :成功
***************************************************************************/
int AddObject(unsigned int key1, unsigned int key2, unsigned int key3)
{
	if (allKey.size() > 10000)
		return -1;

	if (key1 > 65535 || key2 > 65535 || key3 > 65535)
		return -1;

	if (IsObjectExist(key1, key2, key3))
		return -1;

	KEY temp = { key1, key2, key3 };
	allKey.push_back(temp);
	return 0;
}

/********************************************************************************
功能：删除一个或多个对象
输入：
key1 外部关键字 KEY1
key2 外部关键字 KEY2
key3 外部关键字 KEY3
输出：无
返回：无

说明：用例保证参数取值为合法值和通配符0xFFFFFFFF, 通配符表示0~65535范围内的任意值;
举例:key1=1,key2=2,key3= 0xFFFFFFFF，表示删除key1=1,key2=2的所有对象;
key1,key2,key3取值全为0xFFFFFFFF时,表示删除所有对象。
*********************************************************************************/
void DeleteObject(unsigned int key1, unsigned int key2, unsigned int key3)
{
	bool flag1 = false, flag2 = false, flag3 = false; // 通配标识位

	if (key1 == 0xffffffff)
		flag1 = true;

	if (key2 == 0xffffffff)
		flag2 = true;

	if (key3 == 0xffffffff)
		flag3 = true;

	list<KEY>::iterator it = allKey.begin();
	while (it != allKey.end())
	{
		if (flag1 || it->key1 == key1)
		if (flag2 || it->key2 == key2)
		if (flag3 || it->key3 == key3)
		{
			it = allKey.erase(it); // 指向下一个位置
			continue;
		}
		++it;
	}

	return;
}

/********************************************************************************
功能：查询单个对象是否存在
输入：
key1 外部关键字 KEY1
key2 外部关键字 KEY2
key3 外部关键字 KEY3
输出：无
返回：
0：不存在
1：存在
**********************************************************************************/
int IsObjectExist(unsigned int key1, unsigned int key2, unsigned int key3)
{
	list<KEY>::iterator it = allKey.begin();
	while (it != allKey.end())
	{
		if (it->key1 == key1 && it->key2 == key2 && it->key3 == key3)
			return 1;
		++it;
	}

	return 0;
}

/******************************************************************************************************
Description     清空所有对象
Prototype       void Clear();
Input Param     无
Output Param    无
Return Value    无

********************************************************************************************************/
void Clear(void)
{
	allKey.clear();
	return;
}