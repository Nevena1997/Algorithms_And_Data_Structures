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

//Funkcija koja azurira vrednost elementa na poziciji i u pocetnom nizu tako sto upise novi element v
void update_tree(std::vector<int> &segment_tree, int n, int index, int new_value)
{
    //Azuriramo vrednost
    //Element koji se nalazio u pocetnom nizu na poziciji index, u segmentnom stablu se nalazi na poziciji index + n
    int k = index + n;
    segment_tree[k] = new_value;

    //Azuriramo vrednosti roditelja cvora na poziciji k jer su to jedini cvorovi koji se menjaju
    //Roditelj cvora k se nalazi na poziciji k/2
    for (k /= 2; k >= 1; k /= 2)
        segment_tree[k] = segment_tree[2 * k] + segment_tree[2 * k + 1];
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

    int i, v;

    //Ucitavamo vrednost i i v
    //i je indeks element koji zelimo da azuriramo, a v je vrednost koju zelimo da upisemo
    //Pretpostavljamo da su unete vrednosti validne
    std::cin >> i >> v;

    //Racunamo i ispisujemo sumu niza na segmentu [a,b]
    update_tree(segment_tree, n, i, v);

    for (int x : segment_tree)
        std::cout << x << " ";

    std::cout << "\n";

    return 0;
}

