#include <iostream>

#include "task.h"

int main()
{
    TaskList taskList;
    TaskGenerator generator1(&taskList);
    TaskExecuter executer1(&taskList);
    TaskGenerator generator2(&taskList);
    TaskExecuter executer2(&taskList);
    TaskGenerator generator3(&taskList);
    TaskExecuter executer3(&taskList);

    std::thread tg1(generator1);
    std::thread te1(executer1);
    std::this_thread::sleep_for(static_cast<std::chrono::seconds>(1));
    std::thread tg2(generator2);
    std::this_thread::sleep_for(static_cast<std::chrono::seconds>(1));
    std::thread tg3(generator3);

    tg1.join();
    te1.join();
    tg2.join();
    tg3.join();

    std::cout << "finish";
    system("pause");
    return 0;
}