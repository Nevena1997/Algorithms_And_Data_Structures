#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

void build_segment_tree(std::vector<int> &array, std::vector<int> &segment_tree, int k, int x, int y)
{
    if (x == y) {
        segment_tree[k] = array[x];
        return ;
    }

    int middle = (x + y) / 2;

    build_segment_tree(array, segment_tree, 2 * k + 1, x, middle);
    build_segment_tree(array, segment_tree, 2 * k + 2, middle + 1, y);

    //U cvoru pamtimo vecu od vrednosti levog i desnog deteta
    segment_tree[k] = std::max(segment_tree[2 * k + 1], segment_tree[2 * k + 2]);
}

int max_element_in_segment(std::vector<int> &segment_tree, int x, int y, int a, int b, int k)
{
    if (x > b || y < a)
        return INT_MIN;

    if (x >= a && y <= b)
        return segment_tree[k];

    int middle = (x + y) / 2;

    return std::max(max_element_in_segment(segment_tree, x, middle, a, b, 2 * k + 1), max_element_in_segment(segment_tree, middle + 1, y, a, b, 2 * k + 2));
}

int main ()
{
    std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

    int n = array.size();

    int height = ceil(log2(n));

    n = pow(2, height);

    array.resize(n);

    //Zelimo da koren bude na poziciji 0 pa ce nam trebati 2 * n - 1 element u segmentnom stablu
    std::vector<int> segment_tree(2 * n - 1);

    //Formiramo segmentno stablo tako da se koren nalazi na poziciji 0
    build_segment_tree(array, segment_tree, 0, 0 , n - 1);

    for (int x : segment_tree)
        std::cout << x << " ";

    std::cout << "\n";

    int a, b;

   //Ucitavamo segment [a, b] ciju sumu zelimo da izracunamo
   //Pretpostavljamo da su unete vrednosti validne
    std::cin >> a >> b;

    std::cout << max_element_in_segment(segment_tree, 0, n - 1, a, b, 0) << "\n";

    return 0;
}
