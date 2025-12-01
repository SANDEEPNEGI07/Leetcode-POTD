// 2141. Maximum Running Time of N Computers

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    bool possible(vector<int>& batteries, long long mid, int n){
        long long targetMin = n * mid;

        for(int i = 0; i < batteries.size(); i++){
            targetMin -= min((long long)batteries[i], mid);

            if(targetMin <= 0) return true;
        }
        return false;
    }

    long long maxRunTime(int n, vector<int>& batteries) {
        
        long long l = *min_element(batteries.begin(), batteries.end());
        
        long long totalMin = 0;
        for(int i = 0; i < batteries.size(); i++){
            totalMin += batteries[i];
        }
        long long r = totalMin / n;

        long long result = 0;

        while(l <= r){
            long long mid = l + (r - l)/2;

            if(possible(batteries, mid, n)){
                result = mid;
                l = mid + 1;
            } else{
                r = mid - 1;
            }
        }
        return result;
    }
};