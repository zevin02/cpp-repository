class Solution {
public:
    int evalRPN(vector<string>& tokens) {
    stack<int>ret;
    int i=0;
    int top;
    while(i<tokens.size())
    {
    if(tokens[i]=="+")
    {
  top = ret.top();
                ret.pop();
                ret.top() += top;
                i++;
    }
       else if(tokens[i]=="-")
    {
  top = ret.top();
                ret.pop();
                ret.top() -= top;
                i++;
    }
           else if(tokens[i]=="*")
    {
  top = ret.top();
                ret.pop();
                ret.top() *= top;
                i++;
    }
           else if(tokens[i]=="/")
    {
  top = ret.top();
                ret.pop();
                ret.top() /= top;
                i++;
    }
    else
    {
         ret.push(stoi(tokens[i]));
                i++;
    }
    }
    return ret.top();
    }
};
