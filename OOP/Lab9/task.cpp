#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <random>
#include <windows.h>
#include <filesystem>
#include <fstream>

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

    std::uniform_int_distribution<int> distrib2(2, 7);
    int num2 = distrib2(gen);

    unsigned long long id = timeSinceEpochMillisec() / 1000 / 15;

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

void TaskExecuter::addFile(std::string filename, std::filesystem::path filePath)
{
    std::ofstream file(filePath);
    if (file)
    {
        std::cout << "Created file: " << filename << std::endl;
    }
}

void TaskExecuter::deleteFile(std::string filename, std::filesystem::path filePath)
{
    if (std::filesystem::exists(filePath))
    {
        std::filesystem::remove(filePath);
        std::cout << "Deleted file: " << filename << std::endl;
    }
}

void TaskExecuter::renameFile(std::string filename, std::filesystem::path filePath)
{
    if (std::filesystem::exists(filePath)) {
        std::string newFilename = "..\\tasks\\renamed_" + filename;
        std::filesystem::rename(filePath, newFilename);
        std::cout << "Renamed file to: " << newFilename << std::endl;
    }
}

void TaskExecuter::printFile(std::string filename, std::filesystem::path filePath)
{
    std::ifstream file(filePath);

    if (file)
    {
        std::cout << "Contents of " << filename << ":\n";
        std::string line;
        while (std::getline(file, line))
        {
            std::cout << line << std::endl;
        }
    }
}

void TaskExecuter::addDataFile(std::string filename, std::filesystem::path filePath, std::string Id)
{
    std::ofstream file(filePath, std::ios::app);
    if (file)
    {
        file << "Random data " << Id << "\n";
        std::cout << "Added data to file: " << filename << std::endl;
    }
}

void TaskExecuter::removeDataFile(std::string filename, std::filesystem::path filePath)
{
    std::ofstream file(filePath, std::ios::trunc);
    if (file)
    {
        std::cout << "Cleared contents of file: " << filename << std::endl;
    }
}

void TaskExecuter::operator()()
{
    while (true)
    {
        Task *task = takeTask();

        if (task != nullptr)
        {
            std::cout << "Before executing task: " << std::endl;
            std::string filename = "file_" + task->getId() + ".txt";
            std::filesystem::path filePath = std::filesystem::current_path() / ".." /"tasks" / filename;

            std::string type = task->getType();

            if (type == "add_file")
            {
                addFile(filename, filePath);
            }
            else if (type == "delete_file")
            {
                deleteFile(filename, filePath);
            }
            else if (type == "rename_file")
            {
                renameFile(filename, filePath);
            }
            else if (type == "print_file")
            {
                printFile(filename, filePath);
            }
            else if (type == "add_data_file")
            {
                std::string Id = task->getId();
                addDataFile(filename, filePath, Id);
            }
            else
            {
                removeDataFile(filename, filePath);
            }

            delete task;
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
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