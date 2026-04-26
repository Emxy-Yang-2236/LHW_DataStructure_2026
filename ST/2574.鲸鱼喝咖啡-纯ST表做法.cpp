#include <bits/stdc++.h>

using namespace std;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            f = -1;
        }
        ch = getchar();
    }


    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }

    return x * f;
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

constexpr int maxn = 1e5 + 1;

int n,l,r;
int sum[maxn] , lg[maxn] , st[maxn][20];

int main() {
    n = read();
    l = read();
    r = read();

    for (int i = 1 ; i <= n ; ++i) {
        //sum[i] = sum[i-1] + read();
        st[i][0] = st[i-1][0] + read();
    }

    lg[1] = 0;
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i>>1] + 1;
    }

    for (int j = 1 ; j <= lg[n] ; ++j) {
        for (int i = 0 ; i <= n - (1<<j) +1 ; ++i) {
            st[i][j] = min(st[i][j-1] , st[i + (1<<(j-1))][j-1]);
        }
    }

    for (int i = 1 ; i <= n ; ++i) {
        int ans = static_cast<int>(-1e9);

        for (int right = i; right <= min(n, i + r - 1); right++) {
            int ql = max(0,right - r);
            int qr = min(i - 1 , right - l);

            if (ql <= qr) {
                int k = lg[qr - ql + 1];
                int min_sum = min(st[ql][k], st[qr - (1 << k) + 1][k]);
                ans = max(ans , st[right][0] - min_sum);
            }
        }

        write(ans);
        printf(" ");
    }
    return 0;
}