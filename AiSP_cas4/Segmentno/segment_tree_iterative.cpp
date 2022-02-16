#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

//using namespace std;

// Funkcija koja od niza array kreira segmentno stablo segment_tree
void build_segment_tree(std::vector<int> &array, std::vector<int> &segment_tree, int n)
{
    //Kopiramo sve elemente niza array (kojih ima ukupno n) u segmentno stablo od pozicije n pa do kraja
    std::copy_n(array.begin(), n, segment_tree.begin() + n);
    //Popunjavamo niz od pozicije n - 1 pa do pozicije 1, tj do korena
    //Svaki roditelj ima decu na pozicijama 2 * k i 2 * k + 1 (indeksiranje krecemo od 1)
    for(int k = n - 1; k >= 1; k--)
        segment_tree[k] = segment_tree[2 * k] + segment_tree[2 * k + 1];
}

int main ()
{
    std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

    //Pretpostavljamo da je duzina niza stepen dvojke
    int n = array.size();

    //Ako duzina niza ne bi bila stepen dvojke, morali bismo da dopunimo niz nulama na kraju do duzine prvog veceg stepena dvojke od n
    //Nalazimo prvi veci broj od n koji je stepen dvojke
    //Funkcija ceil vraca prvi veci ili jednak ceo broj od vrednosti argumenta
    //int height = ceil(log2(n));
    //n = pow(2, height);
    //Prosirujemo niz nulama na kraju (Ovo smo mogli regulisati i prilikom kopiranja niza u segmentno stablo)
    //array.resize(n);

    std::vector<int> segment_tree(2 * n);

    build_segment_tree(array, segment_tree, n);

    for (int x : segment_tree)
        std::cout << x << " ";

    std::cout << "\n";

    return 0;
}
