// 2872. Maximum Number of K-Divisible Components

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int count;

    int dfs(int node, int parent, unordered_map<int, vector<int>> &adj, vector<int> &values, int k){
        int sum = values[node];

        // for childrens if exists
        for(auto &it : adj[node]){
            if(it != parent){
                sum += dfs(it, node, adj, values, k);
                sum %= k;
            }
        }

        //Node which have no child will be check if its sum % k == 0 or not
        sum %= k;
        if(sum == 0){
            count++;
        }
        return sum;
    }
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        unordered_map<int, vector<int>> adj;

        for(auto &e : edges){
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        count = 0;
        dfs(0, -1, adj, values, k);

        return count;
    }
};