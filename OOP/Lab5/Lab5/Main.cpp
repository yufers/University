#include "TelephoneBook.h"
#include <vector>
#include <iostream>

int main() {
	setlocale(LC_ALL, "Russian");
	BookDataBase bookDataBase;
	
	bookDataBase.addPerson("������", "��. �����", "34534536");
	bookDataBase.addPerson("�������", "��. �����", "12345678");
	bookDataBase.addPerson("������", "��. �����", "87654321");

	bookDataBase.addOrganization("��� ������", "��. ����� 1", "12345", "123", "�����");
	bookDataBase.addOrganization("��� Fdg", "��. ������", "54321", "321", "�����1");
	bookDataBase.addOrganization("��� ssdcds", "��. ����� 1", "13579", "135", "�����2");

	bookDataBase.addFriend("��������", "��. ������", "098", "21-02-2004");
	bookDataBase.addFriend("��������1", "��. ������", "456", "23-02-2004");
	bookDataBase.addFriend("��������1", "��. ������1", "189", "17-02-2004");

	bookDataBase.addMarket("magazin1", "adres1", "88001");
	bookDataBase.addMarket("magazin2", "adres2", "88002");

	bookDataBase.addVIPContact("VIPANTON1", "322");
	bookDataBase.addVIPContact("VIPANTON2", "223");

	size_t count = bookDataBase.countRecords();
	std::cout << "���������� �������: " << count << std::endl;
	std::cout << "---------------------------------------------" << std::endl;

	std::vector<TelephoneBook*> matchesTable = bookDataBase.findMatched("��. ���");

	for (auto entry : matchesTable) {
		entry->printData();
	}

	std::cout << "---------------------------------------------" << std::endl;

	bookDataBase.printAllData();

	bookDataBase.dropDataTable();
}