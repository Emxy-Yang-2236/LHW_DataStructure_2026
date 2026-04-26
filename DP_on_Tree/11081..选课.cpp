#include "Graph_Demo_of_tree.hpp"
#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int maxm = 210;
int dp[maxm][maxm], sz[maxm];
bool vis[maxm];
vector<vector<int>> tr(maxm);
int m,n;
int u,w;

void dfs(int u) {
    vis[u] = true;
    for (auto v: tr[u]) {
        if (vis[v]) continue;
        cout<<"on : "<<u<<"  , checking : "<<v<<endl;
        dfs(v);
        cout<<"now dfs on : "<<u<<endl;
        for (int i = min(sz[u], n + 1); i >= 1; --i) {
            for (int j = 1; j <= sz[v] && i+j <= n + 1; ++j) {
                int tmp = dp[u][i+j];
                dp[u][i+j] = max(dp[u][i+j], dp[u][i] + dp[v][j]);
                cout<<"operating dp["<<u<<"]["<<i+j<<"] , the old value is : "<<tmp<<" , the new value is : "<<dp[u][i+j]<<endl;
            }
        }

        sz[u] += sz[v];
    }
}

int main() {
    cin>>m>>n;
    memset(vis, false, sizeof(bool)* (m+1));
    sz[0] = 1;
    dp[0][1] = 0;
    for (int i = 1 ; i <= m ; ++i) {
        cin>>u>>w;
        tr[u].emplace_back(i);
        dp[i][1] = w;
        sz[i] = 1;
    }

    printTree(tr,0);
    cout<<endl<<"Print weight:  ";
    for (auto i = 0 ; i <= m ; ++i) {
        cout<<dp[i][1]<<" ";
    }
    cout<<endl<<endl;;
    dfs(0);
    cout<<dp[0][n+1]<<endl;

}