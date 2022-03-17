#include <iostream>
#include<vector>
using namespace  std;
class Solution {
    public:
        int singleNumber(vector<int>& nums) {
            int value=0;
            for(int i=0;i<nums.size();i++)
            {
                value^=nums[i];

            }
            return value;
                
        }

};
int main()
{
    Solution st;
   vector<int>nums;
   nums.push_back(2);
   nums.push_back(1);
   nums.push_back(2);
   int ret=st.singleNumber(nums);
   cout<<ret<<endl;
    return 0;
}
