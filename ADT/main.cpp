#define _CRT_SECURE_NO_WARNINGS

#include "FlightBookingService_C.h"

// Функция, которая вызывается при неудачной аллокации памяти.
// Выводит сообщение об ошибке и аварийно завершает программу.
void memoryAllocationFailure() {
	fprintf(stderr, "Memory allocation failed.\n");
	exit(1);
}

// Функция, предназначенная для аллокации памяти для экземпляра структуры Timestamp и возвращающая указатель на нее. 
Timestamp* createTimestamp(int hour, int minute, int day, int month) {
	Timestamp* timestamp = (struct Timestamp*)malloc(sizeof(struct Timestamp));
	if (timestamp == NULL) {
		memoryAllocationFailure();
	}

	timestamp->hour = hour;
	timestamp->minute = minute;
	timestamp->day = day;
	timestamp->month = month;

	return timestamp;
}

// Функция, предназначенная для создания экземпляра через консоль.
Timestamp* createTimestampFromConsole() {
	int hour, minute, day, month;
	printf("Введите часы, минуты, день и месяц временной отметки через пробел (HH mm dd MM): ");
	scanf("%d %d %d %d", &hour, &minute, &day, &month);

	Timestamp* timestamp = createTimestamp(hour, minute, day, month);
	
	return timestamp;
}

// Функция, предназначенная для деаллокации памяти экземпляра структуры Timestamp.
void deleteTimestamp(struct Timestamp* timestamp) {
	free(timestamp);
}

// Функция, распечатывающая временную метку.
void printTimestamp(struct Timestamp* timestamp) {
	if (timestamp->hour < 10) printf("0");
	printf("%d:", timestamp->hour);
	if (timestamp->minute < 10) printf("0");
	printf("%d, ", timestamp->minute);
	if (timestamp->day < 10) printf("0");
	printf("%d.", timestamp->day);
	if (timestamp->month < 10) printf("0");
	printf("%d\n", timestamp->month);
}

// Функция, предназначенная для аллокации памяти для экземпляра структуры Route и возвращающая указатель на нее.
Route* createRoute(
	int ticket_price,
	const char* departure_city,
	const char* arrival_city,
	Timestamp* departure_time,
	Timestamp* arrival_time)
{
	Route* route = (struct Route*)malloc(sizeof(struct Route));
	if (route == NULL) {
		memoryAllocationFailure();
	}

	route->departure_city = (char*)malloc(strlen(departure_city) + 1);
	if (route->departure_city == NULL) {
		memoryAllocationFailure();
	}

	route->arrival_city = (char*)malloc(strlen(arrival_city) + 1);
	if (route->arrival_city == NULL) {
		memoryAllocationFailure();
	}

	route->ticket_price = ticket_price;
	strcpy(route->departure_city, departure_city);
	strcpy(route->arrival_city, arrival_city);
	memcpy(&route->departure_time, departure_time, sizeof(struct Timestamp));
	memcpy(&route->arrival_time, arrival_time, sizeof(struct Timestamp));

	return route;
}

// Функция, предназначенная для создания экземпляра структуры Route через консоль.
Route* createRouteFromConsole() {
	int ticket_price;
	printf("Введите цену билета: ");
	scanf("%d", &ticket_price);
	while (getchar() != '\n');

	char departure_city[50], arrival_city[50];
	printf("Введите город вылета: ");
	fgets(departure_city, sizeof(departure_city), stdin);
	departure_city[strcspn(departure_city, "\n")] = '\0';

	printf("Введите город посадки: ");
	fgets(arrival_city, sizeof(arrival_city), stdin);
	arrival_city[strcspn(arrival_city, "\n")] = '\0';

	puts("Для вылета: ");
	Timestamp* departure_time = createTimestampFromConsole();

	puts("Для посадки: ");
	Timestamp* arrival_time = createTimestampFromConsole();

	Route* route = createRoute(ticket_price, departure_city, arrival_city, departure_time, arrival_time);
	return route;
}

// Функция, предназначенная для деаллокации памяти экземпляра структуры Route.
void deleteRoute(struct Route* route) {
	free(route->departure_city);
	free(route->arrival_city);
	free(route);
}

// Функция, печатающая информацию о выбранном маршруте.
void printRouteInfo(struct Route* route) {
	printf("Маршрут: %s - %s\n", route->departure_city, route->arrival_city);
	printf("Время взлёта: ");
	printTimestamp(&route->departure_time);
	printf("Время посадки: ");
	printTimestamp(&route->arrival_time);
	printf("Цена билета: %d\n\n", route->ticket_price);
}

// Вспомогательная функция, предназначенная для сравнения объектов структуры Timestamp.
// Возвращает "1", если все поля структур совпадают, в противном случае - "0".
int compareTimestamps(struct Timestamp* lhs, struct Timestamp* rhs) {
	if (lhs->day != rhs->day || lhs->month != rhs->month
		|| lhs->minute != rhs->minute || lhs->hour != rhs->hour)
	{
		return 0;
	}
	return 1;
}

// Вспомогательная функция, предназначенная для сравнения объектов структуры Route.
// Возвращает "1", если все поля структур совпадают, в противном случае - "0".
int compareRoutes(struct Route* lhs, struct Route* rhs) {
	if (lhs->ticket_price != rhs->ticket_price ||
		strcmp(lhs->departure_city, rhs->departure_city) != 0 ||
		strcmp(lhs->arrival_city, rhs->arrival_city) != 0 ||
		compareTimestamps(&lhs->departure_time, &rhs->departure_time) != 1 ||
		compareTimestamps(&lhs->arrival_time, &rhs->arrival_time) != 1) 
	{
		return 0;
	}
	return 1;
}

// Функция, предназначенная для аллокации памяти для экземпляра структуры Account и возвращающая указатель на нее.
Account* createAccount(const char* name, const char* email, const char* telephone, int age, int balance) {
	Account* account = (struct Account*)malloc(sizeof(struct Account));
	if (account == NULL) {
		memoryAllocationFailure();
	}

	account->name = (char*)malloc(strlen(name) + 1);
	if (account->name == NULL) {
		memoryAllocationFailure();
	}

	account->email = (char*)malloc(strlen(email) + 1);
	if (account->email == NULL) {
		memoryAllocationFailure();
	}

	account->telephone = (char*)malloc(strlen(telephone) + 1);
	if (account->telephone == NULL) {
		memoryAllocationFailure();
	}

	strcpy(account->name, name);
	strcpy(account->email, email);
	strcpy(account->telephone, telephone);
	account->age = age;
	account->balance = balance;
	account->ticket = NULL;

	return account;
}

// Функция, предназначенная для создания экземпляра структуры Account через консоль.
Account* createAccountFromConsole() {
	char name[50], email[50], telephone[50];
	printf("Введите Ваше имя: ");
	fgets(name, sizeof(name), stdin);
	name[strcspn(name, "\n")] = '\0';

	printf("Введите Вашу почту: ");
	fgets(email, sizeof(email), stdin);
	email[strcspn(email, "\n")] = '\0';

	printf("Введите Ваш телефон: ");
	fgets(telephone, sizeof(telephone), stdin);
	telephone[strcspn(telephone, "\n")] = '\0';

	int age, balance;
	printf("Введите Ваш возраст: ");
	scanf("%d", &age);
	while (getchar() != '\n');

	printf("Введите сумму, на которую будет сразу пополнен Ваш счёт: ");
	scanf("%d", &balance);

	Account* account = createAccount(name, email, telephone, age, balance);
	
	return account;
}

// Функция, предназначенная для деаллокации памяти экземпляра структуры Account.
void deleteAccount(struct Account* account) {
	free(account->name);
	free(account->email);
	free(account->telephone);
	if (account->ticket != NULL) deleteRoute(account->ticket);
	free(account);
}

// Функция, предназначенная для пополнения баланса пользователя
void topUpBalance(struct Account* account, int amount) {
	account->balance += amount;
	printf("Ваш баланс успешно пополнен на %d рублей.\n", amount);
	printf("Теперь он составляет %d рублей.\n\n", account->balance);
}

// Функция, распечатывающая информацию об аккаунте.
void printAccountInfo(struct Account* account) {
	printf("Данные аккаунта:\n");
	printf("ФИО: %s\n", account->name);
	printf("Возраст: %d\n", account->age);
	printf("Почта: %s\n", account->email);
	printf("Телефон: %s\n\n", account->telephone);
}

// Функция, предназначенная для изменения информации профиля.
void changeAccountInfo(
	struct Account* account,
	const char* new_name,
	const char* new_email,
	const char* new_telephone,
	int new_age)
{
	char* temp;
	temp = (char*)realloc(account->name, strlen(new_name) + 1);
	if (temp == NULL) {
		memoryAllocationFailure();
	}
	account->name = temp;

	char* temp2;
	temp2 = (char*)realloc(account->email, strlen(new_email) + 1);
	if (temp2 == NULL) {
		memoryAllocationFailure();
	}
	account->email = temp2;
	
	char* temp3;
	temp3 = (char*)realloc(account->telephone, strlen(new_telephone) + 1);
	if (temp3 == NULL) {
		memoryAllocationFailure();
	}
	account->telephone = temp3;

	strcpy(account->name, new_name);
	strcpy(account->email, new_email);
	strcpy(account->telephone, new_telephone);
	
	account->age = new_age;
	puts("Учетные данные Вашего профиля успешно изменены.\n");
}

// Функция, предназначенная для аллокации памяти для экземпляра структуры FlightBookingService
// и возвращающая указатель на нее.
FlightBookingService* createFlightBookingService(
	const char* name,
	const char* email,
	const char* telephone,
	int age, 
	int balance) 
{
	FlightBookingService* fbs = (struct FlightBookingService*)malloc(sizeof(struct FlightBookingService));
	if (fbs == NULL) {
		memoryAllocationFailure();
	}

	fbs->routes_amount = 0;
	fbs->account = createAccount(name, email, telephone, age, balance);

	return fbs;
}

// Функция, предназначенная для создания экземпляра структуры FlightBookingService через консоль.
FlightBookingService* createFlightBookingServiceFromConsole() {
	
	FlightBookingService* fbs = (struct FlightBookingService*)malloc(sizeof(struct FlightBookingService));
	if (fbs == NULL) {
		memoryAllocationFailure();
	}

	fbs->routes_amount = 0;
	fbs->account = createAccountFromConsole();

	return fbs;
}

// Функция, предназначенная для деаллокации памяти экземпляра структуры FlightBookingService.
void deleteFlightBookingService(struct FlightBookingService* fbs) {
	deleteAccount(fbs->account);
	free(fbs);
}

// Функция, распечатывающая информацию обо всех существующих маршрутах.
void printAvailableRoutes(struct FlightBookingService* fbs) {
	if (fbs->routes_amount > 0) {
		puts("Доступные маршруты:\n");
		int index = 1;
		
		for (int i = 0; i < fbs->routes_amount; ++i) {
			printf("%d. ", index++);
			printRouteInfo(&fbs->routes[i]);
		}
	}
	else {
		puts("В данный момент нет доступных маршрутов.");
	}
}

// Функция, предназначенная для добавления маршрутов.
void addRoute(struct FlightBookingService* fbs, struct Route* route) {
	if (fbs->routes_amount < MAX_FLIGHTS_AMOUNT) {
		for (int i = 0; i < fbs->routes_amount; ++i) {
			if (compareRoutes(&fbs->routes[i], route) == 1) {
				puts("Данный маршрут уже существует, добавление невозможно.");
				return;
			}
		}
		memcpy(&fbs->routes[fbs->routes_amount++], route, sizeof(struct Route));
		printf("Маршрут успешно добавлен.\n");
	}
	else {
		printf("Достигнуто максимально возможное количество маршрутов, невозможно добавить новый.\n");
	}
}

// Функция, преназначенная для удаления маршрутов.
void removeRoute(struct FlightBookingService* fbs, struct Route* route) {
	int is_found = 0;
	if (fbs->routes_amount > 0) { 
		Route routes[MAX_FLIGHTS_AMOUNT];
		for (int i = 0, index = 0; i < fbs->routes_amount; ++i) {
			if (compareRoutes(&fbs->routes[i], route) == 1 && !is_found) {
				printf("Маршрут успешно удален.\n");
				is_found = 1;
				continue;
			}
			memcpy(&routes[index++], &fbs->routes[i], sizeof(struct Route));
		}
		memcpy(fbs->routes, routes, sizeof(struct Route) * MAX_FLIGHTS_AMOUNT);
		if (is_found) fbs->routes_amount--;
		else printf("Данный маршрут не найден, удаление невозможно.\n");
	}
}

// Функция, производящая поиск маршрутов по выбранному городу.
// Выводит список всех доступных городов, город посадки которых совпадает с выбранным.
void searchTicketsByCity(struct FlightBookingService* fbs, const char* desired_city) {
	int is_found = 0, index = 1;
	for (int i = 0; i < fbs->routes_amount; ++i) {
		if (strcmp(fbs->routes[i].arrival_city, desired_city) == 0) {
			if (!is_found) {
				is_found = 1;
				printf("Найдены следующие маршруты до города %s:\n", desired_city);
			}
			printf("%d. ", index++);
			printRouteInfo(&fbs->routes[i]);
		}
	}
	if (!is_found) {
		puts("Подходящих маршрутов не найдено.");
	}
}

// Функция, производящая поиск маршрутов по заданной цене.
// Выводит список всех доступных городов, цена билетов которых не превышает заданную.
void searchTicketsByPrice(struct FlightBookingService* fbs, int available_money) {
	int is_found = 0, index = 1;
	for (int i = 0; i < fbs->routes_amount; ++i) {
		if (fbs->routes[i].ticket_price <= available_money) {
			if (!is_found) {
				is_found = 1;
				printf("Найдены следующие маршруты стоимость до %d рублей:\n", available_money);
			}
			printf("%d. ", index++);
			printRouteInfo(&fbs->routes[i]);
		}
	}
	if (!is_found) {
		puts("Подходящих маршрутов не найдено.");
	}
}

// Функция, предназначенная для покупки билетов.
void buyTicket(struct FlightBookingService* fbs, struct Route* route) {
	if (fbs->account->ticket != NULL) {
		puts("У Вас уже куплен билет, купить еще один невозможно.\n");
		return;
	}

	int is_not_enough_money = 0;
	for (int i = 0; i < fbs->routes_amount; ++i) {
		if (compareRoutes(&fbs->routes[i], route) == 1) {
			if (fbs->account->balance >= route->ticket_price) {
				
				fbs->account->ticket = createRoute(route->ticket_price, route->departure_city,
					route->arrival_city, &route->departure_time, &route->arrival_time);
				
				fbs->account->balance -= route->ticket_price;

				printf("Билет успешно куплен, на вашем счету осталось %d рублей.\n\n", fbs->account->balance);
				return;
			}
			else {
				is_not_enough_money = 1;
			}
		}
	}
	if (is_not_enough_money) {
		puts("На Вашем счету недостаточно средств для покупки билета.\n");
	}
	else {
		puts("Данный маршрут пока недоступен.\n");
	}
}

// Функция, предназначенная для продажи билетов.
void sellTicket(struct Account* account) {
	if (account->ticket != NULL) {
		account->balance += account->ticket->ticket_price;
		free(account->ticket);
		account->ticket = NULL;
		printf("Билет успешно продан, на Вашем счету %d рублей.\n\n", account->balance);
	}
	else puts("На Вашем аккаунте нет купленных билетов.\n\n");
}

// Функция, распечатывающая информацию о купленном билете.
void printTicketInfo(struct Account* account) {
	if (account->ticket) {
		printRouteInfo(account->ticket);
	}
	else puts("Билет не куплен, просмотреть информацию невозможно.");
}

int main(void) {
	setlocale(LC_ALL, "ru");
	FlightBookingService* fbs = createFlightBookingServiceFromConsole(); // Создаем сам сервис
	printAccountInfo(fbs->account); // Распечатываем информацию о профиле
	changeAccountInfo(fbs->account, "Timofey Tagaev", "timofey.tagaev.2004.12@gmail.com", "88005553535", 18); // Меняем информацию профиля
	printAccountInfo(fbs->account); // Распечатываем измененную информацию о профиле

	Timestamp* timestamps[6] = { 
		createTimestamp(12, 10, 23, 11),
		createTimestamp(18, 00, 23, 11),
		createTimestamp(18, 45, 10, 12),
		createTimestamp(2, 0, 11, 12),
		createTimestamp(10, 0, 21, 9),
		createTimestamp(14, 10, 21, 9)
	};

	Route* routes[3] = {
		createRoute(20000, "Barnaul", "Salt Lake City", timestamps[0], timestamps[1]),
		createRoute(60000, "Barnaul", "Stockholm", timestamps[2], timestamps[3]),
		createRoute(40000, "Barnaul", "Moscow", timestamps[4], timestamps[5])
	};

	for (int i = 0; i < 3; ++i) addRoute(fbs, routes[i]); // Добавляем маршруты в сервис
	
	printAvailableRoutes(fbs); // Распечатываем все доступные маршруты
	searchTicketsByPrice(fbs, fbs->account->balance); // Поиск маршрутов, цена которых не превосходит баланс аккаунта
	buyTicket(fbs, routes[2]); // Покупаем билет
	printTicketInfo(fbs->account); // Распечатываем информацию о билете
	buyTicket(fbs, routes[1]); // Пытаемся снова купить билет и получаем информацию об ошибке
	sellTicket(fbs->account); // Продаем купленный билет
	searchTicketsByCity(fbs, "Stockholm"); // Поиск городов по городу назначения "Stockholm"
	buyTicket(fbs, routes[1]); // Пытаемся купить билет и получаем сообщению о недостатке средств
	topUpBalance(fbs->account, 10000); // Пополняем баланс
	buyTicket(fbs, routes[1]); // Покупаем билет
	removeRoute(fbs, routes[2]); // Удаляем маршрут из списка доступных
	printAvailableRoutes(fbs); // Распечатываем и видим, что маршрута нет в списке

	for (int i = 0; i < 3; ++i) deleteRoute(routes[i]);
	for (int i = 0; i < 6; ++i) deleteTimestamp(timestamps[i]);
	deleteFlightBookingService(fbs);
	
	// --- Демонстрация работы со статическим объектом

	FlightBookingService static_object;

	// Обращение к полям статического объекта осуществляется через оператор .
	// В данный момент поля данного объекта не проинициализированы, но можно воспользоваться функцией 
	// memcpy, копируя все данные из созданного вспомогательного динамического объекта или проиниализировать все поля вручную.
	static_object.account = createAccount("name", "email", "telephone", 0, 0);
	static_object.routes_amount = 0;

	// И не забыть деаллоцировать используемую память в конце работы с объектом.
	deleteAccount(static_object.account);

	// Демонстрация работы с динамическим объектом приведена выше при демонстрации работы всей программы.

	return 0;
}
