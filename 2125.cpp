// 2125. Number of Laser Beams in a Bank

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int countOne(string &s){
        int count = 0;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '1'){
                count++;
            }
        }
        return count;
    }

    int numberOfBeams(vector<string>& bank) {
        vector<int> counter;
        for(auto it : bank){
            int cnt = countOne(it);

            if(cnt > 0){
                counter.push_back(cnt);
            }
        }
        int sum = 0;
        if(counter.size() <= 1) return 0;
        for(int i = 1; i < counter.size(); i++){
            sum += counter[i] * counter[i-1];
        }
        return sum;
    }
};