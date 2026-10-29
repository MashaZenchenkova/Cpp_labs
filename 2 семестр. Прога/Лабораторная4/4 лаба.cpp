#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
using namespace std;
class Tile;
class Creature
{
private:
    static int nextId;
    int id;
    string vid;
    int health;
    int havka;
    int age;
    int maxage;
    int speed;
    int sila;
    int razmnog;
    string foodtype;
    bool isAlive;
    Tile* mesto;
    int x;
    int y;
    int mapSize;
public:
    Creature(string vid, int maxage, int speed, int sila, int razmnog, string foodtype, int x, int y, int mapSize) : id(nextId++), vid(vid), health(100), havka(100), age(0), maxage(maxage), speed(speed), sila(sila), razmnog(razmnog), foodtype(foodtype), isAlive(true), mesto(nullptr), x(x), y(y), mapSize(mapSize)
    {}
    virtual ~Creature() {}
    int getId() const { return id; }
    string getvid() const { return vid; }
    int gethealth() const { return health; }
    int gethavka() const { return havka; }
    int getage() const { return age; }
    int getmaxage() const { return maxage; }
    int getspeed() const { return speed; }
    int getsila() const { return sila; }
    int getrazmnog() const { return razmnog; }
    string getfoodtype() const { return foodtype; }
    bool getisAlive() const { return isAlive; }
    Tile* getTile() { return  mesto; }
    int getX() const { return x; }
    int getY() const { return y; }
    int getMapSize() const { return mapSize; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void moveTo(Tile* newTile);
    void setTile(Tile* tile);
    void setsila(int s)
    {
        sila = s;
        if (sila < 1) 
        {
            sila = 1;
        }
        else if (s > 100)
        {
            sila = 100;
        }
    }
    void setHealth(int h)
    {
        if (h <= 0)
        {
            health = 0;
            isAlive = false;
        }
        else if (h > 100)
        {
            health = 100;
        }
        else
        {
            health = h;
        }
    }
    void setHavka(int h)
    {
        if (h < 0)
        {
            havka = 0;
        }
        else if (h > 100)
        {
            havka = 100;
        }
        else
        {
            havka = h;
        }
    }
    void setAge(int a)
    {
        age = a;
        if (age >= maxage)
        {
            isAlive = false;
        }
    }
    void setRazmnog(int s)
    {
        razmnog = s;
        if (razmnog > 100)
        {
            razmnog = 100;
        }
        if (razmnog < 0)
        {
            razmnog = 0;
        }
    }
    virtual void move() = 0;
    virtual void reprazmnog() = 0;
    virtual void goda() = 0;
    virtual void golod() = 0;
    virtual void eat(Tile* tile) = 0;
    virtual void printInfo() const
    {
        cout << "ID: " << id << endl;
        cout << "Вид: " << vid << endl;
        cout << "Здоровье: " << health << "/100" << endl;
        cout << "Сытость: " << havka << "/100" << endl;
        cout << "Возраст: " << age << "/" << maxage << endl;
        cout << "Скорость: " << speed << endl;
        cout << "Сила: " << sila << endl;
        cout << "Плодовитость: " << razmnog << "%" << endl;
        cout << "Тип питания: " << foodtype << endl;
        cout << "Жив: " << (isAlive ? "Да" : "Нет") << endl;
        cout << "Позиция: (" << x+1 << "," << y+1 << ")" << endl;
    }
};
int Creature::nextId = 1;
class Tile
{
private:
    string type_mest;
    int x;
    int y;
    vector <Creature*> creatures;
    int plants;
public:
    Tile(int x, int y, string t) : x(x), y(y), type_mest(t)
    {
        if (type_mest == "forest" || type_mest == "field" || type_mest == "desert")
        {
            plants = 100;
        }
    }
    char gettype_mest() const
    {
        if (type_mest == "forest") return 'F';
        if (type_mest == "field") return 'P';
        if (type_mest == "desert") return 'D';
        if (type_mest == "water") return 'W';
        if (type_mest == "mountain") return 'M';
        return '?';
    }
    vector<Creature*>& getCreatures() { return creatures; }
    void addCreature(Creature* c)
    {
        creatures.push_back(c);
        c->setTile(this);
    }
    void removeCreature(Creature* c)
    {
        auto it = find(creatures.begin(), creatures.end(), c);
        if (it != creatures.end())
            creatures.erase(it);
    }
    int getx() { return x; }
    int gety() { return y; }
    int getPlants() { return plants; }
    void setPlants()
    {
        plants = 0;
    }
};
void Creature::moveTo(Tile* newTile)
{
    if (mesto)
    {
        mesto->removeCreature(this);
    }
    mesto = newTile;
    newTile->addCreature(this);
    x = newTile->getx();
    y = newTile->gety();
}
void Creature::setTile(Tile* tile)
{
    mesto = tile;
    if (tile)
    {
        x = tile->getx();
        y = tile->gety();
    }
}
class Herbivore : public Creature
{
public:
    Herbivore(string name, int x, int y, int mapSize) : Creature(name, 20, 3, 2, 10, "Травоядный", x, y, mapSize)
    {}
    void reprazmnog() override;
    void goda() override;
    void golod() override;
    void move() override;
    void eat(Tile* tile) override;
};
class Predator : public Creature
{
private:
    bool isHungry;
public:
    Predator(string name, int x, int y, int mapSize) : Creature(name, 30, 5, 10, 20, "Хищник", x, y, mapSize)
    {}
    void reprazmnog() override;
    void goda() override;
    void golod() override;
    void move() override;
    void eat(Tile* tile) override;
};
class Omnivore : public Creature
{
private:
    bool isHungry;
public:
    Omnivore(string name, int x, int y, int mapSize) : Creature(name, 25, 7, 8, 20, "Всеядное", x, y, mapSize)
    {}
    void reprazmnog() override;
    void goda() override;
    void golod() override;
    void move() override;
    void eat(Tile* tile) override;
};
class map
{
private:
    vector <vector <Tile*>> grid;
    int size;
    vector<Creature*> allCreatures;
public:
    int getSize() const { return size; }
    void add_creature()
    {
        int vbr;
        string name;
        int x, y;
        cout << "Выберите тип существа (1 - Травоядное, 2 - Хищник, 3 - Всеядное): ";
        cin >> vbr;
        cin.ignore();
        cout << "Введите название животного: ";
        getline(cin, name);
        cout << "Введите координаты (x y) от 1 до " << size << ": ";
        cin >> x >> y;
        x--;
        y--;
        if (x < 0 || x >= size || y < 0 || y >= size)
        {
            cout << "Ошибка: координаты вне карты!" << endl;
            return;
        }
        Creature* newCreature = nullptr;
        switch (vbr)
        {
        case 1:
            newCreature = new Herbivore(name, x, y, size);
            cout << "Создано травоядное: " << name << endl;
            break;
        case 2:
            newCreature = new Predator(name, x, y, size);
            cout << "Создан хищник: " << name << endl;
            break;
        case 3:
            newCreature = new Omnivore(name, x, y, size);
            cout << "Создано всеядное: " << name << endl;
            break;
        default:
            cout << "Ало!" << endl;
            return;
        }
        if (newCreature)
        {
            allCreatures.push_back(newCreature);
            grid[x][y]->addCreature(newCreature);
            cout << "Существо добавлено на клетку (" << x + 1 << "," << y + 1 << ")" << endl;
        }
    }
    void porazmnog()
    {
        if (allCreatures.empty())
        {
            cout << "Вместо них хочется, да?" << endl;
            return;
        }
        string name;
        cout << "Введите имя существа для размножения: ";
        cin.ignore();
        getline(cin, name);
        int type;
        cout << "Выберите тип питания (1-Травоядное, 2-Хищник, 3-Всеядное): ";
        cin >> type;
        string foodType;
        if (type == 1)
        {
            foodType = "Травоядный";
        }
        else if (type == 2)
        {
            foodType = "Хищник";
        }
        else if (type == 3)
        {
            foodType = "Всеядное";
        }
        else
        {
            cout << "Вместо них хочется, да?" << endl;
            return;
        }
        bool found = false;
        for (Creature* c : allCreatures)
        {
            if (c->getisAlive() && c->getvid() == name && c->getfoodtype() == foodType)
            {
                c->reprazmnog();
                found = true;
                break;  
            }
        }
        if (!found)
        {
            cout << "Существо не найдено!" << endl;
            return;
        }
        allCreatures.clear();
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (Creature* cr : grid[i][j]->getCreatures())
                {
                    allCreatures.push_back(cr);
                }
            }
        }
        cout << "Успешно" << endl;
    }
    void pokushat()
    {
        if (size == 0)
        {
            cout << "Карта не создана!" << endl;
            return;
        }
        if (allCreatures.empty())
        {
            cout << "На карте нет существ!" << endl;
            return;
        }
        cout << "Существа на карте:" << endl;
        for (Creature* c : allCreatures)
        {
            if (c->getisAlive())
            {
                cout << "  " << c->getvid() << " (" << c->getfoodtype() << ") сытость: " << c->gethavka() << "/100" << endl;
            }
        }
        string name;
        cout << "Введите имя существа, которое будет кушать: ";
        cin.ignore();
        getline(cin, name);
        int type;
        cout << "Выберите тип питания существа:" << endl;
        cout << "1 - Травоядное" << endl;
        cout << "2 - Хищник" << endl;
        cout << "3 - Всеядное" << endl;
        cout << "Ваш выбор: ";
        cin >> type;
        string foodType;
        if (type == 1)
        {
            foodType = "Травоядный";
        }
        else if (type == 2)
        {
            foodType = "Хищник";
        }
        else if (type == 3)
        {
            foodType = "Всеядное";
        }
        else
        {
            cout << "Неверный выбор!" << endl;
            return;
        }
        Creature* target = nullptr;
        for (Creature* c : allCreatures)
        {
            if (c->getisAlive() && c->getvid() == name && c->getfoodtype() == foodType)
            {
                target = c;
                break;
            }
        }
        if (target == nullptr)
        {
            cout << "Существо с именем '" << name << "' и типом '" << foodType << "' не найдено!" << endl;
            return;
        }
        Tile* currentTile = target->getTile();
        if (!currentTile)
        {
            cout << "Ошибка: существо не на карте!" << endl;
            return;
        }
        target->golod();
        target->eat(currentTile);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                auto& tile = grid[i][j]->getCreatures();
                for (auto it = tile.begin(); it != tile.end();)
                {
                    if (!(*it)->getisAlive())
                    {
                        delete* it;
                        it = tile.erase(it);
                    }
                    else ++it;
                }
            }
        }
        allCreatures.clear();
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (Creature* c : grid[i][j]->getCreatures())
                {
                    allCreatures.push_back(c);
                }
            }
        }
        cout << "Приём пищи завершён!" << endl;
    }
    void sled_god()
    {
        for (Creature* c : allCreatures)
        {
            if (c->getisAlive())
            {
                c->setAge(c->getage() + 1);
                c->setHavka(5);
                c->setRazmnog(100);
            }
        }
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                auto& tile = grid[i][j]->getCreatures();
                for (auto it = tile.begin(); it != tile.end();)
                {
                    if (!(*it)->getisAlive())
                    {
                        delete* it;
                        it = tile.erase(it);
                    }
                    else ++it;
                }
            }
        }
        allCreatures.clear();
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (Creature* c : grid[i][j]->getCreatures())
                {
                    allCreatures.push_back(c);
                }
            }
        }
    }
    void pokhodit()
    {
        if (size == 0)
        {
            cout << "Карта не создана!" << endl;
            return;
        }
        if (allCreatures.empty())
        {
            cout << "На карте нет существ!" << endl;
            return;
        }
        vector<Creature*> creaturesCopy = allCreatures;
        for (Creature* c : creaturesCopy)
        {
            if (c->getisAlive())
            {
                int oldX = c->getX();
                int oldY = c->getY();
                c->move();
                int newX = c->getX();
                int newY = c->getY();
                Tile* newTile = grid[newX][newY];
                c->moveTo(newTile);
                cout << c->getvid() << " переместился с (" << oldX + 1 << "," << oldY + 1 << ") на (" << newX + 1 << "," << newY + 1 << ")" << endl;
            }
        }
        allCreatures.clear();
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (Creature* c : grid[i][j]->getCreatures())
                {
                    allCreatures.push_back(c);
                }
            }
        }
    }
    void delete_creature()
    {
        if (size == 0)
        {
            cout << "Карта не создана!" << endl;
            return;
        }
        if (allCreatures.empty())
        {
            cout << "На карте нет существ!" << endl;
            return;
        }
        cout << "Существа на карте:" << endl;
        for (Creature* c : allCreatures)
        {
            if (c->getisAlive())
            {
                cout << c->getvid() << " (" << c->getfoodtype() << ")" << endl;
            }
        }
        string name;
        cout << "Кого удалить: ";
        cin.ignore();
        getline(cin, name);
        int type;
        cout << "Выберите тип питания существа:" << endl;
        cout << "1 - Травоядное" << endl;
        cout << "2 - Хищник" << endl;
        cout << "3 - Всеядное" << endl;
        cout << "Ваш выбор: ";
        cin >> type;
        string foodType;
        if (type == 1)
        {
            foodType = "Травоядный";
        }
        else if (type == 2)
        {
            foodType = "Хищник";
        }
        else if (type == 3)
        {
            foodType = "Всеядное";
        }
        else
        {
            cout << "Удались сам, пожалуйста" << endl;
            return;
        }
        Creature* target = nullptr;
        for (Creature* c : allCreatures)
        {
            if (c->getisAlive() && c->getvid() == name && c->getfoodtype() == foodType)
            {
                target = c;
                break;
            }
        }
        if (target == nullptr)
        {
            cout << "Такого нет" << endl;
            return;
        }
        Tile* tile = target->getTile();
        if (tile)
        {
            tile->removeCreature(target);
        }
        auto it = find(allCreatures.begin(), allCreatures.end(), target);
        if (it != allCreatures.end())
        {
            allCreatures.erase(it);
        }
        delete target;
        cout << "Успешно" << endl;
        allCreatures.clear();
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (Creature* c : grid[i][j]->getCreatures())
                {
                    allCreatures.push_back(c);
                }
            }
        }
    }
    void sozd_map()
    {
        cout << "Введите размерность игрового поля: ";
        cin >> size;
        grid.resize(size, vector<Tile*>(size));
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                string types[] = { "forest", "field", "desert", "water", "mountain" };
                grid[i][j] = new Tile(i, j, types[rand() % 5]);
            }
        }
    }
    void display()
    {
        cout << "\n    ";
        for (int j = 0; j < size; j++)
        {
            cout << j + 1 << "    "; 
        }
        cout << endl << endl;
        for (int i = 0; i < size; i++)
        {
            cout << i + 1 << "   ";
            for (int j = 0; j < size; j++)
            {
                cout << grid[i][j]->gettype_mest();
                vector<Creature*>& creatures = grid[i][j]->getCreatures();
                if (!creatures.empty())
                {
                    string name = creatures[0]->getvid();
                    cout << "-" << name.substr(0, 1); 
                    if (creatures.size() > 1)
                    {
                        cout << "+";
                    }
                    cout << "   "; 
                }
                else
                {
                    cout << "    ";  
                }
            }
            cout << endl << endl; 
        }
        cout << "F - лес, P - поле, D - пустыня, W - вода, M - горы" << endl;
        if (!allCreatures.empty())
        {
            cout << "Существа на карте:" << endl;
            for (Creature* c : allCreatures)
            {
                if (c->getisAlive())
                {
                    c->printInfo();
                    cout << "------------------------" << endl;
                }
            }
        }
    }
    void save_to_csv()
    {
        if (size == 0)
        {
            cout << "Карта не создана!" << endl;
            return;
        }
        string filename = "живность.csv";
        ofstream file(filename);
        if (!file.is_open())
        {
            cout << "Ошибка" << endl;
            return;
        }
        file << "Size," << size << endl << endl;
        file << "Map (F-лес, P-поле, D-пустыня, W-вода, M-горы)" << endl;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                file << grid[i][j]->gettype_mest();
                if (j < size - 1) file << ",";
            }
            file << endl;
        }
        file << endl;
        file << "Creatures" << endl;
        file << "ID,Name,Type,Health,Hunger,Age,MaxAge,Speed,Strength,Fertility,X,Y,Alive" << endl;
        for (Creature* c : allCreatures)
        {
            file << c->getId() << "," << c->getvid() << "," << c->getfoodtype() << "," << c->gethealth() << "," << c->gethavka() << "," << c->getage() << "," << c->getmaxage() << "," << c->getspeed() << "," << c->getsila() << "," << c->getrazmnog() << "," << c->getX() + 1 << "," << c->getY() + 1 << "," << (c->getisAlive() ? "Yes" : "No") << endl;
        }
        file.close();
        cout << "Успешно" << endl;
    }
    void load_from_csv()
    {
        for (auto& row : grid)
        {
            for (auto& tile : row)
            {
                delete tile;
            }
        }
        grid.clear();
        for (Creature* c : allCreatures)
        {
            delete c;
        }
        allCreatures.clear();
        string filename = "живность.csv";
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Ошибка при открытии файла " << filename << "!" << endl;
            return;
        }
        string line;
        getline(file, line);
        size = stoi(line.substr(5));
        getline(file, line);
        getline(file, line);
        grid.resize(size, vector<Tile*>(size));
        for (int i = 0; i < size; i++)
        {
            getline(file, line);
            stringstream ss(line);
            string cell;
            int j = 0;
            while (getline(ss, cell, ','))
            {
                string type;
                if (cell == "F") type = "forest";
                else if (cell == "P") type = "field";
                else if (cell == "D") type = "desert";
                else if (cell == "W") type = "water";
                else if (cell == "M") type = "mountain";
                grid[i][j] = new Tile(i, j, type);
                j++;
            }
        }
        while (getline(file, line))
        {
            if (line == "Creatures") break;
        }
        getline(file, line);
        while (getline(file, line))
        {
            stringstream ss(line);
            string field;
            vector<string> fields;
            while (getline(ss, field, ','))
            {
                fields.push_back(field);
            }
            if (fields.size() < 13) continue;
            int id = stoi(fields[0]);
            string name = fields[1];
            string type = fields[2];
            int health = stoi(fields[3]);
            int havka = stoi(fields[4]);
            int age = stoi(fields[5]);
            int maxage = stoi(fields[6]);
            int speed = stoi(fields[7]);
            int sila = stoi(fields[8]);
            int razmnog = stoi(fields[9]);
            int x = stoi(fields[10]) - 1;
            int y = stoi(fields[11]) - 1;
            bool isAlive = (fields[12] == "Yes");
            if (!isAlive) continue;
            Creature* creature = nullptr;
            if (type == "Травоядный")
            {
                creature = new Herbivore(name, x, y, size);
            }
            else if (type == "Хищник")
            {
                creature = new Predator(name, x, y, size);
            }
            else if (type == "Всеядное")
            {
                creature = new Omnivore(name, x, y, size);
            }
            if (creature)
            {
                creature->setHealth(health);
                creature->setHavka(havka);
                creature->setAge(age);
                creature->setRazmnog(razmnog);
                allCreatures.push_back(creature);
                grid[x][y]->addCreature(creature);
            }
        }
        file.close();
        cout << "Успешно" << endl;
    }
    ~map()
    {
        for (auto& row : grid)
            for (auto& tile : row)
                delete tile;
    }
};
void Herbivore::reprazmnog()
{
    if (getrazmnog() <= 50)
    {
        cout << "Еще рано" << endl;
        return;
    }
    Tile* currentTile = getTile();
    if (!currentTile)
    {
        return;
    }
    for (Creature* partner : currentTile->getCreatures())
    {
        if (partner != this && partner->getisAlive() && partner->getrazmnog() > 50)
        {
            cout << getvid() << " размножился с " << partner->getvid() << endl;
            string babyName = getvid() + "x" + partner->getvid();
            Creature* baby = nullptr;
            int randomType = rand() % 3 + 1;
            int avgSila = (getsila() + partner->getsila()) / 2 + (rand() % 50 + 1);

            switch (randomType)
            {
            case 1:
                baby = new Herbivore(babyName, getX(), getY(), getMapSize());
                cout << "Родился травоядный: " << babyName << " (сила: " << avgSila << ")" << endl;
                break;
            case 2:
                baby = new Predator(babyName, getX(), getY(), getMapSize());
                cout << "Родился хищник: " << babyName << " (сила: " << avgSila << ")" << endl;
                break;
            case 3:
                baby = new Omnivore(babyName, getX(), getY(), getMapSize());
                cout << "Родился всеядный: " << babyName << " (сила: " << avgSila << ")" << endl;
                break;
            }
            if (baby)
            {
                currentTile->addCreature(baby);
                baby->setHealth(100);
                baby->setHavka(67);
                baby->setRazmnog(0);
                baby->setsila(avgSila);
            }
            setRazmnog(0);
            partner->setRazmnog(0);
            break;
        }
    }
}
void Herbivore::goda()
{
    setAge(getage() + 1);
    setRazmnog(100);
}
void Herbivore::golod()
{
    if (gethavka() <= 30)
    {
        setHealth(gethealth() - 10);
    }
}
void Herbivore::move()
{
    bool danger = false;
    if (getTile())
    {
        for (Creature* c : getTile()->getCreatures())
        {
            if (c != this && (c->getfoodtype() == "Хищник" || c->getfoodtype() == "Всеядное"))
            {
                danger = true;
                break;
            }
        }
    }
    int dx, dy;
    if (danger)
    {
        dx = (rand() % 3 - 1) * 2;
        dy = (rand() % 3 - 1) * 2;
        cout << getvid() << " убегает от хищника!" << endl;
    }
    else
    {
        dx = rand() % 3 - 1;
        dy = rand() % 3 - 1;
    }
    int newX = (getX() + dx + getMapSize()) % getMapSize();
    int newY = (getY() + dy + getMapSize()) % getMapSize();
    setX(newX);
    setY(newY);
}
void Herbivore::eat(Tile* tile)
{
    if (tile->getPlants() > 0)
    {
        setHavka(100);
        setHealth(100);
        tile->setPlants();
    }
}
void Predator::reprazmnog()
{
    if (getrazmnog() <= 60)
    {
        cout << "Еще рано" << endl;
        return;
    }
    Tile* currentTile = getTile();
    if (!currentTile)
    {
        return;
    }
    for (Creature* partner : currentTile->getCreatures())
    {
        if (partner != this && partner->getisAlive() && partner->getrazmnog() > 50)
        {
            cout << getvid() << " размножился с " << partner->getvid() << endl;
            string babyName = getvid() + "x" + partner->getvid();
            Creature* baby = nullptr;
            int randomType = rand() % 3 + 1;
            int avgSila = (getsila() + partner->getsila()) / 2 + (rand() % 50 + 1);

            switch (randomType)
            {
            case 1:
                baby = new Herbivore(babyName, getX(), getY(), getMapSize());
                cout << "Родился травоядный: " << babyName << " (сила: " << avgSila << ")" << endl;
                break;
            case 2:
                baby = new Predator(babyName, getX(), getY(), getMapSize());
                cout << "Родился хищник: " << babyName << " (сила: " << avgSila << ")" << endl;
                break;
            case 3:
                baby = new Omnivore(babyName, getX(), getY(), getMapSize());
                cout << "Родился всеядный: " << babyName << " (сила: " << avgSila << ")" << endl;
                break;
            }
            if (baby)
            {
                currentTile->addCreature(baby);
                baby->setHealth(100);
                baby->setHavka(67);
                baby->setRazmnog(0);
                baby->setsila(avgSila);
            }
            setRazmnog(0);
            partner->setRazmnog(0);
            break;
        }
    }
}
void Predator::goda()
{
    setAge(getage() + 1);
    setRazmnog(10);
}
void Predator::golod()
{
    if (gethavka() <= 30)
    {
        isHungry = true;
        setHealth(gethealth() - 20);
    }
    else
    {
        isHungry = false;
    }
}
void Predator::move()
{
    if (isHungry)
    {
        int dx = (rand() % 3 - 1) * 2; 
        int dy = (rand() % 3 - 1) * 2;
        int newX = (getX() + dx + getMapSize()) % getMapSize();
        int newY = (getY() + dy + getMapSize()) % getMapSize();
        setX(newX);
        setY(newY);
        cout << getvid() << " хочет хавать!" << endl;
    }
    else
    {
        int dx = rand() % 3 - 1;
        int dy = rand() % 3 - 1;
        int newX = (getX() + dx + getMapSize()) % getMapSize();
        int newY = (getY() + dy + getMapSize()) % getMapSize();
        setX(newX);
        setY(newY);
    }
}
void Predator::eat(Tile* tile)
{
    if (isHungry)
    {
        bool ate = false;
        for (Creature* c : tile->getCreatures())
        {
            if (c != this && c->getisAlive() && (c->getfoodtype() == "Травоядный" || c->getfoodtype() == "Всеядное"))
            {
                if (c->getfoodtype() == "Всеядное")
                {
                    if (getsila() > c->getsila())
                    {
                        c->setHealth(0);
                        setHavka(100);
                        setHealth(gethealth() + 30);
                        cout << getvid() << " съел " << c->getvid() << " (победил в схватке!)" << endl;
                        tile->removeCreature(c);
                        ate = true;
                        break;
                    }
                    else
                    {
                        cout << getvid() << " попытался съесть " << c->getvid() << ", но проиграл схватку!" << endl;
                        setHealth(gethealth() - 20);
                        cout << getvid() << " получил 20 урона!" << endl;
                        break;
                    }
                }
                else
                {
                    c->setHealth(0);
                    setHavka(100);
                    setHealth(gethealth() + 30);
                    cout << getvid() << " съел " << c->getvid() << "!" << endl;
                    tile->removeCreature(c);
                    ate = true;
                    break;
                }
            }
        }
        if (!ate)
        {
            cout << getvid() << " не нашёл еды!" << endl;
        }
    }
    else
    {
        cout << "Не хочу" << endl;
    }
}
void Omnivore::reprazmnog()
{
    if (getrazmnog() <= 75)
    {
        cout << "Еще рано" << endl;
        return;
    }
    Tile* currentTile = getTile();
    if (!currentTile)
    {
        return;
    }
    for (Creature* partner : currentTile->getCreatures())
    {
        if (partner != this && partner->getisAlive() && partner->getrazmnog() > 50)
        {
            cout << getvid() << " размножился с " << partner->getvid() << endl;
            string babyName = getvid() + "x" + partner->getvid();
            Creature* baby = nullptr;
            int randomType = rand() % 3 + 1;
            int avgSila = (getsila() + partner->getsila()) / 2 + (rand() % 50 + 1);

            switch (randomType)
            {
            case 1:
                baby = new Herbivore(babyName, getX(), getY(), getMapSize());
                cout << "Родился травоядный: " << babyName << " (сила: " << avgSila << ")" << endl;
                break;
            case 2:
                baby = new Predator(babyName, getX(), getY(), getMapSize());
                cout << "Родился хищник: " << babyName << " (сила: " << avgSila << ")" << endl;
                break;
            case 3:
                baby = new Omnivore(babyName, getX(), getY(), getMapSize());
                cout << "Родился всеядный: " << babyName << " (сила: " << avgSila << ")" << endl;
                break;
            }
            if (baby)
            {
                currentTile->addCreature(baby);
                baby->setHealth(100);
                baby->setHavka(67);
                baby->setRazmnog(0);
                baby->setsila(avgSila);
            }
            setRazmnog(0);
            partner->setRazmnog(0);
            break;
        }
    }
}void Omnivore::goda()
{
    setAge(getage() + 1);
    setRazmnog(10);
}
void Omnivore::golod()
{
    if (gethavka() <= 30)
    {
        isHungry = true;
        setHealth(gethealth() - 5);
    }
    else
    {
        isHungry = false;
    }
}
void Omnivore::move()
{
    int dx = rand() % 3 - 1;
    int dy = rand() % 3 - 1;
    int newX = (getX() + dx + getMapSize()) % getMapSize();
    int newY = (getY() + dy + getMapSize()) % getMapSize();
    setX(newX);
    setY(newY);
}
void Omnivore::eat(Tile* tile)
{
    if (isHungry)
    {
        bool ate = false;
        for (Creature* c : tile->getCreatures())
        {
            if (c != this && c->getisAlive() && c->getfoodtype() == "Травоядный")
            {
                c->setHealth(0);
                setHavka(100);
                setHealth(gethealth() + 30);
                cout << getvid() << " съел " << c->getvid() << "!" << endl;
                tile->removeCreature(c);
                ate = true;
                break;
            }
        }
        if (!ate)
        {
            for (Creature* c : tile->getCreatures())
            {
                if (c != this && c->getisAlive() && c->getfoodtype() == "Хищник")
                {
                    if (getsila() > c->getsila())
                    {
                        c->setHealth(0);
                        setHavka(100);
                        setHealth(gethealth() + 30);
                        cout << getvid() << " съел " << c->getvid() << " (победил в схватке!)" << endl;
                        tile->removeCreature(c);
                        ate = true;
                        break;
                    }
                    else
                    {
                        cout << getvid() << " попытался съесть " << c->getvid() << ", но проиграл схватку!" << endl;
                        setHealth(gethealth() - 20);
                        cout << getvid() << " получил 20 урона!" << endl;
                        break;
                    }
                }
            }
        }
        if (!ate && tile->getPlants() > 0)
        {
            tile->setPlants();
            setHavka(100);
            setHealth(gethealth() + 10);
            cout << getvid() << " съел растения" << endl;
            ate = true;
        }
        if (!ate)
        {
            cout << getvid() << " не нашёл еды!" << endl;
        }
    }
    else
    {
        cout << "Не хочу" << endl;
    }
}
map Map;
void menu_igr()
{
    int num = 0;
    cout << "-----------------------------------------------------" << endl;
    cout << "1. Создать карту" << endl;
    cout << "2. Добавить существо" << endl;
    cout << "3. Показать карту" << endl;
    cout << "4. Поразмножаться" << endl;
    cout << "5. Поесть" << endl;
    cout << "6. Следующий год" << endl;
    cout << "7. Походить" << endl;
    cout << "8. Сохранить симуляцию" << endl;
    cout << "9. Загрузить симуляцию" << endl;
    cout << "10. Удалить существо" << endl;
    cout << "11. Автоматический режим на 5 лет" << endl;
    cout << "0. Выход" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Введите номер: ";
    cin >> num;
    switch (num)
    {
    case 1:
    {
        Map.sozd_map();
        menu_igr();
    }
    case 2:
    {
        if (Map.getSize() == 0)
        {
            cout << "АЛО! Сначала пункт 1!" << endl;
        }
        else
        {
            Map.add_creature();
        }
        menu_igr();
    }
    case 3:
    {
        if (Map.getSize() == 0)
        {
            cout << "АЛО! Сначала пункт 1!" << endl;
        }
        else
        {
            Map.display();
        }
        menu_igr();
    }
    case 4:
    {
        if (Map.getSize() == 0)
        {
            cout << "АЛО! Сначала пункт 1!" << endl;
        }
        else
        {
            Map.porazmnog();
        }
        menu_igr();
    }
    case 5:
    {
        if (Map.getSize() == 0)
        {
            cout << "АЛО! Сначала пункт 1!" << endl;
        }
        else
        {
            Map.pokushat();
        }
        menu_igr();
    }
    case 6:
    {
        if (Map.getSize() == 0)
        {
            cout << "АЛО! Сначала пункт 1!" << endl;
        }
        else
        {
            Map.sled_god();
        }
        menu_igr();
    }
    case 7:
    {
        if (Map.getSize() == 0)
        {
            cout << "АЛО! Сначала пункт 1!" << endl;
        }
        else
        {
            Map.pokhodit();
        }
        menu_igr();
        break;
    }
    case 8:
    {
        if (Map.getSize() == 0)
        {
            cout << "АЛО! Сначала пункт 1!" << endl;
        }
        else
        {
            Map.save_to_csv();
        }
        menu_igr();
        break;
    }
    case 9:
    {
        Map.load_from_csv();
        menu_igr();
        break;
    }
    case 10:
    {
        if (Map.getSize() == 0)
        {
            cout << "АЛО! Сначала пункт 1!" << endl;
        }
        else
        {
            Map.delete_creature();
        }
        menu_igr();
        break;
    }
    case 11:
    {
        if (Map.getSize() == 0)
        {
            cout << "АЛО! Сначала пункт 1!" << endl;
        }
        else
        {
            for (int i = 0; i < 5; i++)
            {
                Map.pokhodit();
                Map.sled_god();
            }
        }
        menu_igr();
        break;
    }
    case 0:
        exit(0);
    default:
        cout << "Такого задания нет!" << endl;
        menu_igr();
    }
}
int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(0));
    menu_igr();
    return 0;
}
