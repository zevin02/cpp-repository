#include<iostream>
#include<cmath>
using namespace std;
int gcd(int a,int b)
{
    return b==0?a:gcd(b,a%b);
}
int lcm(int a,int b)
{
    return a/gcd(a,b)*b;
}
int pathlen(int a,int b)
{
    if(abs(a-b)>21)
    {
        return 0;
    }
    else
    {
        return lcm(a,b);
    }
}
int main()
{
    int min=-1;
    for(int i=1;i<2021;i++)
    {
        for(int j=i+1;j<2021;j++)
        {
            if((min==-1||min>pathlen(i,j))&&min!=0)
            {
                min=pathlen(i,j);
            }
        }
    }
    cout<<min<<endl;
    return 0;
}
