#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <locale>
#include <unordered_map>
using namespace std;
struct Book
{
    char* title;
    char* author;
    int year;
};
struct Library
{
    Book* books;
    int count;
    int capacity;
};
void operacii();
void istoriav();
void addistor(int a, int b, char znak, int c);
void obmen_znach();
void menucalc();
void max_min();
void perevernut(char* str);
void poiskpalindroma();
void poiskanagramm();
void reversestr(char* str);
void itogrevers();
int countslov(string str);
void kolvoslow();
bool isLetter(char s);
void dlinnoeslovo();
void chiststroka();
void menustroki();
void matrica();
char* createString(const char* source);
void menubook();
void freeLibrary(Library* lib);
void printAllBooks(const Library* lib);
void findBookByAuthor(const Library* lib, const char* author);
void findBookByTitle(const Library* lib, const char* title);
void addBook(Library* lib, const char* title, const char* author, int year);
void resizeLibrary(Library* lib, int newCapacity);
void initLibrary(Library* lib, int initialCapacity);
void freeString(char* str);
Library myLibrary;

void studentu()
{
    srand(time(0));
    setlocale(LC_ALL, "rus");
    int student[15];
    double summ = 0;
    float sredball = 0;
    int typ = 0;
    int otl = 0;
    int count2 = 0;
    int count3 = 0;
    int count4 = 0;
    int count5 = 0;
    double protl = 0;
    int maxcount = count2;
    int moda = 2;
    cout << "Оценки: ";
    for (int i = 0; i <= 14; i++)
    {
        int x = rand() % 4 + 2;
        student[i] = x;
        cout << student[i] << " ";
        summ += student[i];
        if (student[i] < 3)
        {
            typ += 1;
        }
        if (student[i] == 5)
        {
            otl += 1;
            count5 += 1;
        }
        if (student[i] == 4)
        {
            count4 += 1;
        }
        if (student[i] == 3)
        {
            count3 += 1;
        }
        if (student[i] == 2)
        {
            count2 += 1;
        }
    }
    if (count3 > maxcount)
    {
        maxcount = count3;
        moda = 3;
    }
    if (count4 > maxcount)
    {
        maxcount = count4;
        moda = 4;
    }
    if (count5 > maxcount)
    {
        maxcount = count5;
        moda = 5;
    }
    sredball = summ / 15;

    protl = (static_cast<double>(otl)) / 15 * 100;

    cout << " " << endl;
    cout << "Средний балл: " << sredball << endl;
    cout << "Количество неуспевающих: " << typ << endl;
    cout << "Процент отличников: " << protl << endl;
    cout << "Cамая частая оценка (мода): " << moda << endl;
}
int plus1(int* a, int* b)
{
    return *a + *b;
}
int mines(int* a, int* b)
{
    return *a - *b;
}
int ymnog(int* a, int* b)
{
    return *a * *b;
}
int del(int* a, int* b)
{
    return *a / *b;
}
void menu_obmen_znach(int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}
void obmen_znach()
{
    cout << "Введите первое значение: ";
    int a = 0;
    cin >> a;
    cout << "Введите второе значение: ";
    int b = 0;
    cin >> b;
    menu_obmen_znach(&a, &b);
    cout << "Первое значение после обмена: " << a << endl;
    cout << "Второе значение после обмена: " << b << endl;
}
void operacii()
{
    cout << "Введите первое число: ";
    int a = 0;
    cin >> a;
    cout << "Введите второе число: ";
    int b = 0;
    cin >> b;
    cout << "Введите арифметическую операцую (+, -, *, /): ";
    char znak;
    cin >> znak;
    if (znak == '+')
    {
        int c = plus1(&a, &b);
        cout << "Результат: " << c << endl;
        addistor(a, b, znak, c);
    }
    else if (znak == '-')
    {
        int c = mines(&a, &b);
        cout << "Результат: " << c << endl;
        addistor(a, b, znak, c);
    }
    else if (znak == '*')
    {
        int c = ymnog(&a, &b);
        cout << "Результат: " << c << endl;
        addistor(a, b, znak, c);
    }
    else if (znak == '/' && a != 0 && b != 0)
    {
        int c = del(&a, &b);
        cout << "Результат: " << c << endl;
        addistor(a, b, znak, c);
    }
    else { cout << "Ошибка" << endl; }
}
string istor[5];
int ist_count = 0;
void addistor(int a, int b, char znak, int c)
{
    string S = to_string(a) + " " + znak + " " + to_string(b) + " = " + to_string(c);
    if (ist_count < 5)
    {
        ist_count++;
    }
    for (int i = 4; i > 0; i--)
    {
        istor[i] = istor[i - 1];
    }
    istor[0] = S;
}
void istoriav()
{
    for (int i = 0; i < ist_count; i++)
    {
        cout << i + 1 << ". " << istor[i] << endl;
    }
}
void max_min()
{
    int maxmin[10];
    srand(time(0));
    int* minn;
    int* maxx;
    for (int i = 0; i < 10; i++)
    {
        int x = rand() % 100;
        maxmin[i] = x;
    }
    for (int i = 0; i < 10; i++)
    {
        cout << maxmin[i] << " ";
    }
    cout << " " << endl;
    minn = &(maxmin[0]);
    maxx = &(maxmin[0]);

    for (int i = 1; i < 10; i++)
    {
        if (maxmin[i] < *minn) minn = &(maxmin[i]);
        if (maxmin[i] > *maxx) maxx = &(maxmin[i]);
    }
    cout << "Минимальное значение: " << *minn << endl;
    cout << "Максимальное значение: " << *maxx << endl;
}
void matrica()
{
    int M;
    int N;
    cout << "Введите количество строк: ";
    cin >> M;
    cout << "Введите количество столбцов: ";
    cin >> N;
    int** matrix = new int* [M];
    for (int i = 0; i < M; i++)
    {
        matrix[i] = new int[N];
    }
    srand(time(0));
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = rand() % 100;
        }
    }
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "-------------------------------------------" << endl;
    int** trans = new int* [N];
    for (int i = 0; i < N; i++)
    {
        trans[i] = new int[M];
    }
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            trans[j][i] = matrix[i][j];
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << trans[i][j] << "\t";
        }
        cout << endl;
    }
    for (int i = 0; i < M; i++)
    {
        int summstr = 0;
        for (int j = 0; j < N; j++)
        {
            summstr += matrix[i][j];
        }
        cout << "Строка " << i << ": " << summstr << endl;
    }
    for (int j = 0; j < N; j++)
    {
        int summstol = 0;
        for (int i = 0; i < M; i++)
        {
            summstol += matrix[i][j];
        }
        cout << "Столбец " << j << ": " << summstol << endl;
    }
    for (int i = 0; i < M; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    for (int i = 0; i < N; i++) {
        delete[] trans[i];
    }
    delete[] trans;
}

void glavnoemenu()
{
    int num = 0;
    cout << "-----------------------------------------------------" << endl;
    cout << "Задача 1. Анализатор успеваемости группы" << endl;
    cout << "Задача 2. Умный калькулятор с историей операций" << endl;
    cout << "Задача 3. Детектор палиндромов и анаграмм" << endl;
    cout << "Задача 4. Транспонирование матрицы произвольного размера" << endl;
    cout << "Задача 5. Система управления библиотекой книг" << endl;
    cout << "0. Выход" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Введите номер: ";
    cin >> num;
    switch (num)
    {
    case 1:
        studentu();
        glavnoemenu();
    case 2:
        menucalc();
        glavnoemenu();
    case 3:
        menustroki();
        glavnoemenu();
    case 4:
        matrica();
        glavnoemenu();
    case 5:
        menubook();
        glavnoemenu();
    case 0:
        exit(0);
    default:
        cout << "Такого задания нет!" << endl;
        glavnoemenu();
    }
}
void menucalc()
{
    int num = 0;
    cout << "-----------------------------------------------------" << endl;
    cout << "1. Выполнить арифметическую операцию" << endl;
    cout << "2. Показать историю операций" << endl;
    cout << "3. Обмен значений двух переменных" << endl;
    cout << "4. Поиск минимального и максимального в массиве" << endl;
    cout << "0. Выход" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Введите номер: ";
    cin >> num;
    switch (num)
    {
    case 1:
        operacii();
        menucalc();
    case 2:
        istoriav();
        menucalc();
    case 3:
        obmen_znach();
        menucalc();
    case 4:
        max_min();
        menucalc();
    case 0:
        glavnoemenu();
    default:
        cout << "Такого задания нет!" << endl;
        menucalc();
    }
}
void perevernut(char* str)
{
    char* start = str;
    char* end = str + strlen(str) - 1;
    while (start < end)
    {
        char c = *start;
        *start = *end;
        *end = c;
        start++;
        end--;
    }
}
char str[100] = "";
void poiskpalindroma()
{
    char str1[100] = "";
    cout << "Введите строку: ";
    cin.ignore();
    cin.getline(str1, 100);
    char str2[100] = "";
    strcpy(str2, str1);
    //cout << "Введите строку: ";
    //cin.ignore();
    //cin.getline(str2, 100);
    perevernut(str1);
    cout << str1 << endl;
    if (strcmp(str1, str2) == 0)
    {
        cout << "Палиндром" << endl;
    }
    else
    {
        cout << "Не палиндром" << endl;
    }
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
string normalst(const string& str)
{
    string result;
    for (char s : str)
    {
        if (!isspace(s))
        {
            result += toLower(s);
        }
    }
    return result;
}
bool Anagramm(const string str1, const string str2)
{
    string s1 = normalst(str1);
    string s2 = normalst(str2);
    if (s1.length() != s2.length())
    {
        return false;
    }
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    return s1 == s2;
}
void poiskanagramm()
{
    cin.ignore();
    cout << "Введите первую строку: ";
    string s1;
    getline(cin, s1);
    cout << "Введите вторую строку: ";
    string s2;
    getline(cin, s2);
    if (Anagramm(s1, s2))
    {
        cout << "Строки являются анаграммами" << endl;
    }
    else
    {
        cout << "Строки не являются анаграммами" << endl;
    }
}
void reversestr(char* str)
{
    if (str == nullptr) return;
    char* start = str;
    char* end = str;
    while (*end != '\0')
    {
        end++;
    }
    end--;
    while (start < end)
    {
        char ptr = *start;
        *start = *end;
        *end = ptr;
        start++;
        end--;
    }
}
void itogrevers()
{
    cin.ignore();
    char text[100];
    cout << "Введите строку: ";
    cin >> text;
    reversestr(text);
    cout << "Перевернутая строка: " << text << endl;
}
int countslov(string str)
{
    int count = 0;
    char s_1 = ' ';
    for (char s : str)
    {
        if isspace(s)&&!isspace(s_1)
        {
            count += 1;
        }
        s_1 = s;
    }
    return count;
}

void kolvoslow()
{
    cin.ignore();
    string str;
    cout << "Введите строку: ";
    getline(cin, str);
    cout << "Количество слов: " << countslov(str) + 1 << endl;
}
bool isLetter(char s)
{
    return (s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= 'а' && s <= 'я') || (s >= 'А' && s <= 'Я') || s == 'ё' || s == 'Ё';
}
void chiststroka()
{
    cin.ignore();
    string str;
    string gotovstr;
    cout << "Введите строку: ";
    getline(cin, str);
    for (char s : str)
    {
        if (isLetter(s))
        {
            gotovstr += s;
        }

    }
    cout << "Итог: " << gotovstr << endl;
}
void dlinnoeslovo()
{
    cin.ignore();
    cout << "Введите строку: ";
    string str;
    getline(cin, str);
    int countsimv = 0;
    int maxx = 0;
    for (char s : str)
    {
        if (isLetter(s))
            countsimv++;
        else
        {
            countsimv = 0;
        }
        if (countsimv >= maxx)
        {
            maxx = countsimv;
        }
    }
    cout << "Самое длинное слово: " << maxx << endl;
}
//struct Book
//{
//    char* title;
//    char* author;
//    int year;
//};
//struct Library
//{
//    Book* books;
//    int count;
//    int capacity;
//};
char* createString(const char* source)
{
    if (source == nullptr) return nullptr;

    char* newString = new char[strlen(source) + 1];
    strcpy(newString, source);
    return newString;
}
void freeString(char* str)
{
    if (str != nullptr)
    {
        delete[] str;
    }
}
void initLibrary(Library* lib, int initialCapacity = 10)
{
    lib->books = new Book[initialCapacity];
    lib->count = 0;
    lib->capacity = initialCapacity;
}
void resizeLibrary(Library* lib, int newCapacity)
{
    Book* newBooks = new Book[newCapacity];
    for (int i = 0; i < lib->count; i++)
    {
        newBooks[i] = lib->books[i];
    }
    delete[] lib->books;
    lib->books = newBooks;
    lib->capacity = newCapacity;
}
void addBook(Library* lib, const char* title, const char* author, int year)
{
    if (lib->count >= lib->capacity)
    {
        resizeLibrary(lib, lib->capacity * 2);
    }
    lib->books[lib->count].title = createString(title);
    lib->books[lib->count].author = createString(author);
    lib->books[lib->count].year = year;
    lib->count++;
    cout << "Книга добавлена успешно!\n";
}
void findBookByTitle(const Library* lib, const char* title)
{
    bool found = false;
    cout << "Результаты поиска по названию \"" << title << "\":\n";

    for (int i = 0; i < lib->count; i++)
    {
        if (strstr(lib->books[i].title, title) != nullptr)
        {
            cout << "Название: " << lib->books[i].title
                << ", Автор: " << lib->books[i].author
                << ", Год: " << lib->books[i].year << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "Книги не найдены.\n";
    }
}
void findBookByAuthor(const Library* lib, const char* author)
{
    bool found = false;
    cout << "Результаты поиска по автору \"" << author << "\":\n";
    for (int i = 0; i < lib->count; i++)
    {
        if (strstr(lib->books[i].author, author) != nullptr)
        {
            cout << "Название: " << lib->books[i].title
                << ", Автор: " << lib->books[i].author
                << ", Год: " << lib->books[i].year << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Книги не найдены.\n";
    }
}
void printBooksByAuthor(const Library* lib, const char* author)
{
    bool found = false;
    cout << "Книги автора " << author << ":\n";
    for (int i = 0; i < lib->count; i++)
    {
        if (strcmp(lib->books[i].author, author) == 0)
        {
            cout << "Название: " << lib->books[i].title
                << ", Год: " << lib->books[i].year << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "Книги не найдены.\n";
    }
}
void removeBook(Library* lib, const char* title, const char* author)
{
    for (int i = 0; i < lib->count; i++)
    {
        if (strcmp(lib->books[i].title, title) == 0 && strcmp(lib->books[i].author, author) == 0)
        {
            freeString(lib->books[i].title);
            freeString(lib->books[i].author);
            for (int j = i; j < lib->count - 1; j++)
            {
                lib->books[j] = lib->books[j + 1];
            }
            lib->count--;
            cout << "Книга удалена успешно!\n";
            return;
        }
    }
    cout << "Книга не найдена.\n";
}
void sortBooksByYear(Library* lib)
{
    for (int i = 0; i < lib->count - 1; i++)
    {
        for (int j = 0; j < lib->count - i - 1; j++)
        {
            if (lib->books[j].year > lib->books[j + 1].year)
            {
                Book temp = lib->books[j];
                lib->books[j] = lib->books[j + 1];
                lib->books[j + 1] = temp;
            }
        }
    }
    cout << "Книги отсортированы по году издания.\n";
}
void printAllBooks(const Library* lib)
{
    if (lib->count == 0)
    {
        cout << "Библиотека пуста.\n";
        return;
    }
    cout << "Все книги в библиотеке:\n";
    for (int i = 0; i < lib->count; i++)
    {
        cout << i + 1 << ". Название: " << lib->books[i].title << ", Автор: " << lib->books[i].author << ", Год: " << lib->books[i].year << endl;
    }
}
void freeLibrary(Library* lib)
{
    for (int i = 0; i < lib->count; i++)
    {
        freeString(lib->books[i].title);
        freeString(lib->books[i].author);
    }
    delete[] lib->books;
    lib->count = 0;
    lib->capacity = 0;
    cout << "Память освобождена.\n";
}
void initializeWithSampleData(Library* lib)
{
    addBook(lib, "Война и мир", "Лев Толстой", 1869);
    addBook(lib, "Преступление и наказание", "Федор Достоевский", 1866);
    addBook(lib, "Мастер и Маргарита", "Михаил Булгаков", 1967);
    addBook(lib, "1984", "Джордж Оруэлл", 1949);
    addBook(lib, "Анна Каренина", "Лев Толстой", 1877);
    cout << "Библиотека инициализирована с начальными данными.\n\n";
}
void menubook()
{
    int num;
    char title[100], author[100];
    int year;
    //Library myLibrary;
    cout << "\n=== Система управления библиотекой ===\n";
    cout << "1. Добавить книгу\n";
    cout << "2. Найти книгу по названию\n";
    cout << "3. Найти книгу по автору\n";
    cout << "4. Показать все книги автора\n";
    cout << "5. Удалить книгу\n";
    cout << "6. Сортировать книги по году\n";
    cout << "7. Показать все книги\n";
    cout << "0. Выйти\n";
    cout << "Выберите действие: ";
    cin >> num;
    cin.ignore();

    switch (num)
    {
    case 1:
        cout << "Введите название книги: ";
        cin.getline(title, 100);
        cout << "Введите автора: ";
        cin.getline(author, 100);
        cout << "Введите год издания: ";
        cin >> year;
        cin.ignore();
        addBook(&myLibrary, title, author, year);
        menubook();

    case 2:
        cout << "Введите название для поиска: ";
        cin.getline(title, 100);
        findBookByTitle(&myLibrary, title);
        menubook();

    case 3:
        cout << "Введите автора для поиска: ";
        cin.getline(author, 100);
        findBookByAuthor(&myLibrary, author);
        menubook();

    case 4:
        cout << "Введите автора: ";
        cin.getline(author, 100);
        printBooksByAuthor(&myLibrary, author);
        menubook();

    case 5:
        cout << "Введите название книги для удаления: ";
        cin.getline(title, 100);
        cout << "Введите автора книги: ";
        cin.getline(author, 100);
        removeBook(&myLibrary, title, author);
        menubook();

    case 6:
        sortBooksByYear(&myLibrary);
        menubook();

    case 7:
        printAllBooks(&myLibrary);
        menubook();

    case 0:
        cout << "Выход из программы...\n";
        glavnoemenu();

    default:
        cout << "Неверный выбор. Попробуйте снова.\n";
        menubook();
    }
}
void menustroki()
{
    int num = 0;
    cout << "-----------------------------------------------------" << endl;
    cout << "1. Проверить на палиндром" << endl;
    cout << "2. Проверить две строки на анаграммы" << endl;
    cout << "3. Реверс строки" << endl;
    cout << "4. Подсчитать количество слов" << endl;
    cout << "5. Найти самое длинное слово" << endl;
    cout << "6. Очистить строку от не-буквенных символов" << endl;
    cout << "0. Выход" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Введите номер: ";
    cin >> num;
    switch (num)
    {
    case 1:
        poiskpalindroma();
        menustroki();
    case 2:
        poiskanagramm();
        menustroki();
    case 3:
        itogrevers();
        menustroki();
    case 4:
        kolvoslow();
        menustroki();
    case 5:
        dlinnoeslovo();
        menustroki();
    case 6:
        chiststroka();
        menustroki();
    case 0:
        glavnoemenu();
    default:
        cout << "Такого задания нет!" << endl;
        menustroki();
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    //Library myLibrary;
    initLibrary(&myLibrary);
    initializeWithSampleData(&myLibrary);
    //freeLibrary(&myLibrary);
    glavnoemenu();
    freeLibrary(&myLibrary);
    return 0;
}













