/**
* avltree.h 
* avl agaci uygulamasi 
* 1.ogretim yaz okulu B grubu
* 2.odev(Final) 
* 31/08/2020
* Bugrahan Erk Vural s191210241
*/

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <string>
#include <iostream>
#include <stack> 
using namespace std;

class avltree {
private:
    struct node {
        node* right, * left;
        node* lastvisit; // Son ziyaret edilen dugum(kontrollerde kullanilacak)
        string data;
        stack<char> mystack;
        int key;
        int         height, balance;
    };
    //Agac kokunu saklayan giden bir pointer 
    node* root;

    // private fonksiyonlari
    bool insert(int k, string d, node*& n);
    void postorder(node* n);
    void debugprint(node* n);
    void rotateleft(node*& n);
    void rotateright(node*& n);
    void checkrotation(node*& n);
    void updateheight(node* n);

public:
    // public method'lari
    bool insert(int k, string d);
    avltree() { root = NULL; }
    void display() { postorder(root); }
    void debug() { debugprint(root); }    
};

#endif
