#include <iostream>

#include "FileChat.h"

int main() {
	setlocale(LC_ALL, "Russian");

	FileChat fileChat;

	cout << "����:" << endl;
	cout << "1. �������� ������������" << endl;
	cout << "2. �������� ������ �������������" << endl;
	cout << "3. ��������� ��������� ���������" << endl;
	cout << "4. �������� ������������ ��������� ������������" << endl;
	cout << "5. ��������� ���� ������������" << endl;
	cout << "6. �������� ����� �������� �����" << endl;
	cout << "7. �����" << endl << endl;

	int choi�e;
	bool work = true;
	while (work) {

		cout << "�������� �������: ";
		cin >> choi�e;

		string userName;
		string text;
		string recipientName;
		string fileName;
		bool res = true;

		switch (choi�e)
		{
		case 1:
			cout << "������� ��� ������������: ";
			cin >> userName;

			res = fileChat.addUser(userName);

			break;
		case 2:
			fileChat.listUsers();

			break;
		case 3:
			cout << "������� ��� �����������: ";
			cin >> userName;
			cout << "������� ��� ����������: ";
			cin >> recipientName;
			cout << "������� ����� ��� ��������: ";
			getline(cin, text);
			getline(cin, text);
			res = fileChat.sendMessage(userName, recipientName, text);

			break;
		case 4:
			cout << "������� ��� ������������: ";
			cin >> userName;

			res = fileChat.listMesages(userName);

			break;
		case 5:
			cout << "������� ��� �����������: ";
			cin >> userName;
			cout << "������� ��� ����������: ";
			cin >> recipientName;
			cout << "������� �������� ����� ��� ��������: ";
			cin >> fileName;

			res = fileChat.sendFile(userName, recipientName, fileName);

			break;
		case 6:
			cout << "������� ��� ����������: ";
			cin >> recipientName;
			cout << "������� �������� �����: ";
			cin >> fileName;

			res = fileChat.getFileDate(recipientName, fileName);

			break;
		case 7:
			work = false;

			break;
		default:
			cout << "������������ �������" << endl;
			break;
		}

		if (!res) {
			cout << "������� ������������ ������. ���������� ��� ���." << endl;
		}
	}

	return 0;
}