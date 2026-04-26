//Heavy Path Decomposition

#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> fa, depth, sz, hs;  //hs store the heavier son of all point   //first dfs
vector<int> dfn, top, id, out;       //idx in dfs sequence ; the top of heavy chain ; dfs sequence    //second dfs
vector<int> tr, tag;            //segment tree
int n,q,obj;
string op;

void dfs1(int u) {
    sz[u] = 1;
    hs[u] = -1;
    for (auto v : adj[u]) {
        fa[v] = u;
        depth[v] = depth[u] + 1;
        dfs1(v);
        sz[u] += sz[v];
        if (hs[u] == -1 || sz[v] > sz[hs[u]]) {
            hs[u] = v;
        }
    }
}

int timer = 0;
void dfs2(int u) {
    dfn[u] = ++timer;
    id[timer] = u;
    if (hs[u] != -1) {
        top[hs[u]] = top[u];
        dfs2(hs[u]);
    }
    for (auto v : adj[u]) {
        if (v == hs[u]) continue;
        top[v] = v;
        dfs2(v);
    }
    out[u] = timer;
}

#define ls p<<1
#define rs (p<<1|1)
#define m int mid = (l+r)>>1;

void push_up(int p) {
    tr[p] = tr[ls] + tr[rs];
}
void apply(int l, int r, int p, int op) {
    int len = r-l+1;
    if (op == 1) {
        tr[p] = len;
    }else {
        tr[p] = 0;
    }
    tag[p] = op;
}
void push_down(int l, int r, int p) {
    if (tag[p] == 0) return;
    m
    apply(l,mid,ls,tag[p]), apply(mid+1,r,rs,tag[p]);
    tag[p] = 0;
}
void update_range(int nl, int nr, int l, int r, int p, int op) {
    if (nl <= l && nr >= r) {
        apply(l,r,p,op);
        return;
    }
    push_down(l,r,p);
    m
    if (nl <= mid) update_range(nl,nr,l,mid,ls,op);
    if (nr > mid) update_range(nl,nr,mid+1,r,rs,op);
    push_up(p);
}
int query_seg(int nl, int nr, int l, int r, int p) {
    if (nl <= l && nr >= r) return tr[p];
    push_down(l,r,p);
    m
    if (nl > mid) return query_seg(nl,nr,mid+1,r,rs);
    if (nr <= mid) return query_seg(nl,nr,l,mid,ls);
    else return query_seg(nl,nr,mid+1,r,rs) + query_seg(nl,nr,l,mid,ls);
}
int query(int u) {
    int ans = 0;
    while (top[u] != 0) {
        int nl = dfn[top[u]];
        int nr = dfn[u];
        ans += query_seg(nl,nr,1,n,1);
        u = fa[top[u]];
    }
    int nl = 1, nr = dfn[u];
    ans += query_seg(nl,nr,1,n,1);
    return ans;
}
void update(int u, int op) {
    while (top[u] != 0) {
        int nl = dfn[top[u]];
        int nr = dfn[u];
        update_range(nl,nr,1,n,1,op);
        u = fa[top[u]];
    }
    int nl = 1, nr = dfn[u];
    update_range(nl,nr,1,n,1,op);
}
int main() {
    cin>>n;
    adj.resize(n), fa.resize(n), depth.resize(n), sz.resize(n), hs.resize(n);
    dfn.resize(n+1), top.resize(n), id.resize(n+1), out.resize(n+1);
    tr.resize((n+1)<<2, 0), tag.resize((n+1)<<2, 0);
    for (int i = 1 ; i < n ; ++i) {
        int u;
        cin>>u;
        adj[u].emplace_back(i);
    }
    top[0] = 0;
    dfs1(0), dfs2(0);
    cin>>q;
    for (int i = 1 ; i <= q ; ++i) {
        cin>>op>>obj;
        if (op == "install") {
            cout<<depth[obj] + 1 - query(obj)<<endl;
            update(obj,1);
        }else {
            cout<<query_seg(dfn[obj], out[obj], 1, n, 1)<<endl;
            update_range(dfn[obj], out[obj], 1,n,1,-1);
        }
    }

    return 0;
}
