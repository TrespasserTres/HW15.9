#include "Header.h"
#include<iostream>
#include <string>
using namespace std;

int main()
{
	HashTable a;
	a.add("Firs", "Pas1");
	a.add("Second", "Pas2");
	a.add("Third", "Pas3");
	a.add("Fourth", "Pas4");
	a.add("Fifth", "Pas5");
	a.add("Sixth", "Pas6");
	a.print();
	a.del("Second");
	a.print();
	a.add("Second", "Pas2");
	a.print();
	a.find("nine");
	return 0;
}