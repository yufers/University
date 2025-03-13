#include "FractionsHandler.h"

#include <iostream>
#include <exception>
#include <random>
#include <numeric>
#include <windows.h>

int main() {
	SetConsoleOutputCP(CP_UTF8);


	FractionUtils fractionUtils;
	FractionsHandler fr1(3, 5);
	FractionsHandler fr2(8, 6);

	FractionsHandler test1, test2, test3, test4; 
	bool test5, test6, test7, test8, test9;

	try {
		test1 = fr1 + fr2;
		test2 = fr1 - fr2;
		test3 = fr1 * fr2;
		test4 = fr1 / fr2;
		test5 = fr1 == fr2;
		test6 = fr1 > fr2;
		test7 = fr1 < fr2;
		test8 = fr1 >= fr2;
		test9 = fr1 <= fr2;
	}
	catch (const DivisionByZeroError& e1) {
		std::cout << e1.what() << std::endl;
	}
	catch (const OverflowError& e2) {
		std::cout << e2.what() << std::endl;
	}

	std::cout << "Результат 1, с сокращением дроби" << std::endl << std::endl;
	test1.fractionReduce().printFraction();
	test2.fractionReduce().printFraction();
	test3.fractionReduce().printFraction();
	test4.fractionReduce().printFraction();
	std::cout << "res for is == " << std::boolalpha << test5 << std::endl;
	std::cout << "res for is > " << std::boolalpha << test6 << std::endl;
	std::cout << "res for is < " << std::boolalpha << test7 << std::endl;
	std::cout << "res for is >= " << std::boolalpha << test8 << std::endl;
	std::cout << "res for is <= " << std::boolalpha << test9 << std::endl << std::endl;

	std::cout << "<===========================================>" << std::endl << std::endl;

	std::cout << "Результат 2, с выводом дроби в виде числа" << std::endl << std::endl;
	test1.printfractionInNum();
	test2.printfractionInNum();
	test3.printfractionInNum();
	test4.printfractionInNum();
	std::cout << "res for == is " << std::boolalpha << test5 << std::endl;
	std::cout << "res for is > " << std::boolalpha << test6 << std::endl;
	std::cout << "res for is < " << std::boolalpha << test7 << std::endl;
	std::cout << "res for is >= " << std::boolalpha << test8 << std::endl;
	std::cout << "res for is <= " << std::boolalpha << test9 << std::endl;

	std::cout << "<===========================================>" << std::endl << std::endl;

	FractionsHandler fr3 = fractionUtils.generateRandomFraction();
	FractionsHandler fr4 = fractionUtils.generateRandomFraction();

	try {
		test1 = fr3 + fr4;
		test2 = fr3 - fr4;
		test3 = fr3 * fr4;
		test4 = fr3 / fr4;
		test5 = fr3 == fr4;
		test6 = fr3 > fr4;
		test7 = fr3 < fr4;
		test8 = fr3 >= fr4;
		test9 = fr3 <= fr4;
	}
	catch (const DivisionByZeroError& e1) {
		std::cout << e1.what() << std::endl;
	}
	catch (const OverflowError& e2) {
		std::cout << e2.what() << std::endl;
	}

	std::cout << "Результат 3, рандомные дроби с сокращением" << std::endl << std::endl;
	test1.fractionReduce().printFraction();
	test2.fractionReduce().printFraction();
	test3.fractionReduce().printFraction();
	test4.fractionReduce().printFraction();
	std::cout << "res for is == " << std::boolalpha << test5 << std::endl;
	std::cout << "res for is > " << std::boolalpha << test6 << std::endl;
	std::cout << "res for is < " << std::boolalpha << test7 << std::endl;
	std::cout << "res for is >= " << std::boolalpha << test8 << std::endl;
	std::cout << "res for is <= " << std::boolalpha << test9 << std::endl << std::endl;

	std::cout << "<===========================================>" << std::endl << std::endl;
	std::cout << "Результат 4, пример ошибок" << std::endl << std::endl;

	FractionsHandler fr5(3, 0);
	FractionsHandler fr6(0, 100000000000000000);
	try {
		test1 = fr5 + fr6;
		test2 = fr5 - fr6;
		test3 = fr5 * fr6;
		test4 = fr5 / fr6;
	}
	catch (const DivisionByZeroError& e1) {
		std::cout << e1.what() << std::endl;
	}
	catch (const OverflowError& e2) {
		std::cout << e2.what() << std::endl;
	}

	std::cout << "<===========================================>" << std::endl << std::endl;
	std::cout << "Результат 5, пример ошибок" << std::endl << std::endl;

	FractionsHandler fr7(3, 5);
	FractionsHandler fr8(0, 100000000000000000);
	try {
		test1 = fr7 + fr8;
		test2 = fr7 - fr8;
		test3 = fr7 * fr8;
		test4 = fr7 / fr8;
	}
	catch (const DivisionByZeroError& e1) {
		std::cout << e1.what() << std::endl;
	}
	catch (const OverflowError& e2) {
		std::cout << e2.what() << std::endl;
	}

	return 0;
}
