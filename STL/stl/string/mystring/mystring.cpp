#include<iostream>
#include<string>
using namespace std;
int main()
{
    string s="aaaaa";
    s.resize(2,'b');
    cout<<s<<endl;
    return 0;
}