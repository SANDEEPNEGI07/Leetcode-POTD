// 3370. Smallest Number With All Set Bits

#include <iostream>
#include <math.h>
using namespace std;

class Solution {
public:
    int smallestNumber(int n) {
        int result = 0;
        for(int i = 0; i <= n; i++){
            if(pow(2, i) > n){
                result = pow(2, i) - 1;
                break;
            }
        }
        return result;
    }
};