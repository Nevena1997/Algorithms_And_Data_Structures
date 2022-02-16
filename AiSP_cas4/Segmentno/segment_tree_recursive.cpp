#include <iostream>
#include <vector>
#include <cmath>

//using namespace std

//Rekurzivna funkcija koja kreira segmentno stablo segment_tree od niza brojeva array
//k predstavlja poziciju (indeks) cvora unutar segmentnog stabla (tj. niza segment_tree)
//x i y oznacavaju krajeve intervala koje cvor na poziciji k obuhvata, tj. [x, y] predstavlja interval pocetnog niza cija se suma nalazi u cvoru na poziciji k u segmentnom stablu
//Na pocetku je taj interval ceo niz, tj. [0, n - 1], jer izracunavanje pocinjemo od korena
//Interval se polovi kroz rekurzivne pozive tako da levu polovinu obradjuje levo dete, a desnu polovinu desno dete
void build_segment_tree (std::vector<int> &array, std::vector<int> &segment_tree, int k, int x, int y)
{
    //Ukoliko smo dosli do jednoclanog intervala (list u stablu), nema vise polovnjenja intervala pa zavrsavamo rekurziju
    if (x == y) {
        segment_tree[k] = array[x];
        return;
    }

    //Trazimo sredinu intervala [x, y] da bismo znali koji interval pokriva levo dete, a koji interval pokriva desno dete
    int middle = (x + y) / 2;

    //Ukoliko se koren segmentnog stabla nalazi na pozicji 1, tj ukoliko pozicija 0 ostaje nepopunjena, tada vazi
    //da se levo dete cvora na poziciji k nalazi na poziciji 2 * k i da se desno dete cvora na poziciji k nalazi na poziciji 2 * k + 1
    //Rekurzivno racunamo vrednosti levog i desnog deteta
    //Levo dete cvora k ce pokrivati segment [x, middle], a desno dete cvora k ce pokrivati segmen [middle + 1, y]
    build_segment_tree(array, segment_tree, 2 * k, x, middle);
    build_segment_tree(array, segment_tree, 2 * k + 1, middle + 1, y);

    //Nakon sto smo kreirali oba sina, potrebno je odrediti koji broj se cuva u ocu, a to je zbir brojeva potomaka
    //Ukoliko ne bismo imali ovu liniju, samo bi listovi imali neke vrednosti, unutrasnji cvorovi ne bi bili popunjeni
    segment_tree[k] = segment_tree[2 * k] + segment_tree[2 * k + 1];
}

/***************************************** ALTERNATIVNA IMPLEMENTACIJE GDE INDEKSIRANJE KRECE OD 0 *****************************************/
void build_segment_tree_alternative (std::vector<int> &array, std::vector<int> &segment_tree, int k, int x, int y)
{
    if (x == y) {
        segment_tree[k] = array[x];
        return;
    }

    int middle = (x + y) / 2;

    //Ukoliko se koren segmentnog stabla nalazi na pozicji 0, tada vazi
    //da se levo dete cvora na poziciji k nalazi na poziciji 2 * k + 1 i da se desno dete cvora na poziciji k nalazi na poziciji 2 * k + 2
    //Rekurzivno racunamo vrednosti levog i desnog deteta
    build_segment_tree_alternative(array, segment_tree, 2 * k + 1, x, middle);
    build_segment_tree_alternative(array, segment_tree, 2 * k + 2, middle + 1, y);

    segment_tree[k] = segment_tree[2 * k + 1] + segment_tree[2 * k + 2];
}

int main ()
{
    std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

    //Pretpostavljamo da je duzina niza stepen dvojke.
    int n = array.size();

    //Ako duzina niza ne bi bio stepen dvojke, morali bismo da dopunimo niz nulama na kraju do duzine prvog veceg stepena dvojke od n
    //Nalazimo prvi veci broj od n koji je stepen dvojke
    //int height = ceil(log2(n));
    //n = pow(2, height);
    //Prosirujemo niz nulama na kraju. (Ovo smo mogli i regulisati prilikom kopiranja niza u segmentno stablo)
    //array.resize(n);

    std::vector<int> segment_tree(2 * n);

    build_segment_tree(array, segment_tree, 1, 0, n - 1);

    //Primer formiranja segmentnog stabla gde se koren nalazi na poziciji 0. Jedino sto se menja jeste nacin racunanja indeksa levog i desnog deteta nekog cvora
    //Poziv funkcije ce sada biti za k = 0
    //U ovom slucaju ce duzina segmentnog stabla biti 2 * n - 1
    //build_segment_tree_alternative(array, segment_tree, 0, 0 , n - 1);

    for (int x : segment_tree)
        std::cout << x << " ";

    std::cout << "\n";

    return 0;
}
