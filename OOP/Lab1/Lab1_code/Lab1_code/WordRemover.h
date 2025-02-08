#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <filesystem>

#include "BaseRemover.h"

using namespace std;

#pragma once
class WordRemover : public BaseRemover
{
private:
    string removeWords(string str, string word);

public:
    void deleteWords(string path);
};

