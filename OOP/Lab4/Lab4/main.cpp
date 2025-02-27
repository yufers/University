#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdio>

class StringMethods {
private:
	char* ptr;
	int n;

public:
	StringMethods(int n) : n(n) {
		ptr = new char[n + 1]; 
		ptr[0] = '\0';
	}

	StringMethods(int n, const char* ptr) : n(n) {
		this->ptr = new char[n + 1];
		strncpy(this->ptr, ptr, n);
		this->ptr[n] = '\0';
	}

	~StringMethods() {
		delete[] ptr;
	}

	void input() {
		int i = 0;
		while (i < n) {
			fgets(ptr + i, 2, stdin);
			if (*(ptr + i) != '\n') {
				i++;
			}
		}
		ptr[n] = '\0';
	}

	int countSpaces() {
		int spaces = 0;
		for (int i = 0; i < n; i++) {
			if (ptr[i] == '\0') {
				break;
			}
			if (ptr[i] == ' ') {
				spaces++;
			}
		}
		return spaces;
	}

	void upperToLower() {
		for (int i = 0; i < n; i++) {
			if (ptr[i] == '\0') {
				break;
			}
			if (isupper(ptr[i])) {
				ptr[i] = tolower(ptr[i]);
			}
		}
	}

	void removePunctuation() {
		int j = 0;
		for (int i = 0; ptr[i] != '\0'; i++) {
			if (!ispunct(ptr[i])) {
				ptr[j++] = ptr[i];
			}
		}
		ptr[j] = '\0';
	}

	int length() {
		int len = 0;
		for (int i = 0; i < n; i++) {
			if (ptr[i] == '\0') {
				break;
			}
			len++;
		}
		return len;
	}

	void print() {
		std::cout << ptr << std::endl;
	}

	StringMethods operator/(const StringMethods& other) {
		int otherLen = strlen(other.ptr);
		if (otherLen == 0) {
			throw std::runtime_error("Деление на строку нулевой длины невозможно");
		}

		int newLength = length() / otherLen;

		char* newStr = new char[newLength + 1];
		for (int i = 0; i < newLength; i++) {
			newStr[i] = ptr[i];
		}
		newStr[newLength] = '\0';

		StringMethods result(newLength, newStr);
		delete[] newStr;

		return result;
	}

	void operator>>(int shift) {
		if (shift <= 0 || shift >= n) return;

		for (int i = n - 1; i >= shift; i--) {
			ptr[i] = ptr[i - shift];
		}
		for (int i = 0; i < shift; i++) {
			ptr[i] = ' ';
		}
	}
};

int main() {
	setlocale(LC_ALL, "Russian");

	int n;
	std::cout << "Введите длину: ";
	std::cin >> n;
	
	StringMethods text1(n);
	std::cout << "Введите текст: ";
	text1.input();

	int spaces = text1.countSpaces();
	std::cout << "Количество пробелов: " << spaces << std::endl;

	text1.upperToLower();
	std::cout << "Замена прописных символов на строчные: ";
	text1.print();

	text1.removePunctuation();
	std::cout << "Текст после удаления пунктуации: ";
	text1.print();

	char testStr[] = "abc\0";
	StringMethods test(3, testStr);

	StringMethods text2 = text1 / test;
	std::cout << "Результат деления строк: ";
	text2.print();

	text1 >> 2;
	std::cout << "Сдвиг на 2 символа: ";
	text1.print();

	return 0;
}