#include <bits/stdc++.h>
using namespace std;

inline void read(int &x){
    char ch=getchar();int f=1;x=0;
    while(!isdigit(ch) && ch^'-') ch=getchar();
    if(ch=='-') f=-1,ch=getchar();
    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    x*=f;
}
inline void write(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}

const int maxn = 5e5 + 10;
int n,m;
int x,bl,br;
int h[maxn] ,tr[maxn<<2], tag[maxn<<2];

inline void push_up(int p) {
    tr[p] = max(tr[p<<1] , tr[p<<1|1]);
}

inline void build(int l, int r, int p) {
    tag[p] = -1;
    if (l == r) {
        tr[p] = h[l];
        return;
    }
    int mid = (l+r)>>1;
    build(l , mid , p<<1) , build(mid+1,r,p<<1|1);
    push_up(p);
}

inline void apply(int p, int k) {
    if (tr[p] > k) {
        tr[p] = k;
        tag[p] = k;
    }
}

inline void push_down(int p) {
    if (tag[p] == -1) return;
    apply(p<<1,tag[p]) , apply(p<<1|1 , tag[p]);
    tag[p] = -1;
}

inline void update(int nl, int nr, int l, int r, int p, int k) {
    if (tr[p] <= k) return;

    if (nl <= l && nr >= r) {
        if (tr[p] <= k) {
            return;
        }
        return (void) apply(p,k);
    }
    push_down(p);

    int mid = (l+r)>>1;
    if (nl <= mid) update(nl, nr, l, mid, p<<1, k);
    if (nr >= mid+1) update(nl, nr, mid+1, r, p<<1|1, k);

    push_up(p);
}

void query(int l , int r , int p) {
    if (l == r) {
        h[l] = tr[p];
        return;
    }
    push_down(p);

    int mid = (l+r)>>1;
    query(l,mid,p<<1);
    query(mid+1,r,p<<1|1);
}

int main() {
    read(n),read(m);
    //memset(tag,-1,sizeof(int)*((n<<2)+5));
    for (int i = 1 ; i <= n ; ++i) {
        read(h[i]);
    }
    build(1,n,1);
    for (int i = 1 ; i <= m ; ++i) {
        read(x),read(bl),read(br);
        update(bl,br,1,n,1,x);
    }
    query(1,n,1);
    for (int i = 1 ; i <= n ; ++i) {
        write(h[i]);
        printf(" ");
    }
    return 0;
}