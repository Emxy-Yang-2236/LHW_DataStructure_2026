#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+7;
vector<vector<pair<int,int>>> adj(maxn); //former point and latter weight
int weight[maxn];
int n,q,x,y,w;

void dfs_init(int u, int p, int w) {
    weight[u] = weight[p] ^ w;
    for (auto v: adj[u]) {
        if (v.first != p) {
            dfs_init(v.first,u,v.second);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    cin>>n>>q;
    for (int i = 1; i <= n-1; ++i) {
        cin>>x>>y>>w;
        adj[x].emplace_back(y,w);
        adj[y].emplace_back(x,w);
    }
    dfs_init(1,0,0);

    for (int i = 1; i <= q; ++i) {
        cin>>x>>y;
        cout<<(weight[x]^weight[y]) <<'\n';
    }
}

