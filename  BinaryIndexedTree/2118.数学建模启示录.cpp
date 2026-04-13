#include<bits/stdc++.h>
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

int n , tot , ans = 0;
const int maxn = 1e6;
const int mod = 10000007;
int a[maxn],  b[maxn], c[maxn], tree[maxn], pre[maxn], suf[maxn];

int mul_mod(int k, int l, int v) {
    return ((__int128)k * l % mod) * v % mod;
}

void update(int x) {
    int val = b[x] % mod;
    for (; x <= n; x += lowbit(x)) {
        tree[x] = (val + tree[x]) % mod;
    }
}

int query(int x) {
    int res = 0;
    for (; x > 0; x -= lowbit(x)) {
        res = (tree[x] + res) % mod;
    }
    return res;
}

int main() {
    read(n);
    for (int i = 1 ; i <= n ; ++i) {
        read(a[i]);
        b[i] = a[i];
    }
    std::sort(b+1 , b+n+1);
    tot = std::unique(b + 1, b + n + 1) - (b+1);
    for (int i = 1; i <= n; i++) {
        c[i] = std::lower_bound(b + 1, b + tot + 1, a[i]) - b;
    }

    memset(tree,0,sizeof(int)*(n+1));
    for (int i = 1 ; i <= n ; ++i) {
        pre[i] = query(c[i] - 1);
        update(c[i]);
    }

    memset(tree,0,sizeof(int)*(n+1));
    for (int i = n ; i >= 1 ; --i) {
        suf[i] = (query (tot) + mod - query(c[i])) % mod;
        update(c[i]);
    }

    for (int i = 1 ; i <= n ; ++i) {
        ans = (ans + mul_mod(pre[i] , a[i] , suf[i])) % mod;
    }

    write(ans);
    printf("\n");
}