#include "TelephoneBook.h"
#include <vector>
#include <iostream>

int main() {
	setlocale(LC_ALL, "Russian");
	BookDataBase bookDataBase;
	
	bookDataBase.addPerson("Мовчан", "ул. Улица", "34534536");
	bookDataBase.addPerson("Пвповла", "ул. Улица", "12345678");
	bookDataBase.addPerson("Яплдап", "ул. Улица", "87654321");

	bookDataBase.addOrganization("ООО Мовчан", "ул. Улица 1", "12345", "123", "Антон");
	bookDataBase.addOrganization("ООО Fdg", "ул. Адская", "54321", "321", "Антон1");
	bookDataBase.addOrganization("ООО ssdcds", "ул. Улица 1", "13579", "135", "Антон2");

	bookDataBase.addFriend("Дмитриев", "ул. Адская", "098", "21-02-2004");
	bookDataBase.addFriend("Дмитриев1", "ул. Адская", "456", "23-02-2004");
	bookDataBase.addFriend("Дмитриев1", "ул. Адская1", "189", "17-02-2004");

	bookDataBase.addMarket("magazin1", "adres1", "88001");
	bookDataBase.addMarket("magazin2", "adres2", "88002");

	bookDataBase.addVIPContact("VIPANTON1", "322");
	bookDataBase.addVIPContact("VIPANTON2", "223");

	size_t count = bookDataBase.countRecords();
	std::cout << "Количество записей: " << count << std::endl;
	std::cout << "---------------------------------------------" << std::endl;

	std::vector<TelephoneBook*> matchesTable = bookDataBase.findMatched("ул. Адс");

	for (auto entry : matchesTable) {
		entry->printData();
	}

	std::cout << "---------------------------------------------" << std::endl;

	bookDataBase.printAllData();

	bookDataBase.dropDataTable();
}