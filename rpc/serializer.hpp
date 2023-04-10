#pragma once
//序列化
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include<iostream>
#include<assert.h>
#include<cstring>
using namespace std;

// 存储数据流的容器,因为数据在TCP里面是以字节流的形式来展示
// Buffer这个类继承了vector<char>这个容器,所以所有的数据都是放到这个容器里面
class Buffer : public std::vector<char>
{
public:
    typedef std::shared_ptr<Buffer> ptr; //把当前的一个buffer的智能指针重命名为ptr
    Buffer() : curpos_(0) {}
    Buffer(const char *s, size_t len) : curpos_(0)
    {
        insert(begin(), s, s + len);
    }
    const char *data() //返回buffer容器的底层指针
    {
        return &(*this)[0];
    }
    const char *curdata() //返回buffer容器从curpos开始位置的底层指针
    {
        return &(*this)[curpos_]; //返回从curpos位置开始的字符串
    }
    size_t cursize() const //返回当前可读取的数据个数
    {
        return size() - curpos_;
    }
    void offset(int k) { curpos_ += k; }
    //插入到数据流中
    void append(const char *s, size_t len)
    {
        insert(end(), s, s + len); //把数据尾插进去
    }
    //把游标设置成0，清空里面所有的数据
    void reset()
    {
        curpos_ = 0;
        clear();
    }

private:
    size_t curpos_; //表示当前数据流的读取位置
};

// 主机字节序是否小端字节序
static bool isLittleEndian() //如果是小端字节序的话，就返回一个小端字节序
{
    static uint16_t flag = 1;
    static bool little_end_flag = *((uint8_t *)&flag) == 1;
    return little_end_flag;
}

class Serializer
{
public:
    typedef std::shared_ptr<Serializer> ptr; //再把serializer这个函数的智能指针设置为ptr，暴露给外面
    Serializer()
    {
        buffer_ = std::make_shared<Buffer>(); // buffer这里是一个智能指针，所以我们需要先make_shared来构造一下这个智能指针对象
    }
    Serializer(const char *s, size_t len)
    {
        buffer_ = std::make_shared<Buffer>();
        input(s, len); //使用了一个字符串来进行初始化
    }
    Serializer(Buffer::ptr buffer) //使用了一个Buffer的智能指针来进行初始化
        : buffer_(buffer)
    {
    }

    template <typename T>
    void input_type(T t);//在类里面声明，但是在类外面定义

    template <typename T>
    void output_type(T &t);

    void reset() //调用buffer中的reset函数来清空数据
    {
        buffer_->reset();
    }
    void clear() //清空数据
    {
        reset();
    }
    void input(const char *data, int len) // input就是把数据添加到buffer里面
    {
        buffer_->append(data, len);
    }

    template <typename Tuple, std::size_t Id>
    void getv(Serializer &ds, Tuple &t)
    {
        ds >> std::get<Id>(t);
    }

    template <typename Tuple, std::size_t... I>
    Tuple get_tuple(std::index_sequence<I...>)
    {
        Tuple t;
        std::initializer_list<int>{(getv<Tuple, I>(*this, t), 0)...};
        return t;
    }

    template <typename T>
    Serializer &operator>>(T &i)//流输出
    {
        output_type(i);
        return *this;
    }

    template <typename T>
    Serializer &operator<<(T i) //重载<<，向buffer里面添加数据
    {
        input_type(i);//根据对应的不同类型，调用对应的函数
        return *this;
    }

    const char *data() //放回当前数据的首地址
    {
        return buffer_->curdata();
    }
    size_t size() const //返回buffer中的当前还可以读取的元素
    {
        return buffer_->cursize();
    }
    std::string toString() //将buffer首地址中的数据转化成为string类型
    {
        return std::string(data(), size());
    }

private:
    static void byteOrder(char *s, int len)//按照字节序来插入
    {
        if (isLittleEndian())//如果当前是小端机，就需要把字符串进行反转
            std::reverse(s, s + len);
    }

private:
    int byteOrder_;
    Buffer::ptr buffer_; //这个是一个智能指针对象
};

template <typename T>
inline void Serializer::input_type(T v)//这个地方就是在类里面声明然后在类外面进行实现,这个一般是非字符串类型要这样做
{
    size_t len = sizeof(v);//获得当前v的字节数
    char *p = reinterpret_cast<char *>(&v);//把传入进行的v强制类型转化成一个字符串
    byteOrder(p, len);
    input(p, len);//把数据添加到buffer中
}

//偏特化，这个地方需要写一个<>
template <>
inline void Serializer::input_type(std::string v)//指定特化成什么类型
{
    // 先存入字符串长度，存入字符串的长度是因为在反序列化的时候，程序可以先读取字符串的长度，并且根据长度信息在二进制流中定位字符串数据

    uint16_t len = v.size();
    input_type(len);//先输入字符串的长度
    byteOrder(const_cast<char*>(v.c_str()), len);//将v按照对应的字节序列的方式进行一个转化
    // 将转化好在字符串放到buffer中
    input(v.c_str(), len);
}

//再进行一个偏特化
template <>
inline void Serializer::input_type(const char* v)
{
    input_type<std::string>(std::string(v));//指定当前类型为string类型，进行调用
}


template <typename T>
inline void Serializer::output_type(T& v)//根据buffer里面存储的数据进行一个反序列化输出
{
    size_t len = sizeof(v);//先获得元素的字节大小
    assert(size() >= len);
    ::memcpy(&v, data(), len);//把buffer中的数据拷贝给v
    buffer_->offset(len);//将对应的buffer中的有变进行移动
    byteOrder(reinterpret_cast<char*>(&v), len);//再把他根据对应的字节许转化回来,因为插入的时候就因为是小端机而反转了一次
    //所以现在获得的时候也要再反转回来
}

//将输出
template <>
inline void Serializer::output_type(std::string& v)//将对应的流里面的字符串类型进行输出到对应的元素中
{
    uint16_t strLen = 0;//获得字符串的长度
    output_type(strLen);//递归调用
    v = std::string(data(), strLen);
    buffer_->offset(strLen);
    byteOrder(const_cast<char*>(v.c_str()), strLen);
}