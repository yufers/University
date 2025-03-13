#include "FractionsHandler.h"

#include <iostream>
#include <exception>
#include <random>
#include <numeric>

FractionsHandler FractionsHandler::operator+(FractionsHandler f) {
	if (denom == 0 || f.denom == 0) { throw DivisionByZeroError(); }

	if (num > INT_MAX / f.denom || f.num > INT_MAX / denom) {
		throw OverflowError();
	}

	if (denom > INT_MAX / f.denom) { throw OverflowError(); }

	int new_num = num * f.denom + f.num * denom;

	int new_denom = denom * f.denom;

	return FractionsHandler(new_num, new_denom);
}

FractionsHandler FractionsHandler::operator-(FractionsHandler f) {
	if (denom == 0 || f.denom == 0) { throw DivisionByZeroError(); }

	if (num > INT_MAX / f.denom || f.num > INT_MAX / denom) {
		throw OverflowError();
	}

	if (denom > INT_MAX / f.denom) { throw OverflowError(); }

	int new_num = num * f.denom - f.num * denom;
	int new_denom = denom * f.denom;

	return FractionsHandler(new_num, new_denom);
}

FractionsHandler FractionsHandler::operator*(FractionsHandler f) {
	if (denom == 0 || f.denom == 0) { throw DivisionByZeroError(); }

	if (num > INT_MAX / f.num) { throw OverflowError(); }
	int new_num = num * f.num;

	if (denom > INT_MAX / f.denom) { throw OverflowError(); }
    int new_denom = denom * f.denom;

	return FractionsHandler(new_num, new_denom);
} 

FractionsHandler FractionsHandler::operator/(FractionsHandler f) {
    if (denom == 0 || f.denom == 0 || f.num == 0) { throw DivisionByZeroError(); }

    if (num > INT_MAX / f.denom) { throw OverflowError(); }
    int new_num = num * f.denom;

    if (denom > INT_MAX / f.num) { throw OverflowError(); }
    int new_denom = denom * f.num;

    return FractionsHandler(new_num, new_denom);
}

bool FractionsHandler::operator==(FractionsHandler f) {
    return fractionInNum() == f.fractionInNum();
}

bool FractionsHandler::operator>(FractionsHandler f) {
    return fractionInNum() > f.fractionInNum();
}

bool FractionsHandler::operator<(FractionsHandler f) {
    return fractionInNum() < f.fractionInNum();
}

bool FractionsHandler::operator>=(FractionsHandler f) {
    return fractionInNum() >= f.fractionInNum();
}

bool FractionsHandler::operator<=(FractionsHandler f) {
    return fractionInNum() <= f.fractionInNum();
}

double FractionsHandler::fractionInNum() {
	return (num + 0.0) / denom;
}

void FractionsHandler::printfractionInNum() {
	std::cout << fractionInNum() << std::endl;
}

void FractionsHandler::printFraction() {
	std::cout << num << " / " << denom << std::endl;
}

FractionsHandler& FractionsHandler::fractionReduce() {
	int nod_val = std::gcd(num, denom);

	num /= nod_val;
	denom /= nod_val;

	return *this;
}

FractionsHandler FractionUtils::generateRandomFraction() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, INT_MAX);
	 
	int random_num = dist(gen);
	int random_denum = dist(gen);
	return FractionsHandler(random_num, random_denum);
}
