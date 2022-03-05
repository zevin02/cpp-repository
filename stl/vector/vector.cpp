#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>


void test_vector1()
{
    //构造函数初始化
    vector<int>v1;//无参,
    vector<int>v2(10,8);//10个8
    vector<int>v3(++v2.begin(),--v2.end());//使用迭代器进行赋值的初始化，6个8
    vector<int>v4(v3);//用v3进行拷贝构造
    string s("hello world");
    vector<char>v5(s.begin(),s.end());//类比v3
    

    
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
    for(i=0;i<v.size();i++)//v.size()计算vector的有效个数
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
    v.resize(100);//把空间弄成100，同时把其余初始化为0,这个在vector里面非常常用
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
    v.erase(ret1);//删除ret1迭代器位置的数
    }   
    v.clear();//将所有数字都清空
   cout<<v.capacity()<<endl;  //计算v的容量
    v.front();//v的第一个元素
    v.back();//v的最后一个数据
}
void test_vector5()
{
    //二维数组
    //c语言的二维数组静态可以弄，但是无法动态扩容
  //  int** p=(int**)malloc(sizeof(int*)*3);//每个数组存int*，他就是int**,同时他的每一行都要进行开辟，所以就很麻烦
    //p[i][j];//第i行的第j个
    vector<vector<int> > vv;//二维数组，里面的每个数据又是一个vector,VV[I][J],由析构函数，两次的函数调用，
    vv.resize(5);
    cout<<vv.capacity()<<endl;//5
    cout<<vv.size()<<endl;//5，
    int i=0;

    for(i=0;i<5;i++)
    {
        //先开空间再使用，
        vv[i].resize(i+1);//vv[i]里面也是vector，使用resize对其size进行设置
        //先开空间再去访问
        vv[i].front()=vv[i].back()=1;//第一列和每一行的最后一个都是1
        //vv[i][0]=vv[i][vv[i].size()-1]=1;//和上面是一样的
    }
    //遍历二维数组
    for(int i=0;i<vv.size(),i++)
    {
        for(int j=0;j<vv[i].size();j++)

        {
            if(vv[i][j]==0)//上面resize初始化默认是0
            {
                vv[i][j]=vv[i-1][j]+vv[i-1][j-1];
            }
        }
    }


}
//vector可以动态内存申请的数组
int main()
{
    test_vector1();
    test_vector2(); 
    test_vector3();
    test_vector4();
    test_vector5();

    return 0;
    
}
