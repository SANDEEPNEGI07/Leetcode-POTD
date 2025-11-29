// 3512. Minimum Operations to Make Array Sum Divisible by K

#include<bits/stdc++.h>

using namespace std;

// Solution 1 - adding the modulas of sum to next element, so that it won't overflow(When constraints are high)
class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        int sum = 0;
        for(int i = 0; i < nums.size(); i++){
            sum += nums[i]; 
            sum %= k; // adding the remainder of previous sum to the next element
        }
        return sum;
    }
};

// Solution 2 - total sum % k (When constraints are low)
class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        int sum = 0;
        for(int &num : nums){
            sum += num;
        }
        return sum % k; 
        // Remainder will be the number of operation need to make it divisile by k
    }
};