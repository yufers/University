#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <random>
#include <windows.h>

#include "task.h"

Task *TaskGenerator::generateTask()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib1(1, 6);
    int num1 = distrib1(gen);

    std::string type;

    switch (num1)
    {
    case 1:
        type = "add_file";
        break;
    case 2:
        type = "delete_file";
        break;
    case 3:
        type = "rename_file";
        break;
    case 4:
        type = "print_file";
        break;
    case 5:
        type = "add_data_file";
        break;
    case 6:
        type = "remove_data_file";
        break;
    }

    std::uniform_int_distribution<int> distrib2(2, 10);
    int num2 = distrib2(gen);

    unsigned long long id = timeSinceEpochMillisec();

    Task *task = new Task(type, num2, std::to_string(id));
    (*taskList).addTask(task);

    return task;
}

void TaskGenerator::operator()()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(5, 20);

    while (1)
    {
        Task *task = generateTask();
        std::cout << "generated: " << *task << std::endl;

        int num = distrib(gen);
        std::this_thread::sleep_for(static_cast<std::chrono::seconds>(num));
    }
}

unsigned long long TaskGenerator::timeSinceEpochMillisec()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void TaskList::addTask(Task *task)
{
    m1.lock();
    que.push(task);
    m1.unlock();
}

Task *TaskExecuter::takeTask()
{
    if ((*taskList).isEmpty())
    {
        return nullptr;
    }
    Task *task = (*taskList).pullTask();

    if (task == nullptr)
    {
        return nullptr;
    }

    return task;
}

void TaskExecuter::operator()()
{
    while (1)
    {

        Task *task = takeTask();

        if (task != nullptr)
        {
            std::this_thread::sleep_for(static_cast<std::chrono::seconds>(task->getTime()));

            std::cout << "finished: " << *task << std::endl;

            delete task;
        }
        else
        {
            std::this_thread::sleep_for(static_cast<std::chrono::seconds>(1));
        }
    }
}

Task *TaskList::pullTask()
{
    m1.lock();
    if (que.empty())
    {
        return nullptr;
    }
    Task *task = que.front();
    que.pop();
    m1.unlock();
    return task;
}

bool TaskList::isEmpty()
{
    return que.empty();
}