#include "BaseRemover.h"

void BaseRemover::printFile(string path) {
    string line;

    ifstream file(path);

    if (!file.is_open()) {
        cout << "������: �� ������� ������� ����!" << endl;
        return;
    }

    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}