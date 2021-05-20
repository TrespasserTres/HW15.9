#include "Header.h"
#include<iostream>
#include <cstring>
using namespace std;

HashTable::HashTable()
{
    count = 0;
    mem_size = 10;
    array = new Pair[mem_size];
}

HashTable::~HashTable()
{
    delete[] array;
}

int HashTable::hash_func(const UserName us_name)
{
    int sum = 0, i = 0;    // вычисляем индекс
    for (; i < strlen(us_name); i++)
    {
        sum += us_name[i];
    }
    double A = 0.618033;

    // проба
    return mem_size * fmod(sum * A, 1);
}

void HashTable::add(const UserName us_name, const UserPassword us_pass)
{
    int index = -1, i = 0;    // берем пробы по всем i от 0 до размера массива
    for (;i < mem_size; i++)
    {
        index = hash_func(us_name);
        if (array[index].status != enPairStatus::engaged)            // найдена пустая ячейка, занимаем ее
        {
            break;
        }
    }
    if (i >= mem_size)
    {
        resize(); // не нашли места делаем ресайз и снова добавляем
        add(us_name, us_pass);
    }
    else
    {
        array[index] = Pair(us_name, us_pass);
        count++;
    }
}

char HashTable::find(const UserName us_name)
{
    cout << "find " << us_name << endl;

    for (int i = 0;i < mem_size; i++)
    {
        int index = hash_func(us_name);
        if (array[index].status == enPairStatus::engaged &&
            !strcmp(array[index].user_name, us_name))
        {
            cout << "was finded " << endl;
        }
        else if (array[index].status == enPairStatus::free)
        {
            cout << "wasn't finded " << endl;
            return -1;
        }
    }
    return -1;
}

void HashTable::del(const UserName us_name)
{
    cout << "del " << us_name << endl;
    int index = -1, i = 0;                    // берем пробы по всем i от 0 до размера массива
    for (;i < mem_size; i++)
    {
        index = hash_func(us_name);
        if (array[index].status == enPairStatus::engaged &&
            !strcmp(array[index].user_name, us_name))
        {
            array[index].status = enPairStatus::deleted;
            count--;
            cout << "deleted " << index << endl;
            return;
        }
        else if (array[index].status == enPairStatus::free)
        {
            cout << "failed delete " << us_name << endl;
            return;
        }
    }
}

void HashTable::print()
{
    cout << "priting" << endl;
    for (int i = 0;i < mem_size; i++)
    {
        if (array[i].status == enPairStatus::engaged)
            cout << "index" << i << ": " << array[i].user_name << " " << array[i].user_pass << endl;
    }
}

void HashTable::resize()
{
    Pair* oldArray = array; // запоминаем старый массив
    int oldSize = mem_size;
    mem_size *= 2;  // увеличиваем размер в два раза   
    count = 0; // обнуляем количество элементов
    array = new Pair[mem_size]; // выделяем новую память
    for (int i = 0; i < oldSize; i++)
    {
        Pair current = oldArray[i];
        if (current.status == enPairStatus::engaged)
            add(current.user_name, current.user_pass);
    }
    // чистим за собой
    delete[] oldArray;
}
