#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int maxn = 3000;
vector<vector<int>> tr(maxn);
int dp[maxn][maxn];        //在选择点u的情况下，以u为根的子树大小为y的联通分量的情况数目
int sz[maxn];
int n,u,v;

void dfs(int u, int p) {
    dp[u][1] = 1;
    sz[u] = 1;

    for (auto v : tr[u]) {
        if (v == p) continue;

        dfs(v,u);

        for (int i = sz[u]; i >= 1; --i) {
            for (int j = 1; j <= sz[v]; ++j) {
                dp[u][i+j] = ((long long)dp[u][i] * dp[v][j] + dp[u][i+j]) % mod;
            }
        }

        sz[u] += sz[v];
    }
}

int main() {
    cin>>n;
    for (int i = 1 ; i <= n-1 ; ++i) {
        cin>>u>>v;
        tr[u].emplace_back(v);
        tr[v].emplace_back(u);
    }
    dfs(1,0);

    int ans = 0;
    for (int i = 1 ; i <= n ; ++i) {
        for (int s = 3 ; s <= n ; ++s) {
            ans = ((long long)ans + dp[i][s]) % mod;
        }
    }
    cout<<ans<<endl;

    return 0;
}