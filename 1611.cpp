// 1611. Minimum One Bit Operations to Make Integers Zero

#include<iostream>

using namespace std;

class Solution {
public:
    int minimumOneBitOperations(int n) {
        int res = 0;
        while(n){
            res ^= n;
            n >>= 1;
        }
        return res;
    }
};

// Used Gray-code conversion
//So we just need to find the number of steps from n’s Gray code representation to 0’s Gray code (which is 0).