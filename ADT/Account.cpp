#include "Account.h"
#include <iostream>

Account::Account(const std::string& name, const std::string& email, const std::string& tel, int age, int bal)
	: name(name), email(email), telephone(tel), age(age), balance(bal), ticket(nullptr)
{}

Account::Account() 
	: name(""), email(""), telephone(""), age(0), balance(0), ticket(nullptr)
{}

Account::Account(const Account& other) {
	this->name = other.name;
	this->email = other.email;
	this->telephone = other.telephone;
	this->age = other.age;
	this->balance = other.balance;

	if (other.ticket) *this->ticket = *other.ticket;
	else this->ticket = nullptr;
}

Account::~Account() {
	if (ticket) delete ticket;
}

// ����������� �����, ����������� ��� �������� ���������� ������ Account ����� �������.
Account Account::createFromConsole() {
	std::string name, email, telephone;
	int age, balance;
	std::cout << "������� ���� ���: ";
	std::getline(std::cin, name);

	std::cout << "������� ���� �����: ";
	std::getline(std::cin, email);

	std::cout << "������� ��� �������: ";
	std::getline(std::cin, telephone);

	std::cout << "������� ��� �������: ";
	std::cin >> age;

	std::cout << "������� �����, �� ������� ����� ����� �������� ��� ����: ";
	std::cin >> balance;

	return Account(name, email, telephone, age, balance);
}

Account& Account::operator=(const Account& other) {
	if (this == &other) return *this;

	this->name = other.name;
	this->email = other.email;
	this->telephone = other.telephone;
	this->age = other.age;
	this->balance = other.balance;

	return *this;
}