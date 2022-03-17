#include<iostream>
using namespace std;
#include<vector>

class Solution {
        string phone[10]={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
public:
void _letterCombinations(string digits,int i,string comstr,vector<string>& retstr)
{
        if(i==digits.size())
        {
                    retstr.push_back(comstr);
                            return;
                                
        }
            string s=phone[digits[i]-'0'];
                for(int j=0;j<s.size();j++)
                {
                            _letterCombinations(digits,i+1,comstr+s[j],retstr);
                                
                }

}
vector<string> letterCombinations(string digits) {
    vector<string> retstr;
    if(digits.empty())
    {
            return retstr;

    }
    string comstr;
    _letterCombinations(digits,0,comstr,retstr);
    return retstr;
        
}
};

int main()
{
    Solution st;
    st.letterCombinations("24");
    return 0;

}
