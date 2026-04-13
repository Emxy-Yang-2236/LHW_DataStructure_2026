#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 10;
int n,m;
int op,x,y;
struct seg {
    int seg_max;
    int lmax;
    int rmax;
    int tag;
    int len;
};
seg tr[maxn<<2];

void apply(int p, int op) {
    if (op) {
        tr[p] = {0,0,0,op,tr[p].len};
    }else {
        int l = tr[p].len;
        tr[p] = {l,l,l,op,l};
    }
}

void push_up(int p) {
    int l = tr[p<<1].seg_max;
    int r = tr[p<<1|1].seg_max;
    int mid = tr[p<<1].rmax + tr[p<<1|1].lmax;

    tr[p].len = tr[p<<1].len + tr[p<<1|1].len;
    tr[p].lmax = tr[p<<1].lmax + (tr[p<<1].lmax == tr[p<<1].len ? tr[p<<1|1].lmax : 0);
    tr[p].rmax = tr[p<<1|1].rmax + (tr[p<<1|1].rmax == tr[p<<1|1].len ? tr[p<<1].rmax : 0);
    tr[p].seg_max = max(max(l,r),mid);
}

void build(int l , int r , int p) {
    tr[p].tag = -1;
    if (l == r) {
        tr[p] = {1,1,1,-1,1};
        return;
    }
    int mid = (l+r)>>1;
    build(l , mid , p<<1) , build(mid+1,r,p<<1|1);
    push_up(p);
}

void push_down(int p) {
    if (tr[p].tag == -1) return;
    apply(p<<1,tr[p].tag) , apply(p<<1|1 , tr[p].tag);
    tr[p].tag = -1;
}

void modify(int nl, int nr ,int op,  int l , int r , int p) {
    if (nl <= l && nr >= r) {
        apply(p, op);
        return;
    }
    push_down(p);
    int mid = (l + r) >> 1;


    if (nl <= mid) modify(nl, nr, op, l, mid, p << 1);
    if (nr > mid)  modify(nl, nr, op, mid + 1, r, p << 1 | 1);

    push_up(p);
}

int query(int sz, int l, int r, int p) {
    if (l == r) return l;
    push_down(p);
    int mid = (l + r) >> 1;

    if (tr[p << 1].seg_max >= sz) {
        return query(sz, l, mid, p << 1);
    }
    if (tr[p << 1].rmax + tr[p << 1 | 1].lmax >= sz) {
        return mid - tr[p << 1].rmax + 1;
    }
    if (tr[p << 1 | 1].seg_max >= sz) {
        return query(sz, mid + 1, r, p << 1 | 1);
    }

    return 0;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;
    build(1,n,1);
    for (int i = 1 ; i <= m ; ++i) {
        cin>>op;
        if (op == 1) {
            cin>>x;
            int ans = query(x,1,n,1);
            if (ans != 0) {
                modify(ans,ans+x-1,1,1,n,1);
            }
            cout<<ans<<endl;
        }else {
            cin>>x>>y;
            modify(x,x+y-1,0,1,n,1);
        }
    }

    return 0;
}