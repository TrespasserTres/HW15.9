#pragma once
#include <string>
using namespace std;

#define NAMELENGTH 10  // Зафиксируем длину имени

typedef char UserName[NAMELENGTH]; // тип имя фрукта
typedef char UserPassword[NAMELENGTH]; // тип имя фрукта

class HashTable { // хеш-таблица
public:

    HashTable();
    ~HashTable();
    void add(const UserName us_name, const UserPassword us_pass);
    void del(const UserName us_name);
    char find(const UserName us_name);
    void print();
    void resize();

private:

    enum class enPairStatus
    {
        free, // свободен
        engaged, //занят
        deleted //удален
    };

    struct Pair // пара ключ-значение
    {
        Pair() : // конструктор по умолчанию
            user_name(""),
            user_pass(""),
            status(enPairStatus::free)
        {

        }
        Pair(const UserName us_name, const UserPassword us_pass) : // конструктор копирования
            status(enPairStatus::engaged)
        {
            strcpy_s(user_name, us_name);
            strcpy_s(user_pass, us_pass);
        }
        Pair& operator = (const Pair& other) //  оператор присваивания
        {
            strcpy_s(user_name, other.user_name);
            strcpy_s(user_pass, other.user_pass);
            status = other.status;
            return *this;
        }
        UserName user_name; // имя фрукта (ключ)
        UserPassword user_pass; // количество фрукта (значение)
        enPairStatus status; // состояние ячейки
    };

    int hash_func(const UserName us_name);

    Pair* array;
    int mem_size;
    int count;
};