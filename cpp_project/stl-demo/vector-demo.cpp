/*************************************************************************
	> File Name: vector-demo.cpp
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Sun 23 Apr 2017 09:12:08 PM PDT
 ************************************************************************/
#include<iostream>
#include<vector>
using namespace std;
int main()
{
    vector<int> q;
    q.push_back(1);
    q.push_back(2);
    for(vector<int>::iterator itq=q.begin();itq<q.end();itq++)
        cout<<*itq<<endl;
    vector<int> v;
    for(int i=0; i<5; ++i)
    {
        v.push_back(i);
    }
    for(vector<int>::iterator itt=v.begin();itt<v.end();itt++)
        cout<<*itt<<endl;
    vector<int>::iterator it=v.begin()+1;
    it=v.insert(it,33);
    for(vector<int>::iterator itt=v.begin();itt<v.end();itt++)
        cout<<*itt<<endl;
    v.insert(it,q.begin(),q.end());
    for(vector<int>::iterator itt=v.begin();itt<v.end();itt++)
        cout<<*itt<<endl;
    it=v.begin()+3;
    v.erase(it);
    it=v.begin()+1;
    //v.erase(it,it+4);
    for(vector<int>::iterator itt=v.begin();itt<v.end();itt++)
        cout<<*itt<<endl;
    v.clear();
    return 0;
}
