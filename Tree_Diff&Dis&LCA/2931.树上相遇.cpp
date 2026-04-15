#include <bits/stdc++.h>
using namespace std;

const int LOG = 16;
const int maxn = 2e4+7;
vector<vector<int>> adj(maxn);
int eu[2*maxn], depth[2*maxn], first[maxn];
int st[2*maxn][LOG], lg[2*maxn];
int pt = 1;
int n,q,u,v,a,b;

void dfs_init(int u, int p, int d) {
    first[u] = pt;
    eu[pt] = u;
    depth[pt++] = d;
    for (auto v : adj[u]) {
        if (v != p) {
            dfs_init(v,u,d+1);
            eu[pt] = u;
            depth[pt++] = d;
        }
    }
}

int better(int x, int y) {
    return depth[x] < depth[y] ? x : y;
}
int better_(int x, int y) {
    return depth[first[x]] > depth[first[y]] ? x : y;
}

inline int getmin(int l, int r) {
    long long k = lg[r - l + 1];
    return better(st[l][k], st[r - (1 << k) + 1][k]);
}

void st_init() {
    int N = 2*n-1;
    for (int i = 2; i <= N; ++i) {
        lg[i] = lg[i>>1] + 1;
    }
    for (int i = 1; i <= N; ++i) {
        st[i][0] = i;
    }
    for (int j = 1; j <= lg[N]; ++j) {
        for (int i = 1; i <= N - (1<<j) + 1; ++i) {
            st[i][j] = better(st[i][j-1], st[i + (1<<(j-1))][j-1]);
        }
    }
}

int lca(int u, int v) {
    if (u == v) return u;
    int l = first[u], r = first[v];
    if (l > r) swap(l,r);
    int idx = getmin(l,r);
    return eu[idx];
}

int dis(int u, int v) {
    if (u == v) return 0;
    int a = lca(u,v);
    return depth[first[u]] + depth[first[v]] - 2*depth[first[a]];
}

int main() {
    cin>>n>>q;
    for (int i = 1 ; i <= n-1; ++i) {
        cin>>u>>v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs_init(1,0,0);
    st_init();

    for (int i = 1; i <= q; ++i) {
        cin>>u>>v>>a>>b;
        int a_min = better_(better_(lca(u,a),lca(u,b)),better_(lca(v,a),lca(v,b)));
        if ((dis(u,v) == dis(u,a_min) + dis(v,a_min)) && (dis(a,b) == dis(a,a_min) + dis(b,a_min))) {
            cout<<"Y"<<endl;
        }else {
            cout<<"N"<<endl;
        }
    }
}
