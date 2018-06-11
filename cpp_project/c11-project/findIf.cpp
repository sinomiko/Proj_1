

class map_finder
{
public:
    map_finder(const std::string &cmp_string) :m_s_cmp_string(cmp_string) {}
    bool operator ()(const std::map<int, std::string>::value_type &pair)
    {
        return pair.second == m_s_cmp_string;
    }
private:
    const std::string &m_s_cmp_string;
};

template<class InputIterator, class T>
bool unary_find(InputIterator first, InputIterator last, UnaryPredicate pred, T& res)
{
    while (first != last) {
        if (*first == res)) return first;
        ++first;
    }
    return last;
}


template<class InputIterator, class T>
bool binary_find(InputIterator first, InputIterator last, UnaryPredicate pred, T& res)
{
    while (first != last) {
        if (*first == res)) return first;
        ++first;
    }
    return last;
}

//https://stackoverflow.com/questions/7335546/find-the-first-value-greater-than-user-specified-value-from-a-map-container
//http://en.cppreference.com/w/cpp/algorithm/find

template <class Key, class Value, class Value>
struct BinaryFinder
{
    bool operator()(const std::pair<Key, Value>& item, Value& val) const
    {
        return item.second == val;
    }
};
template<class InputIt, class UnaryPredicate>
InputIt MapFind(InputIt first, InputIt last, UnaryPredicate p)
{
    for (; first != last; ++first) {
        if (p(*first)) {
            return first;
        }
    }
    return last;
}

//std::find_if(Mymap.begin(), Mymap.end(), Finder(MYVALUE));