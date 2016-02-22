// 时间超限
#include <iostream>
#include <map>
#include <deque>
#include <algorithm>
#include <vector>
using namespace std;
//结构体tLine表示一条双向的线段
typedef struct
{
	int pot1;
	int pot2;
}tLine;

class node
{
public:
	tLine line;
	bool visited;

	node(tLine theLine)
	{
		line = theLine;
		visited = false;
	}

};

vector<node> Lines;			// 线段集合
map<int, vector<int>> Map;  // 图：节点， 以及与节点相连的点
deque<int> res; // 路径节点

// 判断线段是否被访问了
bool IsVisited(int pot1, int pot2)
{
	if (pot1 > pot2)
		swap(pot1, pot2);

	for (int i = 0; i < Lines.size(); ++i)
	{
		if (Lines[i].line.pot1 == pot1 && Lines[i].line.pot2 == pot2)
			return Lines[i].visited;
	}
}

// 设置线段访问标识
void SetVisited(int pot1, int pot2)
{
	if (pot1 > pot2)
		swap(pot1, pot2);

	for (int i = 0; i < Lines.size(); ++i)
	{
		if (Lines[i].line.pot1 == pot1 && Lines[i].line.pot2 == pot2)
		{
			Lines[i].visited = true;
		}
	}
}

// 重置线段访问标识
void ResetVisited(int pot1, int pot2)
{
	if (pot1 > pot2)
		swap(pot1, pot2);

	for (int i = 0; i < Lines.size(); ++i)
	{
		if (Lines[i].line.pot1 == pot1 && Lines[i].line.pot2 == pot2)
		{
			Lines[i].visited = false;
		}
	}
}

//  对数据进行初始化
void Init(int n, tLine* arrLines)
{
	for (int i = 0; i < n; ++i)
	{
		node temp(arrLines[i]);
		Lines.push_back(temp);

		Map[arrLines[i].pot1].push_back(arrLines[i].pot2);
		Map[arrLines[i].pot2].push_back(arrLines[i].pot1);
	}
	for (int i = 0; i < Map.size(); ++i)
		sort(Map[i].begin(), Map[i].end());
}

// 是否找到路径
bool IsFind()
{
	for (int i = 0; i < Lines.size(); ++i)
	{
		if (Lines[i].visited == false)
			return false;
	}
	return true;
}

// 依次对边进行遍历
// pot: 节点
bool GetPath(int pot)
{

	bool found = false;
	for (int i = 0; i < Map[pot].size(); ++i)
	{
		int pot1 = pot;
		int pot2 = Map[pot][i];
		if (!IsVisited(pot1, pot2))
		{
			if (res.empty())
				res.push_back(pot1);

			res.push_back(pot2);

			SetVisited(pot1, pot2);
			found = GetPath(pot2);

			if (found)
				return true;
			
			ResetVisited(pot1, pot2);
			res.pop_back();
		}
	}

	return IsFind();
}

/************************************************************************
Description  : 一笔画出给定图形
Prototype    :
Input Param  : n表示要画的线段的条数
arrLines表示由多条线段组成的图形，由调用者负责指针的分配，释放和保证合法性
Output Param : 	aDrawline输出画线顺序，调用者保证指针合法性，由调用者负责指针的分配，释放和保证合法性
Return Value :	 成功返回 0 ，失败返回-1
/************************************************************************/
int OneLineDrawMap(int n, tLine* arrLines, int* aDrawline)
{
	Init(n, arrLines);
	if (!GetPath(1))
		return -1;

	for (int i = 0; i < res.size(); ++i)
		aDrawline[i] = res[i];
	return 0;
}

int main()
{
	tLine aMap[3] = { { 1, 2 }, { 1, 3 }, { 2, 3 } };
	// tLine aMap[] = { { 1, 2 }, { 1, 4 }, { 2, 3 }, { 3, 4 }, { 1, 3 } };
	// tLine aMap[6] = { { 1, 2 }, { 1, 3 }, { 1, 4 }, { 2, 3 }, { 2, 4 }, { 3, 4 } };
	//Init(5, aMap);
	//test2(1);
	//cout << endl;
	 int *a = new int[20];
	 OneLineDrawMap(3, aMap, a);

	 for (int i = 0; i < 4; ++i)
		 cout << a[i] << " ";
	 cout << endl;

}