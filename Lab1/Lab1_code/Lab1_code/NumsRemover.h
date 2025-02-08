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
	void removeNums(string path) {
		ifstream file(path);

		if (!file.is_open()) {
			cout << "Open file error" << endl;
			return;
		}

		ostringstream oss;

		int positive_count = 0, negative_count = 0;
		vector<int> positive;
		vector<int> negative;
		
		string line;
		while (getline(file, line)) {
			istringstream iss(line);

			int num;
			
			while (iss >> num) {
				if (num > 0) {
					positive.push_back(num);
					positive_count++;
				}
				else {
					negative.push_back(num);
					negative_count++;
				}
			}

			if (positive_count > negative_count) {
				positive.resize(negative_count);
			} else if (positive_count < negative_count) {
				negative.resize(positive_count);
			}

			bool first = true;
			while (!positive.empty() && !negative.empty()) {
				if (first) {
					first = false;
				} else {
					oss << " ";
				}
				oss << positive.back() << " " << negative.back();
				positive.pop_back(), negative.pop_back();
			}
		}
		oss << endl;

		file.close();

		ofstream file_out(path);
		file_out << oss.str();

		file_out.close();
	}
};

