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
vector<long long> dp0, dp1;

void dfs(long long u, long long p) {
    long long base = 0;
    vector<long long> gain;

    for (auto [v,w] : g[u]) {
        if (v == p) continue;
        dfs(v,u);

        base += dp0[v];
        long long d = w + dp1[v] - dp0[v];
        if (d > 0) gain.emplace_back(d);
    }

    sort(gain.rbegin(), gain.rend());
    dp0[u] = base;
    dp1[u] = base;

    for (int i = 0; i < gain.size() && i < k; ++i) {
        dp0[u] += gain[i];
    }

    for (int i = 0; i < gain.size() && i < k - 1; ++i) {
        dp1[u] += gain[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>k;
    g.resize(n+1);
    dp0.resize(n+1);
    dp1.resize(n+1);
    for (long long i = 1; i <= n-1; ++i) {
        cin>>u>>v>>w;
        g[u].emplace_back(v,w);
        g[v].emplace_back(u,w);
    }

    dfs(0,-1);

    cout << dp0[0] << '\n';
}

