// 2257. Count Unguarded Cells in the Grid

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards,
                       vector<vector<int>>& walls) {
        vector<vector<char>> grid(m, vector<char>(n, '.'));
        for (auto i : guards) {
            grid[i[0]][i[1]] = 'G';
        }
        for (auto i : walls) {
            grid[i[0]][i[1]] = 'W';
        }
        int ans = 0;
        vector<vector<int>> dir = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

        for (auto it : guards) {
            int x = it[0];
            int y = it[1];
            for (auto d : dir) {
                int dx = x + d[0];
                int dy = y + d[1];
                while (dx >= 0 && dx < m && dy >= 0 && dy < n) {
                    if (grid[dx][dy] == 'G' || grid[dx][dy] == 'W')break;
                    if (grid[dx][dy] == '.')
                        grid[dx][dy] = '+';
                    dx += d[0];
                    dy += d[1];
                }
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '.')
                    ++ans;
            }
        }
        return ans;
    }
};