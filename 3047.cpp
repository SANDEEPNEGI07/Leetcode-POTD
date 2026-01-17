// 3047. Find the Largest Area of Square Inside Two Rectangles

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        int n = bottomLeft.size();

        int max_side = 0;

        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                //width
                int top_right_x = min(topRight[i][0], topRight[j][0]);
                int bottom_left_x = max(bottomLeft[i][0], bottomLeft[j][0]);
                int width = top_right_x - bottom_left_x;

                //Height
                int top_right_y = min(topRight[i][1], topRight[j][1]);
                int bottom_left_y = max(bottomLeft[i][1], bottomLeft[j][1]);
                int height = top_right_y - bottom_left_y;

                // Calculate side
                int side = min(width, height);
                // Update maximum side
                max_side = max(max_side, side);
            }
        }
        return 1LL * max_side * max_side;
    }
};