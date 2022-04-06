#include<iostream>
#include<vector>
using namespace std;
int cardnumber[10]={2019,2019,2019,2019,2019,2019,2019,2019,2019,2019};
bool canmade(int number)
{
    //先获取其中的每个数字
    string num=to_string(number);
    auto it=num.begin();
    while(it!=num.end())
    {
        if(cardnumber[*it-'0']==0)
        {
            return false;
        }
        else 
        {
            cardnumber[*it-'0']--;
            it++;
        }
    }
    return true;
}
int main()
{
    
    int number=1;
    while(1)
    {
        if(canmade(number))//可以组成，就number++
        {
            number++;

        }
        else 
        {
            break;
        }

    }
    cout<<number<<endl;
    return 0;
}