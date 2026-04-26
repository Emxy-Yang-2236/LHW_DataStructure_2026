#include <bits/stdc++.h>
using namespace std;

int n,w;
const int maxn = 10007;

struct Node {
    int weight;
    int left, right;

    Node(int w, int l = -101, int r = -101): weight(w), left(l), right(r) {}
};
struct cmp {
    bool operator()(const Node& a, const Node& b) {
        return a.weight > b.weight;
    }
};

priority_queue<Node, vector<Node>, cmp> q;


int main() {
    cin>>n;
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        cin>>w;
        q.emplace(w);
    }
    while (q.size() >= 2) {
        auto a = q.top();
        q.pop();
        auto b = q.top();
        q.pop();
        q.emplace(a.weight + b.weight);
        ans += a.weight + b.weight;
    }

    cout<<ans<<endl;
    return 0;
}