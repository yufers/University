#ifndef CHAT_H
#define CHAT_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <ctime>
#include <iomanip>

using namespace std;

class User {
private:
	int userId;
	string userName;
public:
	User(int userId, string userName) :
		userId(userId), userName(userName) {}

	int getUserId();
	string getUserName();
};

class Message {
protected:
	string text;
	User *sender;
	User *recipient;
public:
	Message(User *sender, User *recipient, string text) :
		sender(sender), recipient(recipient), text(text) {}

	virtual string buildMessage();
};

class FileMessage : public Message {
private:
	string fileName;
	time_t dateOfPost;

public:
	FileMessage(User *sender, User *recipient, string text, string fileName) :
		Message(sender, recipient, text), fileName(fileName), dateOfPost(0) {}

	FileMessage(User *sender, User *recipient, string fileName, time_t dateOfPost) :
		Message(sender, recipient, ""), fileName(fileName), dateOfPost(dateOfPost) {}

	string buildMessage() override;
	string getFileName();
	time_t getDateOfPost();
};

class FileChat {
private:
	vector<User*> users;
	map<User*, vector<Message*>> messages;

protected:
	User* findUser(string userName);

public:
	bool addUser(string userName);
	void listUsers();
	bool sendMessage(string from, string to, string msg);
	bool listMesages(string userName);
	bool sendFile(string from, string to, string fileName);
	bool getFileDate(string to, string fileName);
};

#endif