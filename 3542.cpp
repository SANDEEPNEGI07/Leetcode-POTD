// 3542. Minimum Operations to Convert All Elements to Zero

#include<iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        vector<int> stack(nums.size() + 1, 0);
        int top = 0;
        int ans = 0;

        for(int num : nums){
            while (stack[top] > num){
                top--;
                ans++;
            }
            if (stack[top] != num){
                top++;
                stack[top] = num;
            }
        }
        return ans + top;
    }
};