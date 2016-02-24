#include <stdlib.h>
#include "oj.h"
#include "CommonDef.h"

#include <iostream>
#include <list>
using namespace std;

class Task
{
public:
	TaskType type;
	TaskStatus status;
	TaskID id;

	Task(TaskType aType, TaskID aID)
	{
		type = aType;
		status = Waiting;
		id = aID;
	}
};

list<Task> TaskManager;
int WaitingATaskNums;

// 功能：初始化任务管理器
// 输入：无
// 输出：无         
// 返回：无
void initialize()
{
	WaitingATaskNums = 0;
}

// 功能：清空任务管理器中的任务队列
// 输入：无
// 输出：无         
// 返回：无
void finitialize()
{
	TaskManager.clear();
}

list<Task>::iterator FindTask(TaskID id)
{
	list<Task>::iterator ip = TaskManager.begin();
	while (ip != TaskManager.end())
	{
		if (ip->id == id)
			break;
		++ip;
	}
	return ip;
}
bool AddTaskOperate(TaskType type, TaskID id)
{
	Task newTask(type, id);
	if (type == ATask)
	{
		if (WaitingATaskNums >= MAX_WAITTING_ATASK)
			return false;
		else
			++WaitingATaskNums;
	}
	TaskManager.push_back(newTask);
	return true;
}

bool RunTaskOperate(TaskID id)
{
	list<Task>::iterator ip = FindTask(id);
	if (ip == TaskManager.end() || ip->status != Waiting)
		return false;

	ip->status = Finished;
	if (ip->type == ATask)
		--WaitingATaskNums;
	return true;
}

bool DelTaskOperate(TaskID id)
{
	list<Task>::iterator ip = FindTask(id);
	if (ip == TaskManager.end() || ip->status != Finished)
		return false;

	TaskManager.erase(ip);
	return true;
}

bool DelForceTaskOperate(TaskID id)
{
	list<Task>::iterator ip = FindTask(id);
	if (ip == TaskManager.end())
		return false;

	if (ip->type == ATask && ip->status == Waiting)
		--WaitingATaskNums;

	TaskManager.erase(ip);
	return true;
}

bool ClearTaskOperate(TaskType type)
{
	list<Task>::iterator ip = TaskManager.begin();
	int cnt = 0;
	while (ip != TaskManager.end())
	{
		if (ip->type == type && ip->status != Finished)
			return false;

		if (ip->type == type && ip->status == Finished)
			++cnt;
		++ip;
	}

	if (cnt == 0)
		return false;

	ip = TaskManager.begin();
	while (ip != TaskManager.end())
	{
		if (ip->type == type)
		{
			ip = TaskManager.erase(ip);
			continue;
		}
		++ip;
	}
	return true;
}
// 功能：操作任务，可以增加、运行、删除、强制删除、清除任务。
// 输入：TaskType type: 任务类型
//       TaskID id    : 任务ID，唯一标识任务
//       OperateType opType : 任务操作类型
// 输出：无         
// 返回：操作成功返回true，失败返回false
bool OperateTask(TaskType type, TaskID id, OperateType opType)
{
	bool res;
	switch (opType)
	{
	case AddTask:
		res = AddTaskOperate(type, id);
		break;
	case RunTask:
		res = RunTaskOperate(id);
		break;
	case DelTask:
		res = DelTaskOperate(id);
		break;
	case DelForceTask:
		res = DelForceTaskOperate(id);
		break;
	case ClearTask:
		res = ClearTaskOperate(type);
		break;
	default:
		break;
	}
	return res;
}

// 功能：获取Task当前状态
// 输入：TaskID id：查找的任务ID号
// 输出：TaskStatus &status：当前任务的状态
// 返回：无
void GetTaskStatus(TaskID id, TaskStatus &status)
{
	list<Task>::iterator ip = FindTask(id);
	if (ip == TaskManager.end())
		status = NotExist;
	else
		status = ip->status;
}