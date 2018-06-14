#include <iostream>     // std::cout
#include <vector>

using namespace  std;

template <class BidirectionalIterator, class UnaryPredicate>
BidirectionalIterator partition(BidirectionalIterator first,
    BidirectionalIterator last, UnaryPredicate pred)
{
    while (first != last) {
        while (pred(*first)) {
            ++first;
            if (first == last) return first;
        }
        do {
            --last;
            if (first == last) return first;
        } while (!pred(*last));
        swap(*first, *last);
        ++first;
    }
    return first;
}

template <typename ForwardIt>
void QuickSort(ForwardIt first, ForwardIt last)
{
    if (first ==last)
    {
        return;
    }
    auto pivot = *std::next(first, std::distance(first, last) / 2);
    ForwardIt middle1 = std::partition(first, last, [pivot](const auto& em) {return em < pivot});
    ForwardIt middle2 = std::partition(middle1, last, [pivot](const auto& em) {return em < pivot});

    QuickSort(first, middle1);
    QuickSort(middle2, last);
}

int main() {
    vector<int> test2;
    int a = 2;
    int p = a;
    test2.push_back(p);
    std::partition(test2.front(), test2.back(), [&](int a) {return })
    getchar();
    return 0;
}