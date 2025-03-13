#include <mutex>
#include <thread>
#include <iostream>
#include <random> 
#include <windows.h>

class Action {
protected:
	char* arr;
	int len;
	std::mutex& m1;
	std::mutex& m2;
	bool& updated_status;

public:
	Action(char* arr, int len, std::mutex& m1, std::mutex& m2, bool& updated_status) :
		arr(arr), len(len), m1(m1), m2(m2), updated_status(updated_status) {}

	virtual void makeOperation() const = 0;

	virtual void operator()() const {
		while (1)
		{
			m1.lock();
			m2.lock();

			makeOperation();

			updated_status = true;

			m2.unlock();
			using namespace std::literals;
			std::this_thread::sleep_for(1s);
			m1.unlock();
		}
	}
};

class CommandsUpper : public Action {
public:
	CommandsUpper(char* arr, int len, std::mutex& m1, std::mutex& m2, bool& updated_status) :
		Action(arr, len, m1, m2, updated_status) {}
	
	void makeOperation() const override {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distrib(0, len - 1);
		int index = distrib(gen);

		arr[index] = std::toupper(arr[index]);
	}
};

class CommandsLower : public Action {
public:
	CommandsLower(char* arr, int len, std::mutex& m1, std::mutex& m2, bool& updated_status) :
		Action(arr, len, m1, m2, updated_status) {
	}

	void makeOperation()  const override {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distrib(0, len - 1);
		int index = distrib(gen);

		arr[index] = std::tolower(arr[index]);
	}
};

class ResOut {
private:
	char* arr;
	int len;
	std::mutex& m2;
	bool& updated_status;

public:
	ResOut(char* arr, int len, std::mutex& m2, bool& updated_status) :
		arr(arr), len(len), m2(m2), updated_status(updated_status) {
	}

	void operator()() const {
		int p = 0;
		while (1)
		{
			m2.lock();

			if (updated_status) {
				std::string str(arr);
				std::cout << str << std::endl;
				updated_status = false;
			}

			m2.unlock();

			using namespace std::literals;
			std::this_thread::sleep_for(100ms);
		}
	}
};

int main() {
	setlocale(0, "RUS");

	char arr[21] = {'f', 'u', 'z', 'g', 'a', 'i', 'n', 'v', 'r', 't', 'x', 'y', 'a', 'm', 'j', 'c', 'u', 'p', 's', 'd', '\0'};
	std::mutex m1;
	std::mutex m2;
	
	bool updated_status = false;

	int len = sizeof(arr) / sizeof(char);

	CommandsUpper commandsUpper(arr, len, ref(m1), ref(m2), std::ref(updated_status));
	CommandsLower commandsLower(arr, len, ref(m1), ref(m2), std::ref(updated_status));
	ResOut resOut(arr, len, ref(m2), std::ref(updated_status));

	std::thread th1(commandsUpper);
	std::thread th2(commandsLower);

	std::thread th3(resOut);

	th1.join();
	th2.join();
	th3.join();

	std::cout << "finish";
	system("pause");
	return 0;
}