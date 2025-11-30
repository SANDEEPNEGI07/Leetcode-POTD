// 1590. Make Sum Divisible by P

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int sum = 0;
        int n = nums.size();

        for(int i = 0; i < nums.size(); i++){
            sum = (sum + nums[i]) % p;   
        }

        if(sum == 0) return 0;

        unordered_map<int, int> mp; // prev sum % p ko store karega
        
        int curr = 0;
        mp[0] = -1;

        int result = n;
        for(int j = 0; j < n; j++){
            curr = (curr + nums[j]) % p;

            int remain = (curr - sum + p) % p; // adding p to handle the -ve modulas
            if(mp.find(remain) != mp.end()){
                result = min(result, j - mp[remain]);
            }

            mp[curr] = j;
        }

        return (result == n) ? -1 : result;
    }
};