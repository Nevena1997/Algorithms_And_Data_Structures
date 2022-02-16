#include <iostream>
#include <vector>

//Rekurzivna funkcija koja racuna sumu segmenta (0, index] Fenvikovog stabla
//Na poziciji k Fenvikovog stabla nalazi se suma elementa pocetnog niza iz segmenta (f(k), k]
//f(k) jeste vrednost koja se dobija brisanjem prve jedinice sa desne strane u binarnom zapisu broja k
//k = 6 (110)  f(k) = 4 (100)
//k = 21 (10101)  f(k) = 20 (10100)
int recursive_sum(std::vector<int> &fenwick_tree, int index)
{
    //Vracamo 0 jer smo stigli do segmenta (0,0]
    if (index == 0) return 0;

    //Rezultat je suma segmenta (f(k), k] na koju dodajemo sumu segmenta (f(f(k)), f(k)]
    //Ovde je k oznaceno sa index
    return recursive_sum(fenwick_tree, index - (index & (- index))) + fenwick_tree[index];
}

//Iterativna funkcija koja racuna sumu segmenta (0, index] Fenvikovog stabla
int sum_to_index(std::vector<int> &fenwick_tree, int index)
{
    index++;

    int result = 0;

    //Sve dok je segment neprazan, dodaj sumu segmenta (f(k), k] i promeni k na f(k)
    //Ovde je k oznaceno sa index
    while (index > 0) {
        result += fenwick_tree[index];
        index -= index & (-index);
    }

    return result;
}

//Rekurzivna funkcija koja dodaje element value na poziciju index u Fenvikovo stablo
//Menjamo vrednost na svim pozicijama Fenvikovog stabla koje u svojoj sumi ukljucuju i vrednost tog elementa
void add_recursive(std::vector<int> &fenwick_tree, int n, int index, int value)
{
    if (index > n) return ;

    fenwick_tree[index] += value;
    add_recursive(fenwick_tree, n, index + (index & (-index)), value);
}

//Iterativna funkcija koja dodaje element value na poziciju index u Fenvikovo stablo
void add_to_tree(std::vector<int> &fenwick_tree, int n, int index, int value)
{
    index++;

    while (index <= n) {
        fenwick_tree[index] += value;
        // Pomeramo indeks na sledecu vrednost indeksa na koju utice promena prethodne vrednosti
        index += index & (-index);
    }
}

//Sumu segmenta [a, b] racunamo kao razliku suma segmenata (0, b] i (0, a - 1]
//[a, b] = (0, b] - (0, a - 1]
int sum_in_segment(std::vector<int> &fenwick_tree, int index_1, int index_2)
{
    return sum_to_index(fenwick_tree, index_2) - sum_to_index(fenwick_tree, index_1 - 1);
}

int main ()
{
    std::vector<int> array = { 2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9 };

    int n = array.size();

    //Imamo 2 vektora, jedan za iterativnu konstrukciju Fenvikovog satbla i jedan za rekurzivnu konstrukciju Fenvikovog stabla
    std::vector<int> fenwick_tree(n + 1), fenwick_recursive(n + 1);

    //void fill (ForwardIterator first, ForwardIterator last, const T& val);
    //std::fill(fenwick_tree.begin(), fenwick_tree.end(), 0);

    //Fenvikovo stablo formiramo tako sto dodajemo element po element
    for (int i = 0; i < n; i++) {
        add_recursive(fenwick_recursive, n, i + 1, array[i]);
        add_to_tree(fenwick_tree, n, i, array[i]);
    }

    //Ispisujemo elemente Fenvikovog stabla dobijenog iterativnom metodom
    for (int x : fenwick_tree)
        std::cout << x << " ";

    std::cout << "\n";

    //Ispisujemo elemente Fenvikovog satbla dobijenog rekurzivnom metodom
    for (int x : fenwick_recursive)
        std::cout << x << " ";

    std::cout << "\n";

    int a = 2;
    int b = 5;

    //Racunamo sumu segmenta [a, b] iz Fenvikovih stabala dobijenih iterativnom i rekurzivnom metodom
    std::cout << sum_in_segment(fenwick_tree, a, b) << std::endl;
    std::cout << recursive_sum(fenwick_recursive, b + 1) - recursive_sum(fenwick_recursive, a) << "\n";

    return 0;
}
