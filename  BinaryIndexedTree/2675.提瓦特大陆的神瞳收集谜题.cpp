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

inline int lowbit(int x) {
    return x & (-x);
}

struct Q {
    int idx_;
    int l_;
    int r_;
    int ans_ = 0;
    Q() = default;
    Q(int idx , int l , int r):idx_(idx) , l_(l) , r_(r){}
};

int n,m;
const int maxn = 1e7;
int a[maxn],b[maxn],tree[maxn];
Q q[maxn];

void simplify() {
    for (int i = 1; i <= n; i++) b[i] = a[i];
    std::sort(b + 1, b + n + 1);
    int tot = std::unique(b + 1, b + n + 1) - (b + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = std::lower_bound(b + 1, b + tot + 1, a[i]) - b;
    }
}
void update(int x, int v) {
    for (; x <= n; x += lowbit(x)) {
        tree[x] += v;
    }
}

int query(int x) {
    int res = 0;
    for (; x > 0; x -= lowbit(x)) {
        res += tree[x];
    }
    return res;
}
int main() {
    read(n);
    for (int i = 1 ; i <= n ; ++i) {
        read(a[i]);
    }
    simplify();
    memset(b,0,sizeof(int) * (n + 1));
    read(m);
    for (int i = 1 ; i <= m ; ++i) {
        q[i].idx_ = i;
        read(q[i].l_);
        read(q[i].r_);
    }
    std::sort(q+1 , q+m+1 , [](const Q & a , const Q &b) -> bool {
        return a.r_ <= b.r_;
    });

    int p = 1;
    for (int i = 1 ; i <= n ; ++i) {
        if (b[a[i]]) {
            update(b[a[i]], -1);
            update(i,1);
            b[a[i]] = i;
        }else {
            update(i,1);
            b[a[i]] = i;
        }

        while (p <= m && q[p].r_ == i) {
            q[p].ans_ = query(i) - query(q[p].l_ - 1);
            ++p;
        }
    }

    std::sort(q+1 , q+m+1 , [](const Q & a , const Q &b) -> bool {
        return a.idx_ <= b.idx_;
    });
    for (int i = 1 ; i <= m ; ++i) {
        write(q[i].ans_);
        printf("\n");
    }
    return 0;
}