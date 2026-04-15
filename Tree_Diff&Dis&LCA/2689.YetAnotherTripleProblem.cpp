#include <bits/stdc++.h>
using namespace std;

const int LOG = 20;
const int maxn = 1e5+7;
vector<vector<int>> tr(maxn);
int eu[2*maxn], depth[2*maxn], first[maxn];
int st[2*maxn][LOG], lg[2*maxn];
int n,q,u,v,w;
int l1,l2,l3;

int pt = 1;

int better(int x, int y) {
    return depth[x] < depth[y] ? x:y;
}

void dfs(int u, int p, int d) {
    first[u] = pt;
    eu[pt] = u;
    depth[pt++] = d;
    for (auto v : tr[u]) {
        if (v != p) {
            dfs(v,u,d+1);
            eu[pt] = u;
            depth[pt++] = d;
        }
    }
}

inline int getmin(int l, int r) {
    long long k = lg[r - l + 1];
    return better(st[l][k], st[r - (1 << k) + 1][k]);
}

inline int lca(int u, int v) {
    int l = first[u];
    int r = first[v];
    if (l>r) swap(l,r);
    int idx = getmin(l,r);
    return eu[idx];
}

inline int dist(int u, int v) {
    int a = lca(u,v);
    return depth[first[u]] + depth[first[v]] -2*depth[first[a]];
}

int main() {
    cin>>n>>q;
    int N = 2*n-1;
    for (int i = 2; i <= N; i++) {
        lg[i] = lg[i>>1] + 1;
    }
    for (int i = 1 ; i < n ; ++i) {
        cin>>u>>v;
        tr[u].emplace_back(v);
        tr[v].emplace_back(u);
    }
    dfs(1,0,0);

    N = pt - 1;
    for (int i = 1 ; i <= N ; ++i) {
        st[i][0] = i;
    }
    for (int j = 1 ; j <= lg[N] ; ++j) {
        for (int i = 1 ; i <= N - (1<<j) + 1 ; ++i) {
            st[i][j] = better(st[i][j-1] , st[i + (1<<(j-1))][j-1]);
        }
    }

    for (int i = 1 ; i <=q; ++i) {
        cin>>u>>v>>w;
        l1 = dist(u,v);
        l2 = dist(u,w);
        l3 = dist(v,w);
        if (l1 + l3 != l2 && l2 + l1 != l3 && l2 + l3 != l1) {
            cout<<"No"<<endl;
        }else {
            cout<<"Yes"<<endl;
        }
    }
    return 0;
}
