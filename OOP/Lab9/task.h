#ifndef TASK_H
#define TASK_H

#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <windows.h>
#include <chrono>
#include <cstdint>

class Task
{
private:
    std::string type;
    int time;
    std::string id;

public:
    Task(std::string &type) : type(type), time(5) {}
    Task(std::string &type, int time) : type(type), time(time) {}
    Task(const std::string &type, int time, std::string id)
        : type(type), time(time), id(id) {}

    void setType(std::string type)
    {
        this->type = type;
    }

    std::string getType()
    {
        return type;
    }

    operator std::string() const
    {
        return type;
    }

    int getTime()
    {
        return time;
    }

    std::string getId()
    {
        return id;
    }

    friend std::ostream &operator<<(std::ostream &os, const Task &task)
    {
        os << "ID: " << task.id << " | Type: " << task.type << " | Time of process: " << task.time;
        return os;
    }
};

class TaskList
{
private:
    std::queue<Task *> que;
    std::mutex m1;

public:
    void addTask(Task *task);
    Task *pullTask();
    bool isEmpty();
};

class TaskExecuter
{
private:
    TaskList *taskList;

public:
    TaskExecuter(TaskList *taskList) : taskList(taskList) {}

    Task *takeTask();
    virtual void operator()();
};

class TaskGenerator
{
private:
    TaskList *taskList;

public:
    TaskGenerator(TaskList *taskList) : taskList(taskList) {}

    Task *generateTask();
    unsigned long long timeSinceEpochMillisec();
    virtual void operator()();
};

#endif