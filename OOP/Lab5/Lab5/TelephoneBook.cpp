#include "TelephoneBook.h"

#include <iostream>

void Person::printData() const {
	std::cout << lastName << " " <<
		address << " " <<
		number << std::endl;
}

bool Person::isMatch(std::string pattern) const {
	return (lastName.find(pattern) != std::string::npos) || 
		(address.find(pattern) != std::string::npos) ||
		(number.find(pattern) != std::string::npos);
}

void Organization::printData() const {
	std::cout << name << " " <<
		address << " " << 
		number << " " <<
		fax << " " <<
		contactPerson << std::endl;
}

bool Organization::isMatch(std::string pattern) const {
	return (name.find(pattern) != std::string::npos) || 
		(address.find(pattern) != std::string::npos) ||
		(number.find(pattern) != std::string::npos) || 
		(fax.find(pattern) != std::string::npos) ||
		(contactPerson.find(pattern) != std::string::npos);
}

void Friend::printData() const {
	std::cout << lastName << " " <<
		address << " " <<
		number << " " <<
		birthDate << std::endl;
}

bool Friend::isMatch(std::string pattern) const {
	return (lastName.find(pattern) != std::string::npos) || 
		(address.find(pattern) != std::string::npos) ||
		(number.find(pattern) != std::string::npos) || 
		(birthDate.find(pattern) != std::string::npos);
}

void Market::printData() const {
	std::cout << name << " " <<
		address << " " <<
		number << std::endl;
}

bool Market::isMatch(std::string pattern) const {
	return (name.find(pattern) != std::string::npos) ||
		(address.find(pattern) != std::string::npos) ||
		(number.find(pattern) != std::string::npos);
}

void VIPContact::printData() const {
	std::cout << name << " " <<
		number << std::endl;
}

bool VIPContact::isMatch(std::string pattern) const {
	return (name.find(pattern) != std::string::npos) ||
		(number.find(pattern) != std::string::npos);
}

void BookDataBase::addPerson(std::string lastName, std::string address, std::string number) {
	data.push_back(new Person(lastName, address, number));
}

void BookDataBase::addOrganization(std::string name, std::string address, std::string number, std::string fax, std::string contactPerson) {
	data.push_back(new Organization(name, address, number, fax, contactPerson));
}

void BookDataBase::addFriend(std::string lastName, std::string address, std::string number, std::string birthDate) {
	data.push_back(new Friend(lastName, address, number, birthDate));
}

void BookDataBase::addMarket(std::string name, std::string address, std::string number) {
	data.push_back(new Market(name, address, number));
}

void BookDataBase::addVIPContact(std::string name, std::string number) {
	data.push_back(new VIPContact(name, number));
}

void BookDataBase::dropDataTable() {
	for (auto& entry : data) {
		delete entry;
	}
}

void BookDataBase::printAllData() {
	for (auto entry : data) {
		entry->printData();
	}
}

size_t BookDataBase::countRecords() {
	return data.size();
}

std::vector<TelephoneBook*> BookDataBase::findMatched(std::string pattern) {
	std::vector<TelephoneBook*> matcedRecords;

	for (auto& entry : data) {
		if (entry->isMatch(pattern)) {
			matcedRecords.push_back(entry);
		}
	}
	return matcedRecords;
}