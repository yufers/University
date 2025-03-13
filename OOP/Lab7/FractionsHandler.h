#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <exception>

class OverflowError : public std::overflow_error {
public:
	OverflowError(const std::string& errorText) : std::overflow_error(errorText) {}

	OverflowError() : std::overflow_error("Ошибка : переполнение") {}
};

class DivisionByZeroError : public std::domain_error {
public:
	DivisionByZeroError(const std::string& errorText) : std::domain_error(errorText) {}

	DivisionByZeroError() : std::domain_error("Ошибка : деление на ноль") {}
};

class FractionsHandler {
private:
	int num, denom;
public:
	FractionsHandler() : num(0), denom(0) {}
	FractionsHandler(int num, int denom) : num(num), denom(denom) {}

	int getNum() { return num; }
	int getDenom() { return denom; }

	FractionsHandler operator+(FractionsHandler f);
	FractionsHandler operator-(FractionsHandler f);
	FractionsHandler operator*(FractionsHandler f);
	FractionsHandler operator/(FractionsHandler f);

	bool operator==(FractionsHandler f);
    bool operator>(FractionsHandler f);
    bool operator<(FractionsHandler f);
    bool operator>=(FractionsHandler f);
    bool operator<=(FractionsHandler f);

	double fractionInNum();
	void printfractionInNum();
	void printFraction();
	FractionsHandler& fractionReduce();
};

class FractionUtils {
public:
	FractionsHandler generateRandomFraction();
};

#endif