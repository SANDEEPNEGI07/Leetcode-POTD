// 3381. Maximum Subarray Sum With Length Divisible by K

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();

        vector<long long> prefixSum(n);
        prefixSum[0] = nums[0];

        for(int i = 1; i < n; i++){
            prefixSum[i] = prefixSum[i - 1] + nums[i];
        }

        // result to hold the max sum
        long long result = LLONG_MIN;

        // There are k - 1 starting elements after that subarray are repeating itselfs
        for(int start = 0; start < k; start++){
            int i = start;
            long long currSum = 0;

            // Kadane's algorithm
            while(i < n && i + k - 1 < n){ // i + k - 1 -> end point of the subarray
                int j = i + k - 1;
                long long subSum = prefixSum[j] - ((i > 0) ? prefixSum[i - 1] : 0);

                currSum = max(subSum, currSum + subSum);
                result = max(result, currSum);

                i += k; // 2k,3k so that the length will be divisible by k 
            }
        }
        return result;
    }
};