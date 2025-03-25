#include <iostream>
#include <fstream>
#include <random>
#include <numeric>

const int NUM_CAFEDRAL = 4;
const int NUM_GROUP = 4;
const int NUM_STUDENT = 4;
const int NUM_SESSION = 4;
const int NUM_SUBJECT = 4;
const int NUM_GRADE = 5;

void generateData(const std::string& filename) {
    std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, NUM_GRADE);

    std::ofstream file(filename);

    for (int c = 1; c <= NUM_CAFEDRAL; c++) {
        for (int g = 1; g <= NUM_GROUP; g++) {
            for (int s = 1; s <= NUM_STUDENT; s++) {
                for (int se = 1; se <= NUM_SESSION; se++) {
                    for (int su = 1; su <= NUM_SUBJECT; su++) {
                        file << c << "->" << g << "->" << s << "->" << se << "->" << su << "->" << dist(gen) << "\n";
                    }
                }
            }
        }
    }
    file.close();
}
