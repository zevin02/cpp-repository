#pragma once 
using namespace std;
#include<iostream>
#include<cstring>
#include<assert.h>
namespace xzw
{

    template<class T>
        class vector
        {
            public:
            typedef T* iterator;//指针，迭代器
            vector()
            :_start(nullptr)
             ,_finish(nullptr)
             ,_endofstorage(nullptr)

            {
            
            }
            iterator begin()
            {
                return _start;
            }
            iterator end()
            {
                return _finish;
            }
            T& operator[](size_t i)//获得第i个位置的值
            {
                assert(i<size());//合理的i才可以使用

                return _start[i];//因为出了作用域依然存在不会消失，所以用引用返回
            }
            size_t size()//返回有多少有效元素
            {
                return _finish-_start;
            }
            size_t capacity()const{//记录容量
                return _endofstorage-_start;
            }
            void push_back(const T& x)
            {
                if(_finish==_endofstorage)//达到容量了
                {
                    //扩容
                    //

                    size_t newcapacity=capacity()==0?4:capacity()*2;//新开辟空间
                    T* tmp=new T[newcapacity];//把开空间和扩容弄在了一起操作
                    if(_start)//_start不为空，就说明有数据，有数据，我们在上面new之后，就要把原来的数据拷贝过去，再把之前的给析构掉
                    {
                        memcpy(tmp,_start,sizeof(T)*size());
                        delete[] _start;//把前面的给析构掉
                    }

                    _finish=tmp+size();
                    _start=tmp;
                    _endofstorage=_start+newcapacity;
                }
               *_finish=x;
               
               ++_finish;
            }
            private:
            iterator _start;
            iterator _finish;
            iterator _endofstorage;

        };
    
            void test_vector1()
            {
                vector<int> v;
                v.push_back(1);
                v.push_back(2);
                v.push_back(3);
                v.push_back(4);
                v.push_back(5);
                v.push_back(6);
                v.push_back(7);
               size_t i=0;
                for(i=0;i<v.size();i++)
                {
                   std:: cout<<v[i]<<" ";
                }    
                vector<int>::iterator it=v.begin();
                while(it!=v.end())
                {
                    cout<<*it<<" ";
                    ++it;
                }
                cout<<endl;
            }
}
