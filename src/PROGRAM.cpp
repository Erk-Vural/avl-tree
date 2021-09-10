/**
* PROGRAM.cpp
* avl agaci uygulamasi
* 1.ogretim yaz okulu B grubu
* 2.odev(Final)
* 31/08/2020
* Bugrahan Erk Vural s191210241
*/

#include "avltree.h"
#include "person.h"
#include <fstream>
#include <sstream>

int main() {
	avltree* T = new avltree; //Yeni avl agaci
	Person* personList = new Person[64]; //Bilgi kayitlari icin obje listesi olusturuldu
	
	int count = 0;//dosyadaki satir sayisi icin sayac
	
	string getPerson;
	ifstream myFile;
	myFile.open("kisiler.txt");
	
	while (getline(myFile, getPerson)) { //yeni satir al
			stringstream iss(getPerson);

			for (int j = 1; j <= 3 && getline(iss, getPerson, '#'); j++) {//objelere bilgileri al
				if (j == 1) { personList[count].getName(getPerson); }
				if (j == 2) { personList[count].getDate(getPerson); }
				if (j == 3) { personList[count].getWeight(getPerson); }
			}
			personList[count].setFull();
			getPerson.clear();

			T->insert(personList[count].age, personList[count].personFull);//agaca yeni kisiyi ekle

			count++;
	}
	
	//Agacin yazdirilmasi
	T->debug();
	cout << endl;
	T->display();

	//Agac ve objeler destructor'lar 
	delete[] personList;
	delete T;
	return 0;
}

