#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>


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
    
    v.assign(10,5);//用10个5去覆盖,变成新的值
    cout<<v.max_size()<<endl;//非常大
    v.reserve(50);//把扩容成50
    v.resize(100);//把空间弄成100，同时把其余初始化为0
    //v[]是用assert来判断错误
    //
}

void test_vector4()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    vector<int>::iterator ret= find(v.begin(),v.end(),3);//返回的是找到的3的第一个位置迭代器,
    if(ret!=v.end())
    {
        cout<<"1"<<endl;
        v.insert(ret,30);//头插,第一个是迭代器的位置，在ret迭代器位置插入一个30
        //不能在这里删除，迭代器会失效
        
    }
    int i=0;
    for(i=0;i<v.size();i++)
    {
        cout<<v[i];

    }
    //删除一个值
    
    vector<int>::iterator ret1= find(v.begin(),v.end(),3);//返回的是找到的3的第一个位置迭代器,
   if(ret1!=v.end())
    {
    v.erase(ret1);
    }   
    v.clear();
   cout<<v.capacity()<<endl;  

}

//vector可以动态内存申请的数组
int main()
{
    test_vector1();
    test_vector2(); 
    test_vector3();
    test_vector4();
    return 0;
    
}
