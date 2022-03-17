//杨辉三角
#include<iostream>
using namespace std;
#include<vector>
class Solution {
    public:
        vector<vector<int>> generate(int numRows) {
            vector<vector<int>>vv;
            //第1行1个，
            vv.resize(numRows);
            for(int i=0;i<numRows;i++)
            {

                vv[i].resize(i+1);
                vv[i].front()=vv[i].back()=1;
            }
            for(int i=0;i<numRows;i++)
            {
                for(int j=0;j<vv[i].size();j++)
                {
                    if(vv[i][j]==0)
                    {
                        vv[i][j]=vv[i-1][j]+vv[i-1][j-1];
                    }
                }
            }
                return vv;
        }

};
int main()
{
    Solution st;
    st.generate(5);
    
    return 0;
}
