#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
#define ls p<<1
#define rs (p<<1|1)
#define cm int mid = (l+r)>>1;
    const int mod = 1e9+7;
    vector<vector<int>> adj;
    vector<int> dfn, out, id, sz;
    int timer = 0;

    void dfs(int u) {
        dfn[u] = ++timer;  //存储点再dfs序数组中第一次出现位置的数组
        id[timer] = u;     //存储dfs序的数组

        for (auto v : adj[u]) {
            dfs(v);
        }
        out[u] = timer;
        //sz[u] = out[u] - dfn[u] + 1;
    }

    vector<int> tr, tag;

    void push_up(int p) {
        tr[p] = (tr[ls] + tr[rs])%mod;
    }
    void apply(int l, int r, int p, int k) {
        int len = r-l+1;
        tr[p] = ((long long) tr[p] + len*k) % mod;
        tag[p] = ((long long) tag[p] + k) % mod;

    }
    void push_down(int l, int r, int p) {
        if (tag[p] == 0) return ;
        cm
        apply(l,mid,ls,tag[p]), apply(mid+1,r,rs,tag[p]);
        tag[p] = 0;
    }
    void update_range(int nl, int nr, int l, int r, int p, int k) {
        if (nl <= l && nr >= r) {
            apply(l,r,p,k);
            return;
        }
        push_down(l,r,p);
        cm
        if (nl <= mid) update_range(nl,nr,l,mid,ls,k);
        if (nr > mid) update_range(nl,nr,mid+1,r,rs,k);
        push_up(p);
    }
    int query(int nl, int nr, int l, int r, int p) {
        if (nl <= l && nr >= r) return tr[p];
        push_down(l,r,p);
        cm;
        if (nl > mid) return query(nl,nr,mid+1,r,rs);
        if (nr <= mid) return query(nl,nr,l,mid,ls);
        else return (query(nl,nr,mid+1,r,rs) + query(nl,nr,l,mid,ls)) % mod;
    }

    vector<int> bonus(int n, vector<vector<int>>& leadership, vector<vector<int>>& operations) {
        adj.resize(n+1), dfn.resize(n+1), out.resize(n+1), id.resize(n+1);
        for (auto i : leadership) {
            adj[i[0]].emplace_back(i[1]);
        }
        dfs(1);

        tr.resize((n+1)<<2, 0), tag.resize((n+1)<<2, 0);

        vector<int> ans;

        for (auto op : operations) {
            auto obj = op[1], ix = op[0];
            if (ix == 1) {
                update_range(dfn[obj], dfn[obj], 1,n,1, op[2]);
            }else if (ix == 2) {
                update_range(dfn[obj], out[obj], 1,n,1,op[2]);
            }else {
                ans.emplace_back(query(dfn[obj], out[obj], 1,n,1));
            }
        }

        return ans;
    }
};



int main() {
    int n = 6;

    vector<vector<int>> leadership = {
        {1, 2},
        {1, 6},
        {2, 3},
        {2, 5},
        {1, 4}
    };

    vector<vector<int>> operations = {
        {1, 1, 500},
        {2, 2, 50},
        {3, 1},
        {2, 6, 15},
        {3, 1}
    };

    Solution s;
    auto ans = s.bonus(n,leadership,operations);

    for (auto i : ans) {
        cout<<i<<endl;
    }

}