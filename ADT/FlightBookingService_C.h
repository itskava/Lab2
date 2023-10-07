#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_FLIGHTS_AMOUNT 20

void memoryAllocationFailure();

// Структура, представляющая собой временную отметку;
// Хранит в себе часы, минуты, день и месяц.
struct Timestamp {
	int hour;
	int minute;
	int day;
	int month;
};

Timestamp* createTimestamp(int hour, int minute, int day, int month);

Timestamp* createTimestampFromConsole();

void deleteTimestamp(struct Timestamp* timestamp);

void printTimestamp(struct Timestamp* timestamp);

// Структура, представляющая собой маршрут из одного города в другой;
// Содержит информацию о городах взлета и посадки, времени взлета и посадки, а также о цене билета.
struct Route {
	int ticket_price;
	char* departure_city;
	char* arrival_city;
	Timestamp departure_time;
	Timestamp arrival_time;
};

Route* createRoute(
	int ticket_price,
	const char* departure_city,
	const char* arrival_city,
	Timestamp* departure_time,
	Timestamp* arrival_time);

Route* createRouteFromConsole();

void deleteRoute(struct Route* route);

void printRouteInfo(struct Route* route);

int compareTimestamps(struct Timestamp* lhs, struct Timestamp* rhs);

int compareRoutes(struct Route* lhs, struct Route* rhs);

// Структура, представляющая собой профиль пользователя;
// Содержит информацию об имени, почте, телефоне и возрасте, а также о купленном билете.
struct Account {
	char* name;
	char* email;
	char* telephone;
	int age;
	int balance;
	Route* ticket;
};

Account* createAccount(const char* name, const char* email, const char* telephone, int age, int balance);

Account* createAccountFromConsole();

void deleteAccount(struct Account* account);

void topUpBalance(struct Account* account, int amount);

void printAccountInfo(struct Account* account);

void changeAccountInfo(
	struct Account* account,
	const char* new_name,
	const char* new_email,
	const char* new_telephone,
	int new_age);


// Структура, представляющая собой сам сервис для покупки и продажи билетов для путешествий.
// Содержит в себе массив, хранящий все доступные маршруты, и указатель на аккаунт пользователя.
struct FlightBookingService {
	int routes_amount;
	Route routes[MAX_FLIGHTS_AMOUNT];
	Account* account;
};

FlightBookingService* createFlightBookingServiceFromConsole();

void deleteFlightBookingService(struct FlightBookingService* fbs);

void printAvailableRoutes(struct FlightBookingService* fbs);

void addRoute(struct FlightBookingService* fbs, struct Route* route);

void removeRoute(struct FlightBookingService* fbs, struct Route* route);

void searchTicketsByCity(struct FlightBookingService* fbs, const char* desired_city);

void searchTicketsByPrice(struct FlightBookingService* fbs, int available_money);

void buyTicket(struct FlightBookingService* fbs, struct Route* route);

void sellTicket(struct Account* account);

void printTicketInfo(struct Account* account);
