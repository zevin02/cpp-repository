#include <iostream>
using namespace std;
#include <map>

//通过一个值找到另一个值

void test1()
{
    map<string, string> dict;
    dict.insert(pair<string, string>("hello", "你好")); //直接用匿名对象
    pair<string, string> kv1("world", "世界");          //构造一个对象插入进去
    dict.insert(kv1);
    dict.insert(make_pair("sort", "排序")); // make_pair本质就是一个函数模板,把pair进行封装了
    //优势在于可以自动推导类型

    //如果insert插入的key出现过了，就不会操作

    dict.erase("hello");           //删除一个值
    auto pos = dict.find("world"); //
    if (pos != dict.end())
    {
        cout << "19" << endl;
    }
    if (dict.count("hello") == 0)
    {
        cout << "23" << endl;
    }

    auto it = dict.begin();

    // map也是有排序的，按照key排序
    // map 是可以通过迭代器进行修改的
    // key不支持修改，但是value是可以支持修改的
    while (it != dict.end())
    {
        cout << it->first << ":" << it->second << endl;
        it++;
    }
    for (auto &e : dict)
    {
        cout << e.first << " " << e.second << endl;
    }
}
#include <string>
#include <vector>
void test2()
{
    vector<string> arr = {"apple", "apple", "banana", "banana", "pair"};
    map<string, int> coutmap;
    /*
    for(auto& e: arr)
    {
        auto ret=coutmap.find(e);
        if(ret==coutmap.end())
        {
            //这里面没有这个值
            // coutmap.insert(make_pair(e,1));
            coutmap[e]=1;//直接在这里
        }
        else
        {
            //这个值存在
            ret->second++;
        }
    }
    */
    for (auto &str : arr)
    {
        auto kv = coutmap.insert(make_pair(str, 1)); //先不管这个key在不在，直接先插入
        //如果已经出现过了，就插入没有成功
        if (!kv.second)
        {
            //插入失败
            kv.first->second++; //因为没有成功也会返回那个位置相等的迭代器
        }
    }

    for (auto &e : arr)
    {
        //实际最常用的就是[]
        coutmap[e]++; //调用了int的默认构造函数就是0
    }

    for (auto &e : coutmap)
    {
        cout << e.first << ":" << e.second << endl;
    }
}

void test3()
{
    /*
    []的作用
    1. 插入
    2. 查找
    3. 修改
    */
    //水果第一次出现，充当查找和修改

    //[]的返回值就是value的引用
    map<int,int> s;
    s[1]=1;
    s[1]=1;
    s[1]=2;//一个key只能对应一个value，修改

    s[1];//如果有充当查找，没有充当插入
    auto it=s.find(1);
    if(it!=s.end())
    {
        cout<<"110"<<endl;
    }
    for(auto e: s)
    {
        cout << e.first << ":" << e.second << endl;

    }
}
void test4()
{
    multimap<int,int> dict;//可以实现key的冗余
    dict.insert(make_pair(1,1));
    dict.insert(make_pair(1,2));
    dict.insert(make_pair(1,3));
    dict.insert(make_pair(1,1));
     for(auto e: dict)
    {
        cout << e.first << ":" << e.second << endl;

    }
    cout<<dict.count(1)<<endl;//查找有几个key
}
int main()
{
    // test1();
    // test2();
    test3();
    test4();
    return 0;
}