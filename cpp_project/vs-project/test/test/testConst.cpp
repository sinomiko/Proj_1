#include <iostream>
#include <vector>
using namespace std;

vector<int> genFunc(int index)
{
    vector<int> strVect;
    for (int i = 0; i < index; i++)
    {
        strVect.push_back(i);
    }
    return strVect;
}
vector<int> catchFunc(int index)
{
    if (index == 0)
    {
        return{};
    }
    return genFunc(index);
}

int main()
{
    const vector<int>& tmp = catchFunc(2);

    cout << "=====" << tmp.size() << "====" << endl;

    return 0;
}
