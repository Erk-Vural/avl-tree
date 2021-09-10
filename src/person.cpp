/**
* person.cpp
* avl agaci uygulamasi
* 1.ogretim yaz okulu B grubu
* 2.odev(Final)
* 31/08/2020
* Bugrahan Erk Vural s191210241
*/

#include "person.h"

//Bilgi alma fonksyonlari
void Person::getName(string n)
{
	name = n;
}

void Person::getDate(string n)
{
	birthD = n;
	setAge();
}

void Person::getWeight(string n)
{
	weight = n;
}

void Person::setAge()
{
	age = currentYear - stoi(birthD);
}

//Dugume Data olarak kaydetmek icin butun bilgiler birlestirildi
void Person::setFull()
{
	personFull = name + " " + birthD + " " + weight;
}
