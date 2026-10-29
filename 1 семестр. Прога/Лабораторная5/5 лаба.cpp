#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath> 
#include <ctime> 
#include <algorithm>
#include <string>
#include <cctype>
#define  _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <Windows.h>
#include <locale>
#include <unordered_map>
#include <map>
#include <fstream>
#include <iomanip>
#include <random>
#include <sstream> 
void glavnoemenu();
void menu_1();
void add_zap();
void menu_2();
void dobav_zadacha();
char toLower(char s);
using namespace std;
/// начало 1 задача
struct Date
{
	int day;
	int month;
	int year;
};
struct Nastr
{
	Date date;
	int moodScore;      
	string comment;
};
vector <Nastr> Diary;
void add_zap()
{
	Nastr N;
	cout << "Введите дату (DD MM YYYY): ";
	cin >> N.date.day >> N.date.month >> N.date.year;
	cout << "Введите оценку настроения: ";
	cin >> N.moodScore;
	cout << "Напишите комментарий: ";
	cin.ignore();
	getline(cin, N.comment);
	if (N.date.day >= 1 && N.date.day <= 31 && N.date.month >= 1 && N.date.month <= 12 && N.date.year >= 0 && N.moodScore >= 1 && N.moodScore <= 5)
	{
		Diary.push_back(N);
	}
	else
	{
		cout << "Ошибка, запись не добавлена. Проверьте правильность введенной даты или настроения" << endl;
	}
}
void prosmotr_diary()
{
	for (int i = 0; i < size(Diary); i++)
	{
		cout << "Дата: " << Diary[i].date.day << "." << Diary[i].date.month << "." << Diary[i].date.year << endl;
		cout << "Оценка настроения: " << Diary[i].moodScore << endl;
		cout << "Комментарий: " << Diary[i].comment << endl;
	}
}
void zap_v_file() 
{
	ofstream file("Задача_5_1.CSV");

	if (!file.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		return;
	}
	file << "Дата; Оценка; Комментарий" << endl;
	for (const auto& N : Diary) 
	{
		file << N.date.day << "." << N.date.month << "." << N.date.year << ";" << N.moodScore << ";" << "\"" << N.comment << "\"" << endl;
	}
	file.close();
	cout << "Данные сохранены в Задача_5_1.CSV" << endl;
}
void loadFromCSV() 
{
	Diary.clear();
    ifstream file("Задача_5_1.CSV");
    if (!file.is_open()) 
	{
        cout << "Файл Задача_5_1.CSV не найден" << endl;
        return;
    }
    string line;
	string nastroen;
    int count = 0;
    getline(file, line);
    while (getline(file, line)) 
	{
		if (line.empty())
		{
			continue;
		}
        stringstream ss(line);
        string data_str;
        Nastr N;
        int fieldCount = 0;
		if (!getline(ss, data_str, ';'))
		{
			continue;
		}
        size_t dotPos = data_str.find('.');
        if (dotPos != string::npos) 
		{
			size_t dotPos2 = data_str.find('.', dotPos + 1);
            if (dotPos2 != string::npos) 
			{
				N.date.day = stoi(data_str.substr(0, dotPos));
                N.date.month = stoi(data_str.substr(dotPos + 1, dotPos2 - dotPos - 1));
                N.date.year = stoi(data_str.substr(dotPos2 + 1));
            }
			if (!getline(ss, nastroen, ';'))
			{
				continue;
			}
            N.moodScore = stoi(nastroen);
            getline(ss, N.comment);
            Diary.push_back(N);
			count++;
        }
      
    }
    file.close();
    if (count > 0) 
	{
        cout << "Успешно загружено " << count << " записей." << endl;
    }
    else {
        cout << "Записи не загружены" << endl;
    }
}
void prosmotr_za_day()
{
	Date date;
	cout << "Введите дату: ";
	cin >> date.day >> date.month >> date.year;
	for (int i = 0; i < size(Diary); i++)
	{
		if (date.day == Diary[i].date.day && date.month == Diary[i].date.month && date.year == Diary[i].date.year)
		{
			cout << "Дата: " << Diary[i].date.day << "." << Diary[i].date.month << "." << Diary[i].date.year << endl;
			cout << "Оценка настроения: " << Diary[i].moodScore << endl;
			cout << "Комментарий: " << Diary[i].comment << endl;
		}
	}
}
void sr_nastr()
{
	Date date;
	double summ = 0;
	double sred_ball = 0;
	int count = 0;
	cout << "Введите первый день недели: ";
	cin >> date.day >> date.month >> date.year;
	Date new_date = date;
	for (int i = 0; i < 7; i++)
	{
		if (i != 0)
		{
			new_date.day++;
		}
		if (new_date.day > 31)
		{
			new_date.month++;
			new_date.day = 1;
		}
		if (new_date.month > 12)
		{
			new_date.year++;
			new_date.month = 1;
		}
		for (int j = 0; j < size(Diary); j++)
		{
			if (new_date.day == Diary[j].date.day && new_date.month == Diary[j].date.month && new_date.year == Diary[j].date.year)
			{
				summ += Diary[j].moodScore;
				count++;
			}
		}
	}
	sred_ball = summ / count;
	cout << "Средний балл: " << sred_ball << endl;
}
void chastoe_nastr()
{
	int max_pair_second = 0;
	int max_pair_first = 0;
	map < int, int > chastota;
	for (int i = 0; i < Diary.size(); i++)
	{
		chastota[Diary[i].moodScore] = chastota[Diary[i].moodScore] + 1;
	}
	for (auto& pair : chastota)
	{
		if (pair.second > max_pair_second)
		{
			max_pair_second = pair.second;
			max_pair_first = pair.first;
		}
		cout << pair.first << ": " << pair.second << endl;
	}
	cout << "Самое частое настроение: " << max_pair_first << endl;
}
void menu_1()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "1. Добавление новой записи настроения (дата, оценка от 1 до 5, комментарий)" << endl;
	cout << "2. Просмотр дневника" << endl;
	cout << "3. Сохранить дневник в файл" << endl;
	cout << "4. Прочитать дневник из файла" << endl;
	cout << "5. Просмотр всех записей за выбранный день" << endl;
	cout << "6. Расчет среднего настроения за неделю" << endl;
	cout << "7. Определение самого частого настроения" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		add_zap();
		menu_1();
	case 2:
		prosmotr_diary();
		menu_1();
	case 3:
		zap_v_file();
		menu_1();
	case 4:
		loadFromCSV();
		menu_1();
	case 5:
		prosmotr_za_day();
		menu_1();
	case 6:
		sr_nastr();
		menu_1();
	case 7:
		chastoe_nastr();
		menu_1();
	case 0:
		zap_v_file();
		glavnoemenu();
	default:
		cout << "Такого задания нет!" << endl;
		menu_1();
	}
}
/// конец 1 задача
/// начало 2 задача
struct Zadacha
{
	string nazvanie;
	int prioritet;
	Date date_vp;
	bool status;
};
vector <Zadacha> Spisok_del;
void dobav_zadacha()
{
	Zadacha Z;
	string nazvanie;
	int prioritet;
	bool status;
	cout << "Введите дату выполнения (DD MM YYYY): ";
	cin >> Z.date_vp.day >> Z.date_vp.month >> Z.date_vp.year;
	cin.ignore();
	cout << "Введите название задачи: ";
	getline(cin, Z.nazvanie);
	cout << "Введите приоритет (5 - самый высокий, 1 - самый низкий): ";
	cin >> Z.prioritet;
	Z.status = false;
	if (Z.date_vp.day >= 1 && Z.date_vp.day <= 31 && Z.date_vp.month >= 1 && Z.date_vp.month <= 12 && Z.date_vp.year >= 0 && Z.prioritet >= 1 && Z.prioritet <= 5)
	{
		Spisok_del.push_back(Z);
		cout << "Задача добавлена" << endl;
	}
	else
	{
		cout << "Ошибка, запись не добавлена. Проверьте правильность введенной даты или приоритета" << endl;
	}
}
void prosmotr_spisok_del()
{
	for (int i = 0; i < size(Spisok_del); i++)
	{
		cout << "Название задачи: " << Spisok_del[i].nazvanie << endl;
		cout << "Приоритет: " << Spisok_del[i].prioritet << endl;
		cout << "Срок выполнения: " << Spisok_del[i].date_vp.day << "." << Spisok_del[i].date_vp.month << "." << Spisok_del[i].date_vp.year << endl;
		cout << "Статус: " << Spisok_del[i].status << endl;
	}
}
void vp_zadacha()
{
	cin.ignore();
	string nazvanie;
	cout << "Введите название выполненной задачи: ";
	getline(cin, nazvanie);
	for (int i = 0; i < size(Spisok_del); i++)
	{
		if (Spisok_del[i].nazvanie == nazvanie)
		{
			if (Spisok_del[i].status == true)
			{
				cout << "Задача уже выполнена" << endl;
			}
			else
			{
				Spisok_del[i].status = true;
				cout << "Задача " << nazvanie << " отмечена как выполненная" << endl;
			}
		}
	}
}
void del_zadacha()
{
	cin.ignore();
	string nazvanie;
	cout << "Введите название задачи, которую хотите удалить: ";
	getline(cin, nazvanie);
	bool found = false;
	for (auto i = Spisok_del.begin(); i != Spisok_del.end(); ++i)
	{
		if (i->nazvanie == nazvanie)
		{
			Spisok_del.erase(i);
			cout << "Задача " << nazvanie << " удалена" << endl;
			found = true;
			break; 
		}
	}
	if (!found)
	{
		cout << "Задача " << nazvanie << " не найдена." << endl;
	}
}
void zadachi_na_segodnu_i_prosroch()
{
	cin.ignore();
	Zadacha Z;
	cout << "Введите сегодняшнюю дату (DD MM YYYY): ";
	cin >> Z.date_vp.day >> Z.date_vp.month >> Z.date_vp.year;
	cout << "Задачи на сегодня:" << endl;
	for (int i = 0; i < size(Spisok_del); i++)
	{
		if (Spisok_del[i].date_vp.day == Z.date_vp.day && Spisok_del[i].date_vp.month == Z.date_vp.month && Spisok_del[i].date_vp.year == Z.date_vp.year)
		{
			cout << "Название задачи: " << Spisok_del[i].nazvanie << endl;
			cout << "Приоритет: " << Spisok_del[i].prioritet << endl;
			cout << "Статус: " << Spisok_del[i].status << endl;
		}
	}
	cout << "Просроченные задачи:" << endl;
	for (int i = 0; i < size(Spisok_del); i++)
	{
		bool flag = false;
		if (Spisok_del[i].date_vp.year < Z.date_vp.year)
		{
			flag = true;
		}
		else if (Spisok_del[i].date_vp.year > Z.date_vp.year)
		{
			flag = false;
		}
		else if (Spisok_del[i].date_vp.month < Z.date_vp.month)
		{
			flag = true;
		}
		else if (Spisok_del[i].date_vp.month > Z.date_vp.month)
		{
			flag = false;
		}
		else if (Spisok_del[i].date_vp.day < Z.date_vp.day)
		{
			flag = true;
		}
		else if (Spisok_del[i].date_vp.day > Z.date_vp.day)
		{
			flag = false;
		}
		if (flag == true)
		{
			cout << "Название задачи: " << Spisok_del[i].nazvanie << endl;
			cout << "Приоритет: " << Spisok_del[i].prioritet << endl;
			cout << "Срок выполнения: " << Spisok_del[i].date_vp.day << "." << Spisok_del[i].date_vp.month << "." << Spisok_del[i].date_vp.year << endl;
			cout << "Статус: " << Spisok_del[i].status << endl;
		}
	}
}
void zap_v_file_zadacha2()
{
	ofstream file("Задача_5_2.CSV");

	if (!file.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		return;
	}
	file << "Срок выполнения; Название; Приоритет; Статус" << endl;
	for (const auto& Z : Spisok_del)
	{
		file << Z.date_vp.day << "." << Z.date_vp.month << "." << Z.date_vp.year << ";" << Z.nazvanie << ";" <<  Z.prioritet << ";" << Z.status << endl;
	}
	file.close();
	cout << "Данные сохранены в Задача_5_2.CSV" << endl;
}
void loadFromCSV_2zadacha()
{
	Spisok_del.clear();
	ifstream file("Задача_5_2.CSV");
	if (!file.is_open())
	{
		cout << "Файл Задача_5_2.CSV не найден" << endl;
		return;
	}
	string line;
	string nazvanie;
	string status;
	int count = 0;
	getline(file, line);
	while (getline(file, line))
	{
		if (line.empty())
		{
			continue;
		}
		stringstream ss(line);
		string data_str;
		string prioritet;
		Zadacha Z;
		int fieldCount = 0;
		if (!getline(ss, data_str, ';'))
		{
			continue;
		}
		size_t dotPos = data_str.find('.');
		if (dotPos != string::npos)
		{
			size_t dotPos2 = data_str.find('.', dotPos + 1);
			if (dotPos2 != string::npos)
			{
				Z.date_vp.day = stoi(data_str.substr(0, dotPos));
				Z.date_vp.month = stoi(data_str.substr(dotPos + 1, dotPos2 - dotPos - 1));
				Z.date_vp.year = stoi(data_str.substr(dotPos2 + 1));
			}
			if (!getline(ss, nazvanie, ';'))
			{
				continue;
			}
			Z.nazvanie = nazvanie;
			if (!getline(ss, prioritet, ';'))
			{
				continue;
			}
			Z.prioritet = stoi(prioritet);
			if (!getline(ss, status, ';'))
			{
				continue;
			}
			Z.status = stoi(status);
			Spisok_del.push_back(Z);
			count++;
		}
	}
	file.close();
	if (count > 0)
	{
		cout << "Успешно загружено " << count << " записей." << endl;
	}
	else {
		cout << "Записи не загружены" << endl;
	}
}
void menu_2()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "1. Добавление задачи (название, приоритет, срок выполнения)" << endl;
	cout << "2. Просмотр списка дел" << endl;
	cout << "3. Отметка задачи как выполненной" << endl;
	cout << "4. Удаление задачи" << endl;
	cout << "5. Показ задач на сегодня и просроченных" << endl;
	cout << "6. Сохранить задачу в файл" << endl;
	cout << "7. Прочитать список дел из файла" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		dobav_zadacha();
		menu_2();
	case 2:
		prosmotr_spisok_del();
		menu_2();
	case 3:
		vp_zadacha();
		menu_2();
	case 4:
		del_zadacha();
		menu_2();
	case 5:
		zadachi_na_segodnu_i_prosroch();
		menu_2();
	case 6:
		zap_v_file_zadacha2();
		menu_2();
	case 7:
		loadFromCSV_2zadacha();
		menu_2();
	case 0:
		zap_v_file_zadacha2();
		glavnoemenu();
	default:
		cout << "Такого задания нет!" << endl;
		menu_2();
	}
}
/// конец 2 задача
/// начало 3 задача
struct Time
{
	int hour;
	int min;
	int sec;
};
struct Priem_pishi
{
	string nazvanie_bludo;
	int kaloria;
	Time time;
};
vector <Priem_pishi> Pisha_day;
struct Day_food
{
	vector <Priem_pishi> food; 
	Date date;
};
vector<Day_food> Day;
void dobav_priem_pisha()
{
	Priem_pishi P;

	cout << "Введите время приема пищи (HH MM SS): ";
	cin >> P.time.hour >> P.time.min >> P.time.sec;
	cin.ignore(); 
	cout << "Введите название блюда: ";
	getline(cin, P.nazvanie_bludo);
	cout << "Введите количество калорий: ";
	cin >> P.kaloria;
	if (P.kaloria > 0 && P.time.hour >= 0 && P.time.hour < 24 && P.time.min >= 0 && P.time.min < 60 && P.time.sec >= 0 && P.time.sec < 60)
	{
		Pisha_day.push_back(P);
		cout << "Прием пищи добавлен в дневной список" << endl;
	}
	else
	{
		cout << "Ошибка, запись не добавлена. Проверьте правильность введенных данных" << endl;
	}
}
void dobav_pisha_day()
{
	Day_food D;
	cout << "Введите дату (DD MM YYYY): ";
	cin >> D.date.day >> D.date.month >> D.date.year;
	D.food = Pisha_day;
	if (D.date.day >= 1 && D.date.day <= 31 && D.date.month >= 1 && D.date.month <= 12 && D.date.year >= 0)
	{
		Day.push_back(D);
		Pisha_day.clear();
		cout << "Дневной рацион добавлен" << endl;
	}
	else
	{
		cout << "Ошибка введенных данных" << endl;
	}
}
void prosmotr_day()
{
	Day_food  D;
	cout << "Введите дату дня, которую хотите посмотреть (DD MM YYYY): ";
	cin >> D.date.day >> D.date.month >> D.date.year;
	for (int i = 0; i < size(Day); i++)
	{
		if (Day[i].date.day == D.date.day && Day[i].date.month == D.date.month && Day[i].date.year == D.date.year)
		{
			for (int j = 0; j < Day[i].food.size(); j++)
			{
				cout << "Название блюда: " << Day[i].food[j].nazvanie_bludo << endl;
				cout << "Калории: " << Day[i].food[j].kaloria << endl;
				cout << "Время приема пищи: " << Day[i].food[j].time.hour << "." << Day[i].food[j].time.min << "." << Day[i].food[j].time.sec << endl;
			}
		}
	}
}
void prosmotr_priem_pishi()
{
	Day_food  D;
	for (int i = 0; i < size(Day); i++)
	{
		cout << Day[i].date.day << "." << Day[i].date.month << "." << Day[i].date.year << endl;
		for (int j = 0; j < Day[i].food.size(); j++)
		{
			cout << "Название блюда: " << Day[i].food[j].nazvanie_bludo << endl;
			cout << "Калории: " << Day[i].food[j].kaloria << endl;
			cout << "Время приема пищи: " << Day[i].food[j].time.hour << "." << Day[i].food[j].time.min << "." << Day[i].food[j].time.sec << endl;
		}
	}
}
void calorii_za_day()
{
	Day_food  D;
	int limit_kalor = 0;
	int kalor = 0;
	cout << "Введите дату дня, которую хотите посмотреть (DD MM YYYY): ";
	cin >> D.date.day >> D.date.month >> D.date.year;
	cout << "Введите свой лимит калорий: ";
	cin >> limit_kalor;
	for (int i = 0; i < size(Day); i++)
	{
		if (Day[i].date.day == D.date.day && Day[i].date.month == D.date.month && Day[i].date.year == D.date.year)
		{
			for (int j = 0; j < Day[i].food.size(); j++)
			{
				cout << j + 1 << "." << endl;
				cout << "Название блюда: " << Day[i].food[j].nazvanie_bludo << endl;
				cout << "Калории: " << Day[i].food[j].kaloria << endl;
				cout << "Время приема пищи: " << Day[i].food[j].time.hour << "." << Day[i].food[j].time.min << "." << Day[i].food[j].time.sec << endl;
				kalor += Day[i].food[j].kaloria;
			}
		}
	}
	if (limit_kalor < kalor)
	{
		cout << "Вы привысили лимит на " << kalor - limit_kalor << " калорий. Всего было употреблено: " << kalor << endl;
	}
	if (limit_kalor > kalor)
	{
		cout << "У вас осталось еще " << limit_kalor - kalor << " калорий. Всего было употреблено: " << kalor << endl;
	}
	if (limit_kalor == kalor)
	{
		cout << "Вы потребили все калории. Всего было употреблено: " << kalor << endl;
	}
}
void zap_v_file_zadacha3()
{
	ofstream file("Задача_5_3.CSV");

	if (!file.is_open())
	{
		cout << "Ошибка открытия файла для записи!" << endl;
		return;
	}
	file << "Дата;Название блюда;Калории;Время (часы);Время (минуты);Время (секунды)" << endl;
	for (const auto& day : Day)
	{
		for (const auto& s : day.food)
		{
			file << day.date.day << "." << day.date.month << "." << day.date.year << ";" << s.nazvanie_bludo << ";" << s.kaloria << ";" << s.time.hour << ";" << s.time.min << ";" << s.time.sec << endl;
		}
	}
	file.close();
	cout << "Данные сохранены в Задача_5_3.CSV" << endl;
}
void load_from_csv_3()
{
	ifstream file("Задача_5_3.CSV");
	if (!file.is_open())
	{
		cout << "Файл Задача_5_3.CSV не найден" << endl;
		return;
	}
	Day.clear();
	Pisha_day.clear();
	string line;
	int line_count = 0;
	getline(file, line);
	Date current_date;
	Day_food current_day;  
	bool new_day = true;
	while (getline(file, line))
	{
		if (line.empty()) 
			continue;
		stringstream ss(line);
		string field;
		vector <string> fields;
		while (getline(ss, field, ';'))
		{
			fields.push_back(field);
		}
		size_t dot1 = fields[0].find('.');
		size_t dot2 = fields[0].rfind('.');
		Date meal_date;
		meal_date.day = stoi(fields[0].substr(0, dot1));
		meal_date.month = stoi(fields[0].substr(dot1 + 1, dot2 - dot1 - 1));
		meal_date.year = stoi(fields[0].substr(dot2 + 1));
		Priem_pishi meal;
		meal.nazvanie_bludo = fields[1];
		meal.kaloria = stoi(fields[2]);
		meal.time.hour = stoi(fields[3]);
		meal.time.min = stoi(fields[4]);
		meal.time.sec = stoi(fields[5]);
		if (line_count == 0 ||
			meal_date.day != current_date.day ||
			meal_date.month != current_date.month ||
			meal_date.year != current_date.year)
		{
			if (line_count > 0 && !current_day.food.empty())
			{
				Day.push_back(current_day);
			}
			current_day.date = meal_date;
			current_day.food.clear();
			current_date = meal_date;
		}
		current_day.food.push_back(meal);
		line_count++;
	}
	if (!current_day.food.empty())
	{
		Day.push_back(current_day);
	}
	file.close();
	if (line_count > 0)
	{
		cout << "Успешно загружено " << line_count << " приемов пищи за " << Day.size() << " дней." << endl;
	}
}
void menu_3()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "1. Ввод приема пищи (блюдо, количество калорий, время)" << endl;
	cout << "2. Ввод дня (после всех приемов пищи)" << endl;
	cout << "3. Все приемы пищи за конкретный день" << endl;
	cout << "4. Все калории за конкретный день" << endl;
	cout << "5. Записать данные в файл" << endl;
	cout << "6. Считать данные из файла" << endl;
	cout << "7. Просмотр всех приемов пищи" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		dobav_priem_pisha();
		menu_3();
	case 2:
		dobav_pisha_day();
		menu_3();
	case 3:
		prosmotr_day();
		menu_3();
	case 4:
		calorii_za_day();
		menu_3();
	case 5:
		zap_v_file_zadacha3();
		menu_3();
	case 6:
		load_from_csv_3();
		menu_3();
	case 7:
		prosmotr_priem_pishi();
		menu_3();
	case 0:
		zap_v_file_zadacha3();
		glavnoemenu();
	default:
		cout << "Такого задания нет!" << endl;
		menu_3();
	}
}
/// конец 3 задача
/// начало 4 задача
void zap_v_file_zadacha4_zashifr(const string& str_shifr)
{
	ofstream file("Задача_5_4_zashif.txt");
	if (!file.is_open()) 
	{
		cout << "Ошибка открытия файла!" << endl;
		return;
	}
	file << "Зашифрованные строки:" << endl;
	file << str_shifr << endl;
	file.close();
	cout << "Данные сохранены в Задача_5_4_zashif.txt" << endl;
}
string str;
void De_Cezar(const string& str_zashif)
{
	string str = str_zashif;
	string ABC_rus = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	string ABC_eng = "abcdefghijklmnopqrstuvwxyz";
	int pos;
	int sdvig;
	cin.ignore();
	cout << "Введите сдвиг: ";
	cin >> sdvig;
	for (size_t i = 0; i < str.size(); i++)
	{
		str[i] = toLower(str[i]);
		pos = ABC_rus.find(str[i]);
		if (pos != string::npos)
		{
			int new_pos = (pos - sdvig + ABC_rus.size()) % ABC_rus.size();
			str[i] = ABC_rus[new_pos];
		}
		else
		{
			pos = ABC_eng.find(str[i]);
			if (pos != string::npos)
			{
				int new_pos = (pos - sdvig + ABC_eng.size()) % ABC_eng.size();
				str[i] = ABC_eng[new_pos];
			}
		}
	}
	cout << "Расшифрованная строка: " << str << endl;
}
void loadFromCSV_4zadacha()
{
	Diary.clear();
	ifstream file("Задача_5_4_zashif.txt");
	if (!file.is_open())
	{
		cout << "Файл Задача_5_4_zashif.txt не найден" << endl;
		return;
	}
	string line;
	getline(file, line);
	getline(file, line);
	str = line;
	file.close();
	De_Cezar(str);
}
void Cezar()
{
	string ABC_rus = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	string ABC_eng = "abcdefghijklmnopqrstuvwxyz";
	int pos;
	int sdvig;
	cin.ignore();
	cout << "Введите текст: ";
	getline(cin, str);
	cout << "Введите сдвиг: ";
	cin >> sdvig;
	for (size_t i = 0; i < size(str); i++)
	{
		str[i] = toLower(str[i]);
		pos = ABC_rus.find(str[i]);
		if (pos != string::npos)
		{
			str[i] = ABC_rus[(pos + sdvig) % size(ABC_rus)];
		}
		else
		{
			pos = ABC_eng.find(str[i]);
			if (pos != string::npos)
			{
				str[i] = ABC_eng[(pos + sdvig) % size(ABC_eng)];
			}
		}
	}
	zap_v_file_zadacha4_zashifr(str);
}
char toLower(char s)
{
	if (s >= 'A' && s <= 'Z')
	{
		return s + ('a' - 'A');
	}
	if (s >= 'А' && s <= 'Я')
	{
		return s + ('а' - 'А');
	}
	if (s == 'Ё') return 'ё';
	return s;
}
void menu_4()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "1. Зашифровать строку" << endl;
	cout << "2. Загрузить и расшифровать из файла" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		Cezar();
		menu_4();
	case 2:
		loadFromCSV_4zadacha();
		menu_4();
	case 0:
		glavnoemenu();
	default:
		cout << "Такого задания нет!" << endl;
		menu_4();
	}
}
/// конец 4 задача
/// начало 5 задача
struct Player
{
	string nick;
	string hard_level;
	int record;
};
vector <Player> Players;
vector <Player> Hard_level;
vector <Player> Norm_level;
vector <Player> Easy_level;
void game()
{
	Player igr;
	cin.ignore();
	cout << "Игра угадай число" << endl;
	string level;
	int count_try;
	int target = 0;
	int number;
	int x = 0;
	cout << "Введите свой nick: ";
	getline(cin, igr.nick);
	cout << "Введите уровень сложности (Легкий - 100, Нормальный - 500, Сложный - 1000): ";
	getline(cin, level);
	if (level == "Легкий")
	{
		cout << "Вы выбрали легкий уровень. У вас 7 попыток" << endl;
		x = 100;
		target = rand() % x + 1;
		count_try = 7;
	}
	else if (level == "Нормальный")
	{
		cout << "Вы выбрали нормальный уровень. У вас 9 попыток" << endl;
		x = 500;
		target = rand() % x + 1;
		count_try = 9;
	}
	else
	{
		cout << "Вы выбрали сложный уровень. У вас 10 попыток" << endl;
		x = 1000;
		target = rand() % x + 1;
		count_try = 10;
	}
	bool Flag = false;
	for (int i = 0; i < count_try; i++)
	{
		cout << "Попытка " << i + 1 << endl;
		cout << "Введите число: ";
		cin >> number;
		if (number == target)
		{
			Flag = true;
			cout << "Вы выиграли за " << i + 1 << " попыток" << endl;
			igr.hard_level = level;
			igr.record = i + 1;
			bool flag_1 = false;
			for (int j = 0; j < size(Players); j++)
			{
				if (Players[j].nick == igr.nick && Players[j].hard_level == igr.hard_level)
				{
					Players[j].record = igr.record;
					flag_1 = true;
					break;
				}
			}
			if (!(flag_1))
			{
				Players.push_back(igr);
			}
			break;
		}
		else if (number > target)
		{
			cout << "Меньше" << endl;
		}
		else
		{
			cout << "Больше" << endl;
		}
		cout << "--------------------" << endl;
	}
	if (Flag == false)
	{
		cout << "Вы проиграли. Попробуйте еще раз" << endl;
	}
	
}
void top_5_hard()
{
	Hard_level.clear();
	for (int j = 0; j < size(Players); j++)
	{
		if (Players[j].hard_level == "Сложный")
		{
			Hard_level.push_back(Players[j]);
		}
	}
	int top_h = 5;
	cout << "Топ 5. Уровень сложный" << endl;
	if (Hard_level.empty())
	{
		cout << "Нет истории попыток" << endl;
	}
	else
	{
		for (int i = 0; i < size(Hard_level) - 1; i++)
		{
			for (int j = 0; j < size(Hard_level) - i - 1; j++)
			{
				if (Hard_level[j].record > Hard_level[j + 1].record)
				{
					Player shag_h = Hard_level[j];
					Hard_level[j] = Hard_level[j + 1];
					Hard_level[j + 1] = shag_h;
				}
			}
		}
		if (size(Hard_level) < top_h)
		{
			top_h = size(Hard_level);
			for (int e = 0; e < top_h; e++)
			{
				cout << "Место " << e + 1 << endl;
				cout << "Игрок: " << Hard_level[e].nick << endl;
				cout << "Количество попыток: " << Hard_level[e].record << endl;
			}
		}
		else
		{
			for (int e = 0; e < top_h; e++)
			{
				cout << "Игрок: " << Hard_level[e].nick << endl;
				cout << "Количество попыток: " << Hard_level[e].record << endl;
			}
		}
	}
}
void top_5_norm()
{
	Norm_level.clear();
	for (int j = 0; j < size(Players); j++)
	{
		if (Players[j].hard_level == "Нормальный")
		{
			Norm_level.push_back(Players[j]);
		}
	}
	int top_n = 5;
	cout << "Топ 5. Уровень нормальный" << endl;
	if (Norm_level.empty())
	{
		cout << "Нет истории попыток" << endl;
	}
	else
	{
		for (int i = 0; i < size(Norm_level) - 1; i++)
		{
			for (int j = 0; j < size(Norm_level) - i - 1; j++)
			{
				if (Norm_level[j].record > Norm_level[j + 1].record)
				{
					Player shag_n = Norm_level[j];
					Norm_level[j] = Norm_level[j + 1];
					Norm_level[j + 1] = shag_n;
				}
			}
		}
		if (size(Norm_level) < top_n)
		{
			top_n = size(Norm_level);
			for (int e = 0; e < top_n; e++)
			{
				cout << "Место " << e + 1 << endl;
				cout << "Игрок: " << Norm_level[e].nick << endl;
				cout << "Количество попыток: " << Norm_level[e].record << endl;
			}
		}
		else
		{
			for (int e = 0; e < top_n; e++)
			{
				cout << "Игрок: " << Norm_level[e].nick << endl;
				cout << "Количество попыток: " << Norm_level[e].record << endl;
			}
		}
	}
}
void top_5_easy()
{ 
	Easy_level.clear();
	for (int j = 0; j < size(Players); j++)
	{
		if (Players[j].hard_level == "Легкий")
		{
			Easy_level.push_back(Players[j]);
		}
	}
	int top_e = 5;
	cout << "Топ 5. Уровень легкий" << endl;
	if (Easy_level.empty())
	{
		cout << "Нет истории попыток" << endl;
	}
	else
	{
		for (int i = 0; i < size(Easy_level) - 1; i++)
		{
			for (int j = 0; j < size(Easy_level) - i - 1; j++)
			{
				if (Easy_level[j].record > Easy_level[j + 1].record)
				{
					Player shag_e = Easy_level[j];
					Easy_level[j] = Easy_level[j + 1];
					Easy_level[j + 1] = shag_e;
				}
			}
		}
		if (size(Easy_level) < top_e)
		{
			top_e = size(Easy_level);
			for (int e = 0; e < top_e; e++)
			{
				cout << "Место " << e + 1 << endl;
				cout << "Игрок: " << Easy_level[e].nick << endl;
				cout << "Количество попыток: " << Easy_level[e].record << endl;
			}
		}
		else
		{
			for (int e = 0; e < top_e; e++)
			{
				cout << "Игрок: " << Easy_level[e].nick << endl;
				cout << "Количество попыток: " << Easy_level[e].record << endl;
			}
		}
	}
}
void zap_v_file_zadacha5_5()
{
	ofstream file("Задача_5_5.CSV");

	if (!file.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		return;
	}
	file << "Ник;Уровень;Рекорд" << endl;
	for (const auto& P : Players)
	{
		file << P.nick << ";" << P.hard_level << ";" << P.record << endl;
	}
	file.close();
	cout << "Данные сохранены в Задача_5_5.CSV" << endl;
}
void load_from_csv_5_5()
{
	ifstream file("Задача_5_5.CSV");
	if (!file.is_open())
	{
		cout << "Файл Задача_5_5.CSV не найден" << endl;
		return;
	}
	Players.clear();
	string line;
	int line_count = 0;
	getline(file, line);
	while (getline(file, line))
	{
		if (line.empty())
			continue;
		stringstream ss(line);
		string field;
		vector <string> fields;
		while (getline(ss, field, ';'))
		{
			fields.push_back(field);
		}
		Player P;
		P.nick = fields[0];
		P.hard_level = fields[1];
		P.record = stoi(fields[2]);
		Players.push_back(P);
		line_count++;
	}
	file.close();
	if (line_count > 0)
	{
		cout << "Успешно загружено " << line_count << " записей игроков" << endl;
	}
}
void menu_5()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "1. Сыграть в игру" << endl;
	cout << "2. Таблица рекордов (топ-5 игроков) сложный" << endl;
	cout << "3. Таблица рекордов (топ-5 игроков) нормальный" << endl;
	cout << "4. Таблица рекордов (топ-5 игроков) легкий" << endl;
	cout << "5. Записать данные в файл" << endl;
	cout << "6. Загрузить данные из файла" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		game();
		menu_5();
	case 2:
		top_5_hard();
		menu_5();
	case 3:
		top_5_norm();
		menu_5();
	case 4:
		top_5_easy();
		menu_5();
	case 5:
		zap_v_file_zadacha5_5();
		menu_5();
	case 6:
		load_from_csv_5_5();
		menu_5();
	case 0:
		glavnoemenu();
	default:
		cout << "Такого задания нет!" << endl;
		menu_5();
	}
}
/// конец 5 задача
/// начало 6 задача
struct Day_pogoda
{
	Date date;
	int temp;
	bool osadki;
	double veter;
	bool oblachnost;
};
vector <Day_pogoda> Days_pogoda;
void pogoda_zap()
{
	Day_pogoda D;
	cout << "Введите дату (DD MM YYYY): ";
	cin >> D.date.day >> D.date.month >> D.date.year;
	cin.ignore();
	cout << "Введите температуру: ";
	cin >> D.temp;
	cin.ignore();
	cout << "Есть осадки? (1 - да, 0 - нет): ";
	cin >> D.osadki;
	cout << "Введите скорость ветра: ";
	cin >> D.veter;
	cin.ignore();
	cout << "Облачно? (1 - да, 0 - нет): ";
	cin >> D.oblachnost;
	if (D.date.day >= 1 && D.date.day <= 31 && D.date.month >= 1 && D.date.month <= 12 && D.date.year >= 0)
	{
		Days_pogoda.push_back(D);
		cout << "Запись погоды добавлена" << endl;
	}
	else
	{
		cout << "Ошибка, запись не добавлена. Проверьте правильность введенных данных" << endl;
	}
}
void prosmotr_zap_pogoda()
{
	for (int i = 0; i < size(Days_pogoda); i++)
	{
		cout << "Дата: " << Days_pogoda[i].date.day << "." << Days_pogoda[i].date.month << "." << Days_pogoda[i].date.year << endl;
		cout << "Температура: " << Days_pogoda[i].temp << endl;
		cout << "Осадки: " << Days_pogoda[i].osadki << endl;
		cout << "Ветер: " << Days_pogoda[i].veter << endl;
		cout << "Облачность: " << Days_pogoda[i].oblachnost << endl;
	}
}
void max_min_temp()
{
	cin.ignore();
	int max_temp = Days_pogoda[0].temp;
	int max_i = 0;
	int min_temp = Days_pogoda[0].temp;
	int min_i = 0;
	for (int i = 0; i < size(Days_pogoda); i++)
	{
		if (Days_pogoda[i].temp > max_temp)
		{
			max_temp = Days_pogoda[i].temp;
			max_i = i;
		}
		if (Days_pogoda[i].temp < min_temp)
		{
			min_temp = Days_pogoda[i].temp;
			min_i = i;
		}
	}
	for (int j = 0; j < size(Days_pogoda); j++)
	{
		if (max_i == j)
		{
			cout << "Максимальная температура за весь период" << endl;
			cout << "Дата: " << Days_pogoda[j].date.day << "." << Days_pogoda[j].date.month << "." << Days_pogoda[j].date.year << endl;
			cout << "Температура: " << Days_pogoda[j].temp << endl;
			cout << "Осадки: " << Days_pogoda[j].osadki << endl;
			cout << "Ветер: " << Days_pogoda[j].veter << endl;
			cout << "Облачность: " << Days_pogoda[j].oblachnost << endl;
		}
		cout << "-------------------------------------------" << endl;
		if (min_i == j)
		{
			cout << "Минимальная температура за весь период" << endl;
			cout << "Дата: " << Days_pogoda[j].date.day << "." << Days_pogoda[j].date.month << "." << Days_pogoda[j].date.year << endl;
			cout << "Температура: " << Days_pogoda[j].temp << endl;
			cout << "Осадки: " << Days_pogoda[j].osadki << endl;
			cout << "Ветер: " << Days_pogoda[j].veter << endl;
			cout << "Облачность: " << Days_pogoda[j].oblachnost << endl;
		}
	}
}
int comp_date(Date D1, Date D2)
{
	if (D1.year < D2.year)
		return -1;
	if (D1.year > D2.year)
		return 1;
	if (D1.month < D2.month)
		return -1;
	if (D1.month > D2.month)
		return 1;
	if (D1.day < D2.day)
		return -1;
	if (D1.day > D2.day)
		return 1;
	return 0;
}
void sr_temp_week()
{
	if (Days_pogoda.empty())
	{
		cout << "Нет записей о погоде!" << endl;
		return;
	}
	Date D;
	double summ = 0;
	int count = 0;
	double sred_temp_week = 0;
	cout << "Введите дату с которой хотите начать отсчет (DD MM YYYY): ";
	cin >> D.day >> D.month >> D.year;
	cin.ignore();
	Date D_end;
	D_end.day = D.day + 6;
	D_end.month = D.month;
	D_end.year = D.year;
	if (D_end.day > 31)
	{
		D_end.day -= 31;
		D_end.month++;
		if (D_end.month > 12)
		{
			D_end.month = 1;
			D_end.year++;
		}
	}
	for (int i = 0; i < size(Days_pogoda); i++)
	{
		Date D_now = Days_pogoda[i].date;
		if (comp_date(D, D_now) <= 0 && comp_date(D_now, D_end) <= 0)
		{
			count++;
			summ += Days_pogoda[i].temp;
		}
	}
	if (count != 0)
	{
		sred_temp_week = (static_cast<double>(summ)) / count;
		cout << "Средняя температура за неделю - " << sred_temp_week << endl;
	}
	else
	{
		cout << "Недостаточно данных для рассчета средней температуры за неделю" << endl;
	}
}
void sr_temp_month()
{
	if (Days_pogoda.empty())
	{
		cout << "Нет записей о погоде!" << endl;
		return;
	}
	Date D;
	double summ = 0;
	int count = 0;
	double sred_temp_month = 0;
	cout << "Введите дату с которой хотите начать отсчет (DD MM YYYY): ";
	cin >> D.day >> D.month >> D.year;
	cin.ignore();
	Date D_end;
	D_end.day = D.day;
	D_end.month = D.month + 1;
	D_end.year = D.year;
	if (D_end.month > 12)
	{
		D_end.month = 1;
		D_end.year++;
	}
	for (int i = 0; i < size(Days_pogoda); i++)
	{
		Date D_now = Days_pogoda[i].date;
		if (comp_date(D, D_now) <= 0 && comp_date(D_now, D_end) <= 0)
		{
			count++;
			summ += Days_pogoda[i].temp;
		}
	}
	if (count != 0)
	{
		sred_temp_month = (static_cast<double>(summ)) / count;
		cout << "Средняя температура за месяц - " << sred_temp_month << endl;
	}
	else
	{
		cout << "Недостаточно данных для рассчета средней температуры за месяц" << endl;
	}
}
void prosmotr_soln_dojdl_dney()
{
	cout << "Самые солнечные дни" << endl;
	for (int i = 0; i < size(Days_pogoda); i++)
	{
		if (Days_pogoda[i].oblachnost == false && Days_pogoda[i].osadki == false)
		{
			cout << "Дата: " << Days_pogoda[i].date.day << "." << Days_pogoda[i].date.month << "." << Days_pogoda[i].date.year << endl;
			cout << "Температура: " << Days_pogoda[i].temp << endl;
			cout << "Осадки: " << Days_pogoda[i].osadki << endl;
			cout << "Ветер: " << Days_pogoda[i].veter << endl;
			cout << "Облачность: " << Days_pogoda[i].oblachnost << endl;
		}
	}
	cout << "-------------------------------------------" << endl;
	cout << "Самые дождливые дни" << endl;
	for (int i = 0; i < size(Days_pogoda); i++)
	{
		if (Days_pogoda[i].oblachnost == true && Days_pogoda[i].osadki == true)
		{
			cout << "Дата: " << Days_pogoda[i].date.day << "." << Days_pogoda[i].date.month << "." << Days_pogoda[i].date.year << endl;
			cout << "Температура: " << Days_pogoda[i].temp << endl;
			cout << "Осадки: " << Days_pogoda[i].osadki << endl;
			cout << "Ветер: " << Days_pogoda[i].veter << endl;
			cout << "Облачность: " << Days_pogoda[i].oblachnost << endl;
		}
	}
}
void stat_pogod()
{
	Date D;
	cout << "Введите дату, погоду которой хотите узнать (DD MM YYYY): ";
	cin >> D.day >> D.month >> D.year;
	cin.ignore();
	Date D_n;
	D_n.day = D.day;
	D_n.month = D.month;
	D_n.year = D.year - 1;
	for (int i = 0; i < size(Days_pogoda); i++)
	{
		if (Days_pogoda[i].date.day == D_n.day && Days_pogoda[i].date.month == D_n.month && Days_pogoda[i].date.year == D_n.year)
		{
			cout << "Погода будет такая" << endl;
			cout << "Температура: " << Days_pogoda[i].temp << endl;
			cout << "Осадки: " << Days_pogoda[i].osadki << endl;
			cout << "Ветер: " << Days_pogoda[i].veter << endl;
			cout << "Облачность: " << Days_pogoda[i].oblachnost << endl;
		}
	}
}
void zap_v_file_zadacha5_6()
{
	ofstream file("Задача_5_6.CSV");

	if (!file.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		return;
	}
	file << "Дата;Температура;Осадки;Скорость ветра;Облачность" << endl;
	for (const auto& D : Days_pogoda)
	{
		file << D.date.day << "." << D.date.month << "." << D.date.year << ";" << D.temp << ";" << D.osadki << ";" << D.veter << ";" << D.oblachnost << endl;
	}
	file.close();
	cout << "Данные сохранены в Задача_5_6.CSV" << endl;
}
void load_from_csv_5_6()
{
	ifstream file("Задача_5_6.CSV");
	if (!file.is_open())
	{
		cout << "Файл Задача_5_6.CSV не найден" << endl;
		return;
	}
	Days_pogoda.clear();
	string line;
	int line_count = 0;
	getline(file, line);
	while (getline(file, line))
	{
		if (line.empty())
			continue;
		stringstream ss(line);
		string field;
		vector <string> fields;
		while (getline(ss, field, ';'))
		{
			fields.push_back(field);
		}
		size_t dot1 = fields[0].find('.');
		size_t dot2 = fields[0].rfind('.');
		Day_pogoda D;
		D.date.day = stoi(fields[0].substr(0, dot1));
		D.date.month = stoi(fields[0].substr(dot1 + 1, dot2 - dot1 - 1));
		D.date.year = stoi(fields[0].substr(dot2 + 1));
		D.temp = stoi(fields[1]);
		D.osadki = stoi(fields[2]);
		D.veter = stoi(fields[3]);
		D.oblachnost = stoi(fields[4]);
		Days_pogoda.push_back(D);
		line_count++;
	}
	file.close();
	if (line_count > 0)
	{
		cout << "Успешно загружено " << Days_pogoda.size() << " записей о погоде." << endl;
	}
}
void menu_6()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "1. Запись погодных данных (температура, осадки, сила ветра, облачность)" << endl;
	cout << "2. Просмотр всех записей" << endl;
	cout << "3. Максимальная и минимаьная температура за весь период" << endl;
	cout << "4. Средняя температура за неделю" << endl;
	cout << "5. Средняя температура за месяц" << endl;
	cout << "6. Определение самых солнечных и дождливых дней" << endl;
	cout << "7. Простой прогноз на основе статистики предыдущих дней" << endl;
	cout << "8. Добавить данные в файл" << endl;
	cout << "9. Загрузить данные из файла" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		pogoda_zap();
		menu_6();
	case 2:
		prosmotr_zap_pogoda();
		menu_6();
	case 3:
		max_min_temp();
		menu_6();
	case 4:
		sr_temp_week();
		menu_6();
	case 5:
		sr_temp_month();
		menu_6();
	case 6:
		prosmotr_soln_dojdl_dney();
		menu_6();
	case 7:
		stat_pogod();
		menu_6();
	case 8:
		zap_v_file_zadacha5_6();
		menu_6();
	case 9:
		load_from_csv_5_6();
		menu_6();
	case 0:
		glavnoemenu();
	default:
		cout << "Такого задания нет!" << endl;
		menu_6();
	}
}
/// конец 6 задача
void glavnoemenu()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "Задача 1. Дневник настроения" << endl;
	cout << "Задача 2. Умный список дел (To-Do List)" << endl;
	cout << "Задача 3. Персональный счетчик калорий" << endl;
	cout << "Задача 4. Текстовый шифратор сообщений" << endl;
	cout << "Задача 5. Система сохранения игрового прогресса" << endl;
	cout << "Задача 6. Погодный дневник с анализом" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		loadFromCSV();
		menu_1();
		glavnoemenu();
	case 2:
		loadFromCSV_2zadacha();
		menu_2();
		glavnoemenu();
	case 3:
		load_from_csv_3();
		menu_3();
		glavnoemenu();
	case 4:
		loadFromCSV_4zadacha();
		menu_4();
		glavnoemenu();
	case 5:
		load_from_csv_5_5();
		menu_5();
		glavnoemenu();
	case 6:
		load_from_csv_5_6();
		menu_6();
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
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	glavnoemenu();
	return 0;
}