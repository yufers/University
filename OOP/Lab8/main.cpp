#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>

#include "QuaternaryTree.h"

std::vector<std::vector<int>> loadDataFromFile(std::string path)
{
    std::vector<std::vector<int>> vals;

    std::ifstream file(path);
    if (!file)
    {
        std::cerr << "open error" << std::endl;
        return vals;
    }

    std::string line;
    while (std::getline(file, line))
    {
        line = std::regex_replace(line, std::regex("->"), " ");

        std::vector<int> row;
        std::stringstream ss(line);
        int num;
        while (ss >> num)
        {
            row.push_back(num);
        }

        vals.push_back(row);
    }

    file.close();

    return vals;
}

int main()
{

    std::vector<std::vector<int>> nums = loadDataFromFile("..\\test.txt");

    QuaternaryTree<int> tree;
    try
    {
        tree.insert(1);
        auto root = tree.getRoot();

        for (auto row : nums)
        {
            auto childC = tree.getChild(root, row[0] - 1);
            if (!childC)
            {
                tree.insert(row[0], root, row[0] - 1);
                childC = tree.getChild(root, row[0] - 1);
            }

            auto childCGr = tree.getChild(childC, row[1] - 1);
            if (!childCGr)
            {
                tree.insert(row[1], childC, row[1] - 1);
                childCGr = tree.getChild(childC, row[1] - 1);
            }

            auto childCSt = tree.getChild(childCGr, row[2] - 1);
            if (!childCSt)
            {
                tree.insert(row[2], childCGr, row[2] - 1);
                childCSt = tree.getChild(childCGr, row[2] - 1);
            }

            auto childCSes = tree.getChild(childCSt, row[3] - 1);
            if (!childCSes)
            {
                tree.insert(row[3], childCSt, row[3] - 1);
                childCSes = tree.getChild(childCSt, row[3] - 1);
            }

            auto childCPr = tree.getChild(childCSes, row[4] - 1);
            if (!childCPr)
            {
                tree.insert(row[4], childCSes, row[4] - 1);
                childCPr = tree.getChild(childCSes, row[4] - 1);
            }

            tree.insert(row[5], childCPr, 0);

            for (auto num : row)
            {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }

        tree.sortStudentsByGrades(root);

        for (int i = 0; i < 4; ++i)
        {
            auto studentNode = tree.getChild(root, i);
            if (studentNode)
            {
                tree.sortSubjectsByType(studentNode);
            }
        }

        tree.print();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}