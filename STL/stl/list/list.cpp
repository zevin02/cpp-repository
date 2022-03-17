#include<iostream>
using namespace std;
#include<list>
//list是双向带头循环的链表
//在任意位置O（1）插入和删除
void test_list1()

{
list<int> it;//初始化了一个空的list容器
list<int> kt(12,30);//调用构造函数给前两个插入了12个30
//当然也可以实现拷贝构造
list<int> copy(it);
copy.pop_front();

it.swap(copy);//it和copy连个链表交换
//和算法中的swap差不多

it.push_back(1);//尾插
it.push_back(2);//尾插
it.push_back(3);//尾插
it.push_back(4);//尾插
it.push_back(5);//尾插

//list并不能使用下标进行搜索，因为他不是连续的
//所以只能用迭代器进行访问
list<int> ::iterator dt=it.begin();
while(dt!=it.end())
{
  cout<<*dt<<" ";
  dt++;

}
cout<<endl;

//也可以使用范围for，但是范围for也是使用迭代器实现的
//for(auto e:it)
//{
//  cout<<e<<endl;
//}


//也可以用反向迭代器
 list<int> ::reverse_iterator rt=it.rbegin();
//从尾巴开始遍历

//尾删除
it.pop_back();
//头插
it.push_front(0);
//头删
 it.pop_front();
while(rt!=it.rend())
{
  cout<<*rt<<" ";
  rt++;
}
cout<<endl;


}
//排序
void test_list2()
{

list<int> it;//初始化了一个空的list容器
it.push_back(1);//尾插
it.push_back(1);//尾插
it.push_back(1);//尾插
it.push_back(3);//尾插
it.push_back(2);//尾插
it.push_back(4);//尾插
//不能用算法里的sort，因为这个数随即迭代器

list<int> it1;//初始化了一个空的list容器
it1.push_back(1);//尾插
it1.push_back(6);//尾插

//splice


//it.sort();//归并排序,也可以排序出来,按升序排列
//it.reverse();//逆置反转
//
//it.unique();//去重，首先要排序,不然会去不干净
list<int> ::iterator dt=it.begin();
it.splice(dt,it1);//把it1里面的所有元素直接接到it中dt迭代器处，

//it.remove(1);//删除特定的值
//把所有的1都删除

while(dt!=it.end())
{
  cout<<*dt<<" ";
  dt++;

}
cout<<endl;



}




void test_list3()
{

list<int> it;//初始化了一个空的list容器
it.push_back(1);//尾插
it.push_back(7);//尾插
it.push_back(9);//尾插
it.push_back(3);//尾插
it.push_back(2);//尾插
it.push_back(4);//尾插

list<int> it1;//初始化了一个空的list容器
it1.push_back(1);//尾插
it1.push_back(6);//尾插
list<int> ::iterator s=it.begin();
s++;

it.splice(s,it1);
if(it1.empty())//判断是否为空
{
  cout<<"empty"<<endl;
}
it.insert(s,0);//在s迭代器的位置插入一个0
it.erase(s);//删除s迭代器位置的值
int k=it.front();//获得it的第一个值
cout<<k<<endl;

}
int main()
{
//  test_list1();
  test_list2();
test_list3();
  return 0;
}
