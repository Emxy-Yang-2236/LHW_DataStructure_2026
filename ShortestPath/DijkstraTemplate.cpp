#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 62);

struct IndexedMinHeap {
    struct Node {
        int id;     // 元素编号
        int key;    // 优先级
    };

    int sz;
    vector<Node> heap;   // 1-based
    vector<int> pos;     // pos[id] = 下标, 0表示不在堆中

    IndexedMinHeap(int max_id) {
        sz = 0;
        heap.resize(1);          // heap[0]不用
        pos.assign(max_id + 1, 0);
    }

    [[nodiscard]] bool empty() const {
        return sz == 0;
    }

    [[nodiscard]] bool contains(int id) const {
        return pos[id] != 0;
    }

    void swap_node(int i, int j) {
        swap(heap[i], heap[j]);
        pos[heap[i].id] = i;
        pos[heap[j].id] = j;
    }

    void sift_up(int i) {
        while (i > 1) {
            int p = i / 2;
            if (heap[p].key <= heap[i].key) break;
            swap_node(i, p);
            i = p;
        }
    }

    void sift_down(int i) {
        while (true) {
            int l = i * 2, r = i * 2 + 1;
            int smallest = i;
            if (l <= sz && heap[l].key < heap[smallest].key) smallest = l;
            if (r <= sz && heap[r].key < heap[smallest].key) smallest = r;
            if (smallest == i) break;
            swap_node(i, smallest);
            i = smallest;
        }
    }

    [[nodiscard]] Node top() const {
        return heap[1];
    }

    void push(int id, int key) {
        ++sz;
        if ((int)heap.size() <= sz) heap.push_back({id, key});
        else heap[sz] = {id, key};
        pos[id] = sz;
        sift_up(sz);
    }

    void pop() {
        if (sz == 0) return;
        pos[heap[1].id] = 0;
        if (sz == 1) {
            --sz;
            return;
        }
        heap[1] = heap[sz];
        pos[heap[1].id] = 1;
        --sz;
        sift_down(1);
    }

    void decrease_key(int id, int new_key) {
        int i = pos[id];
        if (i == 0) return;
        if (new_key >= heap[i].key) return;
        heap[i].key = new_key;
        sift_up(i);
    }

    void modify_key(int id, int new_key) {
        int i = pos[id];
        if (i == 0) return;
        int old_key = heap[i].key;
        heap[i].key = new_key;
        if (new_key < old_key) sift_up(i);
        else if (new_key > old_key) sift_down(i);
    }

    void erase(int id) {
        int i = pos[id];
        if (i == 0) return;

        pos[id] = 0;
        if (i == sz) {
            --sz;
            return;
        }

        heap[i] = heap[sz];
        pos[heap[i].id] = i;
        --sz;

        if (i > 1 && heap[i].key < heap[i / 2].key) sift_up(i);
        else sift_down(i);
    }
};

struct Edge {
    int to;
    int w;
};

// ret: 源点 s 到所有点的最短路
vector<long long> dijkstra(int n, const vector<vector<Edge>>& g, int s) {
    vector<long long> dist(n + 1, INF);
    vector<bool> vis(n + 1, false);

    IndexedMinHeap queue(n);
    dist[s] = 0;
    queue.push(s, 0);

    while (!queue.empty()) {
        auto cur = queue.top();
        queue.pop();

        int u = cur.id;
        vis[u] = true;                //BFS-like

        for (const auto& e : g[u]) {
            int v = e.to;
            int w = e.w;
            if (vis[v]) continue;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (queue.contains(v)) queue.decrease_key(v, dist[v]);
                else queue.push(v, dist[v]);
            }
        }
    }

    return dist;
}

int main() {
    int n, m, u, v, w;
    cin>>n>>m;
    vector<vector<Edge>> g(n + 1);

    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u,w});
    }

    int s;
    cin >> s;

    vector<long long> dist = dijkstra(n, g, s);

    for (int i = 1; i <= n; ++i) {
        if (dist[i] >= (1LL << 61)) cout << "INF\n";
        else cout << dist[i] << "\n";
    }

    return 0;
}