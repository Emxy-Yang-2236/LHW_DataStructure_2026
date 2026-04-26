#include <bits/stdc++.h>
using namespace std;

const int LOG = 20;
const int maxn = 2e6+7;
vector<vector<int>> adj(maxn);
int depth[2*maxn];
int fa[maxn][LOG];
int pt = 1;
int n,q,u,v,a,b;
vector<pair<int,int>> good_p;

void dfs_init(int u, int p) {
    depth[u] = depth[p] + 1;
    fa[u][0] = p;

    for (int i = 1 ; i < LOG ; ++i) {
        fa[u][i] = fa[fa[u][i-1]][i-1];
    }
    for (auto v: adj[u]) {
        if (v != p) {
            dfs_init(v,u);
        }
    }
}


int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u,v);

    for (int i = LOG-1; i >= 0; --i) {
        if (depth[u] - (1<<i) >= depth[v]) u = fa[u][i];
    }
    if (u == v) return u;
    for (int i = LOG-1; i >= 0; --i) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }

    return fa[u][0];
}

int dis(int u, int v) {
    if (u == v) return 0;
    int a = lca(u,v);
    return depth[u] + depth[v] - 2*depth[a];
}

bool in_road(int u, int v, int p) {
    return dis(u,v) == dis(u,p) + dis(v,p);
}

bool valid(int p) {
    for (auto i : good_p) {
        if (in_road(i.first,i.second,p)) {
            return false;
        }
    }
    return true;
}

int main() {
    cin>>n>>q;
    for (int i = 1 ; i <= n-1; ++i) {
        cin>>u>>v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs_init(1,0);

    for (int i = 1; i <= q; ++i) {
        cin>>u>>v;
        good_p.emplace_back(u,v);
    }

    cin>>u>>v;
    a = lca(u,v);
    b = 0;
    while (u != a) {
        if (valid(u)) ++b;
        u = fa[u][0];
    }
    while (v != a) {
        if (valid(v)) ++b;
        v = fa[v][0];
    }
    if (valid(a)) ++b;
    cout<<b<<endl;
}
