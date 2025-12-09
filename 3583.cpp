// 3583. Count Special Triplets

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int M = 1e9 + 7;
    int specialTriplets(vector<int>& nums) {
        unordered_map<int, int> valid_i;
        unordered_map<int, int> valid_j;

        int result = 0;

        for(int &num : nums){
            if(num % 2 == 0){ //if num is a valid k
                result = (result + valid_j[num/2]) % M;
            }

            //if valid j or not
            valid_j[num] = (valid_j[num] + valid_i[num*2]) % M;

            valid_i[num]++;
        }
        return result;
    }
};