// set可以进行元素去重，同时以升序排列,二叉树

#include <iostream>
using namespace std;
#include <set>
void test1()
{
  //排序+去重
  //set不支持修改


  set<int> s;
  s.insert(1); //如果元素已经存在就不会插入
  s.insert(9);
  s.insert(2);
  s.insert(2);
  s.insert(3);
  s.insert(-1);
  s.insert(-9);
  s.erase(1);//删除, 成功返回1，失败返回0
  s.erase(0);//没找到就不会删除,相等于封装了迭代器的删除
  auto pos=s.find(-9);//获得2的迭代器位置
  set<int> l;
  l.insert(0);
  l.insert(1);
  l.insert(2);
  l.insert(3);
  s.swap(l);//两个set进行交换
  if(pos!=s.end())//删除一个位置，必须要进行检查，必须是一个有效的迭代器
  {
    //找到了
    cout<<"1"<<endl;
    s.erase(pos);
  }
  auto it = s.begin();
  while (it != s.end())
  {
    cout << *it << " ";
    it++;
  }
  // cout<<s.size()<<endl;
  ////s.erase(2);//删除2这个元素
  // if(s.count(2)==1)//如果有2就返回1，没有2就返回0
  //{
  //  cout<<"find 2"<<endl;
  // }
  // else
  //{
  //   cout<<"no find 2"<<endl;
  // }
  if(s.count(1)!=0)
  {
    //说明找到了
    cout<<"222"<<endl;

  }
  
}

/*
  key就是判断在不在，是不是
  k-v就是查找判断
*/

//序列式容器一般都用push，关联式容器一般都用insert

void test2()
{
  //set是可以排序加去重，
  //现在我们只想要排序，不要去重
  multiset<int> s;
  s.insert(1);
  s.insert(1);
  s.insert(2);
  s.insert(3);
  s.insert(2);
  s.insert(5);
  s.erase(1);
  auto it=s.begin();
  
  //这个就是只排序不去重
  auto its=s.find(1);//找哪一个1呢,找到的是第一个1,返回的是第一个中序第一个value值所在的迭代器
  
  while(it!=s.end())
  {
    cout<<*it<<" ";
    it++;
  }

  //我要删除所有的1
  its=s.find(1);
  //不推荐
  // while(its!=s.end()&&*its==1)
  // {
  //   auto next=its;
  //   next++;
  //   s.erase(its);//循环删除
  //   its=next;//提前保存下一个
  // }

  

  //也可以用迭代器区间来删除
 
  //直接用值取删除就行了
}


int main()
{
  test1();
  
  test2();
  return 0;
}