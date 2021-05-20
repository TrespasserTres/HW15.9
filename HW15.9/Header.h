#pragma once
#include <string>
using namespace std;

#define NAMELENGTH 10  // ����������� ����� �����

typedef char UserName[NAMELENGTH]; // ��� ��� ������
typedef char UserPassword[NAMELENGTH]; // ��� ��� ������

class HashTable { // ���-�������
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
        free, // ��������
        engaged, //�����
        deleted //������
    };

    struct Pair // ���� ����-��������
    {
        Pair() : // ����������� �� ���������
            user_name(""),
            user_pass(""),
            status(enPairStatus::free)
        {

        }
        Pair(const UserName us_name, const UserPassword us_pass) : // ����������� �����������
            status(enPairStatus::engaged)
        {
            strcpy_s(user_name, us_name);
            strcpy_s(user_pass, us_pass);
        }
        Pair& operator = (const Pair& other) //  �������� ������������
        {
            strcpy_s(user_name, other.user_name);
            strcpy_s(user_pass, other.user_pass);
            status = other.status;
            return *this;
        }
        UserName user_name; // ��� ������ (����)
        UserPassword user_pass; // ���������� ������ (��������)
        enPairStatus status; // ��������� ������
    };

    int hash_func(const UserName us_name);

    Pair* array;
    int mem_size;
    int count;
};