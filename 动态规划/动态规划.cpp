#include<iostream>
using namespace std;
//动态规划
//考虑
//1.状态定义
//2.状态转义方程（递推方程）（一步一步的变化达到当前的状态）
//3.初始化状态
//4.结果的返回

//实用场景
//最大值，最小值，可不可行，是不是，方案个数


//斐波那契
//状态：定义成第i项的值
//求第n项的结果
//状态转义方程 f(i)=f(i-1)+f(i-2)
//初始状态f（0）=0，f（1）=1

class Solutionfib {
public:
    int fib(int n) {
        int* f = new int[n + 2];
        //初始状态
        f[0] = 0;
        f[1] = 1;
        long long mod = 1e9 + 7;
        int i = 2;
        for (i = 2; i <= n; i++)
        {
            f[i] = (f[i - 1] + f[i - 2]) % mod;//状态转义方程
        }
        return f[n];//返回结果

    }
};


//字符串分割
//给你一个字符串 s 和一个字符串列表 wordDict 作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。

//注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。
//输入: s = "leetcode", wordDict = ["leet", "code"]
//输出 : true
//解释 : 返回 true 因为 "leetcode" 可以由 "leet" 和 "code" 拼接成。
//
//因为是判断可不可以，所以可以用动态规划求解

//全部状态都找出来，进行匹配是否有字串可以找得到
//
//问题：字符串可不可以被分割--》抽象出来状态
//状态的定义：某一个字串可不可以被分割，通过某一字串能不能被找得到
//f（i）=========》前i个字符是否可以被分割
//f（n）代表字符串的所有字符能不能被分割
//状态转义方程：j<i&&f[j]&&[j+1,i]

//f（4）表示前4个字符可不可以被分割，是可以的
//初始状态：整体能不能找得到f（0）：一般为真，辅助的一个状态




//假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
//
//每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
//
//
//
//示例 1：
//
//输入：n = 2
//输出：2
//解释：有两种方法可以爬到楼顶。
//1. 1 阶 + 1 阶
//2. 2 阶
//
//示例 2：
//
//输入：n = 3
//输出：3
//解释：有三种方法可以爬到楼顶。
//1. 1 阶 + 1 阶 + 1 阶
//2. 1 阶 + 2 阶
//3. 2 阶 + 1 阶
//
//来源：力扣（LeetCode）
//链接：https ://leetcode-cn.com/problems/climbing-stairs
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

class Solution {
public:
    int climbStairs(int n) {

        //第i解，要么是从第i-1解爬过来，或者是从i-2解爬过来


        //初始状态
        int* f = new int[n + 2];
        //f代表到第i阶的方法数

        f[0] = 1;//从0到0
        f[1] = 1;//0到1
        for (int i = 2; i <= n; i++)
        {
            f[i] = f[i - 1] + f[i - 2];//状态转义方程
        }
        return f[n];//返回的数
    }
};
#include<vector>
//class Solution {
//public:
//    int minCostClimbingStairs(vector<int>& cost) {
//        int* f = new int[cost.size() + 2];//f[i]代表到第i层需要花的钱，
//        //初始化，第0到0就不用钱，第1到1也不用钱
//        f[0] = 0, f[1] = 0;
//        for (int i = 2; i <= cost.size(); i++)
//        {
//
//            f[i] = min(f[i - 1] + cost[i - 1], f[i - 2] + cost[i - 2]);//状态转义方程
//        }
//        cout << cost.size() << endl;
//        return f[cost.size()];//到达塔顶//结束
//
//    }
//};


//198. 打家劫舍
//
//你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
//
//给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。


//相邻不可以偷
int rob(vector<int>& nums) {
    int* f = new int[nums.size() + 2];//f[i]代表偷到第i家最多头多少钱
    //初始化
    f[0] = nums[0];
    if (nums.size() >= 2)
        f[1] = max(nums[0], nums[1]);
    //
    for (int i = 2; i < nums.size(); i++)
    {
        f[i] = max(f[i - 2] + nums[i], f[i - 1]);
    }
    return f[nums.size() - 1];
}
int main()
{
    vector<int>arr{2};
    rob(arr);
    return 0;
}