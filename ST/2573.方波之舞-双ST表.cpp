#include <bits/stdc++.h>

using namespace std;

inline int read() {
    int x = 0;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x;
}
inline void write(int x) {
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

constexpr long long maxn = 1e6 + 1;

long long n,m,l,r,d,t,q;
long long cnt1[maxn] , cnt0[maxn];
long long st_up[maxn][20] , lg[maxn] , st_down[maxn][20];  //log(1e6)/log(2) ~ 19.99

int main() {
    n = read();
    m = read();

    lg[1] = 0;
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i>>1] + 1;
    }

    for (int i = 1 ; i <= n ; ++i) {
        d = read();
        if (d == 1) {
            cnt1[i] = cnt1[i-1] + 1;
            cnt0[i] = cnt0[i-1];
        }else {
            cnt0[i] = cnt0[i-1] + 1;
            cnt1[i] = cnt1[i-1];
        }
        st_up[i][0] = cnt0[i] - cnt1[i-1];
        st_down[i][0] = cnt1[i] - cnt0[i-1];
    }

    for (int j = 1 ; j <= lg[n] ; ++j) {
        for (int i = 1 ; i <= n - (1<<j) + 1 ; ++i) {
            st_up[i][j] = max(st_up[i][j-1],st_up[i + (1<<(j-1))][j-1]);
            st_down[i][j] = max(st_down[i][j-1],st_down[i + (1<<(j-1))][j-1]);
        }
    }

    while (m--) {
        t = read();
        l = read();
        r = read();

        q = lg[r - l + 1];
        if (t == 1) {
            write(max(st_up[l][q] , st_up[r - (1<<q) + 1][q]) + cnt1[r] - cnt0[l-1]);
        }else {
            long long max_down = max(st_down[l][q], st_down[r - (1<<q) + 1][q]) + cnt0[r] - cnt1[l-1];

            if (max_down == r - l + 1) {
                write(1);
            } else {
                write(2);
            }
        }
        
        printf("\n");
    }

    return 0;
}