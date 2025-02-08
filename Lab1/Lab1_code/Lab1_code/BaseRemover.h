#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <filesystem>

using namespace std;

#pragma once
class BaseRemover
{
public:
    void printFile(string path) {
        string line;

        ifstream file(path);

        if (!file.is_open()) {
            cout << "Ошибка: не удалось открыть файл!" << endl;
            return;
        }

        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
};

