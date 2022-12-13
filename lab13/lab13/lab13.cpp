#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>

class HashTable
{
    int capacity;
    std::list<std::vector<char>>* table; 
    std::vector<int> keys; 

public:
    HashTable(int value);
    void insertItem(int key, std::vector<char> data); // вставка объекта
    int search(std::string text); // поиск объекта

    int checkPrime(int n) // проверка числа на простоту
    {
        int i;
        if (n == 1 || n == 0)
        {
            return 0;
        }
        for (i = 2; i < n / 2; i++)
        {
            if (n % i == 0)
            {
                return 0;
            }
        }
        return 1;
    }

    int getprime(int n)
    {
        if (n % 2 == 0)
        {
            n++;
        }
        while (!checkPrime(n))
        {
            n += 2;
        }
        return n;
    }

    int hashFunction(int key) // хэш функция для определения индекса по ключу
    {
        return (key % capacity);
    }
    void displayHash();
};

HashTable::HashTable(int c)
{
    int size = getprime(c); // получаем ближайшее простое число из c (чтобы размер был оптимальным)
    this -> capacity = size;
    table = new std::list<std::vector<char>>[capacity]; // создаем таблицу полученного размера
}

void HashTable::insertItem(int key, std::vector<char> data) // вставка данных в таблицу
{
    int i = hashFunction(key); // находим индекс по ключу
    std::vector<int>::iterator find = std::find(keys.begin(), keys.end(), i); // производим поиск найденного индекса
    if (find == keys.end()) // если индекс не найден
        keys.push_back(i); // добавляем новый индекс, совпадающий с i
    table[i].push_back(data); // добавляем данные в хэш-таблицу с индексом i
}

void HashTable::displayHash() // отображение хэш-таблицы
{
    std::list<std::vector<char>>::iterator it = table -> begin();
    for (int i = 0; i < keys.size(); i++) 
    {
        std::cout << "[" << keys[i] << "]"; // выводим ключ

        for (auto j : table[keys[i]]) // выводим данные, соответствующие ключу
        {
            for (auto out : j)
                std::cout << out;
      
            std::cout << ' ';
        }
        std::cout << '\n';
    }
}
int HashTable::search(std::string text) // поиск в хэш-таблице
{
    std::vector<char> value;
    for (int i = 0; i <= text.size(); i++) 
    {
        if ((int)text[i] != 0) 
            value.push_back(text[i]); // заполняем вектор value имеющимися символами
    }

    int temp = 0, res = 0;
    for (char i : value) 
        temp += (int)i;
    int index = hashFunction(temp); // находим индекс по ключу temp

    for (auto i : table[index])  // производим поиск необходимого индекса
    {
        if (i == value) // и проверяем данные в нем, ищем необходимые объекты
            res++;
    }
    return res; // возвращаем кол-во совпавших объектов с данным объектом на проверку 
}
int main()
{
    std::string txt;
    std::vector<char> word = {};
    int forkey = 0;
    HashTable hash(12345);

    std::getline(std::cin, txt); // получаем данные на вход

    for (int i = 0; i <= txt.size(); i++) 
    {
        if (txt[i] != ' ' && (int)txt[i] != 0) // находим отдельный объект (разделяются пробелом)
        {
            forkey += (int)txt[i]; // сохраняем данные для нахождения ключа
            word.push_back(txt[i]); 
        }
        else 
        {
            hash.insertItem(hash.hashFunction(forkey), word); // т.к. конец "объекта" => вносим его в хэш-таблицу
            word.clear();
            forkey = 0;
        }
    }

    std::cout << "The number of given objects is ";
    std::cout << hash.search("hello") << std::endl; // поиск кол-ва раз, когда встречается элемент "hello" в хэш-таблице
    std::cout << "The hash table: " << '\n';
    hash.displayHash(); // вывод всей хэш-таблицы
}