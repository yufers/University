#include <filesystem> 
#include <iostream>

#include "WordRemover.h"
#include "NumsRemover.h"

using namespace std;

int main() {
	string path;
	cin >> path;

	WordRemover wordRemover;
	NumsRemover numsRemover;

	filesystem::path p(path.c_str());
	string filename = p.filename().string();

	if (filename == "text1.txt") {
		cout << "before:" << endl << "----------------------" << endl;
		wordRemover.printFile(path);

		wordRemover.deleteWords(path);
		cout << endl;

		cout << "after:" << endl << "----------------------" << endl;
		wordRemover.printFile(path);
	}
	else if (filename == "text2.txt") {
		cout << "before:" << endl << "----------------------" << endl;
		numsRemover.printFile(path);

		numsRemover.removeNums(path);
		cout << endl;

		cout << "after:" << endl << "----------------------" << endl;
		numsRemover.printFile(path);
	}
	return 0;
}