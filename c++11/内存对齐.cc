#include<iostream>
using namespace std;


//c++11引入了内存对齐
//alignof，alignas,这两个是关键字
//aligned_storage alig，前一个是一个类，后一个是函数

struct Foo {   
  char c;     // 0  |  1  |  4
  int i1;     // 4  |  5  |  8
  int i2;     // 8  |  9  |  12 
  long l;     // 16 |  17 |  20
};

void Testalignof()
{
    //alignof,可以直接获取类型T的内存对齐要求，alignof的返回值为size_t,用法类似sizeof

    size_t charsize=alignof(char);//1
    size_t intsize=alignof(int);//4
    size_t longsize=alignof(long);//4
    size_t foo=alignof(Foo());//计算一个类里面的最大对齐数，所以为8
    cout<<charsize<<endl;
    cout<<intsize<<endl;
    cout<<longsize<<endl;
}

// in <type_traits>
template< std::size_t Len, 
          std::size_t Align = /*default-alignment*/ >
struct aligned_storage;

void Testaligned_storage()
{
    //c++11中引入了一个满足内存对齐要求的静态内存分配类
    //对象构造的时候，就分配了len个字节的内存，且满足align的对齐要求
    //这个构造的每个对象都满足内存对齐的要求
    std::aligned_storage_t<sizeof(int), alignof(int)> data[2];
}



int main()
{
    Testalignof();
    Testaligned_storage();
    return 0;
}