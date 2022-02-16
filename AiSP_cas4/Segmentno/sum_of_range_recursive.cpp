#include <iostream>
#include <vector>
#include <cmath>

void build_segment_tree (std::vector<int> &array, std::vector<int> &segment_tree, int k, int x, int y)
{
    if (x == y) {
        segment_tree[k] = array[x];
        return;
    }

    int middle = (x + y) / 2;

    build_segment_tree(array, segment_tree, 2 * k, x, middle);
    build_segment_tree(array, segment_tree, 2 * k + 1, middle + 1, y);

    segment_tree[k] = segment_tree[2 * k] + segment_tree[2 * k + 1];
}

// Funkcija koja racuna sumu elemenata u intervalu [a, b]
// Kao i prilikom rekurzivne implementacije formiranja segmentnog stabla, k je pozicija (indeks) cvora u segmentnom stablu,
// a [x, y] predstavlja interval cija se suma nalazi u cvoru na poziciji k
// Postoje 3 moguca ondosa segmenata [x, y] i [a, b].
// Prvi slucaj je da se segmenti [x, y] i [a,b] ne preklapaju - tada nijedan element iz segmenta [x,y] ne ucestvuje u sumi pa vracamo 0
// Drugi slucaj je da se segment [x, y] nalazi unutar segmenta [a, b] - tada vracamo segment_tree[k] jer taj cvor cuva sumu elemenata iz segmenta [x, y] koji ceo doprinosi sumi
// Treci slucaj je da se segmenti preklapaju, onda delimo segment [x, y] na dva dela i racunamo rekurzvino
int sum_of_segment(std::vector<int> &segment_tree, int x, int y, int a, int b, int k)
{
    //Ukoliko se segmenti [x, y] i [a, b] ne preklapaju
    if (x > b || y < a)
        return 0;

    ////Ukoliko segmenti [x, y] nalazi ceo unutar segmenta [a, b]
    if (x >= a && y <= b)
        return segment_tree[k];

    //Ukoliko se segmenti preklapaju, racunamo rekurzivno za levo i desno dete
    int middle = (x + y) / 2;

    return sum_of_segment(segment_tree, x, middle, a, b, 2 * k) + sum_of_segment(segment_tree, middle + 1, y, a, b, 2 * k + 1);
}


int main ()
{
    std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

    int n = array.size();

    int height = ceil(log2(n));

    n = pow(2, height);

    array.resize(n);

    std::vector<int> segment_tree(2 * n);

    //Formiramo segmentno stablo tako da se koren nalazi na poziciji 1
    build_segment_tree(array, segment_tree, 1, 0 , n - 1);

    for (int x : segment_tree)
        std::cout << x << " ";

    std::cout << "\n";

    int a, b;

    //Ucitavamo segment [a, b] ciju sumu zelimo da izracunamo
    //Pretpostavljamo da su unete vrednosti validne
    std::cin >> a >> b;

    //Racunamo i ispisujemo sumu niza na segmentu [a,b]
    std::cout << sum_of_segment(segment_tree, 0, n - 1, a, b, 1) << "\n";

    return 0;
}
