#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+7;
vector<vector<int>> tr(maxn);
vector<int> sz(maxn);
int n,u,v;
long long ans;

void dfs_sz(int u, int p) {
    sz[u] = 1;
    for (auto v : tr[u]) {
        if (v == p) continue;
        dfs_sz(v,u);
        sz[u] += sz[v];
    }
}

void dfs_calc(int u, int p, int bestmid, int tail) {
    ans += max(bestmid, tail);
    for (auto v : tr[u]) {
        if (v == p) continue;
        int newmid = max(bestmid, sz[u]-sz[v]);
        int new_tail = sz[v];
        dfs_calc(v,u,newmid,new_tail);
    }
}

int main() {
    cin>>n;
    for (int i = 1 ; i <= n-1 ; ++i) {
        cin>>u>>v;
        tr[u].emplace_back(v);
        tr[v].emplace_back(u);
    }

    for (int i = 1 ; i <= n ; ++i) {
        sz.assign(n+1, 0);
        dfs_sz(i,0);

        ans += n;
        for (int v : tr[i]) {
            int bestMid = n - sz[v];
            int tail = sz[v];
            dfs_calc(v, i, bestMid, tail);
        }
    }

    cout<<ans<<endl;
}
