#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    int w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct DSU {
    vector<int> fa, sz;

    DSU(int n) {
        fa.resize(n + 1);
        sz.resize(n + 1, 1);
        for (int i = 1; i <= n; i++) fa[i] = i;
    }

    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
        return true;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    sort(edges.begin(), edges.end());

    DSU dsu(n);
    long long ans = 0;
    int cnt = 0;

    for (auto &e : edges) {
        if (dsu.merge(e.u, e.v)) {
            ans += e.w;
            cnt++;
            if (cnt == n - 1) break;
        }
    }

    if (cnt != n - 1) {
        cout << "The graph is not connected, no MST exists.\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}
