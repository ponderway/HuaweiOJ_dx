#ifndef COMMON_DEF_H
#define COMMON_DEF_H

//A类任务的最大个数
#define MAX_WAITTING_ATASK 100

enum TaskType
{
	ATask,			//A类任务
	BTask,			//B类任务
	CTask,			//C类任务
	NTask = 255		//无效任务
};

enum OperateType
{
	AddTask,		//增加任务
    RunTask,		//运行任务
	DelTask,		//删除任务
	DelForceTask,	//强制删除任务
	ClearTask		//清除一类任务	
};

enum TaskStatus
{
	Waiting,    //任务被创建起来，未运行状态
	Finished,   //任务运行结束，等待被删除
	NotExist    //任务已经被删除，未创建过的任务也是此状态
};

typedef unsigned int TaskID;

#endif