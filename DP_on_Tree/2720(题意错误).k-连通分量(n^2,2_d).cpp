#include <bits/stdc++.h>
using namespace std;

struct Edge {
    long long to;
    long long w;
};

const long long maxn = 1e6;
const long long NEG = -1e15;
long long n,k,u,v,w;
vector<vector<Edge>> g;
vector<vector<long long>> dp;

void dfs(long long u, long long p) {
    dp[u] = vector<long long>(k+2, NEG);
    dp[u][1] = 0;

    for (auto [v,w] : g[u]) {
        if (v == p) continue;
        dfs(v,u);

        vector<long long> tmp(k+2, NEG);
        long long best = NEG;

        for (long long t = 1; t <= k+1; ++t) {
            best = max(best, dp[v][t]);
        }

        for (long long sz = 1; sz <= k+1; ++sz) {
            if (dp[u][sz] == NEG) continue;

            tmp[sz] = max(tmp[sz], dp[u][sz] + best);

            for (long long t = 1; t+sz <= k+1; ++t) {
                if (dp[v][t] == NEG) continue;
                tmp[sz+t] = max(tmp[sz+t], dp[u][sz] + dp[v][t] + w);
            }
        }
        dp[u].swap(tmp);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>k;
    g.resize(n+1);
    dp.resize(n+1);
    for (long long i = 1; i <= n-1; ++i) {
        cin>>u>>v>>w;
        g[u].emplace_back(v,w);
        g[v].emplace_back(u,w);
    }

    dfs(0,-1);

    long long best = NEG;

    for (long long t = 1; t <= k+1; ++t) {
        best = max(best, dp[0][t]);
    }

    cout<<best<<endl;

}
