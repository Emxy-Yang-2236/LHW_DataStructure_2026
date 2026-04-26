#include <bits/stdc++.h>
using namespace std;
#define ls p<<1
#define rs (p<<1 | 1)
typedef long long ll;

constexpr int maxn = 1e5+7;
int tr[maxn<<2], tag1[maxn<<2], tag2[maxn<<2], arr[maxn];   //1:add ; 2:mul
int n,q,m,x,y,op,k;

void push_up(int p) {
    tr[p] = ((ll)tr[ls] + tr[rs]) % m;
}
void apply(int l, int r, int p, int add, int mul) {
    int len = r-l+1;
    tr[p] = ((ll)tr[p] * mul + (ll)add * len) % m;

    tag2[p] = (ll)tag2[p] * mul % m;
    tag1[p] = ((ll)tag1[p] * mul + add) % m;
}
void push_down(int l, int r, int p) {
    if (tag1[p] == 0 && tag2[p] == 1) return;
    int mid = (l+r)>>1;
    apply(l,mid,ls, tag1[p],tag2[p]), apply(mid+1,r,rs, tag1[p],tag2[p]);
    tag1[p] = 0, tag2[p] = 1;
}

void build(int l, int r, int p) {
    tag1[p] = 0, tag2[p] = 1;
    if (l == r) {
        tr[p] = arr[l] % m;
        return;
    }
    int mid = (l+r)>>1;
    build(l , mid , ls) , build(mid+1,r,rs);
    push_up(p);
}

void update_range(int nl, int nr, int l, int r, int p, int add, int mul) {
    if (nl <= l && nr >= r) {
        apply(l,r,p,add,mul);
        return;
    }
    push_down(l,r,p);
    int mid = (l+r)>>1;
    if (nl <= mid) update_range(nl,nr,l,mid,ls,add,mul);
    if (nr >= mid+1) update_range(nl,nr,mid+1,r,rs,add,mul);

    push_up(p);
}

int query(int nl, int nr, int l, int r, int p) {
    if (nl <= l && nr >= r) return tr[p];
    push_down(l,r,p);

    int mid = (l+r)>>1;
    if (nl > mid) return query(nl,nr,mid+1,r,rs);
    if (nr <= mid) return query(nl,nr,l,mid,ls);
    else return (query(nl,nr,mid+1,r,rs) + query(nl,nr,l,mid,ls))% m;
}

int main() {
    cin>>n>>q>>m;
    for (int i = 1 ; i <= n ; ++i) {
        cin>>arr[i];
    }
    build(1,n,1);

    for (int i = 1 ; i <= q ; ++i) {
        cin>>op;
        if (op == 1) {
            cin>>x>>y>>k;
            update_range(x,y,1,n,1,0,k);
        }else if (op == 2) {
            cin>>x>>y>>k;
            update_range(x,y,1,n,1,k,1);
        }else {
            cin>>x>>y;
            cout<<query(x,y,1,n,1)<<endl;
        }
    }
    return 0;
}
