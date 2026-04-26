
#ifndef INC_2026_3___4_GRAPH_DEMO_OF_TREE_HPP
#define INC_2026_3___4_GRAPH_DEMO_OF_TREE_HPP

#include <bits/stdc++.h>
using namespace std;

inline void printTree(const vector<vector<int>>& adj, int root) {
    int n = adj.size();

    function<void(int, int, string, bool)> dfs = [&](int u, int parent, string prefix, bool isLast) {
        cout << prefix;
        if (parent != -1) {
            cout << (isLast ? "└── " : "├── ");
        }
        cout << u << '\n';

        vector<int> children;
        for (int v : adj[u]) {
            if (v != parent) children.push_back(v);
        }

        for (int i = 0; i < (int)children.size(); ++i) {
            bool lastChild = (i == (int)children.size() - 1);
            dfs(children[i], u, prefix + (parent == -1 ? "" : (isLast ? "    " : "│   ")), lastChild);
        }
    };

    dfs(root, -1, "", true);
}

#endif //INC_2026_3___4_GRAPH_DEMO_OF_TREE_HPP
