#include <iostream>
#include <pqxx/pqxx>
#include <stdexcept>
#include <string>
#include <windows.h>
using namespace std;
#pragma warning(disable: 4996)
class DatabaseException : public runtime_error
{
public:
    DatabaseException(const string& message) : runtime_error(message) {}
};
class DateInPastException : public DatabaseException 
{
public:
    DateInPastException(const string& message) : DatabaseException(message) {}
};
class NotFoundException : public DatabaseException 
{
public:
    NotFoundException(const string& message) : DatabaseException(message) {}
};
class InvalidInputException : public DatabaseException 
{
public:
    InvalidInputException(const string& message) : DatabaseException(message) {}
};
class ForbiddenActionException : public DatabaseException 
{
public:
    ForbiddenActionException(const string& message) : DatabaseException(message) {}
};
class DatabaseManager
{
private:
    static DatabaseManager* instance;
    pqxx::connection* conn;
    DatabaseManager()
    {
        try
        {
            conn = new pqxx::connection("dbname=salon_db user=myappuser password=Zench host=localhost port=5432");
            cout << "Pobeda" << endl;
        }
        catch (const exception& e)
        {
            throw DatabaseException("включи убубунту!");
        }
    }
    ~DatabaseManager()
    {
        if (conn && conn->is_open())
        {
            conn->close();
            cout << "До связи" << endl;
        }
    }
public:
    void execute(const string& sql)
    {
        try
        {
            pqxx::work txn(*conn);
            txn.exec(sql);
            txn.commit();
        }
        catch (const exception& e)
        {
            throw DatabaseException(e.what());
        }
    }
    void query(const string& sql, function<void(const pqxx::result&)> callback)
    {
        try
        {
            pqxx::work txn(*conn);
            pqxx::result r = txn.exec(sql);
            callback(r);
            txn.commit();
        }
        catch (const exception& e)
        {
            throw DatabaseException(e.what());
        }
    }
    static DatabaseManager* getInstance()
    {
        if (!instance)
        {
            instance = new DatabaseManager();
        }
        return instance;
    }
    pqxx::connection* getConnection()
    {
        return conn;
    }
};
DatabaseManager* DatabaseManager::instance = nullptr;
class Employee
{
protected:
    int id;
    string full_name;
    string spec;
    int exp;
    double rating;
    double salary_base;
    double salary_percent;
    string status;
    bool is_deleted;
    int maxclients;
    DatabaseManager* db;
public:
    static int rab;
    Employee(DatabaseManager* db, string full_name, string spec, int exp, double rating, double salary_base, double salary_percent, string status, int maxclients) : id(0), full_name(full_name), spec(spec), exp(exp), rating(rating), salary_base(salary_base), salary_percent(salary_percent), status(status), is_deleted(false), maxclients(maxclients), db(db)
    {}
    string getFull_name() const { return full_name; }
    int getID() const { return id; }
    void setID(int newId) { id = newId; }
    double calculateSalary(DatabaseManager* db, int month, int year) const
    {
        double totalServices = 0.0;
        string monthStr = (month < 10) ? "0" + to_string(month) : to_string(month);
        string yearStr = to_string(year);
        string datePattern = "." + monthStr + "." + yearStr; 
        db->query("SELECT SUM(price_at_booking) FROM appointments WHERE employee_id = " + to_string(id) + " AND status = 'completed' AND appointment_date LIKE '%" + datePattern + "'",
            [&totalServices](const pqxx::result& r)
            {
                if (!r.empty() && !r[0][0].is_null())
                {
                    totalServices = r[0][0].as<double>();
                }
            });
        double salary = salary_base + (totalServices * salary_percent / 100.0);
        return salary;
    }
    ~Employee()
    {}
};
class Hairdresser : public Employee
{
public:
    Hairdresser(DatabaseManager* db, string full_name, int exp, double rating, double salary_base, double salary_percent, string status) : Employee(db, full_name, "hairdresser", exp, rating, salary_base, salary_percent, status, 8)
    {}
};
class Manicurist : public Employee
{
public:
    Manicurist(DatabaseManager* db, string full_name, int exp, double rating, double salary_base, double salary_percent, string status) : Employee(db, full_name, "manicurist", exp, rating, salary_base, salary_percent, status, 6)
    {}
};
class Cosmetologist : public Employee
{
public:
    Cosmetologist(DatabaseManager* db, string full_name, int exp, double rating, double salary_base, double salary_percent, string status) : Employee(db, full_name, "cosmetologist", exp, rating, salary_base, salary_percent, status, 5)
    {}
};
class MakeupArtist : public Employee
{
public:
    MakeupArtist(DatabaseManager* db, string full_name, int exp, double rating, double salary_base, double salary_percent, string status) : Employee(db, full_name, "makeup_artist", exp, rating, salary_base, salary_percent, status, 4)
    {}
};
class EmployeeFactory
{
public:
    static Employee* createEmployee(DatabaseManager* db, string type, string full_name, int exp, double rating, double salary_base, double salary_percent, string status)
    {
        if (type == "hairdresser")
        {
            return new Hairdresser(db, full_name, exp, rating, salary_base, salary_percent, status);
        }
        if (type == "manicurist")
        {
            return new Manicurist(db, full_name, exp, rating, salary_base, salary_percent, status);
        }
        if (type == "cosmetologist")
        {
            return new Cosmetologist(db, full_name, exp, rating, salary_base, salary_percent, status);
        }
        if (type == "makeup_artist")
        {
            return new MakeupArtist(db, full_name, exp, rating, salary_base, salary_percent, status);
        }
        return nullptr;
    }
};
class Client
{
private:
    int id;
    string full_name;
    string phone;
    string first_visit_date;
    double total_spent;
    int visits_count;
    int bonus_points;
    DatabaseManager* db;
public:
    Client(string full_name, string phone, string first_visit_date, double total_spent, int visits_count, int bonus_points) : id(0), full_name(full_name), phone(phone), first_visit_date(first_visit_date), total_spent(0), visits_count(0), bonus_points(0), db(db)
    {}
    void setId(int newId) { id = newId; }
    int getBonusPoints() const { return bonus_points; }
    int getLoyaltyLevel() const
    {
        if (total_spent >= 50000) 
        {
            return 15;
        }
        if (total_spent >= 20000) 
        {
            return 10;
        }
        if (total_spent >= 5000) 
        {
            return 5;
        }
        return 0;
    }
    bool spendBonuses(int points)
    {
        if (bonus_points >= points)
        {
            bonus_points -= points;
            db->execute("UPDATE clients SET bonus_points = " + to_string(bonus_points) + " WHERE id = " + to_string(id));
            return true;
        }
        return false;
    }
};
class salon
{
public:
    DatabaseManager* db;
    string current_date;
    string getCurrent_date() const { return current_date; }
    void setCurrent_date(string newdate)
    {
        current_date = newdate;
    }
    void addEmployee(DatabaseManager* db)
    {
        int choice;
        cout << "Выберите специализацию" << endl;
        cout << "1. Парикмахер" << endl;
        cout << "2. Маникюр" << endl;
        cout << "3. Косметолог" << endl;
        cout << "4. Визажист" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;
        string type;
        switch (choice)
        {
        case 1:
        {
            type = "hairdresser";
            break;
        }
        case 2:
        {
            type = "manicurist";
            break;
        }
        case 3:
        {
            type = "cosmetologist";
            break;
        }
        case 4:
        {
            type = "makeup_artist";
            break;
        }
        }
        string full_name;
        int exp;
        double salary_base;
        double salary_percent;
        cout << "Введите ФИО (на английском): ";
        cin.ignore();
        getline(cin, full_name);
        cout << "Введите стаж: ";
        cin >> exp;
        cout << "Введите базовый оклад: ";
        cin >> salary_base;
        cout << "Введите процент от услуг: ";
        cin >> salary_percent;
        db->execute("INSERT INTO employees (full_name, specialization, experience, rating, salary_base, salary_percent, status, is_deleted) VALUES ('" + full_name + "', '" + type + "', " + to_string(exp) + ", " + to_string(0) + ", " + to_string(salary_base) + ", " + to_string(salary_percent) + ", 'work', FALSE)");
        cout << "Успешно" << endl;
    }
    void showEmployee(DatabaseManager* db)
    {
        db->query("SELECT * FROM employees", [](const pqxx::result& r)
            {
                for (auto row : r)
                {
                    cout << "--------------------" << endl;
                    cout << "ID: " << row[0].as<int>() << endl;
                    cout << "ФИО: " << row[1].as<string>() << endl;
                    cout << "Специализация: " << row[2].as<string>() << endl;
                    cout << "Стаж работы: " << row[3].as<int>() << " лет" << endl;
                    cout << "Рейтинг: " << row[4].as<double>() << endl;
                    cout << "Базовый оклад: " << row[5].as<double>() << " руб." << endl;
                    cout << "Процент от услуг: " << row[6].as<double>() << "%" << endl;
                    cout << "Статус: " << row[7].as<string>() << endl;
                    if (row[8].is_null())
                    {
                        cout << "Удалён: Нет (не указано)" << endl;
                    }
                    else {
                        cout << "Удалён: " << (row[8].as<bool>() ? "Да" : "Нет") << endl;
                    }
                    cout << "--------------------" << endl;
                }
            });
    }
    void addService(DatabaseManager* db)
    {
        string name;
        int duration;
        double price;
        string spec;
        int material_cost;
        int vbr;
        cout << "Введите название услуги (на английском): ";
        cin.ignore();
        getline(cin, name);
        cout << "Введите длительность услуги: ";
        cin >> duration;
        if (duration <= 0)
        {
            cout << "Длительность должна быть положительной!" << endl;
            return;
        }
        cout << "Введите цену услуги: ";
        cin >> price;
        if (price < 0)
        {
            cout << "Цена не может быть отрицательной!" << endl;
            return;
        }
        cout << "Выберите специализацию" << endl;
        cout << "1. Hairdresser (Парикмахер)" << endl;
        cout << "2. Manicurist (Маникюр)" << endl;
        cout << "3. Cosmetologist (Косметолог)" << endl;
        cout << "4. Makeup artist (Визажист)" << endl;
        cout << "Ваш выбор: ";
        cin >> vbr;
        switch (vbr)
        {
        case 1: 
        {
            spec = "hairdresser";
            break;
        }
        case 2: 
        {
            spec = "manicurist";
            break;
        }
        case 3: 
        {
            spec = "cosmetologist";
            break;
        }
        case 4: 
        {
            spec = "makeup_artist";
            break;
        }
        default:
            cout << "Неверный выбор специализации!" << endl;
            return;
        }
        cout << "Введите стоимость материалов для услуги: ";
        cin >> material_cost;
        if (material_cost < 0)
        {
            cout << "Стоимость материалов не может быть отрицательной!" << endl;
            return;
        }
        try
        {
            db->execute("INSERT INTO services (name, duration, price, required_specialization, material_cost) VALUES ('" + name + "', " + to_string(duration) + ", " + to_string(price) + ", '" + spec + "', " + to_string(material_cost) + ")");
            cout << "Успешно" << endl;
        }
        catch (const exception& e)
        {
            cout << "Ошибка при добавлении услуги: " << e.what() << endl;
        }
    }
    void Delete_Employee(DatabaseManager* db)
    {
        int ID;
        cout << "Введите ID сотрудника, которого хотите удалить: ";
        cin >> ID;
        bool exists = false;
        db->query("SELECT COUNT(*) FROM employees WHERE id = " + to_string(ID) + " AND is_deleted = FALSE", [&exists](const pqxx::result& r)
            {
                if (!r.empty())
                {
                    exists = (r[0][0].as<int>() > 0);
                }
            });
        if (exists)
        {
            db->execute("UPDATE employees SET status = 'yvolen', is_deleted = TRUE WHERE id = " + to_string(ID));
            cout << "Сотрудник с ID " << ID << " успешно удалён (мягко)." << endl;
        }
        else
        {
            cout << "Сотрудник с ID " << ID << " не найден." << endl;
        }
    }
    void show_rab_Employee(DatabaseManager* db)
    {
        db->query("SELECT * FROM employees WHERE is_deleted = FALSE", [](const pqxx::result& r)
            {
                for (auto row : r)
                {
                    cout << "--------------------" << endl;
                    cout << "ID: " << row[0].as<int>() << endl;
                    cout << "ФИО: " << row[1].as<string>() << endl;
                    cout << "Специализация: " << row[2].as<string>() << endl;
                    cout << "Стаж работы: " << row[3].as<int>() << " лет" << endl;
                    cout << "Рейтинг: " << row[4].as<double>() << endl;
                    cout << "Базовый оклад: " << row[5].as<double>() << " руб." << endl;
                    cout << "Процент от услуг: " << row[6].as<double>() << "%" << endl;
                    cout << "Статус: " << row[7].as<string>() << endl;
                    cout << "--------------------" << endl;
                }
            });
    }
    void Edit_Employee(DatabaseManager* db)
    {
        int ID;
        cout << "Введите ID сотрудника, которого хотите редактировать: ";
        cin >> ID;
        bool exists = false;
        db->query("SELECT COUNT(*) FROM employees WHERE id = " + to_string(ID) + " AND is_deleted = FALSE", [&exists](const pqxx::result& r)
            {
                if (!r.empty())
                {
                    exists = (r[0][0].as<int>() > 0);
                }
            });
        if (!exists)
        {
            cout << "Сотрудник с ID " << ID << " не найден." << endl;
            return;
        }
        int choice;
        cout << "Что вы хотите отредактировать?" << endl;
        cout << "1. ФИО" << endl;
        cout << "2. Стаж" << endl;
        cout << "3. Базовый оклад" << endl;
        cout << "4. Процент от услуг" << endl;
        cout << "5. Статус" << endl;
        cout << "Выбор: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            string new_name;
            cout << "Введите новое ФИО (на английском): ";
            cin.ignore();
            getline(cin, new_name);
            db->execute("UPDATE employees SET full_name = '" + new_name + "' WHERE id = " + to_string(ID));
            cout << "Успешно" << endl;
            break;
        }
        case 2:
        {
            int new_exp;
            cout << "Введите новый стаж (лет): ";
            cin >> new_exp;
            db->execute("UPDATE employees SET experience = " + to_string(new_exp) + " WHERE id = " + to_string(ID));
            cout << "Успешно" << endl;
            break;
        }
        case 3:
        {
            double new_salary;
            cout << "Введите новый базовый оклад: ";
            cin >> new_salary;
            db->execute("UPDATE employees SET salary_base = " + to_string(new_salary) + " WHERE id = " + to_string(ID));
            cout << "Успешно" << endl;
            break;
        }
        case 4:
        {
            double new_percent;
            cout << "Введите новый процент от услуг: ";
            cin >> new_percent;
            db->execute("UPDATE employees SET salary_percent = " + to_string(new_percent) + " WHERE id = " + to_string(ID));
            cout << "Успешно" << endl;
            break;
        }
        case 5:
        {
            string new_status;
            cout << "Введите новый статус (work/otdx): ";
            cin.ignore();
            getline(cin, new_status);
            db->execute("UPDATE employees SET status = '" + new_status + "' WHERE id = " + to_string(ID));
            cout << "Успешно" << endl;
            break;
        }
        default:
            cout << "Ало" << endl;
        }
    }
    void addClient(DatabaseManager* db)
    {
        string full_name;
        string phone;
        string first_visit_date;
        int vbr;
        cout << "Введите ФИО (на английском): ";
        cin.ignore();
        getline(cin, full_name);
        cout << "Введите номер телефона: ";
        getline(cin, phone);
        first_visit_date = getCurrent_date();
        db->execute("INSERT INTO clients (full_name, phone, first_visit_date, total_spent, visits_count, bonus_points) VALUES ('" + full_name + "', '" + phone + "', '" + first_visit_date + "', " + to_string(0) + ", " + to_string(0) + ", " + to_string(0) + ");");
        cout << "Успешно" << endl;
    }
    void poiskClient(DatabaseManager* db)
    {
        int vbr;
        cout << "Поиск клиента" << endl;
        cout << "1. По ID" << endl;
        cout << "2. По ФИО" << endl;
        cout << "3. По телефону" << endl;
        cout << "Ваш выбор: ";
        cin >> vbr;
        cin.ignore();
        switch (vbr)
        {
        case 1:
        {
            int id;
            cout << "Введите ID клиента: ";
            cin >> id;
            db->query("SELECT * FROM clients WHERE id = " + to_string(id), [](const pqxx::result& r)
                {
                    if (r.empty())
                    {
                        cout << "Клиент с таким ID не найден" << endl;
                    }
                    else
                    {
                        for (auto row : r)
                        {
                            cout << "--------------------" << endl;
                            cout << "ID: " << row[0].as<int>() << endl;
                            cout << "ФИО: " << row[1].as<string>() << endl;
                            cout << "Телефон: " << row[2].as<string>() << endl;
                            cout << "Дата первого визита: " << row[3].as<string>() << endl;
                            cout << "Общая сумма потраченных средств: " << row[4].as<double>() << " руб." << endl;
                            cout << "Количество визитов: " << row[5].as<int>() << endl;
                            cout << "Бонусные баллы: " << row[6].as<int>() << endl;
                            cout << "--------------------" << endl;
                        }
                    }
                });
            break;
        }
        case 2:
        {
            string name;
            cout << "Введите ФИО: ";
            getline(cin, name);
            db->query("SELECT * FROM clients WHERE full_name = '" + name + "'", [](const pqxx::result& r)
                {
                    if (r.empty())
                    {
                        cout << "Клиенты с таким ФИО не найдены" << endl;
                    }
                    else
                    {
                        for (auto row : r)
                        {
                            cout << "--------------------" << endl;
                            cout << "ID: " << row[0].as<int>() << endl;
                            cout << "ФИО: " << row[1].as<string>() << endl;
                            cout << "Телефон: " << row[2].as<string>() << endl;
                            cout << "Дата первого визита: " << row[3].as<string>() << endl;
                            cout << "Общая сумма потраченных средств: " << row[4].as<double>() << " руб." << endl;
                            cout << "Количество визитов: " << row[5].as<int>() << endl;
                            cout << "Бонусные баллы: " << row[6].as<int>() << endl;
                            cout << "--------------------" << endl;
                        }
                    }
                });
            break;
        }
        case 3:
        {
            string phone;
            cout << "Введите телефон: ";
            getline(cin, phone);
            db->query("SELECT * FROM clients WHERE phone = '" + phone + "'", [](const pqxx::result& r)
                {
                    if (r.empty())
                    {
                        cout << "Клиент с таким телефоном не найден" << endl;
                    }
                    else
                    {
                        for (auto row : r)
                        {
                            cout << "--------------------" << endl;
                            cout << "ID: " << row[0].as<int>() << endl;
                            cout << "ФИО: " << row[1].as<string>() << endl;
                            cout << "Телефон: " << row[2].as<string>() << endl;
                            cout << "Дата первого визита: " << row[3].as<string>() << endl;
                            cout << "Общая сумма потраченных средств: " << row[4].as<double>() << " руб." << endl;
                            cout << "Количество визитов: " << row[5].as<int>() << endl;
                            cout << "Бонусные баллы: " << row[6].as<int>() << endl;
                            cout << "--------------------" << endl;
                        }
                    }
                });
            break;
        }
        default:
            cout << "Ало" << endl;
        }
    }
    void showServices(DatabaseManager* db)
    {
        db->query("SELECT * FROM services", [](const pqxx::result& r)
            {
                for (auto row : r)
                {
                    cout << "--------------------" << endl;
                    cout << "ID: " << row[0].as<int>() << endl;
                    cout << "Название: " << row[1].as<string>() << endl;
                    cout << "Длительность: " << row[2].as<int>() << " мин" << endl;
                    cout << "Цена: " << row[3].as<int>() << " руб." << endl;
                    cout << "Специализация: " << row[4].as<string>() << endl;
                    cout << "Материалы: " << row[5].as<int>() << " руб." << endl;
                    cout << "--------------------" << endl;
                }
            });
    }
    void showServices_sp(DatabaseManager* db)
    {
        int vbr;
        cout << "Выберите специализацию" << endl;
        cout << "1. Hairdresser" << endl;
        cout << "2. Manicurist" << endl;
        cout << "3. Cosmetologist" << endl;
        cout << "4. Makeup artist" << endl;
        cout << "Ваш выбор: ";
        cin >> vbr;
        string spec;
        switch (vbr)
        {
        case 1:
            spec = "hairdresser";
            break;
        case 2:
            spec = "manicurist";
            break;
        case 3:
            spec = "cosmetologist";
            break;
        case 4:
            spec = "makeup_artist";
            break;
        }
        db->query("SELECT * FROM services WHERE required_specialization = '" + spec + "'", [&spec](const pqxx::result& r)
            {
                if (r.empty())
                {
                    cout << "Услуг для специализации '" << spec << "' не найдено" << endl;
                }
                else
                {
                    for (auto row : r)
                    {
                        cout << "--------------------" << endl;
                        cout << "ID: " << row[0].as<int>() << endl;
                        cout << "Название: " << row[1].as<string>() << endl;
                        cout << "Длительность: " << row[2].as<int>() << " мин" << endl;
                        cout << "Цена: " << row[3].as<int>() << " руб." << endl;
                        cout << "Специализация: " << row[4].as<string>() << endl;
                        cout << "Материалы: " << row[5].as<int>() << " руб." << endl;
                        cout << "--------------------" << endl;
                    }
                }
            });
    }
    void addAppointment(DatabaseManager* db)
    {
        int clientId, empId, serviceId;
        string date, time;
        cout << "Введите ID клиента: ";
        cin >> clientId;
        cout << "Введите ID сотрудника: ";
        cin >> empId;
        cout << "Введите ID услуги: ";
        cin >> serviceId;
        cout << "Введите дату (DD.MM.YYYY): ";
        cin.ignore();
        getline(cin, date);
        int day = stoi(date.substr(0, 2));
        int month = stoi(date.substr(3, 2));
        int year = stoi(date.substr(6, 4));
        int week = getDayOfWeek(day, month, year);
        if (week == 7)
        {
            throw DateInPastException("В воскресенье нельзя");
        }
        string currentDate = current_date;
        if (date <= currentDate) 
        {
            throw DateInPastException("Дата должна быть не раньше следующего дня (текущая: " + currentDate + ")");
        }
        cout << "Введите время (HH:MM): ";
        getline(cin, time);
        int hour = stoi(time.substr(0, 2));
        if ((hour < 10 || hour >= 20) || (week == 6 && (hour < 10 || hour >= 18)))
        {
            cout << "Нерабочее время (салон работает с 10:00 до 20:00), а в субботу до 18:00" << endl;
            return;
        }
        Client* client = nullptr;
        bool clientExists = false;
        db->query("SELECT COUNT(*) FROM clients WHERE id = " + to_string(clientId), [&clientExists](const pqxx::result& r) 
            {
                if (!r.empty()) 
                {
                    clientExists = (r[0][0].as<int>() > 0);
                }
            });
        if (!clientExists) 
        {
            throw NotFoundException("Клиент с ID " + to_string(clientId) + " не найден");
        }
        db->query("SELECT * FROM clients WHERE id = " + to_string(clientId), [&client, clientId](const pqxx::result& r)
            {
                if (!r.empty())
                {
                    auto row = r[0];
                    client = new Client(row[1].as<string>(), row[2].as<string>(), row[3].as<string>(), row[4].as<double>(), row[5].as<int>(), row[6].as<int>());
                    client->setId(clientId);
                }
            });
        bool empExists = false;
        db->query("SELECT COUNT(*) FROM employees WHERE id = " + to_string(empId) + " AND is_deleted <> TRUE", [&empExists](const pqxx::result& r)
            {
                if (!r.empty())
                {
                    empExists = (r[0][0].as<int>() > 0);
                }
            });
        if (!empExists) 
        {
            throw NotFoundException("Сотрудник с ID " + to_string(empId) + " не найден");
        }
        bool serviceExists = false;
        db->query("SELECT COUNT(*) FROM services WHERE id = " + to_string(serviceId), [&serviceExists](const pqxx::result& r)
            {
                if (!r.empty())
                {
                    serviceExists = (r[0][0].as<int>() > 0);
                }
            });
        if (!serviceExists) 
        {
            throw NotFoundException("Услуга с ID " + to_string(serviceId) + " не найдена");
        }
        int duration = 0;
        double price = 0;
        db->query("SELECT duration, price FROM services WHERE id = " + to_string(serviceId), [&duration, &price](const pqxx::result& r)
            {
                if (!r.empty())
                {
                    duration = r[0][0].as<int>();
                    price = r[0][1].as<double>();
                }
            });
        bool hasConflict = false;
        db->query( "SELECT appointment_time, s.duration FROM appointments a JOIN services s ON a.service_id = s.id WHERE a.employee_id = " + to_string(empId) + " AND a.appointment_date = '" + date + "'", [&hasConflict, time, duration](const pqxx::result& r)
            {
                int newStart = stoi(time.substr(0, 2)) * 60 + stoi(time.substr(3, 2));
                int newEnd = newStart + duration;
                for (auto row : r)
                {
                    string existingTime = row[0].as<string>();
                    int existingDuration = row[1].as<int>();
                    int existingStart = stoi(existingTime.substr(0, 2)) * 60 + stoi(existingTime.substr(3, 2));
                    int existingEnd = existingStart + existingDuration;
                    if (!(newEnd <= existingStart || newStart >= existingEnd))
                    {
                        hasConflict = true;
                        break;
                    }
                }
            });
        if (hasConflict) 
        {
            cout << "Мастер занят в это время" << endl;
            return;
        }
        bool clientDouble = false;
        db->query("SELECT COUNT(*) FROM appointments WHERE client_id = " + to_string(clientId) + " AND appointment_date = '" + date + "' AND appointment_time = '" + time + "'", [&clientDouble](const pqxx::result& r) 
            {
                if (!r.empty()) 
                {
                    clientDouble = (r[0][0].as<int>() > 0);
                }
            });
        if (clientDouble) 
        {
            cout << "Клиент уже записан на это время" << endl;
            return;
        }
        int loyalty = client->getLoyaltyLevel();
        double discount = price * loyalty / 100;
        double finalPrice = price - discount;
        cout << "Скидка по лояльности: " << discount << " руб." << endl;
        if (client->getBonusPoints() > 0)
        {
            int bonusToUse = client->getBonusPoints();
            if (client->spendBonuses(bonusToUse))
            {
                finalPrice -= bonusToUse;
                cout << "Автоматически списано " << bonusToUse << " бонусных баллов" << endl;
            }
        }
        cout << "Итоговая цена: " << finalPrice << " руб." << endl;
        db->execute("INSERT INTO appointments (client_id, employee_id, service_id, appointment_date, appointment_time, status, price_at_booking) VALUES (" + to_string(clientId) + ", " + to_string(empId) + ", " + to_string(serviceId) + ", '" + date + "', '" + time + "', 'booked', " + to_string(finalPrice) + ");");
        if (client) 
        {
            delete client;
        }
    }
    void showAppointments(DatabaseManager* db)
    {
        string date;
        cout << "Введите дату (DD.MM.YYYY): ";
        cin.ignore();
        getline(cin, date);
        db->query("SELECT * FROM appointments WHERE appointment_date = '" + date + "'", [](const pqxx::result& r) 
            {
            if (r.empty()) 
            {
                cout << "На эту дату записей нет" << endl;
            }
            else 
            {
                for (auto row : r) 
                {
                    cout << "ID записи: " << row[0].as<int>() << endl;
                    cout << "Клиент: " << row[1].as<int>() << endl;
                    cout << "Сотрудник: " << row[2].as<int>() << endl;
                    cout << "Услуга: " << row[3].as<int>() << endl;
                    cout << "Дата: " << row[4].as<string>() << endl;
                    cout << "Время: " << row[5].as<string>() << endl;
                    cout << "Статус: " << row[6].as<string>() << endl;
                    cout << "Цена: " << row[7].as<double>() << " руб." << endl;
                    cout << "--------------------" << endl;
                }
            }
            });
    }
    void showClientHistory(DatabaseManager* db)
    {
        int clientId;
        cout << "Введите ID клиента: ";
        cin >> clientId;
        db->query("SELECT a.appointment_date, a.appointment_time, s.name, a.price_at_booking FROM appointments a JOIN services s ON a.service_id = s.id WHERE a.client_id = " + to_string(clientId) + " AND a.status = 'completed' ORDER BY a.appointment_date DESC", [](const pqxx::result& r)
            {
                if (r.empty())
                {
                    cout << "У клиента нет выполненных записей" << endl;
                }
                else
                {
                    for (auto row : r)
                    {
                        cout << "Дата: " << row[0].as<string>() << endl;
                        cout << "Время: " << row[1].as<string>() << endl;
                        cout << "Услуга: " << row[2].as<string>() << endl;
                        cout << "Сумма: " << row[3].as<double>() << " руб." << endl;
                    }
                }
            });
    }
    void cancelAppointment(DatabaseManager* db)
    {
        int appointmentId;
        cout << "Введите ID записи, которую хотите отменить: ";
        cin >> appointmentId;
        bool exists = false;
        db->query("SELECT COUNT(*) FROM appointments WHERE id = " + to_string(appointmentId),
            [&exists](const pqxx::result& r) 
            {
                if (!r.empty()) 
                {
                    exists = (r[0][0].as<int>() > 0);
                }
            });
        if (!exists) 
        {
            cout << "Запись с ID " << appointmentId << " не найдена" << endl;
            return;
        }
        string status;
        string date;
        db->query("SELECT status, appointment_date FROM appointments WHERE id = " + to_string(appointmentId), [&status, &date](const pqxx::result& r) 
            {
                if (!r.empty()) 
                {
                    status = r[0][0].as<string>();
                    date = r[0][1].as<string>();
                }
            });
        if (status == "completed") 
        {
            throw ForbiddenActionException("Нельзя отменить уже выполненную запись");
        }
        string currentDate = current_date;
        if (date <= currentDate) 
        {
            cout << "Нельзя отменить запись на прошедшую дату" << endl;
            return;
        }
        db->execute("UPDATE appointments SET status = 'cancelled' WHERE id = " + to_string(appointmentId));
        cout << "Успешно" << endl;
    }
    int getDayOfWeek(int day, int month, int year) 
    {
        if (month < 3) 
        {
            month += 12;
            year--;
        }
        int k = year % 100;
        int j = year / 100;
        int h = (day + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
        return (h + 5) % 7 + 1;
    }
    void showAppointmentsThisWeek(DatabaseManager* db)
    {
        string currentDate = current_date;
        int day = stoi(currentDate.substr(0, 2));
        int month = stoi(currentDate.substr(3, 2));
        int year = stoi(currentDate.substr(6, 4));
        int week_day = getDayOfWeek(day, month, year);
        int kolvo = 7 - week_day;
        string endDate = currentDate;
        for (int i = 0; i <= kolvo; i++)
        {
            cout << week_day << endl;
            db->query("SELECT * FROM appointments WHERE appointment_date = '" + endDate + "'", [](const pqxx::result& r)
                {
                    if (r.empty())
                    {
                        ///пупупу
                    }
                    else
                    {
                       
                        for (auto row : r)
                        {
                            cout << "--------------------" << endl;
                            cout << "ID записи: " << row[0].as<int>() << endl;
                            cout << "Клиент: " << row[1].as<int>() << endl;
                            cout << "Сотрудник: " << row[2].as<int>() << endl;
                            cout << "Услуга: " << row[3].as<int>() << endl;
                            cout << "Дата: " << row[4].as<string>() << endl;
                            cout << "Время: " << row[5].as<string>() << endl;
                            cout << "Статус: " << row[6].as<string>() << endl;
                            cout << "Цена: " << row[7].as<double>() << " руб." << endl;
                            cout << "--------------------" << endl;
                        }
                    }
                });
            day ++;
            if (day > 31)
            {
                day -= 31;
                month++;
                if (month > 12)
                {
                    month = 1;
                    year++;
                }
            }
            string dayStr = (day < 10) ? "0" + to_string(day) : to_string(day);
            string monthStr = (month < 10) ? "0" + to_string(month) : to_string(month);
            string yearStr = to_string(year);
            endDate = dayStr + "." + monthStr + "." + yearStr;
            week_day++;
        }
        
    }
};
salon s;
class SalonSimulator
{
private:
    double cash_balance;    
    double total_revenue;   
    double total_expenses;
public:
    SalonSimulator() : cash_balance(50000), total_revenue(0), total_expenses(0) {}
    void loadFromDB(DatabaseManager* db)
    {
        db->query("SELECT salon_date, cash_balance, total_revenue, total_expenses FROM salon_state ORDER BY id DESC LIMIT 1", [this](const pqxx::result& r)
            {
                if (!r.empty())
                {
                    s.current_date = r[0][0].as<string>();
                    cash_balance = r[0][1].as<double>();
                    total_revenue = r[0][2].as<double>();
                    total_expenses = r[0][3].as<double>();
                }
            });
    }
    void saveToDB(DatabaseManager* db)
    {
        bool recordExists = false;
        db->query("SELECT COUNT(*) FROM salon_state WHERE id = 1",
            [&recordExists](const pqxx::result& r)
            {
                if (!r.empty() && !r[0][0].is_null())
                {
                    recordExists = (r[0][0].as<int>() > 0);
                }
            });
        if (recordExists)
        {
            db->execute("UPDATE salon_state SET salon_date = '" + s.current_date + "', cash_balance = " + to_string(cash_balance) + ", total_revenue = " + to_string(total_revenue) + ", total_expenses = " + to_string(total_expenses) + " WHERE id = 1");
        }
        else
        {
            db->execute("INSERT INTO salon_state (id, salon_date, cash_balance, total_revenue, total_expenses) VALUES (1, '" + s.current_date + "', " + to_string(cash_balance) + ", " + to_string(total_revenue) + ", " + to_string(total_expenses) + ")");
        }
    }
    void nextDay(DatabaseManager* db)
    {
        string currentDate = s.current_date;
        vector<int> ids;
        vector<double> priceList;
        db->query("SELECT id, price_at_booking FROM appointments WHERE appointment_date = '" + currentDate + "' AND status = 'booked'",
            [&ids, &priceList](const pqxx::result& r)
            {
                for (auto row : r)
                {
                    ids.push_back(row[0].as<int>());
                    priceList.push_back(row[1].as<double>());
                }
            });

        if (ids.empty())
        {
            cout << "На сегодня записей нет" << endl;
        }
        else
        {
            for (size_t i = 0; i < ids.size(); i++)
            {
                int appId = ids[i];
                double price = priceList[i];
                cash_balance += price;
                total_revenue += price;
                int clientId = 0;
                int empId = 0;
                db->query("SELECT client_id, employee_id FROM appointments WHERE id = " + to_string(appId),
                    [&clientId, &empId](const pqxx::result& r)
                    {
                        if (!r.empty())
                        {
                            clientId = r[0][0].as<int>();
                            empId = r[0][1].as<int>();
                        }
                    });
                db->execute("UPDATE clients SET visits_count = visits_count + 1, total_spent = total_spent + " + to_string(price) + ", bonus_points = bonus_points + " + to_string((int)(price * 0.05)) + " WHERE id = " + to_string(clientId));
                cout << "Оцените сотрудника с ID " << empId << " за выполненную услугу (1-5): ";
                int newRating;
                cin >> newRating;
                if (newRating < 1 || newRating > 5)
                {
                    throw InvalidInputException("Оценка должна быть от 1 до 5");
                }
                db->execute("UPDATE employees SET rating = (rating + " + to_string(newRating) + ") / 2.0 WHERE id = " + to_string(empId));
                db->execute("UPDATE appointments SET status = 'completed' WHERE id = " + to_string(appId));
            }
        }
        int currentDay = stoi(currentDate.substr(0, 2));
        if (currentDay == 31)
        {
            endOfMonth(db);
        }
        int day = stoi(currentDate.substr(0, 2));
        int month = stoi(currentDate.substr(3, 2));
        int year = stoi(currentDate.substr(6, 4));
        day++;
        if (day > 31)
        {
            day = 1;
            month++;
            if (month > 12)
            {
                month = 1;
                year++;
            }
        }
        string dayStr = (day < 10) ? "0" + to_string(day) : to_string(day);
        string monthStr = (month < 10) ? "0" + to_string(month) : to_string(month);
        string yearStr = to_string(year);
        string newDate = dayStr + "." + monthStr + "." + yearStr;
        s.current_date = newDate;
        cout << "Новый баланс кассы: " << cash_balance << " руб." << endl;
        saveToDB(db);
    }
    void endOfMonth(DatabaseManager* db)
    {
        int month = stoi(s.current_date.substr(3, 2));
        int year = stoi(s.current_date.substr(6, 4));
        cout << "Конец " << month << endl;
        vector<tuple<int, string, string, int, double, double, double, string>> employees;
        db->query("SELECT * FROM employees WHERE is_deleted = FALSE", [&employees](const pqxx::result& r)
            {
                for (auto row : r)
                {
                    employees.push_back(make_tuple( row[0].as<int>(), row[1].as<string>(), row[2].as<string>(), row[3].as<int>(), row[4].as<double>(), row[5].as<double>(), row[6].as<double>(), row[7].as<string>()));
                }
            });
        for (const auto& emp_data : employees)
        {
            int id = get<0>(emp_data);
            string full_name = get<1>(emp_data);
            string spec = get<2>(emp_data);
            int exp = get<3>(emp_data);
            double rating = get<4>(emp_data);
            double salary_base = get<5>(emp_data);
            double salary_percent = get<6>(emp_data);
            string status = get<7>(emp_data);
            if (status != "уволен")
            {
                Employee* emp = EmployeeFactory::createEmployee(db, spec, full_name, exp, rating, salary_base, salary_percent, status);
                if (emp)
                {
                    emp->setID(id);
                    double salary = emp->calculateSalary(db, month, year);
                    db->execute("INSERT INTO salary_log (employee_id, month_year, total_services_sum, salary_calculated, paid_status) VALUES (" + to_string(emp->getID()) + ", '" + to_string(year) + "-" + to_string(month) + "-01', " + to_string(salary) + ", " + to_string(salary) + ", false)");
                    cash_balance -= salary;
                    total_expenses += salary;
                    cout << "Сотрудник " << emp->getFull_name() << " получил зарплату: " << salary << " руб." << endl;
                    delete emp;
                }
            }
        }
        double totalMaterials = 0;
        string monthStr = (month < 10) ? "0" + to_string(month) : to_string(month);
        string datePattern = "." + monthStr + "." + to_string(year);
        db->query("SELECT SUM(material_cost) FROM services s JOIN appointments a ON s.id = a.service_id WHERE a.status = 'completed' AND a.appointment_date LIKE '%" + datePattern + "'",
            [&totalMaterials](const pqxx::result& r) {
                if (!r.empty() && !r[0][0].is_null())
                {
                    totalMaterials = r[0][0].as<double>();
                }
            });
        cash_balance -= totalMaterials;
        total_expenses += totalMaterials;
        cash_balance -= 5000;
        total_expenses += 5000;
        cout << "Списана аренда: 5000 руб." << endl;
        cout << "Месяц завершён" << endl;
    }
    void nextMonth(DatabaseManager* db)
    {
        int currentMonth = stoi(s.current_date.substr(3, 2));
        int currentYear = stoi(s.current_date.substr(6, 4));
        int lastDay = 31;
        while (stoi(s.current_date.substr(0, 2)) <= lastDay)
        {
            nextDay(db);
            if (stoi(s.current_date.substr(0, 2)) == 1 && stoi(s.current_date.substr(3, 2)) != currentMonth)
            {
                break;
            }
        }
        cout << "Успешно" << endl;
    }
    void showFinances()
    {
        cout << "Финансы салона" << endl;
        cout << "Выручка: " << total_revenue << " руб." << endl;
        cout << "Расходы: " << total_expenses << " руб." << endl;
        cout << "Прибыль: " << (total_revenue - total_expenses) << " руб." << endl;
        cout << "Баланс кассы: " << cash_balance << " руб." << endl;
    }
};
SalonSimulator sim;
void menu(DatabaseManager* db)
{
    int vbr;
    cout << "Что-то создать" << endl;
    cout << "1. Создать сотрудника" << endl;
    cout << "2. Создать клиента" << endl;
    cout << "3. Создать услугу" << endl;
    cout << "4. Создать запись" << endl;
    cout << endl;
    cout << "Что-то посмотреть" << endl;
    cout << "5. Посмотреть сотрудников" << endl;
    cout << "6. Посмотреть работающих сотрудников" << endl;
    cout << "7. Найти клиента" << endl;
    cout << "8. История посещений клиента" << endl;
    cout << "9. Посмотреть услуги" << endl;
    cout << "10. Посмотреть услуги конкретной специализации" << endl;
    cout << "11. Посмотреть записи на конкретный день" << endl;
    cout << "12. Посмотреть записи на неделю" << endl;
    cout << "13. Показать финансы" << endl;
    cout << endl;
    cout << "Поуправлять" << endl;
    cout << "14. Уволить сотрудника" << endl;
    cout << "15. Редактировать сотрудника" << endl;
    cout << "16. Отменить запись" << endl;
    cout << "17. Перейти на следующий день" << endl;
    cout << "18. Перейти на следующий месяц" << endl;
    cout << "0. Выход (НАЖАТЬ ОБЯЗАТЕЛЬНО)" << endl;
    cout << "Выбор: ";
    cin >> vbr;
    switch (vbr)
    {
    case 1:
    {
        s.addEmployee(db);
        menu(db);
    }
    case 2:
    {
        s.addClient(db);
        menu(db);
    }
    case 3:
    {
        s.addService(db);
        menu(db);
    }
    case 4:
    {
        s.addAppointment(db);
        menu(db);
    }
    case 5:
    {
        s.showEmployee(db);
        menu(db);
    }
    case 6:
    {
        s.show_rab_Employee(db);
        menu(db);
    }
    case 7:
    {
        s.poiskClient(db);
        menu(db);
    }
    case 8:
    {
        s.showClientHistory(db);
        menu(db);
    }
    case 9:
    {
        s.showServices(db);
        menu(db);
    }
    case 10:
    {
        s.showServices_sp(db);
        menu(db);
    }
    case 11:
    {
        s.showAppointments(db);
        menu(db);
    }
    case 12:
    {
        s.showAppointmentsThisWeek(db);
        menu(db);
        break;
    }
    case 13:
    {
        sim.showFinances();
        menu(db);
    }
    case 14:
    {
        s.Delete_Employee(db);
        menu(db);
    }
    case 15:
    {
        s.Edit_Employee(db);
        menu(db);
    }
    case 16:
    {
        s.cancelAppointment(db);
        menu(db);
    }
    
    case 17: 
    {
        sim.nextDay(db);
        menu(db);
    }
    case 18:
    {
        sim.nextMonth(db);
        menu(db);
    }
    case 0:
    {
        sim.saveToDB(db);
        exit(0);
    }
    default:
    {
        cout << "э" << endl;
        menu(db);
    }
    }
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    try
    {
        DatabaseManager* db = DatabaseManager::getInstance();
        s.current_date = "0";
        sim.loadFromDB(db);
        if (s.current_date == "0")
        {
            string date;
            cout << "Задайте сегодняшнюю дату (DD.MM.YYYY): ";
            getline(cin, date);
            s.setCurrent_date(date);
        }
        cout << s.current_date << endl;
        menu(db);
    }
    catch (const ForbiddenActionException& e)
    {
        cout << "Ошибка: " << e.what() << endl;
    }
    catch (const DateInPastException& e)
    {
        cout << "Ошибка: " << e.what() << endl;
    }
    catch (const NotFoundException& e)
    {
        cout << "Ошибка: " << e.what() << endl;
    }
    catch (const InvalidInputException& e)
    {
        cout << "Ошибка: " << e.what() << endl;
    }
    catch (const DatabaseException& e)
    {
        cout << "Ошибка базы данных: " << e.what() << endl;
    }
    catch (const exception& e)
    {
        cout << "Неизвестная ошибка: " << e.what() << endl;
    }
    return 0;
}