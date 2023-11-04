#pragma once

#include "Route.h"
#include <string>

// �����, �������������� ����� ������� ������������;
// �������� ���������� �� �����, �����, �������� � ��������, � ����� � ��������� ������.
class Account {
private:
	std::string name;
	std::string email;
	std::string telephone;
	int age;
	int balance;
	Route* ticket;

	friend class TravelService;
public:
	Account(const std::string& name, const std::string& email, const std::string& tel, int age, int bal);

	Account();

	Account(const Account& other);

	~Account();

	static Account createFromConsole();

	Account& operator=(const Account& other);
};