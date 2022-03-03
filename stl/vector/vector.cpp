#include<iostream>
using namespace std;
#include<vector>



void test_vector1()
{
    //构造函数初始化
    vector<int>v1;//无参,
    vector<int>v2(10,8);//10个8
    vector<int>v3(++v2.begin(),--v2.end());
    vector<int>v4(v3);
    string s("hello world");
    vector<char>v5(s.begin(),s.end()); 

    
}   


void test_vector2()
{
    //尾插
    vector<int> v;
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    //遍历
    int i=0;
    for(i=0;i<v.size();i++)
    {
        v[i]+=1;
        cout<<v[i];
    }
    cout<<endl;
    //迭代器
    vector<int>::iterator it=v.begin();
    while(it!=v.end())
    {
        *it-=1;
        cout<<*it;
        ++it;
    }
   

//    for(auto e:v)
//    {
//        cout<<e;
//    }
        
   
}


void test_vector3()
{

    vector<int> v;
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.pop_back();//尾巴删除
    v.assign(10,5);//用10个5去覆盖
    cout<<v.max_size()<<endl;

}


//vector可以动态内存申请的数组
int main()
{
    test_vector1();
    test_vector2(); 
    return 0;
}
