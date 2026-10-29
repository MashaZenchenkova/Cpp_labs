#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
void glavnoemenu();
/// Задача1 начало
struct Data
{
	int day;
	int month;
	int year;
};
class Ticket
{
protected:
	int ID;
	Data date;
	int price;
	int kurort;
	string status;
public:
	static int TicketsSold;
	static int vruchka;
	Ticket(int ID, Data date, int price, int kurort) : ID(ID), date(date), price(price), kurort(kurort), status("Забронирован")
	{
		TicketsSold++;
	}
	virtual ~Ticket() = default;
	bool pay() 
	{
		if (status == "Забронирован") 
		{
			status = "Оплачен";
			vruchka += price + kurort;
			cout << "Билет " << ID << " оплачен" << endl;
			return true;
		}
		else if (status == "Оплачен") 
		{
			cout << "Билет " << ID << " уже оплачен" << endl;
			return false;
		}
		else
		{
			cout << "Билет " << ID << " был возвращен и не может быть оплачен" << endl;
			return false;
		}
	}
	bool vozvrat() 
	{
		if (status == "Оплачен") 
		{
			status = "Возвращен";
			TicketsSold--;
			cout << "Билет " << ID << " возвращен. Деньги не вернутся" << endl;
			return true;
		}
		else if (status == "Забронирован") 
		{
			status = "Возвращен";
			TicketsSold--; 
			cout << "Бронирование билета " << ID << " отменено" << endl;
			return true;
		}
		else
		{
			cout << "Билет " << ID << " уже был возвращен" << endl;
			return false;
		}
	}
	int getID() const {return ID;}
	Data getDate() const {return date;}
	int getPrice() const {return price;}
	string getStatus() const {return status;}
	virtual void printInfo() const = 0;
};
int Ticket::TicketsSold = 0;
int Ticket::vruchka = 0;
class MovieTicket : public Ticket
{
private:
	string movie;
	int zal;
	int ryad;
	int mesto;
public:
	MovieTicket(int ID, Data date, int price, int kurort, string movie, int zal, int ryad, int mesto) : Ticket(ID, date, price, kurort), movie(movie), zal(zal), ryad(ryad), mesto(mesto)
	{}
	void printInfo() const override
	{
		cout << "Номер билета: " << ID << endl;
		cout << "Дата: " << date.day << "." << date.month << "." << date.year << endl;
		cout << "Цена: " << price << " руб." << " Вместе с курортным сбором: " << price + kurort << " руб." << endl;
		cout << "Статус: " << status << endl;
		cout << "Фильм: " << movie << endl;
		cout << "Зал: " << zal << ", Ряд: " << ryad << ", Место: " << mesto << endl;
	}
};
class FlightTicket : public Ticket
{
private:
	int reis;
	string class_obsl;
	bool bagag;
public:
	FlightTicket(int ID, Data date, int price, int kurort, int reis, string class_obsl, bool bagag) : Ticket(ID, date, price, kurort), reis(reis), class_obsl(class_obsl), bagag(bagag)
	{}
	void printInfo() const override
	{
		cout << "Номер билета: " << ID << endl;
		cout << "Дата: " << date.day << "." << date.month << "." << date.year << endl;
		cout << "Цена: " << price << " руб." << " Вместе с курортным сбором: " << price + kurort << " руб." << endl;
		cout << "Статус: " << status << endl;
		cout << "Рейс: " << reis << endl;
		cout << "Наличие багажа: " << bagag << endl;
	}
};
class TrainTicket : public Ticket
{
private:
	int number_poezd;
	int vagon;
	string type_mesto;
public:
	TrainTicket(int ID, Data date, int price, int kurort, int number_poezd, int vagon, string type_mesto) : Ticket(ID, date, price, kurort), number_poezd(number_poezd), vagon(vagon), type_mesto(type_mesto)
	{}
	void printInfo() const override
	{
		cout << "Номер билета: " << ID << endl;
		cout << "Дата: " << date.day << "." << date.month << "." << date.year << endl;
		cout << "Цена: " << price << " руб." << " Вместе с курортным сбором: " << price+kurort << " руб." << endl;
		cout << "Статус: " << status << endl;
		cout << "Номер поезда: " << number_poezd << endl;
		cout << "Номер вагона: " << vagon << endl;
		cout << "Тип места: " << type_mesto << endl;
	}
};
vector <unique_ptr <Ticket>> Tickets;
void sozdat_bilet_v_kino()
{
	int price = 500;
	int kurort = 50;
	int id, day, month, year, zal, ryad, mesto;
	string movie;
	cout << "Создание билета в кино" << endl;
	cout << "Введите номер билета: ";
	cin >> id;
	cout << "Введите дату (DD MM YYYY): ";
	cin >> day >> month >> year;
	if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1 || (month == 2 && day > 29))
	{
		cout << "Серьезно?" << endl;
		return;
	}
	cout << "Введите название фильма: ";
	cin.ignore();
	getline(cin, movie);
	cout << "Введите номер зала: ";
	cin >> zal;
	cout << "Введите ряд: ";
	cin >> ryad;
	cout << "Введите место: ";
	cin >> mesto;
	Tickets.push_back(make_unique<MovieTicket>(id, Data{ day, month, year }, price, kurort, movie, zal, ryad, mesto));
}
void sozdat_bilet_v_sam()
{
	int price = 5000;
	int kurort = 500;
	int id, day, month, year, reis;
	string class_obsl;
	bool bagag;
	cout << "Создание билета на самолет" << endl;
	cout << "Введите номер билета: ";
	cin >> id;
	cout << "Введите дату (DD MM YYYY): ";
	cin >> day >> month >> year;
	if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1 || (month == 2 && day > 29))
	{
		cout << "Серьезно?" << endl;
		return;
	}
	cout << "Введите номер рейса: ";
	cin >> reis;
	cout << "Введите класс обслуживания (biznes, econom): ";
	cin.ignore();
	cin >> class_obsl;
	if (class_obsl == "biznes")
	{
		price = 10000;
		kurort = 1000;
	}
	cout << "Наличие багажа (1 - Да, 0 - Нет): ";
	cin >> bagag;
	if (bagag)
	{
		price += 1000;
	}
	Tickets.push_back(make_unique<FlightTicket>(id, Data{ day, month, year }, price, kurort, reis, class_obsl, bagag));
}
void sozdat_bilet_v_poezd()
{
	int price = 2500;
	int kurort = 250;
	int id, day, month, year, number_poezd, vagon;
	string type_mesto;
	cout << "Создание билета на самолет" << endl;
	cout << "Введите номер билета: ";
	cin >> id;
	cout << "Введите дату (DD MM YYYY): ";
	cin >> day >> month >> year;
	if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1 || (month == 2 && day > 29))
	{
		cout << "Серьезно?" << endl;
		return;
	}
	cout << "Введите номер поезда: ";
	cin >> number_poezd;
	cout << "Введите номер вагона: ";
	cin >> vagon;
	cout << "Введите тип места (kype, platskart): ";
	cin.ignore();
	cin >> type_mesto;
	if (type_mesto == "kype")
	{
		price = 5000;
		kurort = 500;
	}
	Tickets.push_back(make_unique<TrainTicket>(id, Data{ day, month, year }, price, kurort, number_poezd, vagon, type_mesto));
}
void pokazat_vse_bilety()
{
	if (Tickets.empty()) 
	{
		cout << "Билетов нет!" << endl;
		return;
	}
	for (int i = 0; i < Tickets.size(); i++) 
	{
		cout << "Билет " << i + 1 << ":" << endl;
		Tickets[i] -> printInfo();
	}
}
void oplata_bilet()
{
	if (Tickets.empty())
	{
		cout << "Нет билетов для оплаты" << endl;
		return;
	}
	int id;
	cout << "Введите ID билета для поиска: ";
	cin >> id;
	bool flag = false;
	for (int i = 0; i < Tickets.size(); i++)
	{
		if (Tickets[i]->getID() == id)
		{
			flag = true;
			if (Tickets[i]->getStatus() == "Забронирован")
			{
				Tickets[i]->pay();
				cout << "Билет оплачен" << endl;
			}
			else if (Tickets[i]->getStatus() == "Оплачен")
			{
				cout << "Этот билет уже оплачен" << endl;
			}
			else
			{
				cout << "Этот билет был возвращен" << endl;
			}
			break;
		}
	}
	if (!flag)
	{
		cout << "Билет " << id << " не найден!" << endl;
	}
}
void vernut_bilet()
{
	if (Tickets.empty())
	{
		cout << "Нет билетов для снятия брони" << endl;
		return;
	}
	int id;
	cout << "Введите ID билета для снятия брони: ";
	cin >> id;
	bool flag = false;
	for (int i = 0; i < Tickets.size(); i++)
	{
		if (Tickets[i]->getID() == id)
		{
			flag = true;
			if (Tickets[i]->getStatus() == "Оплачен")
			{
				Tickets[i]->vozvrat();
				cout << "Билет возвращен" << endl;
			}
			else if (Tickets[i]->getStatus() == "Забронирован")
			{
				Tickets[i]->vozvrat();
				cout << "Бронь отменилась" << endl;
			}
			else
			{
				cout << "Этот билет был возвращен" << endl;
			}
			break;
		}
	}
	if (!flag)
	{
		cout << "Билет " << id << " не найден" << endl;
	}
}
void zadacha1()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "Все билеты безвозвратные!" << endl;
	cout << "1. Создать билет в кино" << endl;
	cout << "2. Создать билет на самолет" << endl;
	cout << "3. Создать билет на поезд" << endl;
	cout << "4. Показать все билеты" << endl;
	cout << "5. Оплатить билет" << endl;
	cout << "6. Вернуть билет" << endl;
	cout << "7. Общее количество проданных билетов" << endl;
	cout << "8. Общее количество выручки" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		sozdat_bilet_v_kino();
		zadacha1();
	case 2:
		sozdat_bilet_v_sam();
		zadacha1();
	case 3:
		sozdat_bilet_v_poezd();
		zadacha1();
	case 4:
		pokazat_vse_bilety();
		zadacha1();
	case 5:
		oplata_bilet();
		zadacha1();
	case 6:
		vernut_bilet();
		zadacha1();
	case 7:
		cout << "Проданно билетов: " << Ticket::TicketsSold << endl;
		zadacha1();
	case 8:
		cout << "Выручка: " << Ticket::vruchka << " руб" << endl;
		zadacha1();
	case 0:
		glavnoemenu();
	default:
		cout << "Такого задания нет!" << endl;
		zadacha1();
	}
}
/// Задача1 конец
/// Задача2 начало
class Employee
{
protected:
	string name;
	int ID;
	int zp_chas;
	int salary;
public:
	static int kolvo_deneg;
	Employee(string name, int ID, int zp_chas, int salary) : name(name), ID(ID), zp_chas(zp_chas), salary(salary)
	{}
	virtual ~Employee() = default;
	string getname() const {return name;}
	int getID() const {return ID;}
	int getzp_chas() const {return zp_chas;}
	virtual void printInfo() = 0;
	virtual int calculateSalary() = 0;
	virtual string getType() const = 0;
	virtual string getCSVData() const = 0;
};
int Employee::kolvo_deneg = 0;
class SalariedEmployee : public Employee
{
private:
	int prem; 
public:
	SalariedEmployee(string name, int ID, int zp_chas, int salary, int prem) : Employee(name, ID, zp_chas, salary), prem(prem)
	{
		salary = calculateSalary();
		kolvo_deneg += salary;
	}
	int calculateSalary() override
	{
		salary = zp_chas * 100 + prem;
		return salary;
	}
	string getType() const override
	{
		return "Штатный";
	}
	string getCSVData() const override
	{
		return getType() + ";" + name + ";" + to_string(ID) + ";" + to_string(zp_chas) + ";" + to_string(prem) + ";" + ";" + ";" + ";" + ";" + to_string(salary);
	}
	void printInfo() override
	{
		cout << "Штатный сотрудник" << endl;
		cout << "Имя: " << name << endl;
		cout << "ID: " << ID << endl;
		cout << "Оклад: " << zp_chas*100 << " руб." << endl;
		cout << "Премия: " << prem << " руб." << endl;
		cout << "Итог: " << calculateSalary() << " руб." << endl;
	}
};
class HourlyEmployee : public Employee
{
private:
	int hoursWorked;  
public:
	HourlyEmployee(string name, int ID, int zp_chas, int salary, int hoursWorked) : Employee(name, ID, zp_chas, salary), hoursWorked(hoursWorked)
	{
		salary = calculateSalary();
		kolvo_deneg += salary;
	}
	int calculateSalary() override
	{
		salary = zp_chas * hoursWorked;
		return salary;
	}
	string getType() const override
	{
		return "Почасовой";
	}

	string getCSVData() const override
	{
		return getType() + ";" + name + ";" + to_string(ID) + ";" + to_string(zp_chas) + ";" + ";" + to_string(hoursWorked) + ";" + ";" + ";" + ";" + to_string(salary); 
	}
	void printInfo() override
	{
		cout << "Почасовой сторудник" << endl;
		cout << "Имя: " << name << endl;
		cout << "ID: " << ID << endl;
		cout << "Ставка в час: " << zp_chas << " руб." << endl;
		cout << "Отработано часов: " << hoursWorked << endl;
		cout << "Итог: " << calculateSalary() << " руб." << endl;
	}
};
class Manager : public Employee
{
private:
	double prodazhi;  
	double procent;  
public:
	Manager(string name, int ID, int zp_chas, int salary, double prodazhi, double procent) : Employee(name, ID, zp_chas, salary), prodazhi(prodazhi), procent(procent)
	{
		salary = calculateSalary();
		kolvo_deneg += salary;
	}
	int calculateSalary() override
	{
		salary = zp_chas + prodazhi / 100 + procent / 100;
		return salary;
	}
	string getType() const override
	{
		return "Менеджер";
	}

	string getCSVData() const override
	{
		return getType() + ";" + name + ";" + to_string(ID) + ";" + to_string(zp_chas) + ";" + ";" + ";" + to_string(prodazhi) + ";" + to_string(procent) + ";" + ";" + to_string(salary);  
	}
	void printInfo() override
	{
		cout << "Менеджер" << endl;
		cout << "Имя: " << name << endl;
		cout << "ID: " << ID << endl;
		cout << "Оклад: " << zp_chas << " руб." << endl;
		cout << "Продажи отдела: " << prodazhi << " руб." << endl;
		cout << "Процент: " << procent << endl;
		cout << "Итог: " << calculateSalary() << " руб." << endl;
	}
};
class Freelancer : public Employee
{
private:
	int project;
public:
	Freelancer(string name, int ID, int salary, double project) : Employee(name, ID, 0, salary), project(project)
	{
		salary = calculateSalary();
		kolvo_deneg += salary;
	}
	int calculateSalary() override
	{
		salary = project;
		return salary;
	}
	string getType() const override
	{
		return "Фрилансер";
	}

	string getCSVData() const override
	{
		return getType() + ";" + name + ";" + to_string(ID) + ";" + ";" + ";" + ";" + ";" + ";" + to_string(project) + ";" + to_string(salary); 
	}

	void printInfo() override
	{
		cout << "Фрилансер" << endl;
		cout << "Имя: " << name << endl;
		cout << "ID: " << ID << endl;
		cout << "Оплата за проект: " << project << " руб." << endl;
		cout << "Итог: " << calculateSalary() << " руб." << endl;
	}
};
class PayrollSystem
{
private:
	vector<unique_ptr<Employee>> employees;
public:
	void addEmployee()
	{
		int type;
		cout << "Выбор типа сотрудника" << endl;
		cout << "1. Штатный" << endl;
		cout << "2. Почасовой" << endl;
		cout << "3. Менеджер" << endl;
		cout << "4. Фрилансер" << endl;
		cout << "Выберите тип: ";
		cin >> type;
		string name;
		int id;
		cout << "Введите имя: ";
		cin.ignore();
		getline(cin, name);
		cout << "Введите ID: ";
		cin >> id;
		switch (type)
		{
		case 1:
		{
			int salary = 0;
			int rate;
			int prem;
			cout << "Введите оклад: ";
			cin >> rate;
			cout << "Введите премию: ";
			cin >> prem;
			employees.push_back(make_unique<SalariedEmployee>(name, id, rate, salary, prem));
			break;
		}
		case 2:
		{
			int salary = 0;
			int rate;
			int hours;
			cout << "Введите ставку в час: ";
			cin >> rate;
			cout << "Введите отработанные часы: ";
			cin >> hours;
			employees.push_back(make_unique<HourlyEmployee>(name, id, rate, salary, hours));
			break;
		}
		case 3:
		{
			int salary = 0;
			int rate;
			double sales;
			double percent;
			cout << "Введите оклад: ";
			cin >> rate;
			cout << "Введите продажи отдела: ";
			cin >> sales;
			cout << "Введите процент от продаж: ";
			cin >> percent;
			employees.push_back(make_unique<Manager>(name, id, rate, salary, sales, percent));
			break;
		}
		case 4:
		{
			int salary = 0;
			int payment;
			cout << "Введите оплату за проект: ";
			cin >> payment;
			employees.push_back(make_unique<Freelancer>(name, id, salary, payment));
			break;
		}
		default:
			cout << "Серьезно?" << endl;
			return;
		}
		employees.back()->printInfo();
	}
	void showAllEmployees() const
	{
		if (employees.empty())
		{
			cout << "Нет сотрудников в системе" << endl;
			return;
		}
		for (size_t i = 0; i < employees.size(); i++)
		{
			cout << "Сотрудник " << i + 1 << endl;
			employees[i]->printInfo();
		}
		cout << "Всего сотрудников: " << employees.size() << endl;
	}
	void poisk_Employees() const
	{
		int ID;
		if (employees.empty())
		{
			cout << "Нет сотрудников в системе" << endl;
			return;
		}
		cout << "Введите ID сотрулника: ";
		cin >> ID;
		bool flag = false;
		for (size_t i = 0; i < employees.size(); i++)
		{
			if (employees[i]->getID() == ID)
			{
				flag = true;
				employees[i]->printInfo();
			}
		}
		if (!flag)
		{
			cout << "Нет такого сотрудника" << endl;
		}
	}
	void saveToCSV(const string& filename)
	{
		if (employees.empty())
		{
			cout << "Нет сотрудников для сохранения" << endl;
			return;
		}
		ofstream file(filename);
		if (!file.is_open())
		{
			cout << "Ошибка создания файла " << filename << endl;
			return;
		}
		file << "№;Тип;Имя;ID;Оклад;Премия;Отработаночасов;Продажи;Процент;Проект;Зарплата" << endl;
		for (size_t i = 0; i < employees.size(); i++)
		{
			file << i + 1 << ";";
			file << employees[i]->getCSVData();
			file << endl;
		}
		file << "Итого;;;" << employees.size() << " сотрудников;;;;;;;;" << Employee::kolvo_deneg << " руб." << endl;
		cout << "Успешно" << endl;
		file.close();
	}
	void loadFromCSV(const string& filename)
	{
		ifstream file(filename);
		if (!file.is_open())
		{
			cout << "Ошибка открытия файла" << endl;
			return;
		}
		string line;
		getline(file, line);
		while (getline(file, line))
		{
			if (line.empty() || line.find("ИТОГО") != string::npos)
			{
				continue;
			}
			vector <string> fields;
			stringstream ss(line);
			string field;
			while (getline(ss, field, ';'))
			{
				fields.push_back(field);
			}
			string type = fields[1];      
			string name = fields[2];     
			int id = stoi(fields[3]);     
			bool idExists = false;
			for (const auto& emp : employees)
			{
				if (emp->getID() == id)
				{
					idExists = true;
					break;
				}
			}
			if (type == "Штатный")
			{
				int rate = stoi(fields[4]);    
				int prem = stoi(fields[5]);    
				int salary = 0; 
				employees.push_back(make_unique<SalariedEmployee>(name, id, rate, salary, prem));
			}
			else if (type == "Почасовой")				
			{
				int rate = stoi(fields[4]);    
				int hours = stoi(fields[6]);  
				int salary = 0; 
				employees.push_back(make_unique<HourlyEmployee>(name, id, rate, salary, hours));
			}
			else if (type == "Менеджер")
			{
				int rate = stoi(fields[4]);       
				double sales = stod(fields[7]);    
				double percent = stod(fields[8]); 
				int salary = 0; 
				employees.push_back(make_unique<Manager>(name, id, rate, salary, sales, percent));
			}
			else if (type == "Фрилансер")
			{
				int project = stoi(fields[9]); 
				int salary = 0; 
				employees.push_back(make_unique<Freelancer>(name, id, salary, project));
			}
		}
		file.close();
		cout << "Успешно" << endl;
	}
};
PayrollSystem payroll;
void zadacha2()
{

	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "1. Добавить сотрудника" << endl;
	cout << "2. Все сотрудники" << endl;
	cout << "3. Общий фонд оплаты труда" << endl;
	cout << "4. Поиск сотрудника по ID" << endl;
	cout << "5. Сохранить в CSV файл" << endl;
	cout << "6. Загрузить из CSV файла" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		payroll.addEmployee();
		zadacha2();
	case 2:
		payroll.showAllEmployees();
		zadacha2();
	case 3:
		cout << Employee::kolvo_deneg << " рубля" << endl;
		zadacha2();
	case 4:
		payroll.poisk_Employees();
		zadacha2();
	case 5:
		payroll.saveToCSV("aaa.csv");
		zadacha2();
	case 6:
		payroll.loadFromCSV("aaa.csv");
		zadacha2();
	case 0:
		glavnoemenu();
	default:
		cout << "Такого задания нет!" << endl;
		zadacha2();
	}
}
/// Задача2 конец
/// Задача3 начало
class BankCard
{
protected:
	int nomer;
	int pin;
	string name;
	double balans;
	string type;
	int vor;
public:
	BankCard(int nomer, int pin, string name, double balans, string type, int vor) : nomer(nomer), pin(pin), name(name), balans(balans), type(type), vor(vor)
	{}
	virtual ~BankCard() = default;
	int getnomer() const { return nomer; }
	int getpin() const { return pin; }
	double getbalans() const { return balans; }
	string getname() const { return name; }
	string gettype() const { return type; }
	int getvor() const { return vor; }
	virtual void printInfo() = 0;
	void setBalans(double newBalans)
	{
		balans = newBalans;
	}
	void setvor(int newvor)
	{
		vor = newvor;
	}
};
class DebitCard : public BankCard
{
public:
	DebitCard(int nomer, int pin, string name, double balans, string type, int vor) : BankCard(nomer, pin, name, balans, type, vor)
	{
		type = "Дебетовая карта"; 
	}
	void printInfo() override
	{
		cout << "Дебетовая карта" << endl;
		cout << "Номер: " << nomer << endl;
		cout << "PIN: " << pin << endl;
		cout << "Имя владельца: " << name << endl;
		cout << "Баланс: " << balans << endl;
	}
};
class CreditCard : public BankCard
{
private:
	int creditLimit;
	double dolg;
	double prots_dolg;
public:
	CreditCard(int nomer, int pin, string name, double balans, string type, int vor, int creditLimit, double dolg, double prots_dolg) : BankCard(nomer, pin, name, balans, type, vor), creditLimit(creditLimit), dolg(dolg), prots_dolg(prots_dolg)
	{
		type = "Кредитная карта";
	}
	void printInfo() override
	{
		cout << "Кредитная карта" << endl;
		cout << "Номер: " << nomer << endl;
		cout << "PIN: " << pin << endl;
		cout << "Имя владельца: " << name << endl;
		cout << "Баланс: " << balans << endl;
		cout << "Кредитный лимит: " << creditLimit << endl;
		cout << "Долг: " << dolg << endl;
		cout << "Процент на долг: " << prots_dolg << endl;
	}
	int getCreditLimit() const { return creditLimit; }
	double getprots_dolg() const { return prots_dolg; }
	double getDolg() const { return dolg; }
	void setDolg(double newDolg) { dolg = newDolg; }
};
class BonusCard : public BankCard
{
private:
	double nakop_bonus;
public:
	BonusCard(int nomer, int pin, string name, double balans, string type, int vor, double nakop_bonus) : BankCard(nomer, pin, name, balans, type, vor), nakop_bonus(nakop_bonus)
	{
		type = "Бонусная карта";
	}
	void printInfo() override
	{
		cout << "Бонусная карта" << endl;
		cout << "Номер: " << nomer << endl;
		cout << "PIN: " << pin << endl;
		cout << "Имя владельца: " << name << endl;
		cout << "Баланс: " << balans << endl;
		cout << "Процент за покупку: 10" << endl;
		cout << "Накопленные бонусы: " << nakop_bonus << endl;
	}
	double getBonus() const { return nakop_bonus; }
	void setBonus(double newBonus)
	{
		nakop_bonus = newBonus;
	}
};
class ATM
{
private:
	vector<unique_ptr<BankCard>> cards;
public:
	void add_card()
	{
		int type1;
		cout << "Выбор типа карты" << endl;
		cout << "1. Дебетовая" << endl;
		cout << "2. Кредитная" << endl;
		cout << "3. Бонусная" << endl;
		cout << "Выберите тип: ";
		cin >> type1;
		int nomer;
		int pin;
		int vor = 0;
		string name;
		double balans = 0;
		cout << "Введите номер: ";
		cin >> nomer;
		cout << "Задайте PIN: ";
		cin >> pin;
		cout << "Введите ваше имя: ";
		cin.ignore();
		getline(cin, name);
		switch (type1)
		{
		case 1:
		{
			cards.push_back(make_unique <DebitCard>(nomer, pin, name, balans, "Дебетовая карта", vor));
			break;
		}
		case 2:
		{
			int creditLimit;
			double dolg = 0;
			double prots_dolg;
			cout << "Задайте кредитный лимит: ";
			cin >> creditLimit;
			cout << "Задайте процент на просрочку: ";
			cin >> prots_dolg;
			cards.push_back(make_unique <CreditCard>(nomer, pin, name, balans, "Кредитная карта", vor, creditLimit, dolg, prots_dolg));
			break;
		}
		case 3:
		{
			cards.push_back(make_unique <BonusCard>(nomer, pin, name, balans, "Бонусная карта", vor, 0));
			break;
		}
		} 
	}
	void menu_bank()
	{
		int pin;
		int nomer;
		bool flag = false;
		int cardi = -1;
		cout << "Введите номер карты: ";
		cin >> nomer;
		cout << "Введите PIN: ";
		cin >> pin;
		for (int i = 0; i < size(cards); i++)
		{
			if (nomer == cards[i]->getnomer() && pin == cards[i]->getpin() && cards[i]->getvor() < 3)
			{
				flag = true;
				cardi = i;
			}
		}
		if (flag == false)
		{
			cout << "Фу, уходи" << endl;
			for (int i = 0; i < size(cards); i++)
			{
				if (nomer == cards[i]->getnomer())
				{
					int vor = cards[i]->getvor() + 1;
					cards[i]->setvor(vor);

					if (cards[i]->getvor() >= 3)
					{
						cout << "Карта заблокирована" << endl;
					}
					break;
				}
			}
			return;
		}
		else
		{
			int vbr = 5;
			while (vbr != 0)
			{
				cout << "Добро пожаловать, " << cards[cardi]->getname() << endl;
				cout << "Баланс: " << cards[cardi]->getbalans() << endl;
				cout << "Тип карты: " << cards[cardi]->gettype() << endl;
				cout << "1. Снять наличные" << endl;
				cout << "2. Внести наличные" << endl;
				cout << "3. Показать баланс" << endl;
				cout << "0. Выйти" << endl;
				cout << "Выберите тип: ";
				cin >> vbr;
				switch (vbr)
				{
				case 1:
				{
					double deneg_sn;
					double bon_pokup = 0;
					cout << "Введите сумму, которую хотите снять: ";
					cin >> deneg_sn;
					if (deneg_sn <= 0)
					{
						cout << "Сумма должна быть положительной!" << endl;
						break;
					}
					double tek_b = cards[cardi]->getbalans();
					string cardType = cards[cardi]->gettype();
					if (cardType == "Кредитная карта")
					{
						CreditCard* creditCard = dynamic_cast<CreditCard*>(cards[cardi].get());
						if (creditCard)
						{
							double creditAvailable = creditCard->getCreditLimit() - creditCard->getDolg();
							double totalAvailable = tek_b + creditAvailable;
							double dolg = creditCard->getprots_dolg();
							if (deneg_sn > totalAvailable)
							{
								cout << "Превышен кредитный лимит! Доступно: " << totalAvailable << " руб." << endl;
								break;
							}
							if (deneg_sn > tek_b)
							{
								double useCredit = deneg_sn - tek_b;
								creditCard->setDolg(creditCard->getDolg() + useCredit);
								cout << "Через месяц долг будет: " << creditCard->getDolg() + creditCard->getDolg() * dolg / 100 << endl;
								tek_b = 0;
							}
							else
							{
								tek_b -= deneg_sn;
							}
						}
					}
					else if (cardType == "Дебетовая карта")
					{
						if (deneg_sn > tek_b)
						{
							cout << "Недостаточно средств. Доступно: " << tek_b << " руб." << endl;
							break;
						}
						tek_b -= deneg_sn;
					}
					else if (cardType == "Бонусная карта")
					{
						if (deneg_sn > tek_b)
						{
							cout << "Недостаточно средств. Доступно: " << tek_b << " руб." << endl;
							break;
						}
						tek_b -= deneg_sn;
						bon_pokup = deneg_sn * 0.1;
						BonusCard* bonusCard = dynamic_cast<BonusCard*>(cards[cardi].get());
						if (bonusCard)
						{
							double currentBonus = bonusCard->getBonus(); 
							bonusCard->setBonus(currentBonus + bon_pokup);
							cout << "Начислено бонусов: " << bon_pokup << endl;
						}
					}
					cards[cardi]->setBalans(tek_b);
					cout << "Операция успешна!" << endl;
					break;
				}
				case 2:
				{
					double deneg_popoln;
					cout << "Введите сумму, которую хотите внести: ";
					cin >> deneg_popoln;

					if (deneg_popoln <= 0)
					{
						cout << "Сумма должна быть положительной!" << endl;
						break;
					}

					string cardType = cards[cardi]->gettype();
					double tek_b = cards[cardi]->getbalans();

					if (cardType == "Кредитная карта")
					{
						CreditCard* creditCard = dynamic_cast<CreditCard*>(cards[cardi].get());
						if (creditCard)
						{
							double dolg = creditCard->getDolg();
							if (dolg > 0)
							{
								if (deneg_popoln >= dolg)
								{
									deneg_popoln -= dolg;
									creditCard->setDolg(0);
								}
								else
								{
									creditCard->setDolg(dolg - deneg_popoln);
									deneg_popoln = 0;
								}
							}
							if (deneg_popoln > 0)
							{
								tek_b += deneg_popoln;
								cards[cardi]->setBalans(tek_b);
							}
						}
					}
					else
					{
						tek_b += deneg_popoln;
						cards[cardi]->setBalans(tek_b);
					}
					cout << "Операция успешна!" << endl;
					break;
				}
				case 3:
				{
					string cardType = cards[cardi]->gettype();
					if (cardType == "Кредитная карта")
					{
						CreditCard* creditCard = dynamic_cast<CreditCard*>(cards[cardi].get());
						if (creditCard)
						{
							cout << "Собственные средства: " << cards[cardi]->getbalans() << " руб." << endl;
							cout << "Текущий долг: " << creditCard->getDolg() << " руб." << endl;
							cout << "Доступно кредитных средств: " << creditCard->getCreditLimit() - creditCard->getDolg() << " руб." << endl;
						}
					}
					else if (cardType == "Бонусная карта")
					{
						cout << "Баланс: " << cards[cardi]->getbalans() << " руб." << endl;
						BonusCard* bonusCard = dynamic_cast<BonusCard*>(cards[cardi].get());
						if (bonusCard)  
						{
							double bonusAmount = bonusCard->getBonus();
							cout << "Накопленные бонусы: " << bonusAmount << endl;
							if (bonusAmount > 0)
							{
								cout << "Вы можете потратить бонусы при следующей покупке!" << endl;
							}
						}
					}
					else
					{
						cout << "Баланс: " << cards[cardi]->getbalans() << " руб." << endl;
					}
					break;
				}
				}
			}
		}
	}
};
ATM atm;
void zadacha3()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "1. Добавить карту" << endl;
	cout << "2. Меню работы с картой" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		atm.add_card();
		zadacha3();
	case 2:
		atm.menu_bank();
		zadacha3();
	case 0:
		glavnoemenu();
	default:
		cout << "Такого задания нет!" << endl;
		glavnoemenu();
	}
}
/// Задача3 конец
void glavnoemenu()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "Задача 1. Система бронирования билетов (Кинотеатр/Авиа/ЖД)" << endl;
	cout << "Задача 2. Система расчета зарплаты(для разных категорий сотрудников)" << endl;
	cout << "Задача 3. Симулятор работы банкомата с разными типами карт" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		zadacha1();
		glavnoemenu();
	case 2:
		zadacha2();
		glavnoemenu();
	case 3:
		zadacha3();
		glavnoemenu();
	case 0:
		exit(0);
	default:
		cout << "Такого задания нет!" << endl;
		glavnoemenu();
	}
}
int main()
{
	setlocale(LC_ALL, "rus");
	glavnoemenu();
	return 0;
}