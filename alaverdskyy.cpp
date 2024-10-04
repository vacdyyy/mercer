#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include<iomanip>
#include<sstream>

using namespace std;
using namespace std::chrono;

class Bill;
class StandartRoom;
class VIPRoom;
class PremiumRoom;
class LuxRoom;

string formatTimePoint(const system_clock::time_point& tp) {
	time_t time = system_clock::to_time_t(tp);
	tm local_tm;
	localtime_s(&local_tm, &time);
	ostringstream oss;
	oss << put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}



class Guest {
private:
	vector <Guest*>guests;
	int id;
	string name;
	unsigned int age;
	string phone;
	int roomNumber;
public:
	Guest(string name, unsigned int age, string phone) : name(name), age(age), phone(phone) {
		this->id++;
		guests.push_back(this);
	}

	int getId() {
		return id;
	}

	string getName() {
		return name;
	}

	unsigned int getAge() {
		return age;
	}

	string getPhone() {
		return phone;
	}

	int getRoomNumber() {
		return roomNumber;
	}

	void setName(string name) {
		this->name = name;
	}

	void setAge(unsigned int age) {
		this->age = age;
	}

	void setPhone(string phone) {
		this->phone = phone;
	}

	void setRoomNuber(int roomNumber) {
		this->roomNumber = roomNumber;
	}
};


class Room {
public:
	int id;
	int number;
	string type;
	string title;
	int beds;
	bool status;
	int price;
	vector <Guest*> guests;
	virtual void showInfo();
	virtual int getId();


};

class StandartRoom : public Room {
private:
	int id = 0;
	int number;
	string type = "Standart";
	string title;
	int beds;
	bool tV;
	bool status = false;
	int price = 3000;
	vector <Guest*> guests;


public:
	StandartRoom(int number, string title, int beds) : number(number), title(title), beds(beds) {
		this->id = this->id++;
	}

	void showInfo() {
		cout << "Type: " << type << endl << "Title: " << title << endl << "Number: " << number << endl << "Beds: " << beds << endl << "Price on one night: " << price << endl;
	}

	void setStatus(bool status) {
		this->status = status;
	}
	void onTV(bool tv) {
		tV = tv;
		cout << "Tv is working" << endl;
	}

	void offTV(bool tv) {
		tV = tv;
		cout << "Tv is offed" << endl;
	}

	int getId() {
		return this->id;
	}

	string getType() {
		return type;
	}
	void showGuests() {
		for (auto guest : guests) {
			cout << guest->getName() << endl;
		}
	}

};


class VIPRoom : public Room {
private:
	int id;
	int number;
	string type = "VIP";
	string title;
	int beds;
	bool cleaner;
	bool status = false;
	int price = 5000;
	vector <Guest*> guests;
public:
	VIPRoom(int number, string title, int beds) : number(number), title(title), beds(beds) {
		this->id++;
	}

	void showInfo() {
		cout << "Type: " << type << endl << "Title: " << title << endl << "Number: " << number << endl << "Beds: " << beds << endl << "Price on one night: " << price << endl;
	}
	void setStatus(bool status) {
		this->status = status;
	}
	void callCleaner(bool call) {
		cleaner = call;
		cout << "Cleaner is coming" << endl;
	}
	void throwOutCleaner(bool out) {
		cleaner = out;
		cout << "Cleaner is thow out" << endl;
	}

	string getType() {
		return type;
	}
	int getId() {
		return this->id;
	}

};

class PremiumRoom : public Room {
private:
	int id;
	int number;
	string type = "Premium";
	string title;
	int beds;
	bool robotPilesos;
	bool status = false;
	int price = 10000;
	vector <Guest*> guests;
public:
	PremiumRoom(int number, string title, int beds) : number(number), title(title), beds(beds) {
		this->id++;
	}
	void setStatus(bool status) {
		this->status = status;
	}
	void onRobotPilesos(bool on) {
		robotPilesos = on;
		cout << "Robot is cleaning" << endl;
	}
	void offRobotPilesos(bool off) {
		robotPilesos = off;
		cout << "Robot end cleaning" << endl;
	}
	int getId() {
		return this->id;
	}
	string getType() {
		return type;
	}

	void showInfo() {
		cout << "Type: " << type << endl << "Title: " << title << endl << "Number: " << number << endl << "Beds: " << beds << endl << "Price on one night: " << price << endl;
	}
};

class LuxRoom : public Room {
private:
	int id;
	int number;
	string type = "Lux";
	string title;
	int beds;
	bool status = false;
	bool conditioner;
	int price = 20000;
	vector <Guest*> guests;
public:
	LuxRoom(int number, string title, int beds) : number(number), title(title), beds(beds) {
		this->id++;
	}

	int getId() {
		return this->id;
	}
	void onConditioner(bool on) {
		conditioner = on;
	}

	void offConditioner(bool off) {
		conditioner = off;
	}

	void setStatus(bool status) {
		this->status = status;
	}

	string getType() {
		return type;
	}

	void showInfo() {
		cout << "Type: " << type << endl << "Title: " << title << endl << "Number: " << number << endl << "Beds: " << beds << endl << "Price on one night: " << price << endl;
	}
};


class Bill {
private:
	int id;
	double amount;
	int idGuest;
	int idRoom;
	system_clock::time_point checkInDate;
	system_clock::time_point checkOutDate;
	Guest* guest;


public:
	Bill(int idGuest, int idRoom) :idGuest(idGuest), idRoom(idRoom), checkInDate(system_clock::now()) {
		this->id = this->id++;
	}

	int getId() {
		return id;
	}

	void countAmount() {
		checkOutDate = system_clock::now();
		duration <double> diff = checkInDate - checkOutDate;
		amount = ((diff.count() / 3600) / 24) + 1;


	}

};

class HotelManagment {
private:
	vector <Guest*> guests;
	vector <Room*> rooms;
	vector<Bill*> bills;
public:
	HotelManagment() {}

	void checkIn(Guest* guest, int neededBeds, string type) {
		for (auto room : rooms) {
			if (type == room->type && neededBeds == room->beds) {
				room->showInfo();
				room->status = true;
				guest->setRoomNuber(room->number);
				Bill* bill = new Bill(guest->getId(), room->getId());
				guests.push_back(guest);
			}
		}
	}

	/*void guestAvay(Guest* guest) {
		double cost = amount*(room->price);
	}*/

	void addGuest(Guest* guest) {
		guests.push_back(guest);
	}

	void addBill(Bill* bill) {
		bills.push_back(bill);
	}

	void addRoom(Room* room1) {
		rooms.push_back(room1);
	}

	void showGuests() {
		for (auto guest : guests) {
			cout << guest->getName() << endl;
		}
	}

	void showRooms() {
		for (auto room : rooms) {
			room->showInfo();
		}
	}

	void showBills() {
		for (auto bill : bills) {
			cout << bill->getId() << endl;
		}
	}

	void pushRoomInFile(string path) {
		ofstream out(path);
		string str;
		if (out.is_open()) {
			for (int i = 0; i < rooms.size(); i++) {
				out << str << endl;
			}
		}

		out.close();
	}

	void pushGuestInFile(string path) {
		ofstream out(path);
		string str;
		if (out.is_open()) {
			for (int i = 0; i < rooms.size(); i++) {
				out << str << endl;
			}
		}

		out.close();
	}

	void pushBillInFile(string path) {
		ofstream out(path);
		string str;
		if (out.is_open()) {
			for (int i = 0; i < rooms.size(); i++) {
				out << str << endl;
			}
		}

		out.close();
	}


};

void Room::showInfo()
{
	cout << "Type: " << type << endl << "Title: " << title << endl << "Number: " << number << endl << "Beds: " << beds << endl << "Price on one night: " << price << endl;
}

int Room::getId()
{
	return this->id;
}

void menu() {
	cout << "Добро пожаловать в отель: \n выберите действие: \n 1 - добавить гостя \n 2 - добавление комнаты" << endl;
	int choice;
	cin >> choice;
	HotelManagment* h1 = new HotelManagment();
	if (choice == 1) {
		string name;
		int age;
		string phone;
		cout << "Введите имя гостя: " << endl;
		cin >> name;
		cout << "Введите возраст гостя: " << endl;
		cin >> age;
		cout << "Введите номер гостя: " << endl;
		cin >> phone;
		Guest* newGuest = new Guest(name, age, phone);
		h1->addGuest(newGuest);
	}
	else if (choice == 2) {
		int number;
		string title;
		int beds;
		int type;
		cout << "Выберите вид комнаты: \n 1 - Standart \n 2 - VIP \n 3 - Premium \n 4 - Lux" << endl;
		cin >> type;
		cout << "Введите номер комнаты: " << endl;
		cin >> number;
		cout << "Введите название комнаты: " << endl;
		cin >> title;
		cout << "Введите кровати в комнате: " << endl;
		cin >> beds;
		if (type == 1) {
			StandartRoom* room1 = new StandartRoom(number, title, beds);
			h1->addRoom(room1);
		}
		else if (type == 2) {
			VIPRoom* room1 = new VIPRoom(number, title, beds);
			h1->addRoom(room1);
		}
		else if (type == 3) {
			PremiumRoom* room1 = new PremiumRoom(number, title, beds);
			h1->addRoom(room1);
		}
		else if (type == 4) {
			LuxRoom* room1 = new LuxRoom(number, title, beds);
			h1->addRoom(room1);
		}
		else {
			cout << "неправильно выбрано действие" << endl;
		}
	}

	else {
		cout << "неправильно выбрано действие" << endl;
	}
}


int main()
{
	setlocale(LC_ALL, "rus");
	menu();
	menu();
	menu();
}