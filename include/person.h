/**
* person.h
* avl agaci uygulamasi
* 1.ogretim yaz okulu B grubu
* 2.odev(Final)
* 31/08/2020
* Bugrahan Erk Vural s191210241
*/

#ifndef PERSON_H_
#define PERSON_H_

#include "avltree.h"

class Person {
private:
	string name; 
	string birthD;
	string weight;

	int currentYear = 2020;

public:
	string personFull;
	int age;

	// public fonksyonlari
	void getName(string n); 
	void getDate(string n);
	void getWeight(string n);

	void setAge();
	void setFull();
};
#endif