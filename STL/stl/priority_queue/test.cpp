//优先级队列
////底层实际上是一个堆heap
#include<iostream>
#include<queue>
#include<functional>
using namespace std;
#ifdef x
#define x 1
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        //如果n>>k的话，我们可以建一个k个树的小堆
        priority_queue<int,vector<int>,greater<int>> pq(nums.begin(),nums.begin()+k);
        //顶部就是第k小的数字
        //剩下的n-k个数依次和堆顶部数据比较
        //比他大，就替换他入堆
        for(size_t i=k;i<nums.size();i++)
        {
            if(nums[i]>pq.top())
            {
                pq.pop();
                pq.push(nums[i]);
            }

        }
        return pq.top();

    }
};
#endif 

void test_priority()
{
    //默认是大的优先级高，默认是大堆
    
    priority_queue<int,vector<int>,greater<int>>pq;//使得小的优先级高,小堆
  //  priority_queue<int>pq;
    pq.push(1);
    pq.push(2);
    pq.push(9);
    pq.push(0);
    pq.push(7);
    //不提供迭代器
    while(!pq.empty())//堆排序
    {   
        cout<<pq.top()<<" ";//获得堆的数据,
        pq.pop();//删除的是堆顶部的数据
    }
    cout<<endl;
}
int main()
{
    test_priority();
    return 0;
}


