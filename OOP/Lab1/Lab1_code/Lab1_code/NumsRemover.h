#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "BaseRemover.h"

using namespace std;

#pragma once
class NumsRemover : public BaseRemover
{
public:
	void removeNums(string path);
};

