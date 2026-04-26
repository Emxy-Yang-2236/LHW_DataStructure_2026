#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+7;
vector<vector<int>> tr(maxn);
int n,u,v;
int best = maxn;
int sz[maxn];
vector<int> cen;

void dfs(int u, int p) {
    sz[u] = 1;
    int mx = 0;

    for (int v : tr[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        mx = max(mx, sz[v]);
    }
    mx = max(mx, n - sz[u]);

    if (mx < best) {
        cen.clear();
        best = mx;
        cen.emplace_back(u);
    }else if (mx == best) {
        cen.emplace_back(u);
    }
}

pair<int,int> find_leaf(int u, int p) {
    for (int v : tr[u]) {
        if (v == p) continue;
        if (tr[v].size() == 1) return {v,u};
        else return find_leaf(v,u);
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
    if (cen.size() == 1) {
        int i = 1;
        while (tr[i].empty()) ++i;
        int j = tr[i][0];
        cout<<i<<" "<<j<<endl<<i<<" "<<j;
    }else {
        auto ans = find_leaf(cen[0], cen[1]);
        cout<<ans.first<<" "<<ans.second<<endl;
        cout<<ans.first<<" "<<cen[1]<<endl;
    }
}
