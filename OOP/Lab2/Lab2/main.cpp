#include <iostream>

#include "FileChat.h"

int main() {
	setlocale(LC_ALL, "Russian");

	FileChat fileChat;

	cout << "Меню:" << endl;
	cout << "1. Добавить пользователя" << endl;
	cout << "2. Показать список пользователей" << endl;
	cout << "3. Отправить текстовое сообщение" << endl;
	cout << "4. Показать отправленное сообщение пользователя" << endl;
	cout << "5. Отправить файл пользователю" << endl;
	cout << "6. Получить время отправки файла" << endl;
	cout << "7. Выход" << endl << endl;

	int choiсe;
	bool work = true;
	while (work) {

		cout << "Выберите команду: ";
		cin >> choiсe;

		string userName;
		string text;
		string recipientName;
		string fileName;
		bool res = true;

		switch (choiсe)
		{
		case 1:
			cout << "Введите имя пользователя: ";
			cin >> userName;

			res = fileChat.addUser(userName);

			break;
		case 2:
			fileChat.listUsers();

			break;
		case 3:
			cout << "Введите имя отправителя: ";
			cin >> userName;
			cout << "Введите имя получателя: ";
			cin >> recipientName;
			cout << "Введите текст для отправки: ";
			getline(cin, text);
			getline(cin, text);
			res = fileChat.sendMessage(userName, recipientName, text);

			break;
		case 4:
			cout << "Введите имя пользователя: ";
			cin >> userName;

			res = fileChat.listMesages(userName);

			break;
		case 5:
			cout << "Введите имя отправителя: ";
			cin >> userName;
			cout << "Введите имя получателя: ";
			cin >> recipientName;
			cout << "Введите название файла для отправки: ";
			cin >> fileName;

			res = fileChat.sendFile(userName, recipientName, fileName);

			break;
		case 6:
			cout << "Введите имя получателя: ";
			cin >> recipientName;
			cout << "Введите название файла: ";
			cin >> fileName;

			res = fileChat.getFileDate(recipientName, fileName);

			break;
		case 7:
			work = false;

			break;
		default:
			cout << "Неправельная команда" << endl;
			break;
		}

		if (!res) {
			cout << "Введены недопустимые данные. Попробуйте еще раз." << endl;
		}
	}

	return 0;
}