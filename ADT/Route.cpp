#include "Route.h"
#include <iostream>

Route::Route(
	int ticket_price,
	const std::string& departure_city,
	const std::string& arrival_city,
	const Timestamp& departure_time,
	const Timestamp& arrival_time)
	: ticket_price(ticket_price),
	departure_city(departure_city),
	arrival_city(arrival_city),
	departure_time(departure_time),
	arrival_time(arrival_time)
{}

Route::Route()
	: Route(0, "", "", Timestamp(), Timestamp()) 
{}

Route::Route(const Route& other) {
	this->ticket_price = other.ticket_price;
	this->departure_city = other.departure_city;
	this->arrival_city = other.arrival_city;
	this->departure_time = other.departure_time;
	this->arrival_time = other.arrival_time;
}

Route::~Route() = default;

// ����������� �����, ����������� ��� �������� ���������� ������ Route ����� �������.
Route Route::createFromConsole() {
	int ticket_price;
	std::cout << "������� ���� ������: ";
	std::cin >> ticket_price;

	std::string departure_city, arrival_city;
	std::cout << "������� ����� ������: ";
	std::cin >> departure_city;

	std::cout << "������� ����� �������: ";
	std::cin >> arrival_city;

	std::cout << "��� ������:\n";
	Timestamp departure_time = Timestamp::createFromConsole();

	std::cout << "��� �������:\n";
	Timestamp arrival_time = Timestamp::createFromConsole();

	return Route(ticket_price, departure_city, arrival_city, departure_time, arrival_time);
}

// �����, ������� ������������� ������ ���������� � ������ ��������.
void Route::printRouteInfo() const {
	std::cout << "�������: " << departure_city << " - " << arrival_city << '\n';
	std::cout << "����� �����: ";
	departure_time.printTimestamp();
	std::cout << "����� �������: ";
	arrival_time.printTimestamp();
	std::cout << "���� ������: " << ticket_price << "\n\n";
}

bool Route::operator==(const Route& other) const {
	return this->ticket_price == other.ticket_price &&
		this->departure_city == other.departure_city &&
		this->arrival_city == other.arrival_city &&
		this->departure_time == other.departure_time &&
		this->arrival_time == other.arrival_time;
}

bool Route::operator!=(const Route& other) const {
	return !(*this == other);
}

Route& Route::operator=(const Route& other) {
	if (this == &other) return *this;

	this->ticket_price = other.ticket_price;
	this->departure_city = other.departure_city;
	this->arrival_city = other.arrival_city;
	this->departure_time = other.departure_time;
	this->arrival_time = other.arrival_time;

	return *this;
}