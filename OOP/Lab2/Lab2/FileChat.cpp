#include "FileChat.h"

int User::getUserId() {
	return userId;
}

string User::getUserName() {
	return userName;
}

string Message::buildMessage() {
	ostringstream oss;
	oss << "��: " << sender->getUserName() << endl;
	oss << "����: " << recipient->getUserName() << endl;
	oss << "���������: " << text << endl;
	return oss.str();
}

string FileMessage::buildMessage() {
	ostringstream oss;
	oss << "��: " << sender->getUserName() << endl;
	oss << "����: " << recipient->getUserName() << endl;
	oss << "���������: " << text << endl;
	oss << "����: " << fileName << endl;
	return oss.str();
}

string FileMessage::getFileName() {
	return fileName;
}

time_t FileMessage::getDateOfPost() {
	return dateOfPost;
}

bool FileChat::addUser(string userName) {
	if (userName.empty()) {
		cout << "������� ������������ ��� ������������!";
		return false;
	}

	User *user = new User(users.size() + 1, userName);
	users.push_back(user);

	return true;
}

void FileChat::listUsers() {
	for (User *user : users) {
		cout << user->getUserName() << endl;
	}
}

User* FileChat::findUser(string userName) {
	for (User *user : users) {
		if (user->getUserName() == userName) {
			return user;
		}
	}
	
	User *user = new User(-1, "");
	return user;
}

bool FileChat::sendMessage(string from, string to, string msg) {
	User *fromUser = findUser(from);
	User *toUser = findUser(to);

	if ((fromUser->getUserId() == -1) || (toUser->getUserId() == -1)) {
		cout << "������� ������������ ��� ������������!";
		return false;
	}

	Message *message = new Message(fromUser, toUser, msg);

	if (messages.find(toUser) != messages.end()) {
		vector<Message *> userMessages;
		messages.insert({ toUser, userMessages });
	}
	
	messages[toUser].push_back(message);

	return true;
}

bool FileChat::listMesages(string userName) {
	User *user = findUser(userName);

	if (user->getUserId() == -1) {
		cout << "������� ������������ ��� ������������!";
		return false;
	}

	if (messages.find(user) == messages.end()) {
		cout << "� ������� ������������ ��� ���������" << endl;
		return false;
	}

	vector<Message *> userMessages = messages[user];
	for (Message* message : userMessages) {
		cout << message->buildMessage() << endl << endl;
	}

	return true;
}

bool FileChat::sendFile(string from, string to, string fileName) {
	User *fromUser = findUser(from);
	User *toUser = findUser(to);

	if ((fromUser->getUserId() == -1) || (toUser->getUserId() == -1)) {
		cout << "������� ������������ ��� ������������!";
		return false;
	}

	time_t dateOfPost = time(0);

	FileMessage *fileMessage = new FileMessage(fromUser, toUser, fileName, dateOfPost);

	if (messages.find(toUser) != messages.end()) {
		vector<Message *> userMessages;
		messages.insert({ toUser, userMessages });
	}

	messages[toUser].push_back(fileMessage);

	return true;
}

bool FileChat::getFileDate(string to, string fileName) {
	User *toUser = findUser(to);

	if (toUser->getUserId() == -1) {
		cout << "������� ������������ ��� ������������!";
		return false;
	}
	if (messages.find(toUser) == messages.end()) {
		cout << "���� ������������ �� ������� �����!";
		return false;
	}

	vector<Message *> userMessages = messages[toUser];
	for (Message* message : userMessages) {
		if (FileMessage* fileMsg = dynamic_cast<FileMessage*>(message)) {
			if (fileMsg->getFileName() == fileName) {
				time_t time = fileMsg->getDateOfPost();
				struct tm timeInfo;
				localtime_s(&timeInfo, &time);
				cout << put_time(&timeInfo, "%Y-%m-%d %H:%M:%S") << endl;
				return true;
			}
		}
	}
	return false;
}