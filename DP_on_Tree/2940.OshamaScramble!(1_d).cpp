#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int maxn = 5e5+7;
vector<vector<int>> tr(maxn);
int dp[maxn];
int sz[maxn];
int n,u,v;

void dfs(int u, int p) {
    dp[u] = 1;
    sz[u] = 1;

    for (auto v : tr[u]) {
        if (v == p) continue;

        dfs(v,u);

        dp[u] = ((long long)(1+dp[v]) * dp[u]) % mod;

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
        ans = ((long long)dp[i] + ans) % mod;
    }

    ans -= (2*n -1);
    if (ans < 0) ans += mod;

    cout<<ans<<endl;

    return 0;
}
