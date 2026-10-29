#include <iostream>
#include <string>
#define  _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <map>
#include <thread>
#include <chrono>
#include <conio.h>
void glavnoemenu();
using namespace std;
void zadacha1()
{
	srand(time(0));
	int dlina = 0;
	string simv;
	string parol;
	string abc;
	string vbr = "Да";
	int count = 0;
	while (vbr == "Да")
	{
		cout << "Какой длины вам нужен пароль? (6 - 32): ";
		cin >> dlina;
		while (dlina < 6 || dlina > 32)
		{
			cout << "Ошибка!" << endl;
			return;
		}
		cin.ignore();
		while (size(abc) == 0)
		{
			cout << "Выбор типов символов (цифры, прописные буквы, строчные буквы, спецсимволы). Введите через пробел: ";
			getline(cin, simv);
			if (simv.find("цифры") != string::npos)
			{
				count++;
				abc += "0123456789";
			}
			if (simv.find("прописные") != string::npos)
			{
				count++;
				abc += "ЙЦУКЕНГШЩЗХЪЁФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";
			}
			if (simv.find("строчные") != string::npos)
			{
				count++;
				abc += "йцукенгшщзхъёфывапролджэячсмитьбю";
			}
			if (simv.find("спецсимволы") != string::npos)
			{
				count++;
				abc += "!@#$%^&*()_+-=[]{}|;:,.<>?";
			}
			if (size(abc) == 0)
			{
				cout << "Ошибка! Не выбран ни один тип символов" << endl;
			}
		}
		for (int i = 0; i < dlina; i++)
		{
			int s = rand() % abc.size();
			parol += abc[s];
		}
		abc = "";
		simv = "";
		cout << "Сгенерированный пароль: " << parol << endl;
		if (count == 4)
		{
			cout << "Пароль сильный" << endl;
		}
		else if (count == 2 || count == 3)
		{
			cout << "Пароль средний" << endl;
		}
		else
		{
			cout << "Пароль слабый" << endl;
		}
		cout << "Хотите сгенерировать еще один пароль?: ";
		getline(cin, vbr);
	}
}
void zadacha2()
{
	cin.ignore();
	string text;
	int countpr = 0;
	int max_sl = 0;
	string minn_sl;
	string prov_s;
	string maxx_sl;
	int count_pred = 0;
	cout << "Введите ваш текст (до 1000 символов): ";
	getline(cin, text);
	if (size(text) > 1000)
	{
		cout << "Сильно много символов" << endl;
		return;
	}
	int kolvo_simv = size(text);
	for (char c : text)
	{
		if (c == '.' || c == '?' || c == '!')
		{
			count_pred++;
		}
		if (isspace(c))
		{
			countpr++;
		}
	}
	for (int i = 0; i <= size(text); i++)
	{
		if (!isspace(text[i]) && text[i] != '!' && text[i] != '?' && text[i] != '.' && text[i] != ',')
		{
			prov_s += text[i];
			if (size(prov_s) > max_sl)
			{
				max_sl = size(prov_s);
				maxx_sl = prov_s;
			}
		}
		else
		{
			prov_s = "";
		}
	}
	int min_sl = 1001;
	for (int i = 0; i <= size(text); i++)
	{
		if (i == size(text) || isspace(text[i]) || text[i] == '!' || text[i] == '?' || text[i] == '.' || text[i] == ',')
		{
			if (!prov_s.empty() && size(prov_s) < min_sl)
			{
				min_sl = size(prov_s);
				minn_sl = prov_s;
			}
			prov_s = "";
		}
		else
		{
			prov_s += text[i];
		}
	}
	map<char, int> letterCount;
	for (char c : text)
	{
		c = tolower(c);
		if ((c >= 'а' && c <= 'я') || c == 'ё')
		{
			letterCount[c]++;
		}
	}
	string palindrom_pr = "";
	for (char c : text)
	{
		c = tolower(c);
		if ((c >= 'а' && c <= 'я') || c == 'ё')
		{
			palindrom_pr += c;
		}
	}
	bool Palindrom = true;
	if (size(palindrom_pr) > 0)
	{
		for (int i = 0; i < size(palindrom_pr) / 2; i++)
		{
			if (palindrom_pr[i] != palindrom_pr[size(palindrom_pr) - 1 - i])
			{
				Palindrom = false;
				break;
			}
		}
		if (Palindrom)
		{
			cout << "Текст палиндром" << endl;
		}
		else
		{
			cout << "Текст не палиндром" << endl;
		}
	}
	int kolvo_simv_no_prob = kolvo_simv - countpr;
	cout << "Символов: " << kolvo_simv << endl;
	cout << "Символов без пробелов: " << kolvo_simv_no_prob << endl;
	cout << "Слов: " << countpr + 1 << endl;
	cout << "Предложений: " << count_pred << endl;
	cout << "Самое длинное слово: " << maxx_sl << ". Букв: " << max_sl << endl;
	cout << "Самое короткое слово: " << minn_sl << ". Букв: " << min_sl << endl;
	cout << "Частота использования букв:" << endl;
	for (auto& pair : letterCount)
	{
		cout << pair.first << ": " << pair.second << endl;
	}
}
int summ = 10000;
void zadacha3()
{
	int count = 0;
	while (count < 10)
	{
		int snaut_nal = 0;
		int num = 0;
		int popoln = 0;
		cout << "-----------------------------------------------------" << endl;
		cout << "1. Проверка баланса" << endl;
		cout << "2. Cнятие наличных" << endl;
		cout << "3. Пополнение счета" << endl;
		cout << "0. Выход" << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "Введите номер: ";
		cin >> num;
		switch (num)
		{
		case 1:
			cout << "Баланс: " << summ << endl;
			count++;
			break;
		case 2:
			cout << "Какую сумму вы хотите снять? ";
			cin >> snaut_nal;
			if (snaut_nal > 5000 || summ < snaut_nal)
			{
				cout << "Сильно много" << endl;
				return;
			}
			else
			{
				summ = summ - snaut_nal;
				cout << "Баланс: " << summ << endl;
				count++;
			}
			break;
		case 3:
			cout << "Введите сумму поплнения: ";
			cin >> popoln;
			summ = summ + popoln;
			cout << "Баланс: " << summ << endl;
			count++;
			break;
		case 0:
			glavnoemenu();
		default:
			cout << "Такого задания нет!" << endl;
			zadacha3();
		}
	}
	if (count == 10)
	{
		cout << "Превышено количество операций" << endl;
		return;
	}
}
void zadacha4()
{
	string povtor = "Да";
	int vbr = 0;
	int count_pobed = 0;
	int count_nich = 0;
	int count_porog = 0;
	while (povtor == "Да")
	{
		cout << "Выбор пользователя (камень (1), ножницы (2), бумага (3)): ";
		cin >> vbr;
		int komp = rand() % 3 + 1;
		cout << komp << endl;
		if (vbr == 1)
		{
			if (komp == 3)
			{
				cout << "Вы проиграли" << endl;
				count_porog++;
			}
			else if (komp == 2)
			{
				cout << "Вы выиграли" << endl;
				count_pobed++;
			}
			else
			{
				cout << "Ничья" << endl;
				count_nich++;
			}
		}
		if (vbr == 2)
		{
			if (komp == 3)
			{
				cout << "Вы выиграли" << endl;
				count_pobed++;
			}
			else if (komp == 2)
			{
				cout << "Ничья" << endl;
				count_nich++;
			}
			else
			{
				cout << "Вы проиграли" << endl;
				count_porog++;
			}
		}
		if (vbr == 3)
		{
			if (komp == 1)
			{
				cout << "Вы выиграли" << endl;
				count_pobed++;
			}
			else if (komp == 3)
			{
				cout << "Ничья" << endl;
				count_nich++;
			}
			else
			{
				cout << "Вы проиграли" << endl;
				count_porog++;
			}
		}
		cout << "Вы хотите сыграть еще раз?: ";
		cin >> povtor;
	}
	cout << "Итоговый счет" << endl;
	cout << "Побед: " << count_pobed << endl;
	cout << "Ничьих: " << count_nich << endl;
	cout << "Поражений: " << count_porog << endl;
}
void zadacha5()
{
	string abc = "0123456789ABCDEF";
	string chislo;
	int ishod = 0;
	string itog_cel;
	string itog_drob;
	long long celaya = 0;
	long long drob_chisl = 0;
	int cel = 0;
	cout << "Введите число: ";
	cin >> chislo;
	cout << "Введите исходную систему счисления: ";
	cin >> ishod;
	for (char i : chislo)
	{
		if (i == '.')
		{
			continue;
		}
		if (abc.find(toupper(i)) == string::npos)
		{
			cout << "Ошибка! Недопустимый символ" << endl;
			return;
		}
		int digit_value = abc.find(toupper(i));
		if (digit_value >= ishod)
		{
			cout << "Ошибка! Цифра недопустима в системе" << endl;
			return;
		}
	}
	cout << "Введите целевую систему счисления: ";
	cin >> cel;
	string drob_str = "";
	celaya = stoll(chislo.substr(0, chislo.find('.')), nullptr, ishod);
	drob_chisl = 0;
	long long drob_znam = 1;
	int poz = chislo.find('.');
	if (poz == string::npos)
	{
		drob_str = "";
	}
	else
	{
		drob_str = chislo.substr(chislo.find('.') + 1);
	}
	for (char c : drob_str)
	{
		int digit;
		if (c <= '9')
		{
			digit = c - '0';
		}
		else
		{
			digit = toupper(c) - 'A' + 10;
		}
		drob_chisl = drob_chisl * ishod + digit;
		drob_znam *= ishod;
	}
	if (celaya == 0)
	{
		itog_cel = "0";
	}
	else
	{
		while (celaya > 0)
		{
			int ostatok = celaya % cel;
			if (ostatok < 10)
			{
				itog_cel += to_string(ostatok);
			}
			else
			{
				itog_cel += char('A' + (ostatok - 10));
			}
			celaya = celaya / cel;
		}
		reverse(itog_cel.begin(), itog_cel.end());
	}
	if (drob_chisl > 0)
	{
		itog_drob = ".";
		for (int i = 0; i < 10; i++)
		{
			drob_chisl *= cel;
			long long tsifra = drob_chisl / drob_znam;
			drob_chisl = drob_chisl % drob_znam;

			if (tsifra < 10)
				itog_drob += to_string(tsifra);
			else
				itog_drob += char('A' + (tsifra - 10));

			if (drob_chisl == 0) break;
		}
	}
	cout << "Результат: " << itog_cel << itog_drob << endl;
}
void prost_t()
{
	int sec;
	cout << "Установите время в секундах (от 10 до 3600): ";
	cin >> sec;
	if (sec < 10 || sec > 3600)
	{
		cout << "Ошибка!" << endl;
		return;
	}
	bool stop = false;
	cout << "Нажмите пробел для паузы/продолжения" << endl;
	for (int i = 0; i < sec;)
	{
		if (_kbhit() && _getch() == ' ')
		{
			stop = !stop;
			if (stop)
			{
				cout << "Пауза" << endl;
			}
			else
			{
				cout << "Продолжение" << endl;
			}
		}
		if (!stop)
		{
			cout << "Осталось: " << sec - i << " сек" << flush;
			if (i == sec / 10)
			{
				cout << " Прошло 10% времени";
			}
			if (i == sec / 4)
			{
				cout << " Прошло 25% времени";
			}
			if (i == sec / 2)
			{
				cout << " Прошло 50% времени";
			}
			cout << endl;
			i++;
			this_thread::sleep_for(chrono::seconds(1));
		}
	}

	cout << "Время вышло" << endl;
}
void int_t()
{
	int sec;
	cout << "Установите время в секундах (от 10 до 3600): ";
	cin >> sec;
	if (sec < 10 || sec > 3600)
	{
		cout << "Ошибка!" << endl;
		return;
	}
	int count = 0;
	int raz;
	cout << "Сколько раз повторить таймер: ";
	cin >> raz;
	bool stop = false;
	cout << "Нажмите пробел для паузы/продолжения" << endl;
	while (count < raz)
	{
		for (int i = 0; i < sec;)
		{
			if (_kbhit() && _getch() == ' ')
			{
				stop = !stop;
				if (stop)
				{
					cout << "Пауза" << endl;
				}
				else
				{
					cout << "Продолжение" << endl;
				}
			}
			if (!stop)
			{
				cout << "Осталось: " << sec - i << " сек" << flush;
				if (i == sec / 10)
				{
					cout << " Прошло 10% времени";
				}
				if (i == sec / 4)
				{
					cout << " Прошло 25% времени";
				}
				if (i == sec / 2)
				{
					cout << " Прошло 50% времени";
				}
				cout << endl;
				i++;
				this_thread::sleep_for(chrono::seconds(1));
			}
		}
		cout << "Время вышло" << endl;
		count++;
		stop = true;
		if (count != raz)
		{
			cout << "Нажмите пробел, чтобы возобновить таймер" << endl;
		}
	}
}
void zadacha6()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "1. Простой таймер" << endl;
	cout << "2. Интервальный таймер" << endl;
	cout << "0. Выход" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Введите номер: ";
	cin >> num;
	switch (num)
	{
	case 1:
		prost_t();
		zadacha6();
	case 2:
		int_t();
		glavnoemenu();
	case 0:
		glavnoemenu();
	default:
		cout << "Такого задания нет!" << endl;
		zadacha6();
	}
}
void glavnoemenu()
{
	int num = 0;
	cout << "-----------------------------------------------------" << endl;
	cout << "Задача 1. Генератор случайных паролей" << endl;
	cout << "Задача 2. Анализатор текста " << endl;
	cout << "Задача 3. Симулятор банкомата" << endl;
	cout << "Задача 4. Игра Камень, ножницы, бумага" << endl;
	cout << "Задача 5. Конвертер систем счисления" << endl;
	cout << "Задача 6. Таймер обратного отсчета с уведомлениями" << endl;
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
	case 4:
		zadacha4();
		glavnoemenu();
	case 5:
		zadacha5();
		glavnoemenu();
	case 6:
		zadacha6();
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