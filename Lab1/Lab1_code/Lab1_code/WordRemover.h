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
    string removeWords(string str, string word)
    {

        if (str.find(word) != string::npos) {
            string tempWord = word + " ";
            
            size_t p = -1;
            while ((p = str.find(word)) != string::npos) {
                str.replace(p, tempWord.length(), "");
            }

            tempWord = " " + word;
            while ((p = str.find(word)) != string::npos) {
                str.replace(p, tempWord.length(), "");
            }
        }

        return str;
    }

public:
    void deleteWords(string path) {
        ifstream file(path);

        if (!file.is_open()) {
            cout << "Open file error" << endl;
            return;
        }

        ostringstream oss;

        string line;
        map<string, int> wordCounts;

        while (getline(file, line)) {
            istringstream iss(line);
            string word;

            while (iss >> word) {
                if (wordCounts.find(word) == wordCounts.end()) {
                    wordCounts[word] = 0;
                }
                wordCounts[word]++;
            }
            for (auto [key, count] : wordCounts) {
                if (count >= 2) {
                    line = removeWords(line, key);
                }
            }
            oss << line << endl;
        }
        oss << endl;
        file.close();
        
        ofstream file_out(path);
        file_out << oss.str();

        file_out.close();
    }
};

