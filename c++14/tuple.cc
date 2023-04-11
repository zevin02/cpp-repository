#include <iostream>
using namespace std;
#include <tuple>
#include <string>
#include <functional>
// C++元组是将多个值组合成一个对象，相当于结构体

void construct()
{
    tuple<int, double, string> t(42, 2.2, "hello"); //构造一个元组
    //可以使用get函数从元组中取出一个元素
    int i = get<0>(t); //尖括号里面就是提取元组中的第几个元素
    double d = get<1>(t);
    string c = get<2>(t);

    auto m = make_tuple(1, 2, 3); //这个也可以构造一个tuple
    // make_tuple也支持传递引用，但是需要向线程那样使用 ref
    string str = "d";
    auto l = make_tuple(std::ref(str)); //引用传递，这样就不是传递拷贝了,但是需要使用一个functional的头文件
}

template<size_t ...Is,class ...Args>
//这个函数使用了一个元组和一个索引序列
void printTupleReverseImpl(tuple<Args...>& t,index_sequence<Is...>)
{
    cout<<(sizeof...(Args));//计算可变模板的参数个数
    // ((cout<<get<sizeof ...(Args)-Is-1>(t)<<","),...);
    ((cout<<get<Is>(t)<<","),...);
}


//可变模板类
template<class ...Args>
void printTupleReverse(tuple<Args...>& t)//元组里面是一个可变模板参数
{
    constexpr size_t size=sizeof ...(Args);//计算Args的参数包的大小,这个参数在编译的时候就被执行了

    printTupleReverseImpl(t,std::index_sequence_for<Args...>{});

    auto p=make_index_sequence<size>{};//根据t生成一个序列索引

    cout<<endl;    
}


void testIndexSequence1()
{
    /*
        index_sequence是一个模板类，用于表示一系列连续的整数序列，可以在模板元编程的时候使用
        在无需显示列出当读的整数是生成类似for循环的功能函数
        
    */
   tuple<int,double,string> t(42,3.13,"hello");
   printTupleReverse(t);
}

//Is里面实际上就是一个从0-size-1的一个参数包
template<class Tuple,size_t ...Is>
//这个地方使用元组展开语法，将索引按照顺序获取类型名字，并且返回
void help(Tuple t,index_sequence<Is...>)
{
    //这个使用了元组折叠语法
    /*
    将元组展开后就是这样的
    (cout << get<0>(t) << endl), (cout << get<1>(t) << endl), ..., (cout << get<N-1>(t) << endl)
*/
    ((cout<<get<Is>(t)<<endl),...);//进行多次的输出

}



template<class ...Args>
void printtuple(const tuple<Args...>& t)
{
    constexpr size_t size=sizeof ...(Args);
    help(t,std::make_index_sequence<size>{});
}

void testIndexSequence2()
{
   tuple<int,double,string> t(42,3.13,"hello");
    printtuple(t);
}
int main()
{
    construct();//简单的使用
    testIndexSequence1();//测试index_sequence()
    testIndexSequence2();//测试index_sequence()
    return 0;
}