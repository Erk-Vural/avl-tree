/**
* avltree.cpp
* avl agaci uygulamasi
* 1.ogretim yaz okulu B grubu
* 2.odev(Final)
* 31/08/2020
* Bugrahan Erk Vural s191210241
*/

#include "avltree.h"

void avltree::updateheight(node* n)
//Dugum yukseklikgini sag ve sol cocugun 
//yuksekliklerinin dogru oldugu farz edilerek hesapliyoruz
// n dugumunun yuksekligi uzun cocugun 1 fazlasidir
{
    // n'in Null olmadigindan emin olmak icin
    if (n == NULL) return;

    // cocuklarin biri ya da ikiside Null olabilir
    if ((!n->left) && (!n->right)) {
        n->height = 0;
        n->balance = 0;
    }
    else if (!n->left) {
        n->height = n->right->height + 1;
        n->balance = 1;
    }
    else if (!n->right) {
        n->height = n->left->height + 1;
        n->balance = -1;
    }
    // iki cocukta varsa 
    else {
        n->height = n->left->height + 1;
        if (n->height <= n->right->height)
            n->height = n->right->height + 1;
        //n->balance = n->right->height - n->left->height;
    }
}

bool avltree::insert(int k, string d, node*& n)
// yeni dugum agaca eklenir eger ekleme basariliysa 
// checkrotation cagirilir gerekli duzenlemeler yapilir 
{
    // Agacin sonuna gelinirse direk ekle
    if (!n) {
        n = new node;
        if (!n) return false;
        n->data = d;
        n->key = k;
        n->left = NULL;
        n->right = NULL;
        n->height = 0;
        n->balance = 0;
        return true;
        n->mystack.push('O');
    }

    // tekrarli donguyle sag veya sol agacta dogru yer aralir
    if (n->key > k) {
        if (insert(k, d, n->left)) {
            checkrotation(n->left);
            return true;
        }
    }
    else {
        if (insert(k, d, n->right)) {
            checkrotation(n->right);
            return true;
        }
    }

    // ekleme basarisiz
    return false;
}

//postorder olarak agac ekrana yazdirilir
void avltree::postorder(node* n)
{
    if (!n) return;
    postorder(n->left);
    postorder(n->right);
    cout << n->data << "  " << "Yigit: ";
    while (!n->mystack.empty()) {
        cout << ' ' << n->mystack.top();
        n->mystack.pop();
    }
    cout << endl;
}

void avltree::debugprint(node* n)
// pre order olarak baglantilari gosteren cikti
{
    if (!n) return;
    cout << n->key << ":" << n->data << " (";
    if (n->left) cout << n->left->key;
    else cout << "NULL";
    cout << "<-left,right->";
    if (n->right) cout << n->right->key;
    else cout << "NULL";
    cout << ")(height:" << n->height << ", balance: ";
    cout << n->balance << ")" << endl;
    debugprint(n->left);
    debugprint(n->right);
}

void avltree::rotateleft(node*& n)
// n in sag cocugu yukari cikar, n asagi iner
//sag cocugun sol cocugu n 'e baglanir

{
    node* tmp = n;         // n 'i sakla
    n = n->right;          // sag cocugu agacin koku ata
    tmp->right = n->left; // sag cocugun sol cocugunu n' e bagla
    n->left = tmp;         //  n 'i sag cocugun sol cocugu yap
    tmp->mystack.push('A');  //n 'in stack 'ine asagi indigi icin A ekle
    n->mystack.push('Y');     //sag cocugun stack 'ine yukari indigi icin Y ekle
    updateheight(tmp);     // n in yuksekligini kontrol et
    updateheight(n);       // sag cocugun yuksekligini kontrol et
}

void avltree::rotateright(node*& n)
// n in sol cocugu yukari cikar, n asagi iner
//sol cocugun sag cocugu n 'e baglanir

{
    node* tmp = n;         // n 'i sakla
    n = n->left;           // sol cocugu agacin koku ata
    tmp->left = n->right;  // sol cocugun sag cocugunu n' e bagla
    n->right = tmp;        //  n 'i sol cocugun sag cocugu yap
    tmp->mystack.push('A');  //n 'in stack 'ine asagi indigi icin A ekle
    n->mystack.push('Y');    //sol cocugun stack 'ine yukari indigi icin Y ekle
    updateheight(tmp);     // n in yuksekligini kontrol et
    updateheight(n);       // sol cocugun yuksekligini kontrol et
}

void avltree::checkrotation(node*& n)
// n 'e bagli alt agaclarin yuksekliklerini kontrol et
// eger balance 'de dengesizlik varsa duzelt
{
    if (n == NULL) return;

    // height ve balance kontrol edilir
    updateheight(n);

    // n dengedeyse cik
    if (n->balance == 0) {
        return;
    }
   
    // Eger n ve sag cocugu pozitifse n 'i sola cevir
    if ((n->balance > 0) && (n->right->balance > 0))
        rotateleft(n);

    // Eger n ve sol cocugu negatifse n 'i saga cevir
    else if ((n->balance < 0) && (n->left->balance < 0))
        rotateright(n);

    // Eger n negatif sol cocugu pozitif dengedeyse
    // n 'in sol cocugunu sola cevir, n 'i saga cevir
    else if ((n->balance < 0) && (n->left->balance > 0)) {
        rotateleft(n->left);
        rotateright(n);
    }

    // Eger n pozitif sag cocugu negatif dengedeyse
    // n 'in sag cocugunu saga cevir, n 'i sola cevir
    else if ((n->balance > 0) && (n->right->balance < 0)) {
        rotateright(n->right);
        rotateleft(n);
    }
}

bool avltree::insert(int k, string d)
//listede gezip insert icin dogru yeri ara
//k anahtari siralama icin 
//d data yazdirirken gorucez
//eklemeden sonra yukari cikip guncelleme gerekli mi kontrol edilir
{

    node* itrnode = root;
    node* prevnode = NULL;

    //dugumu yerlestirmek icin dogru yeri ara
    while (itrnode != NULL) {
        //Eger yeni anahtar daha kucukse sola git
        if (itrnode->key > k) {
            prevnode = itrnode;
            itrnode = itrnode->left;
            if (itrnode) {
                itrnode->lastvisit = prevnode; //last visited 'i guncelle
            }
                
        }
        else {
            //saga git
            prevnode = itrnode;
            itrnode = itrnode->right;
            if (itrnode)
                itrnode->lastvisit = prevnode; //last visited 'i guncelle
        }
    } //yeni dugum icin dogru yer bulundu
    itrnode = prevnode;

    //yeni dugum yarat
    node* n = new node;
    if (!n) return false;
    n->data = d;
    n->key = k;
    n->left = NULL;
    n->right = NULL;
    n->height = 0;
    n->balance = 0;
    n->lastvisit = NULL;
    n->mystack.push('O');//yeni dugum icin stack' e 'O' ekle

    //yeni dugumu yerlestir
    if (root == NULL) {
        root = n;
        return true;
    }
    if (itrnode->key > k)
        itrnode->left = n;
    else
        itrnode->right = n;

    node* tmp = NULL;
    
    //agacin ustlerine dogru ilerleyip guncelleme gereklimi kontol et
    while (itrnode->lastvisit != NULL) {
        tmp = itrnode->lastvisit; //last visit dugumunu sakla
        itrnode->lastvisit = NULL; 
        itrnode = tmp; //last visited dugume yuksel

        //geldigimiz dugumu guncelle
        if (itrnode->key > k) { //Sol dugumden geldik
            updateheight(itrnode->left);
            checkrotation(itrnode->left);
            itrnode->mystack.push('D');
        }
        else if(itrnode->key < k) { //Sag dugumden geldik
            updateheight(itrnode->right);
            checkrotation(itrnode->right);
            itrnode->mystack.push('D');
        }
    }
    //root u guncelle
    updateheight(root);
    checkrotation(root);

    return true;
}


