#include "TravelService.h"
#include <iostream>

TravelService::TravelService(
	const std::string& name,
	const std::string& email,
	const std::string& telephone,
	int age,
	int balance)
{
	account = new Account(name, email, telephone, age, balance);
}

TravelService::TravelService() {
	account = new Account("", "", "", 0, 0);
}

TravelService::TravelService(const Account& account) {
	this->account = new Account();
	*this->account = account;
}

TravelService::~TravelService() {
	delete account;
}

// ����������� �����, ����������� ��� �������� ���������� ������ FlightBookingService ����� �������.
TravelService TravelService::createFromConsole() {
	return TravelService(Account::createFromConsole());
}

// �����, ��������������� ���������� ��� ���� ������������ ���������.
void TravelService::printAvailableRouts() const {
	if (!routes.empty()) {
		std::cout << "��������� ��������:\n\n";
		std::size_t index = 1;

		for (const auto& route : routes) {
			std::cout << index++ << ". ";
			route.printRouteInfo();
		}
	}
	else {
		std::cout << "� ������ ������ ��� ��������� ���������.\n";
	}
}

// �����, ��������������� ���������� �� ��������.
void TravelService::printAccountInfo() const {
	std::cout << "������ ��������:\n";
	std::cout << "���: " << account->name << '\n';
	std::cout << "�������: " << account->age << '\n';
	std::cout << "�����: " << account->email << '\n';
	std::cout << "�������: " << account->telephone << "\n\n";
}

// �����, ��������������� ��� ��������� ���������� �������.
void TravelService::changeAccountInfo(
	const std::string& name,
	const std::string& email,
	const std::string& telephone,
	int age)
{
	account->name = name;
	account->email = email;
	account->telephone = telephone;
	account->age = age;
	std::cout << "������� ������ ������ �������� ������� ��������.\n\n";
}

// �����, ������������ ������ ������������.
int TravelService::getBalance() const {
	return account->balance;
}

// �����, ��������������� ��� ���������� ������� ������������.
void TravelService::topUpBalance(int amount) {
	account->balance += amount;
	std::cout << "��� ������ ������� �������� �� " << amount << " ������.\n";
	std::cout << "������ �� ���������� " << account->balance << " ������.\n\n";
}

// �����, ��������������� ��� ���������� ���������.
void TravelService::addRoute(const Route& route) {
	for (const auto& rt : routes) {
		if (rt == route) {
			std::cout << "������ ������� ��� ����������, ���������� ����������.\n";
			return;
		}
	}
	routes.push_back(route);
	std::cout << "������� ������� ��������.\n";
}

// �����, ��������������� ��� �������� ��������.
void TravelService::removeRoute(const Route& route) {
	std::size_t index = 0;
	for (const auto& rt : routes) {
		if (rt == route) {
			routes.erase(routes.begin() + index);
			std::cout << "������� ������� ������.\n";
			return;
		}
		index++;
	}
	std::cout << "������ ������� �� ������, �������� ����������.\n";
}

// �����, ������������ ����� ��������� �� ���������� ������.
// ������� ������ ���� ��������� �������, ����� ������� ������� ��������� � ���������.
void TravelService::searchTicketsByCity(const std::string& desired_city) const {
	bool is_found = false;
	std::size_t index = 1;
	for (const auto& rt : routes) {
		if (rt.arrival_city == desired_city) {
			if (!is_found) {
				is_found = true;
				std::cout << "������� ��������� �������� �� ������ " << desired_city << ":\n";
			}
			std::cout << index++ << ". ";
			rt.printRouteInfo();
		}
	}

	if (!is_found) {
		std::cout << "���������� ��������� �� �������.\n";
	}
}

// �����, ������������ ����� ��������� �� �������� ����.
// ������� ������ ���� ��������� �������, ���� ������� ������� �� ��������� ��������.
void TravelService::searchTicketsByPrice(int available_money) const {
	bool is_found = false;
	std::size_t index = 1;
	for (const auto& rt : routes) {
		if (rt.ticket_price <= available_money) {
			if (!is_found) {
				is_found = true;
				std::cout << "������� ��������� �������� ���������� �� " << available_money << " ������:\n";
			}
			std::cout << index++ << ". ";
			rt.printRouteInfo();
		}
	}

	if (!is_found) {
		std::cout << "���������� ��������� �� �������.\n";
	}
}

// �����, ��������������� ��� ������� �������.
void TravelService::buyTicket(const Route& route) const {
	if (account->ticket != nullptr) {
		std::cout << "� ��� ��� ������ �����, ������ ��� ���� ����������.\n\n";
		return;
	}

	bool is_not_enough_money = false;
	for (const auto& rt : routes) {
		if (rt == route) {
			if (account->balance >= rt.ticket_price) {
				account->ticket = new Route();
				*account->ticket = route;
				account->balance -= route.ticket_price;
				std::cout << "����� ������� ������, �� ����� ����� "
					"�������� " << account->balance << " ������.\n\n";
				return;
			}
			else {
				is_not_enough_money = true;
			}
		}
	}
	if (is_not_enough_money) {
		std::cout << "�� ����� ����� ������������ ������� ��� ������� ������.\n\n";
	}
	else {
		std::cout << "������ ������� ���� ����������.\n\n";
	}
}

// �����, ��������������� ��� ������� ������.
void TravelService::sellTicket() {
	if (account->ticket != nullptr) {
		account->balance += account->ticket->ticket_price;
		delete account->ticket;
		account->ticket = nullptr;
		std::cout << "����� ������� ������, �� ����� ����� " << account->balance << " ������.\n\n";
	}
	else std::cout << "�� ����� �������� ��� ��������� �������.\n\n";
}

// �����, ��������������� ���������� � ��������� ������.
void TravelService::printTicketInfo() const {
	if (account->ticket) account->ticket->printRouteInfo();
	else std::cout << "����� �� ������, ����������� ���������� ����������.\n";
}