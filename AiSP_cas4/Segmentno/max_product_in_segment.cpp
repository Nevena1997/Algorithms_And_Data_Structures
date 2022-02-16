#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

//Cvorovi ce sada biti strukture koje cuvaju informaciju o najvecem i drugom najvecem elementu u odgovarajucem segmentu koji taj cvor pokriva
//Ukoliko nadjemo 2 najveca broja u nekom segmentu, nasli smo i najveci proizvod u tom segmentu
//Ovo vazi ako radimo sa pozitivnim brojevima
struct Node
{
    int largest;
    int second_largest;
};

void build_segment_tree (std::vector<int> &array, std::vector<Node> &segment_tree, int k, int x, int y)
{
    //Vrednost INT_MIN nam govori da se radi o listovima, tj o elementima pocetnog cvora
    //Mogli smo staviti i bilo koju drugu negativnu vrednost
    //Svaki pozitivan broj ce biti veci od bilo koje negativne vrednosti pa INT_MIN nikad nece biti u opticaju u visim nivoima za largest ili second_largest vrednosti
    if (x == y) {
        segment_tree[k].largest = array[x];
        segment_tree[k].second_largest = INT_MIN;
        return ;
    }

    int middle = (x + y) / 2;

    build_segment_tree(array, segment_tree, 2 * k, x, middle);
    build_segment_tree(array, segment_tree, 2 * k + 1, middle + 1, y);

    //Azuriramo vrednost roditelja
    segment_tree[k].largest = std::max(segment_tree[2 * k].largest, segment_tree[2 * k + 1].largest);

    segment_tree[k].second_largest = std::min(std::max(segment_tree[2 * k].largest, segment_tree[2 * k + 1].second_largest),
                                            std::max(segment_tree[2 * k].second_largest, segment_tree[2 * k + 1].largest));
}

Node find_max_product_in_segment (std::vector<Node> &segment_tree, int k, int x, int y, int a, int b)
{
    Node result;
    result.largest = INT_MIN;
    result.second_largest = INT_MIN;

    if (a > y || b < x) {
        return result;
    }

    if (x >= a && y <= b)
        return segment_tree[k];

    int middle = (x + y) / 2;

    Node left = find_max_product_in_segment(segment_tree, 2 * k, x, middle, a, b);
    Node right = find_max_product_in_segment(segment_tree, 2 * k + 1, middle + 1, y, a, b);

    result.largest = std::max(left.largest, right.largest);

    result.second_largest = std::min(std::max(left.largest, right.second_largest),
                                            std::max(left.second_largest, right.largest));

    return result;
}

void update_tree(std::vector<Node> &segment_tree, int k, int x, int y, int index, int new_value)
{
    if (x == y) {
        segment_tree[k].largest = new_value;
        segment_tree[k].second_largest = INT_MIN;
        return ;
    }

    int middle = (x + y) / 2;

    if (index <= middle)
        update_tree(segment_tree, 2 * k, x, middle, index, new_value);
    else
        update_tree(segment_tree, 2 * k  + 1, middle + 1, y, index, new_value);

    segment_tree[k].largest = std::max(segment_tree[2 * k].largest, segment_tree[2 * k + 1].largest);

    segment_tree[k].second_largest = std::min(std::max(segment_tree[2 * k].largest, segment_tree[2 * k + 1].second_largest),
                                            std::max(segment_tree[2 * k].second_largest, segment_tree[2 * k + 1].largest));
}

void update_array(std::vector<int> &array, std::vector<Node> &segment_tree, int index, int new_value)
{
    array[index] = new_value;

    update_tree(segment_tree, 1, 0, array.size() - 1, index, new_value);
}

int main ()
{
    std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

    int n = array.size();

    int height = ceil(log2(n));

    n = pow(2, height);

    array.resize(n);

    std::vector<Node> segment_tree(2 * n);

    build_segment_tree(array, segment_tree, 1, 0, n - 1);

    for (Node x : segment_tree)
        std::cout << x.largest << ":" << x.second_largest << " ";

    std::cout << "\n";

    //Ne ucitavamo brojeve sa standardnog ulaza vec smo sami odabrali
    Node result = find_max_product_in_segment(segment_tree, 1, 0, n - 1, 0, 2);

    std::cout << result.largest * result.second_largest << std::endl;

    //Izmenimo niz pa proverimo da li se promenila i vrednost proizvoda u prethodnom segmentu
    update_array(array, segment_tree, 1, 6);

    result = find_max_product_in_segment(segment_tree, 1, 0, n - 1, 0, 2);

    std::cout << result.largest * result.second_largest << std::endl;

    return 0;
}
