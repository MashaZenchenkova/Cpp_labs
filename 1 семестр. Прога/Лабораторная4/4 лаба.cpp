#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath> 
#include <ctime> 
#include <algorithm>
#include <string>
#define  _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <Windows.h>
#include <locale>
#include <unordered_map>
#include <map>
#include <fstream>
#include <iomanip>
#include <random>
using namespace std;
void menu_2();
void glavnoemenu();
char toLower(char s);
void poisk_palindroma();
bool proverka_palindroma(string str);
void statistica();
void menu_3();
void menu_3_1();
void add_student(string Name, int Age, double Sr_ball, vector <string> Predmets);
void menu_3_3();
void menu_4();
void prosmotr_book();
void dat_book();
void vernut_book();
void findBookByTitle();
void findBookByAuthor();
void findBookByJanr();
void stat_book();
void igra();
void print_igr_pole(int y1, int x1, int y2, int x2);
// Блок задача1 начало
void pervau_zadacha()
{
	struct Student
	{
		string Name;
		vector <int> Grade;
		double sredball;
	};
	int const KOLVO_PREDMETOV = 3;
	int const KOLVO_STUDENTOV = 5;
	srand(time(nullptr));
	vector<string> predmet = { "Высшая математика", "Русский язык", "Программирование" };
	vector<Student> students(5);

	students[0].Name = "Иван";
	students[1].Name = "Александр";
	students[2].Name = "Мария";
	students[3].Name = "Дарья";
	students[4].Name = "Никита";

	for (int i = 0; i < KOLVO_STUDENTOV; i++)
	{
		students[i].Grade.resize(KOLVO_PREDMETOV);
		for (int j = 0; j < KOLVO_PREDMETOV; j++)
		{
			students[i].Grade[j] = rand() % 4 + 2;
		}
	}
	for (int i = 0; i < KOLVO_STUDENTOV; i++)
	{
		double summ_studenta = 0;
		for (int j = 0; j < KOLVO_PREDMETOV; j++)
		{
			summ_studenta += students[i].Grade[j];
		}
		double sred_summ_studenta = (static_cast<double>(summ_studenta)) / KOLVO_PREDMETOV;
		students[i].sredball = sred_summ_studenta;
	}
	vector<double> srednie_predmetov(KOLVO_PREDMETOV, 0.0);
	for (int j = 0; j < KOLVO_PREDMETOV; j++)
	{
		double summ_predmeta = 0;
		for (int i = 0; i < KOLVO_STUDENTOV; i++)
		{
			summ_predmeta += students[i].Grade[j];
		}
		srednie_predmetov[j] = (static_cast<double>(summ_predmeta)) / KOLVO_STUDENTOV;
	}
	cout << string(90, '-') << endl;
	cout << setw(15) << left << "Студент";
	for (int j = 0; j < KOLVO_PREDMETOV; j++)
	{
		cout << setw(20) << left << predmet[j];
	}
	cout << setw(15) << right << "Средний балл";
	cout << endl;

	cout << string(90, '-') << endl;
	for (int i = 0; i < KOLVO_STUDENTOV; i++)
	{
		cout << setw(15) << left << students[i].Name;
		for (int j = 0; j < KOLVO_PREDMETOV; j++)
		{
			cout << setw(20) << left << students[i].Grade[j];
		}
		cout << setw(15) << right << fixed << setprecision(2) << students[i].sredball;
		cout << endl;
	}
	cout << string(90, '-') << endl;
	cout << setw(15) << left << "Средний балл:";
	for (int j = 0; j < KOLVO_PREDMETOV; j++)
	{
		cout << setw(20) << left << fixed << setprecision(2) << srednie_predmetov[j];
	}
	cout << setw(15) << right << "";
	cout << endl;

	vector<string> plox_predmet;
	cout << "\n" << string(90, '=') << endl;
	cout << "Анализ успеваемости по предметам" << endl;
	cout << string(50, '-') << endl;
	cout << setw(25) << left << "Предмет";
	cout << setw(20) << right << "Средний балл" << endl;
	cout << string(45, '-') << endl;
	for (int j = 0; j < KOLVO_PREDMETOV; j++)
	{
		cout << setw(25) << left << predmet[j]
			<< setw(20) << right << fixed << setprecision(2) << srednie_predmetov[j] << endl;

		if (srednie_predmetov[j] < 3.5)
		{
			plox_predmet.push_back(predmet[j]);
		}
	}
	sort(students.begin(), students.end(), [](const Student& a, const Student& b)
		{
			return a.sredball > b.sredball;
		});

	cout << "\n" << string(90, '=') << endl;
	cout << "Рейтинг студентов по успеваемости" << endl;
	cout << string(47, '-') << endl;

	cout << setw(6) << left << "Место"
		<< setw(15) << left << "Студент"
		<< setw(25) << right << "Средний балл" << endl;
	cout << string(47, '-') << endl;

	for (int i = 0; i < KOLVO_STUDENTOV; i++)
	{
		cout << setw(6) << left << i + 1
			<< setw(16) << left << students[i].Name
			<< setw(16) << right << fixed << setprecision(2) << students[i].sredball << endl;
	}

	cout << "\n" << string(90, '=') << endl;
	cout << "Проблемные предметы" << endl;
	cout << string(50, '-') << endl;
	if (plox_predmet.empty())
	{
		cout << "Все предметы в норме" << endl;
	}
	else
	{
		for (int i = 0; i < plox_predmet.size(); i++)
		{
			int index = find(predmet.begin(), predmet.end(), plox_predmet[i]) - predmet.begin();
			cout << i+1 << ". " << setw(25) << left << plox_predmet[i]
				<< "Средний балл: " << fixed << setprecision(2) << srednie_predmetov[index] << endl;
		}
	}

	cout << string(90, '=') << endl;

}
// Блок задача1 конец
// Блок задача2 начало
void Cezar()
{
	string ABC = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	string str;
	int pos;
	int sdvig;
	cin.ignore();
	cout << "Введите текст: ";
	getline(cin, str);
	cout << "Введите сдвиг: ";
	cin >> sdvig;
	for (int i = 0; i < size(str); i++)
	{
		str[i] = toLower(str[i]);
		pos = ABC.find(str[i]);
		if (pos != string::npos)
		{
			str[i] = ABC[(pos + sdvig) % size(ABC)];
		}
	}
	cout << "Зашифрованная строка: " << str << endl;
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
void chastotabukv()
{
	string str;
	cin.ignore();
	cout << "Введите текст: ";
	getline(cin, str);
	map < char, int > chastota;
	for (int i = 0; i < str.size(); i++)
	{
		chastota[str[i]] = chastota[str[i]] + 1;
	}
	for (auto& pair :chastota) 
	{
		cout << pair.first << ": " << pair.second << endl;
	}
}
void poisk_palindroma()
{
	string str;
	string slovo = "";
	cin.ignore();
	cout << "Введите текст: ";
	getline(cin, str);
	str = str + " ";
	vector <string> slova;
	for (int i = 0; i < str.size(); i++)
		if (!isspace(str[i]) && (!ispunct(str[i])))
		{
			slovo += str[i];
		}
		else
		{
			if (slovo.size() != 0)
			{
				slova.push_back(slovo);
				slovo = "";
			}
		}
	bool flag = true;
	for (auto& s :slova)
	{
		if (proverka_palindroma(s))
		{
			cout << "Палиндром: " << s << endl;
			flag = false;
		}
	}
	if (flag)
	{
		cout << "Палиндромов нет" << endl;
	}
}
bool proverka_palindroma(string str)
{
	int dlina = str.size();
	for (int i = 0; i < dlina/2; i++)
	{
		if (str[i] != str[dlina - i - 1])
		{
			return false;
		}
	}
	return true;
}
void statistica()
{
	string str;
	cin.ignore();
	int c = 0;
	int d = 0;
	cout << "Введите текст: ";
	getline(cin, str);
	int simvol = str.size();
	for (int i = 1; i < str.size(); i++)
	{
		if (isspace(str[i]))
		{
			c += 1;
		}
		if (isdigit(str[i]))
		{
			d += 1;
		}
	}
	int kolvo_slov = c + 1;
	char target1 = '.';
	char target2 = '!';
	char target3 = '?';
	int count_target1 = count(str.begin(), str.end(), target1);
	int count_target2 = count(str.begin(), str.end(), target2);
	int count_target3 = count(str.begin(), str.end(), target3);
	int predl = count_target1 + count_target2 + count_target3;
	cout << "В тексте: " << endl;
	cout << "Символов: " << simvol << endl;
	cout << "Слов: " << kolvo_slov << endl;
	cout << "Предложений: " << predl << endl;
	cout << "Цифр: " << d << endl;
}
// Блок задача2 конец
// Блок задача3 начало
struct Student
{
	string Name;
	int Age;
	double Sr_ball;
	vector <string> Predmets;
};
vector <Student> Students;
void dobav_student()
{
	string Name;
	int Age;
	double Sr_ball;
	vector <string> Predmets;
	int kol_vo;
	cin.ignore();
	cout << "Введите имя: ";
	getline(cin, Name);
	cout << "Введите возраст: ";
	cin >> Age;
	cout << "Введите средний балл: ";
	cin >> Sr_ball;
	cout << "Введите количество предметов: ";
	cin >> kol_vo;
	cin.ignore();
	for (int i = 0; i < kol_vo; i++)
	{
		cout << "Введите предмет: ";
		string s;
		getline(cin, s);
		Predmets.push_back(s);
	}
	add_student(Name, Age, Sr_ball, Predmets);
}
void add_student(const string Name, const int Age, const double Sr_ball, const vector <string> Predmets)
{
	Student student{ Name, Age, Sr_ball, Predmets };
	Students.push_back(student);
}
void prosmotr()
{
	for (int i = 0; i < size(Students); i++)
	{
		cout << i + 1 << "." << " Студент: " << Students[i].Name << endl;
		cout << "Возраст: " << Students[i].Age << endl;
		cout << "Средний балл: " << Students[i].Sr_ball << endl;
		cout << "Предметы: ";
		for (int j = 0; j < size(Students[i].Predmets); j++)
		{
			cout << Students[i].Predmets[j];
			if (j != size(Students[i].Predmets) - 1)
			{
				cout << ", ";
			}
		}
		cout << endl;
	}
}
void ToFile() 
{
	string filename = "stud4_3.txt";
	ofstream file(filename); 
	if (file.is_open()) 
	{
		for (int i = 0; i < size(Students); i++)
		{
			file << i + 1 << "." << " Студент: " << Students[i].Name << endl;
			file << "Возраст: " << Students[i].Age << endl;
			file << "Средний балл: " << Students[i].Sr_ball << endl;
			file << "Предметы: ";
			for (int j = 0; j < size(Students[i].Predmets); j++)
			{
				file << Students[i].Predmets[j];
				if (j != size(Students[i].Predmets) - 1)
				{
					file << ", ";
				}
			}
			file << endl;
		}
		file.close();
		cout << "Данные успешно записаны в файл: " << filename << endl;
	}
	else 
	{
		cout << "Ошибка: не удалось открыть файл для записи!" << endl;
	}
}
void poisk()
{
	cin.ignore();
	string name;
	cout << "Введите имя: ";
	getline(cin, name);
	bool Flag = true;
	for (int i = 0; i < size(Students); i++)
	{
		if (Students[i].Name == name)
		{
			Flag = false;
			cout << "Студент: " << Students[i].Name << endl;
			cout << "Возраст: " << Students[i].Age << endl;
			cout << "Средний балл: " << Students[i].Sr_ball << endl;
			cout << "Предметы: ";
			for (int j = 0; j < size(Students[i].Predmets); j++)
			{
				cout << Students[i].Predmets[j];
				if (j != size(Students[i].Predmets) - 1)
				{
					cout << ", ";
				}
			}
			cout << endl;
		}
	}
	if (Flag == true)
	{
		cout << "Студент не найден" << endl;
	}
}
void sort_stud()
{
	sort(Students.begin(), Students.end(), [](const Student& a, const Student& b)
		{
			return a.Sr_ball > b.Sr_ball;
		});
	for (int i = 0; i < size(Students); i++)
	{
		cout << Students[i].Name << ": " << Students[i].Sr_ball << endl;
	}
}
void chastotaage()
{
	map < int, int > chastota;
	for (int i = 0; i < size(Students); i++)
	{
		chastota[Students[i].Age] = chastota[Students[i].Age] + 1;
	}
	for (auto& pair : chastota)
	{
		cout << pair.first << ": " << pair.second << endl;
	}
}
void menu_3_1()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "1. Добавить" << endl;
	cout << "2. Просмотреть" << endl;
	cout << "3. Экспорт" << endl;
	cout << "4. Найти" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		dobav_student();
		menu_3_1();
	case 2:
		prosmotr();
		menu_3_1();
	case 3:
		ToFile();
		menu_3_1();
	case 4:
		poisk();
		menu_3_1();
	case 0:
		menu_3();
	default:
		cout << "Такого задания нет!" << endl;
		menu_3();
	}
}
// Блок задача3 конец
// Блок задача4 начало
struct Book
{
	int ID;
	string Title;
	string Author;
	string Janr;
	int Year;
	bool Status_nalich;
};

vector<Book> lib;

void addBook(int ID, const string& Title, const string& Author, const string& Janr, int Year, bool Status_nalich)
{
	Book book{ ID, Title, Author, Janr, Year, Status_nalich };
	lib.push_back(book);
}
void initializeWithSampleData()
{
	addBook(1, "Война и мир", "Лев Толстой", "Роман", 1869, true);
	addBook(2, "Преступление и наказание", "Федор Достоевский", "Роман", 1866, true); 
	addBook(3, "Мастер и Маргарита", "Михаил Булгаков", "Роман", 1967, true); 
	addBook(4, "1984", "Джордж Оруэлл", "Антиутопия", 1949, true); 
	addBook(5, "Анна Каренина", "Лев Толстой", "Роман", 1877, true); 
	cout << "Библиотека инициализирована с начальными данными" << endl;
}
void prosmotr_book()
{
	for (int i = 0; i < size(lib); i++)
	{
		cout << lib[i].ID << ". Название: " << lib[i].Title << ", Автор: " << lib[i].Author <<", Жанр: " << lib[i].Janr << ", Год: " << lib[i].Year << ", Статус: " << lib[i].Status_nalich << endl;
	}
}
void dat_book()
{
	cout << "Какую книгу вы хотите взять? Введите ID: ";
	int ID;
	cin >> ID;
	for (int i = 0; i < size(lib); i++)
	{
		if (lib[i].ID == ID)
		{
			if (lib[i].Status_nalich == false)
			{
				cout << "Книги нет в наличии" << endl;
			}
			else
			{
				lib[i].Status_nalich = false;
				cout << "Книга выдана" << endl;
			}
		}
	}
}
void vernut_book()
{
	cout << "Какую книгу вы хотите вернуть? Введите ID: ";
	int ID;
	cin >> ID;
	for (int i = 0; i < size(lib); i++)
	{
		if (lib[i].ID == ID)
		{
			if (lib[i].Status_nalich == true)
			{
				cout << "Книги итак в наличии" << endl;
			}
			else
			{
				lib[i].Status_nalich = true;
				cout << "Книга принята" << endl;
			}
		}
	}
}
void findBookByTitle()
{
	cin.ignore();
	cout << "Какую книгу вы хотите найти: ";
	string title;
	getline(cin, title);
	bool found = false;
	for (int i = 0; i < size(lib); i++)
	{
		if (lib[i].Title.find(title) != string::npos)
		{
			cout << lib[i].ID << ". Название: " << lib[i].Title << ", Автор: " << lib[i].Author << ", Жанр: " << lib[i].Janr << ", Год: " << lib[i].Year << ", Статус: " << lib[i].Status_nalich << endl;
			found = true;
		}
	}
	if (!found)
	{
		cout << "Книга не найдена" << endl;
	}
}
void findBookByAuthor()
{
	cin.ignore();
	cout << "Книги какого автора вы хотите найти: ";
	string author;
	getline(cin, author);
	bool found = false;
	for (int i = 0; i < size(lib); i++)
	{
		if (lib[i].Title.find(author) != string::npos)
		{
			cout << lib[i].ID << ". Название: " << lib[i].Title << ", Автор: " << lib[i].Author << ", Жанр: " << lib[i].Janr << ", Год: " << lib[i].Year << ", Статус: " << lib[i].Status_nalich << endl;
			found = true;
		}
	}
	if (!found)
	{
		cout << "Книга не найдена" << endl;
	}
}
void findBookByJanr()
{
	cin.ignore();
	cout << "Книги какого жанра вы хотите найти: ";
	string janr;
	getline(cin, janr);
	bool found = false;
	for (int i = 0; i < size(lib); i++)
	{
		if (lib[i].Title.find(janr) != string::npos)
		{
			cout << lib[i].ID << ". Название: " << lib[i].Title << ", Автор: " << lib[i].Author << ", Жанр: " << lib[i].Janr << ", Год: " << lib[i].Year << ", Статус: " << lib[i].Status_nalich << endl;
			found = true;
		}
	}
	if (!found)
	{
		cout << "Книга не найдена" << endl;
	}
}
void stat_book()
{
	map < string, int > statistika_janr;
	map < int, int > statistika_year;
	map < bool, int > statistika_dost;
	for (int i = 0; i < size(lib); i++)
	{
		statistika_janr[lib[i].Janr] = statistika_janr[lib[i].Janr] + 1;
		statistika_year[lib[i].Year] = statistika_year[lib[i].Year] + 1;
		statistika_dost[lib[i].Status_nalich] = statistika_dost[lib[i].Status_nalich] + 1;
	}
	for (auto& pair : statistika_janr)
	{
		cout << pair.first << ": " << pair.second << endl;
	}
	for (auto& pair : statistika_year)
	{
		cout << pair.first << ": " << pair.second << endl;
	}
	for (auto& pair : statistika_dost)
	{
		cout << "Доступность " << pair.first << ": " << pair.second << endl;
	}
}
// Блок задача4 конец
// Блок задача5 начало
struct Card_itog
{
	char znach;
	bool open;
};
vector <vector <Card_itog>> Board(4, vector<Card_itog>(6));
void igra()
{
	vector <char> Card;
	for (int i = 0; i < 12; i++) 
	{
		Card.push_back('A' + i);
		Card.push_back('A' + i);
	}
	mt19937 g(time(0));
	shuffle(Card.begin(), Card.end(), g);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			Board[i][j].znach = Card[i * 6 + j];
			Board[i][j].open = false;
		}
	}
	int count = 0;
	for (int move = 1; move < 100; move++)
	{
		cout << "Ход: " << move << endl;
		print_igr_pole(-1, -1, -1, -1);
		cout << "Введите значение координаты первой карты (сначала по вертикали, а потом по горизантали)" << endl;
		int y1;
		int x1;
		cin >> y1;
		cin >> x1;
		cout << "Введите значение координаты второй карты (сначала по вертикали, а потом по горизантали)" << endl;
		int y2;
		int x2;
		cin >> y2;
		cin >> x2;
		y1--;
		y2--;
		x1--;
		x2--;
		if (y1 < 0 || y1 >= 4 || y2 < 0 || y2 >= 4 || x1 < 0 || x1 >= 6 || x2 < 0 || x2 >= 6)
		{
			cout << "Ошибка" << endl;
			move--;
			continue;
		}
		else 
		{
			if (Board[y1][x1].znach == Board[y2][x2].znach)
			{
				if (Board[y1][x1].open == true)
				{
					cout << "Карта уже открыта" << endl;
					continue;
				}
				else
				{
					Board[y1][x1].open = true;
					Board[y2][x2].open = true;
					count++;
					if (count == 12)
					{
						break;
					}
				}
			}
			print_igr_pole(y1, x1, y2, x2);
		}
		cout << "Нажмите клавишу Enter" << endl;
		cin.ignore(); 
		cin.get();   
		system("cls");

	}
	if (count == 12)
	{
		cout << "Вы выиграли" << endl;
	}
	else
	{
		cout << "Вы проиграли" << endl;
	}
}
void print_igr_pole(int y1, int x1, int y2, int x2)
{
	cout << endl;
	cout << "   1 2 3 4 5 6" << endl;
	cout << "  ------------" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << i + 1 << "| ";
		for (int j = 0; j < 6; j++)
		{
			if ((Board[i][j].open == true) || (i == y1 && j == x1) || (i == y2 && j == x2))
			{
				cout << Board[i][j].znach << " ";
			}
			else
			{
				cout << "* ";
			}
		}
		cout << endl;
	}
}
// Блок задача5 конец
void glavnoemenu()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "Задача 1. Умный анализатор успеваемости" << endl;
	cout << "Задача 2. Текст-шифровальщик" << endl;
	cout << "Задача 3. База данных студентов" << endl;
	cout << "Задача 4. Система управления библиотекой" << endl;
	cout << "Задача 5. Игра на память с динамическими структурами" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		pervau_zadacha();
		glavnoemenu();
	case 2:
		menu_2();
		glavnoemenu();
	case 3:
		menu_3();
		glavnoemenu();
	case 4:
		menu_4();
		glavnoemenu();
	case 5:
		igra();
		glavnoemenu();
	case 0:
		exit(0);
	default:
		cout << "Такого задания нет!" << endl;
		glavnoemenu();
	}
}
void menu_2()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "1. Шифр Цезаря: сдвиг букв на заданное количество позиций" << endl;
	cout << "2. Анализ частоты букв: статистика использования символов в тексте" << endl;
	cout << "3. Поиск палиндромов: автоматическое нахождение слов-перевертышей" << endl;
	cout << "4. Полная статистика текста: символы, слова, предложения, цифры" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		Cezar();
		menu_2();
	case 2:
		chastotabukv();
		menu_2();
	case 3:
		poisk_palindroma();
		menu_2();
	case 4:
		statistica();
		menu_2();
	case 0:
		glavnoemenu();
	default:
		cout << "Такого задания нет!" << endl;
		exit(0);
	}
}
void menu_3_3()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "1. Сортировка по среднему баллу" << endl;
	cout << "2. Статистика по возрастам" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		sort_stud();;
		menu_3_3();
	case 2:
		chastotaage();
		menu_3_3();
	case 0:
		menu_3();
	default:
		cout << "Такого задания нет!" << endl;
		menu_3;
	}
}
void menu_3()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "1. CRUD операции: добавление, просмотр, поиск, экспорт" << endl;
	cout << "2. Статистика: распределение по возрастам, топ студентов" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		menu_3_1();
		menu_3();
	case 2:
		menu_3_3();
		menu_3();
	case 0:
		glavnoemenu();
	default:
		cout << "Такого задания нет!" << endl;
		exit(0);
	}
}
void menu_4()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "1. Инициализировать католог" << endl;
	cout << "2. Полный каталог: книги с авторами, годами, жанрами" << endl;
	cout << "3. Выдать книгу" << endl;
	cout << "4. Вернуть книгу" << endl;
	cout << "5. Поисковая система: по названию" << endl;
	cout << "6. Поисковая система: по автору" << endl;
	cout << "7. Поисковая система: по жанру" << endl;
	cout << "8. Статистика: распределение по жанрам, годам, доступность" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		initializeWithSampleData();
		menu_4();
	case 2:
		prosmotr_book();
		menu_4();
	case 3:
		dat_book();
		menu_4();
	case 4:
		vernut_book();
		menu_4();
	case 5:
		findBookByTitle();
		menu_4();
	case 6:
		findBookByAuthor();
		menu_4();
	case 7:
		findBookByJanr();
		menu_4();
	case 8:
		stat_book();
		menu_4();
	case 0:
		glavnoemenu();
	default:
		cout << "Такого задания нет!" << endl;
		exit(0);
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