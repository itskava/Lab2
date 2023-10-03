#include <iostream>
#include <string>
#include <vector>

// �����, �������������� ����� ��������� �������.
// ������ � ���� ����, ������, ���� � �����.
class Timestamp {
private:
	int hour;
	int minute;
	int day;
	int month;

public:
	// ����������� � �����������.
	Timestamp(int hour, int minute, int day, int month)
		: hour(hour), minute(minute), day(day), month(month) {}
	
	// ����������� ��� ����������.
	Timestamp() : Timestamp(0, 0, 0, 0) {}
	
	// ����������� �����������.
	Timestamp(const Timestamp& other) {
		this->hour = other.hour;
		this->minute = other.minute;
		this->day = other.day;
		this->month = other.month;
	}
	
	// ����������.
	~Timestamp() = default;

	// �����, ��������������� ������ ��������� �����.
	void printTimestamp() const {
		if (hour < 10) std::cout << '0';
		std::cout << hour << ':';
		if (minute < 10) std::cout << '0';
		std::cout << minute << ", ";
		if (day < 10) std::cout << '0';
		std::cout << day << '.';
		if (month < 10) std::cout << '0';
		std::cout << month << '\n';
	}

	// --- ������������� ���������.
	bool operator!=(const Timestamp& other) const {
		if (this->day != other.day || this->month != other.month ||
			this->hour != other.hour || this->minute != other.minute) 
		{
			return true;
		}
		return false;
	}

	bool operator==(const Timestamp& other) const {
		return !(*this != other);
	}

	Timestamp& operator=(const Timestamp& other) {
		if (this == &other) return *this;

		this->hour = other.hour;
		this->minute = other.minute;
		this->day = other.day;
		this->month = other.month;

		return *this;
	}
	// ---
};

// �����, �������������� ����� �������� �������� �� ������ ������ � ������;
// �������� ���������� � ������� ������ � �������, ������� ������ � �������, � ����� � ���� ������.
class Route {
private:
	int ticket_price;
	std::string departure_city;
	std::string arrival_city;
	Timestamp departure_time;
	Timestamp arrival_time;

	friend class FlightBookingService;
public:
	// ����������� � �����������.
	Route(
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

	// ����������� ��� ����������.
	Route() : Route(0, "", "", Timestamp(), Timestamp()) {}

	// ����������� �����������.
	Route(const Route& other) {
		this->ticket_price = other.ticket_price;
		this->departure_city = other.departure_city;
		this->arrival_city = other.arrival_city;
		this->departure_time = other.departure_time;
		this->arrival_time = other.arrival_time;
	}

	// ����������.
	~Route() = default;

	// �����, ������� ������������� ������ ���������� � ������ ��������.
	void printRouteInfo() const {
		std::cout << "�������: " << departure_city << " - " << arrival_city << '\n';
		std::cout << "����� �����: ";
		departure_time.printTimestamp();
		std::cout << "����� �������: ";
		arrival_time.printTimestamp();
		std::cout << "���� ������: " << ticket_price << "\n\n";
	}
	
	// --- ������������� ���������
	bool operator==(const Route& other) const {
		if (this->ticket_price != other.ticket_price ||
			this->departure_city != other.departure_city ||
			this->arrival_city != other.arrival_city ||
			this->departure_time != other.departure_time ||
			this->arrival_time != other.arrival_time) 
		{
			return false;
		}
		return true;
	}

	bool operator!=(const Route& other) const {
		return !(*this == other);
	}

	Route& operator=(const Route& other) {
		if (this == &other) return *this;

		this->ticket_price = other.ticket_price;
		this->departure_city = other.departure_city;
		this->arrival_city = other.arrival_city;
		this->departure_time = other.departure_time;
		this->arrival_time = other.arrival_time;

		return *this;
	}
	// ---
};

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
	
	friend class FlightBookingService;
public:
	// ����������� � �����������.
	Account(const std::string& name, const std::string& email, const std::string& tel, int age, int bal)
		: name(name), email(email), telephone(tel), age(age), balance(bal), ticket(nullptr) 
	{}

	// ���������� ��� ����������.
	Account() : name(""), email(""), telephone(""), age(0), balance(0), ticket(nullptr) {}

	// ����������� �����������.
	Account(const Account& other) {
		this->name = other.name;
		this->email = other.email;
		this->telephone = other.telephone;
		this->age = other.age;
		this->balance = other.balance;

		if (other.ticket) *this->ticket = *other.ticket;
		else this->ticket = nullptr;
	}

	// ����������.
	~Account() {
		if (ticket) delete ticket;
	}

	// ������������� �������� ������������
	Account& operator=(const Account& other) {
		if (this == &other) return *this;

		this->name = other.name;
		this->email = other.email;
		this->telephone = other.telephone;
		this->age = other.age;
		this->balance = other.balance;

		return *this;
	}
};


// �����, �������������� ����� ��� ������ ��� ������� � ������� ������� ��� �����������.
// �������� � ���� ������, �������� ��� ��������� ��������, � ��������� �� ������� ������������.
class FlightBookingService {
private:
	std::vector<Route> routes;
	Account* account;
public:
	// ����������� � �����������.
	FlightBookingService(
		const std::string& name,
		const std::string& email,
		const std::string& telephone,
		int age,
		int balance)
	{
		account = new Account(name, email, telephone, age, balance);
	}

	// ����������� ��� ����������.
	FlightBookingService() {
		account = new Account("", "", "", 0, 0);
	}

	// ����������� � ����� ����������.
	FlightBookingService(const Account& account) {
		*this->account = account;
	}

	// ����������.
	~FlightBookingService() {
		delete account;
	}
	
	// �����, ��������������� ���������� ��� ���� ������������ ���������.
	void printAvailableRouts() const {
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
	void printAccountInfo() const  {
		std::cout << "������ ��������:\n";
		std::cout << "���: " << account->name << '\n';
		std::cout << "�������: " << account->age << '\n';
		std::cout << "�����: " << account->email << '\n';
		std::cout << "�������: " << account->telephone << "\n\n";
	}

	// �����, ��������������� ��� ��������� ���������� �������.
	void changeAccountInfo(
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
	int getBalance() const {
		return account->balance;
	}

	// �����, ��������������� ��� ���������� ������� ������������.
	void topUpBalance(int amount) {
		account->balance += amount;
		std::cout << "��� ������ ������� �������� �� " << amount << " ������.\n";
		std::cout << "������ �� ���������� " << account->balance << " ������.\n\n";
	}

	// �����, ��������������� ��� ���������� ���������.
	void addRoute(const Route& route) {
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
	void removeRoute(const Route& route) {
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
	void searchTicketsByCity(const std::string& desired_city) const {
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
	void searchTicketsByPrice(int available_money) const {
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
	void buyTicket(const Route& route) const {
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
	void sellTicket() {
		if (account->ticket != nullptr) {
			account->balance += account->ticket->ticket_price;
			delete account->ticket;
			account->ticket = nullptr;
			std::cout << "����� ������� ������, �� ����� ����� " << account->balance << " ������.\n\n";
		}
		else std::cout << "�� ����� �������� ��� ��������� �������.\n\n";
	}

	// �����, ��������������� ���������� � ��������� ������.
	void printTicketInfo() const {
		if (account->ticket) account->ticket->printRouteInfo();
		else std::cout << "����� �� ������, ����������� ���������� ����������.\n";
	}
};


int main2(void) {
	setlocale(LC_ALL, "ru");
	// ���� ������ ������� � �������
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

	FlightBookingService fbs(name, email, telephone, age, balance); // ������� ��� ������
	fbs.printAccountInfo(); // ������������� ���������� � �������
	fbs.changeAccountInfo("Timofey Tagaev", "timofey.tagaev.2004.12@gmail.com", "88005553535", 18); // ������ ���������� �������
	fbs.printAccountInfo(); // ������������� ���������� ���������� � �������

	Route routes[] = {
		Route(20000, "Barnaul", "Salt Lake City", Timestamp(12, 10, 23, 11), Timestamp(18, 00, 23, 11)),
		Route(60000, "Barnaul", "Stockholm", Timestamp(18, 45, 10, 12), Timestamp(2, 0, 11, 12)),
		Route(40000, "Barnaul", "Moscow", Timestamp(10, 0, 21, 9), Timestamp(14, 10, 21, 9))
	};
	for (const auto& i : routes) fbs.addRoute(i); // ��������� �������� � ������

	fbs.printAvailableRouts(); // ������������� ��� ��������� ��������
	fbs.searchTicketsByPrice(fbs.getBalance()); // ����� ���������, ���� ������� �� ����������� ������ ��������
	fbs.buyTicket(routes[2]); // �������� �����
	fbs.printTicketInfo(); // ������������� ���������� � ������
	fbs.buyTicket(routes[1]); // �������� ����� ������ ����� � �������� ���������� �� ������
	fbs.sellTicket(); // ������� ��������� �����
	fbs.searchTicketsByCity("Stockholm"); // ����� ������� �� ������ ���������� "Stockholm"
	fbs.buyTicket(routes[1]); // �������� ������ ����� � �������� ��������� � ���������� �������
	fbs.topUpBalance(10000); // ��������� ������
	fbs.buyTicket(routes[1]); // �������� �����
	fbs.removeRoute(routes[2]); // ������� ������� �� ������ ���������
	fbs.printAvailableRouts(); // ������������� � �����, ��� �������� ��� � ������
	 
	// --- ������������ ������������� ��������� �������� ��������
	
	// �������� ������������ ������� ����������� �������� ������.
	FlightBookingService static_array_of_static_objects[3];

	// �������� ������������ ������� ������������ �������� � ��������� ��� ��� ������.
	FlightBookingService* static_array_of_dynamic_objects[3];
	for (std::size_t i = 0; i < 3; ++i) {
		static_array_of_dynamic_objects[i] = new FlightBookingService;
	}
	
	// ������������ ������ �������� � ������� ��������� delete.
	for (std::size_t i = 0; i < 3; ++i) {
		delete static_array_of_dynamic_objects[i];
	}

	// �������� ������������� ������� ����������� ��������.
	FlightBookingService* dynamic_array_of_static_objects = new FlightBookingService[3];

	// ������������ ������������� ������� � ������� ��������� delete[].
	delete[] dynamic_array_of_static_objects;

	// �������� ������������� ������� ������������ ��������;
	// ������� ���������� ������ ��� ��� ������, �� ��� ��� ������� �� ��������.
	FlightBookingService** dynamic_array_of_dynamic_objects = new FlightBookingService*[3];
	for (std::size_t i = 0; i < 3; ++i) {
		dynamic_array_of_dynamic_objects[i] = new FlightBookingService;
	}

	// � ������������ ������: ������� ���� ��������, ����� ������ �������.
	for (std::size_t i = 0; i < 3; ++i) {
		delete dynamic_array_of_dynamic_objects[i];
	}
	delete[] dynamic_array_of_dynamic_objects;

	// ----------------------------------------------------------

	return 0;
}