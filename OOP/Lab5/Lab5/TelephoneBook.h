#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

class TelephoneBook {
public:
	virtual void printData() const = 0;
	virtual bool isMatch(std::string pattern) const = 0;

	virtual ~TelephoneBook() {}
};

class Person : public TelephoneBook {
protected:
	std::string lastName;
	std::string address;
	std::string number;

public:
	Person(std::string lastName, std::string address, std::string number) :
		lastName(lastName), address(address), number(number) {}

	void printData() const override;
	bool isMatch(std::string pattern) const override;
};

class Organization : public TelephoneBook {
protected:
	std::string name;
	std::string address;
	std::string number;
	std::string fax;
	std::string contactPerson;

public:
	Organization(std::string name, std::string address, std::string number, std::string fax, std::string contactPerson) :
		name(name), address(address), number(number), fax(fax), contactPerson(contactPerson) {}

	void printData() const override;
	bool isMatch(std::string pattern) const override;
};

class Friend : public TelephoneBook {
protected:
	std::string lastName;
	std::string address;
	std::string number;
	std::string birthDate;

public:
	Friend(std::string lastName, std::string address, std::string number, std::string birthDate) :
		lastName(lastName), address(address), number(number), birthDate(birthDate) {}

	void printData() const override;
	bool isMatch(std::string pattern) const override;
};

class Market : public TelephoneBook {
protected:
	std::string name;
	std::string address;
	std::string number;

public:
	Market(std::string name, std::string address, std::string number) :
		name(name), address(address), number(number) {}

	void printData() const override;
	bool isMatch(std::string pattern) const override;
};

class VIPContact : public TelephoneBook {
protected:
	std::string name;
	std::string number;

public:
	VIPContact(std::string name, std::string number) :
		name(name), number(number) {
	}

	void printData() const override;
	bool isMatch(std::string pattern) const override;
};

class BookDataBase {
private:
	std::vector<TelephoneBook*> data;

public:
	void addPerson(std::string lastName, std::string address, std::string number);
	void addOrganization(std::string name, std::string address, std::string number, std::string fax, std::string contactPerson);
	void addFriend(std::string lastName, std::string address, std::string number, std::string birthDate);
	void addMarket(std::string name, std::string address, std::string number);
	void addVIPContact(std::string name, std::string number);
	void dropDataTable();
	void printAllData();

	size_t countRecords();
	std::vector<TelephoneBook*> findMatched(std::string pattern);
};

#endif
