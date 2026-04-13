#include <bits/stdc++.h>
using namespace std;

const int maxn=1e6+10;
int tr[maxn << 2] , tag[maxn << 2];

void push_up(int p) {
    tr[p] = tr[p<<1] | tr[p<<1|1];
}
void apply(int p, int k) {
    tr[p] = 1<<(k-1);
    tag[p] = k;
}
void push_down(int p) {
    if (tag[p] == 0) return;
    apply(p<<1,tag[p]) , apply(p<<1|1 , tag[p]);
    tag[p] = 0;
}

void build(int l, int r, int p) {
    tag[p] = 0;
    if (l == r) {
        tr[p] = 1;
        return;
    }
    int mid = (l+r)>>1;
    build(l , mid , p<<1) , build(mid+1,r,p<<1|1);
    push_up(p);
}

void update_range(int nl, int nr, int l, int r, int p, int k) {
    if (nl <= l && nr >= r) {
        return (void) apply(p,k);
    }
    push_down(p);

    int mid = (l+r)>>1;
    if (nl <= mid) update_range(nl, nr, l, mid, p<<1, k);
    if (nr >= mid+1) update_range(nl, nr, mid+1, r, p<<1|1, k);

    push_up(p);
}

int query(int nl, int nr, int l, int r, int p) {
    if (nl <= l && nr >= r) return tr[p];
    push_down(p);

    int mid = (l+r)>>1;
    int res = 0;
    if (nl <= mid) res |= query(nl, nr, l, mid, p << 1);
    if (nr > mid) res |= query(nl, nr, mid + 1, r, p << 1 | 1);
    return res;
}

int n,k,m,a,b,c;
char op;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>k>>m;

    build(1,n,1);
    for (int i = 1 ; i <= m ; ++i) {
        cin>>op;
        if (op == 'C') {
            cin>>a>>b>>c;
            update_range(a,b,1,n,1,c);
        }else {
            cin>>a>>b;
            int val = query(a,b,1,n,1);
            cout << __builtin_popcount(val) << "\n";
        }
    }

    return 0;
}