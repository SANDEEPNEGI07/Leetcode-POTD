// 1262. Greatest Sum Divisible by Three

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;

        // Storing element with remainder 1 in r1 and remainder 2 in r2
        vector<int> r1, r2;
        
        for(int x : nums){
            sum += x;

            if(x % 3 == 1){
                r1.push_back(x);
            } 
            else if(x % 3 == 2){
                r2.push_back(x);
            }
        }

        if(sum % 3 == 0) return sum;

        // Sorting the elements so we get smallest element with rem 1 and 2.
        sort(r1.begin(), r1.end());
        sort(r2.begin(), r2.end());

        int ans = 0;

        if(sum % 3== 1){
            int opt1 = (r1.size() >= 1 ? sum - r1[0] : 0);
            int opt2 = (r2.size() >= 2 ? sum - r2[0] - r2[1] : 0);
            ans = max(opt1, opt2);
        }
        else{
            int opt1 = (r1.size() >= 2 ? sum - r1[0] - r1[1] : 0);
            int opt2 = (r2.size() >= 1 ? sum - r2[0] : 0);
            ans = max(opt1, opt2);
        }
        return ans;
    }
};