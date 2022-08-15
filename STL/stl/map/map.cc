#include <iostream>
using namespace std;
#include <map>
#include <queue>

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
    map<int, int> s;
    s[1] = 1;
    s[1] = 1;
    s[1] = 2; //一个key只能对应一个value，修改

    s[1]; //如果有充当查找，没有充当插入
    auto it = s.find(1);
    if (it != s.end())
    {
        cout << "110" << endl;
    }
    for (auto e : s)
    {
        cout << e.first << ":" << e.second << endl;
    }
}
void test4()
{
    multimap<int, int> dict; //可以实现key的冗余
    dict.insert(make_pair(1, 1));
    dict.insert(make_pair(1, 2));
    dict.insert(make_pair(1, 3));
    dict.insert(make_pair(1, 1));
    for (auto e : dict)
    {
        cout << e.first << ":" << e.second << endl;
    }
    cout << dict.count(1) << endl; //查找有几个key
}
#include <algorithm>

struct CoutMap
{
    string _fruit;
    int _num;
    CoutMap(string fruit, int num)
        : _fruit(fruit), _num(num)
    {
    }
};

// sort的版本1
void GetFavoriteFruit1(vector<string> &arr, size_t k)
{
    map<string, int> coutmap; //统计水果个数
    for (auto &e : arr)
    {
        coutmap[e]++;
    }

    vector<CoutMap> Cmp;
    for (auto &e : coutmap)
    {
        Cmp.push_back(CoutMap(e.first, e.second));
    }

    // priority_queue<int,map<string,int>,greater<int>> pq(arr.begin(),arr.begin()+k);
    //获得前k个最多出现次数的
    //按次数去排
    // 1.用排序

    sort(Cmp.begin(), Cmp.end(), [](const CoutMap &T1, const CoutMap &T2)
         { return T1._num > T2._num; }); //这样就实现了降序排列，获得了前k个
    for (auto &e : Cmp)
    {
        cout << e._fruit << ":" << e._num << endl;
    }
}

// sort的版本2
void GetFavoriteFruit2(vector<string> &arr, size_t k)
{
    map<string, int> coutmap; //统计水果个数
    for (auto &e : arr)
    {
        coutmap[e]++;
    }

    vector<pair<string, int>> Cmp; //里面存pair就行了
    for (auto &e : coutmap)
    {
        Cmp.push_back(e); //把kv存进去,代价有点大
    }

    // priority_queue<int,map<string,int>,greater<int>> pq(arr.begin(),arr.begin()+k);
    //获得前k个最多出现次数的
    //按次数去排
    // 1.用排序

    //这样也是可以的
    sort(Cmp.begin(), Cmp.end(), [](const pair<string, int> &T1, const pair<string, int> &T2)
         { return T1.second > T2.second; }); //这样就实现了降序排列，获得了前k个
    for (auto &e : Cmp)
    {
        cout << e.first << ":" << e.second << endl;
    }
}

void GetFavoriteFruit3(vector<string> &arr, size_t k)
{
    map<string, int> coutmap; //统计水果个数
    for (auto &e : arr)
    {
        coutmap[e]++;
    }

    vector<map<string, int>::iterator> Cmp; //里面存放着map的迭代器,迭代器里面小很多,节省空间
    auto it = coutmap.begin();
    while (it != coutmap.end())
    {
        Cmp.push_back(it);
        it++;
    }
    sort(Cmp.begin(), Cmp.end(), [](const map<string, int>::iterator &T1, const map<string, int>::iterator &T2)
         { return T1->second > T2->second; }); //用迭代器比较
    for (auto &e : Cmp)
    {
        cout << e->first << ":" << e->second << endl;
    }
}

#include<functional>
void GetFavoriteFruit4(vector<string> &arr, size_t k)
{
    map<string, int> coutmap; //统计水果个数
    for (auto &e : arr)
    {
        coutmap[e]++;
    }
    //使用multimap
    multimap<int,string,greater<int>> sortMap;//不支持[]
    for(auto& e: coutmap)
    {
        sortMap.insert(make_pair(e.second,e.first));//这样就是已近排序好了，升序排序
    }

    for (auto &e : sortMap)
    {
        cout << e.second << ":" << e.first << endl;
    }
}


struct CoutVal
{
    bool operator()(const pair<string, int> &T1, const pair<string, int> &T2)
    {
        return T1.second < T2.second;//获得最大的，优先级队列要反着弄
    }
};

void GetFavoriteFruit5(vector<string> &arr, size_t k)
{
    map<string, int> coutmap; //统计水果个数
    for (auto &e : arr)
    {
        coutmap[e]++;
    }
    //使用优先级队列
    priority_queue<map<string, int>::iterator,vector<map<string, int>::iterator>,CoutVal> pq;//类模板传类型，函数模板传对象,第一个是每个元素的类型,第二个就是放在vector容器里面
    //同理也是可以用迭代器进行操作,也是类似的操作
    for(auto& e:coutmap)
    {
        pq.push(e);//插入
    }

    while(k--)
    {
        //顶部的一定就是最大的
        cout<<pq.top().first<<" "<<pq.top().second<<endl;
        pq.pop();
    }

}

void GetFavoriteFruit6(vector<string> &arr, size_t k)
{
    map<string, int> coutmap; //统计水果个数
    for (auto &e : arr)
    {
        coutmap[e]++;
    }
    //使用优先级队列
    priority_queue<pair<string,int>,vector<pair<string,int>>,CoutVal> pq;//类模板传类型，函数模板传对象,第一个是每个元素的类型,第二个就是放在vector容器里面
    //同理也是可以用迭代器进行操作
    for(auto& e:coutmap)
    {
        pq.push(e);//插入
    }

    while(k--)
    {
        //顶部的一定就是最大的
        cout<<pq.top().first<<" "<<pq.top().second<<endl;
        pq.pop();
    }

}

int main()
{
    // test1();
    // test2();
    // test3();
    // test4();
    vector<string> arr = {"bao", "bao", "zi", "zi", "he", "kele", "kele", "kele", "nian"};
    GetFavoriteFruit1(arr, 3);
    GetFavoriteFruit2(arr, 3);
    GetFavoriteFruit3(arr, 3);
    GetFavoriteFruit4(arr, 3);
    GetFavoriteFruit5(arr, 3);
    return 0;
}