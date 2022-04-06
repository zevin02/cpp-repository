
#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;
int main()
{
    ll n;
    vector<ll> factor;
    cin>>n;
    for(ll i=1;i<=n/i;i++)//先获得n的所有约数，因为3个数字相乘一定是n的约数字
    {
        if(n%i==0)
        {
            factor.push_back(i);
            if(i!=n/i)
            {
                factor.push_back(n/i);
            }
        }
    }
   int count=0;
    for(ll i=0;i<factor.size();i++)
    {
        for(ll j=0;j<factor.size();j++)
        {
            for(ll k=0;k<factor.size();k++)
            {
                if(factor[i]*factor[j]*factor[k]==n)
                {
                    count++;
                }
            }
        }
    }
    cout<<count<<endl;

    return 0;
}
 

