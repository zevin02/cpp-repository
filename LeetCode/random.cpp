#include<iostream>
using namespace std;
#include<set>
#include<vector>

int main()
{
    set<int> res;
    int n;
    int number;
    cin>>n;
    while(n--)
    {
        cin>>number;
        res.insert(number);
    }
    cout<<res.size()<<endl;
    auto it=res.begin();       
    while(it!=res.end())
    {
        cout<<*it<<" ";
        it++;
    }
    cout<<endl;
    return 0;
}

