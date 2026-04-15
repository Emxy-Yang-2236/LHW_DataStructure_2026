#include <bits/stdc++.h>
using namespace std;

const long long LOG = 20, maxn = 2e5 + 10;
vector<vector<long long>> adj(maxn);
long long n,q,op,u,v,c;
long long ans[maxn], tag_r[maxn], tag_p[maxn];
long long fa[maxn][LOG], depth[maxn];

void dfs_init(long long u, long long p) {
    depth[u] = depth[p] + 1;
    fa[u][0] = p;

    for (long long i = 1 ; i < LOG ; ++i) {
        fa[u][i] = fa[fa[u][i-1]][i-1];
    }
    for (auto v: adj[u]) {
        if (v != p) {
            dfs_init(v,u);
        }
    }
}

void dfs_collect_path(long long u, long long p) {
    ans[u] = tag_r[u];
    for (auto v: adj[u]) {
        if (v != p) {
            dfs_collect_path(v,u);
            ans[u] += ans[v];
        }
    }
}
void dfs_collect_sub(long long u, long long p) {
    ans[u] += tag_p[u];
    for (auto v: adj[u]) {
        if (v != p) {
            tag_p[v] += tag_p[u];
            dfs_collect_sub(v,u);
            //ans[u] += ans[v];
        }
    }
}

void dfs_collect() {
    dfs_collect_path(1,0);
    dfs_collect_sub(1,0);
}

long long lca(long long u, long long v) {
    if (depth[u] < depth[v]) swap(u,v);

    for (long long i = LOG-1; i >= 0; --i) {
        if (depth[u] - (1<<i) >= depth[v]) u = fa[u][i];
    }
    if (u == v) return u;
    for (long long i = LOG-1; i >= 0; --i) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }

    return fa[u][0];
}

int main() {
    cin>>n>>q;
    for (long long i = 1 ; i < n ; ++i) {
        cin>>u>>v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs_init(1,0);
    for (long long i = 1 ; i <= q ; ++i) {
        cin>>op;
        if (op == 1) {
            cin>>u>>v>>c;
            tag_r[u] += c;
            tag_r[v] += c;
            long long p = lca(u,v);
            tag_r[p] -= c;
            tag_r[fa[p][0]] -= c;
        }else {
            cin>>u>>c;
            tag_p[u] += c;
        }
    }
    dfs_collect();
    for (long long i = 1; i <= n; ++i) {
        cout<<ans[i]<<" ";
    }
    return 0;
}