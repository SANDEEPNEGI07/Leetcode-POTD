// Next Greater Numerically Balanced Number

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool balanced(int num){
        vector<int> freq(10);

        while(num > 0){
            int digit = num % 10;
            freq[digit]++;
            num = num/10;
        }

        for(int d = 0; d < 10; d++){
            if(freq[d] != 0 && freq[d] != d){
                return false;
            }
        }
        return true;
    }

    int nextBeautifulNumber(int n) {
        for(int num = n+1; num <= 1224444; num++){
            if(balanced(num)){
                return num;
            }
        }
        return -1;
    }
};