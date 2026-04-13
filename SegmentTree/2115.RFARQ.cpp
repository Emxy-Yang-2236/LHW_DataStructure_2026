#include <bits/stdc++.h>
using namespace std;

typedef __int128 ll;
const int maxn=1e6+10 , mod = 998244353;
int n,q;
int tr[maxn << 2] , tag1[maxn << 2] , tag2[maxn << 2] , arr[maxn] , fibo[maxn];
int op,ql,qr,qa,qb;

void init_fibo() {
    fibo[0] = 0;
    fibo[1] = 1;
    for (int i = 2 ; i <= n+10 ; ++i) {
        fibo[i] = (fibo[i-1] + fibo[i-2]) % mod;
    }
}

void push_up(int p) {
    tr[p] = (tr[p<<1] + tr[p<<1|1]) % mod;
}

int mul_mod(int a , int b) {
    return (ll)a * b % mod;
}

void apply(int l, int r, int p, int add1 , int add2) {
    if (l == r) {
        tr[p] = (add1 + tr[p]) % mod;
    }else if (r - l == 1) {
        tr[p] = ((ll)add1 + add2 + tr[p]) % mod;
        tag1[p] = ((ll)add1 + tag1[p]) % mod;
        tag2[p] = ((ll)add2 + tag2[p]) % mod;
    }else {
        int len = r - l + 1;
        tr[p] = ((ll)mul_mod(fibo[len] , add1) + mul_mod((fibo[len+1] + mod - 1) % mod , add2) + tr[p]) % mod;
        tag1[p] = (add1 + tag1[p]) % mod;
        tag2[p] = (add2 + tag2[p]) % mod;
    }
}

void push_down(int l , int r , int p) {
    if (l == r) return;
    if (tag1[p] == 0 && tag2[p] == 0) return ;
    int mid = (l + r) >> 1;
    int start = mid+1 - l + 1;
    int add2_1 , add2_2;
    if (start == 1) {
        add2_1 = tag1[p];
        add2_2 = tag2[p];
    }else {
        add2_1 = (mul_mod(fibo[start - 2] , tag1[p]) + mul_mod(fibo[start - 1] , tag2[p])) % mod;
        add2_2 = (mul_mod(fibo[start - 1] , tag1[p]) + mul_mod(fibo[start] , tag2[p])) % mod;
    }
    apply(l,mid,p<<1,tag1[p],tag2[p]) , apply(mid+1,r,p<<1|1,add2_1,add2_2);
    tag1[p] = 0;
    tag2[p] = 0;
}

void build(int l, int r, int p) {
    tag1[p] = 0;
    tag2[p] = 0;
    if (l == r) {
        tr[p] = arr[l] % mod;
        return;
    }
    int mid = (l+r)>>1;
    build(l , mid , p<<1) , build(mid+1,r,p<<1|1);
    push_up(p);
}

void update_range(int nl,int nr,int l,int r,int p,int add1,int add2) {
    if (nl <= l && nr >= r) {
        //return (void) apply(l,r,p,add1,add2);
        int d = l - ql;
        int cur_a, cur_b;
        if (d == 0) {
            cur_a = qa;
            cur_b = qb;
        } else {
            cur_a = (mul_mod(fibo[d - 1], qa) + mul_mod(fibo[d], qb)) % mod;
            cur_b = (mul_mod(fibo[d], qa) + mul_mod(fibo[d + 1], qb)) % mod;
        }
        return apply(l, r, p, cur_a, cur_b);
    }
    push_down(l,r,p);

    int mid = (l+r)>>1;
    if (nl <= mid) update_range(nl,nr,l,mid,p<<1,add1,add2);
    if (nr >= mid+1) update_range(nl,nr,mid+1,r,p<<1|1,add1,add2);

    push_up(p);
}

int query(int nl, int nr, int l, int r, int p) {
    if (nl <= l && nr >= r) return tr[p];
    push_down(l,r,p);

    int mid = (l+r)>>1;
    if (nr <= mid) return query(nl, nr, l, mid, p<<1);
    if (nl >= mid+1) return query(nl, nr, mid+1, r, p<<1|1);
    return (query(nl, nr, l, mid, p<<1) + query(nl, nr, mid+1, r, p<<1|1)) % mod;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>q;
    for (int i = 1 ; i <= n ; ++i) {
        cin>>arr[i];
    }
    build(1,n,1);
    init_fibo();

    for (int i = 1 ; i <= q ; ++i) {
        cin>>op;
        if (op == 1) {
            cin>>ql>>qr>>qa>>qb;
            update_range(ql,qr,1,n,1,qa,qb);
        }else {
            cin>>ql>>qr;
            int ans = query(ql,qr,1,n,1);
            cout<<ans<<endl;
        }
    }
}