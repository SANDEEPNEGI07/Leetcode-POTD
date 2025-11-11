// 474. Ones and Zeroes

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution{
public:
    int findMaxForm(vector<string> &strs, int m, int n){
        vector<vector<int>> dp(m + 1, vector<int> (n + 1, 0));

        for(auto &s : strs){
            int zeroes = count(s.begin(), s.end(), '0');
            int ones = count(s.begin(), s.end(), '1');

            for(int i = m; i >= zeroes; i--){
                for(int j = n; j >= ones; j--){
                    dp[i][j] = (dp[i][j], dp[i - zeroes][j - ones] + 1);
                }
            }
        }
        return dp[m][n];
    }
};