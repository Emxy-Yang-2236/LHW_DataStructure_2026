#include <bits/stdc++.h>
using namespace std;

struct Path {
    long long len;
    int a, b;
};
bool better_path(const Path& x, const Path& y) {
    if (x.len != y.len) return x.len > y.len;
    if (x.a != y.a) return x.a < y.a;
    return x.b < y.b;
}

struct Node {
    long long dist;
    int id;
};
bool cmp_node(const Node& x, const Node& y) {
    if (x.dist != y.dist) return x.dist > y.dist;
    return x.id < y.id;
}

Path make_path(const vector<Node>& vec, int i, int j) {
    int a = vec[i].id;
    int b = vec[j].id;
    if (a > b) swap(a, b);
    return {vec[i].dist + vec[j].dist, a, b};
}

struct PairState {
    int i, j;
    Path path;
};
struct PairStateCmp {
    bool operator()(const PairState& x, const PairState& y) const {
        if (x.path.len != y.path.len) return x.path.len < y.path.len;
        if (x.path.a != y.path.a) return x.path.a > y.path.a;
        return x.path.b > y.path.b;
    }
};
long long encode_pair(int i, int j) {
    return ( (long long)i << 32 ) ^ (unsigned int)j;
}

class PairGen {
public:
    vector<Node> vec;
    priority_queue<PairState, vector<PairState>, PairStateCmp> pq;
    unordered_set<long long> vis;

    PairGen() = default;

    PairGen(const vector<Node>& v) {
        init(v);
    }

    void init(const vector<Node>& v) {
        vec = v;
        while (!pq.empty()) pq.pop();
        vis.clear();

        int n = (int)vec.size();
        if (n >= 2) push_state(0, 1);
    }

    bool empty() const {
        return pq.empty();
    }

    const PairState& top() const {
        return pq.top();
    }

    void pop() {
        auto cur = pq.top();
        pq.pop();

        int i = cur.i;
        int j = cur.j;
        int n = (int)vec.size();

        if (i + 1 < j) push_state(i + 1, j);
        if (j + 1 < n) push_state(i, j + 1);
    }

private:
    void push_state(int i, int j) {
        if (i >= j) return;
        long long key = encode_pair(i, j);
        if (vis.count(key)) return;
        vis.insert(key);

        pq.push({i, j, make_path(vec, i, j)});
    }
};

struct StreamItem {
    Path path;
    int gen_id;
    int sign;
};
struct StreamItemCmp {
    bool operator()(const StreamItem& x, const StreamItem& y) const {
        if (x.path.len != y.path.len) return x.path.len < y.path.len;
        if (x.path.a != y.path.a) return x.path.a > y.path.a;
        return x.path.b > y.path.b;
    }
};

class CentroidStream {
public:
    vector<PairGen> gens;
    vector<int> signs; // 与 gens 对应
    priority_queue<StreamItem, vector<StreamItem>, StreamItemCmp> pq;

    CentroidStream() = default;

    void init(const vector<vector<Node>>& groups) {
        // groups[0] = all
        // groups[1..] = sub_i
        gens.clear();
        signs.clear();
        while (!pq.empty()) pq.pop();

        int sz = (int)groups.size();
        gens.resize(sz);
        signs.resize(sz);

        for (int i = 0; i < sz; ++i) {
            gens[i].init(groups[i]);
            signs[i] = (i == 0 ? +1 : -1);
            if (!gens[i].empty()) {
                pq.push({gens[i].top().path, i, signs[i]});
            }
        }
    }

    bool has_next() {
        normalize();
        return !buffer_empty;
    }

    Path get_next() {
        normalize();
        buffer_ready = false;
        return buffer;
    }

private:
    Path buffer{};
    bool buffer_ready = false;
    bool buffer_empty = true;

    static bool same_path(const Path& x, const Path& y) {
        return x.len == y.len && x.a == y.a && x.b == y.b;
    }

    void advance_gen(int gid) {
        gens[gid].pop();
        if (!gens[gid].empty()) {
            pq.push({gens[gid].top().path, gid, signs[gid]});
        }
    }

    void normalize() {
        if (buffer_ready) return;

        buffer_empty = true;

        while (!pq.empty()) {
            Path target = pq.top().path;
            int cnt = 0;
            vector<int> touched;

            while (!pq.empty() && same_path(pq.top().path, target)) {
                auto item = pq.top();
                pq.pop();
                cnt += item.sign;
                touched.push_back(item.gen_id);
            }

            for (int gid : touched) {
                advance_gen(gid);
            }

            if (cnt > 0) {
                buffer = target;
                buffer_ready = true;
                buffer_empty = false;
                return;
            }
        }
    }
};

const int MAXN = 200005;

struct Edge {
    int to;
    int w;
};

vector<Edge> g[MAXN];
bool removed[MAXN];
int sz[MAXN];
int n, m;

void get_size(int u, int fa) {
    sz[u] = 1;
    for (auto e : g[u]) {
        int v = e.to;
        if (v == fa || removed[v]) continue;
        get_size(v, u);
        sz[u] += sz[v];
    }
}

int total_sz;
int best_centroid, best_balance;

void get_centroid(int u, int fa) {
    int mx = total_sz - sz[u];
    for (auto e : g[u]) {
        int v = e.to;
        if (v == fa || removed[v]) continue;
        get_centroid(v, u);
        mx = max(mx, sz[v]);
    }
    if (mx < best_balance) {
        best_balance = mx;
        best_centroid = u;
    }
}
int find_centroid(int entry) {
    get_size(entry, 0);
    total_sz = sz[entry];
    best_balance = 1e9;
    best_centroid = -1;
    get_centroid(entry, 0);
    return best_centroid;
}
void collect_nodes(int u, int fa, long long dist, vector<Node>& vec) {
    vec.push_back({dist, u});
    for (auto e : g[u]) {
        int v = e.to;
        if (v == fa || removed[v]) continue;
        collect_nodes(v, u, dist + e.w, vec);
    }
}

vector<CentroidStream> streams;
void decompose(int entry) {
    int c = find_centroid(entry);
    removed[c] = true;

    vector<vector<Node>> groups;
    vector<Node> all;
    all.push_back({0LL, c});

    for (auto e : g[c]) {
        int v = e.to;
        if (removed[v]) continue;

        vector<Node> vec;
        collect_nodes(v, c, e.w, vec);
        sort(vec.begin(), vec.end(), cmp_node);

        if (!vec.empty()) {
            groups.push_back(vec);
            for (auto x : vec) all.push_back(x);
        }
    }

    sort(all.begin(), all.end(), cmp_node);

    vector<vector<Node>> real_groups;
    real_groups.push_back(all);
    for (auto &vec : groups) real_groups.push_back(vec);

    CentroidStream cs;
    cs.init(real_groups);
    streams.push_back(std::move(cs));

    for (auto e : g[c]) {
        int v = e.to;
        if (removed[v]) continue;
        decompose(v);
    }
}

struct GlobalItem {
    Path path;
    int sid; // 来自哪个 stream
};

struct GlobalItemCmp {
    bool operator()(const GlobalItem& x, const GlobalItem& y) const {
        if (x.path.len != y.path.len) return x.path.len < y.path.len;
        if (x.path.a != y.path.a) return x.path.a > y.path.a;
        return x.path.b > y.path.b;
    }
};

void init() {
    cin>>n>>m;
    int u,v,w;
    for (int i = 1 ; i <= n-1 ; ++i) {
        cin>>u>>v>>w;
        g[u].emplace_back(v,w);
        g[v].emplace_back(u,w);
    }
    decompose(1);
}

int main() {
    init();
    priority_queue<GlobalItem, vector<GlobalItem>, GlobalItemCmp> gpq;

    for (int i = 0; i < (int)streams.size(); ++i) {
        if (streams[i].has_next()) {
            gpq.push({streams[i].get_next(), i});
        }
    }

    for (int k = 0; k < m && !gpq.empty(); ++k) {
        auto cur = gpq.top();
        gpq.pop();

        cout << cur.path.a << " " << cur.path.b << "\n";

        int sid = cur.sid;
        if (streams[sid].has_next()) {
            gpq.push({streams[sid].get_next(), sid});
        }
    }


    return 0;
}