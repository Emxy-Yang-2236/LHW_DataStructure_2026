#include <bits/stdc++.h>

using namespace std;

inline long long read() {
    long long x = 0, f = 1;
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

inline void write(long long x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}

constexpr long long maxn = 1e5 + 1;
const long long INF = 1e9;

long long n,L,R;
long long sum[maxn] , lg[maxn] , st_min[maxn][20] , st_max[maxn][20], ans[maxn];

inline void build_ST() {
    lg[1] = 0;
    for (long long i = 2; i <= n + 1; i++) lg[i] = lg[i >> 1] + 1;

    for (long long i = 0; i <= n; i++) {
        st_max[i][0] = sum[i];
        st_min[i][0] = sum[i];
    }

    for (long long j = 1; j <= lg[n + 1]; j++) {
        for (long long i = 0; i + (1 << j) - 1 <= n; i++) {
            st_max[i][j] = max(st_max[i][j - 1], st_max[i + (1 << (j - 1))][j - 1]);
            st_min[i][j] = min(st_min[i][j - 1], st_min[i + (1 << (j - 1))][j - 1]);
        }
    }
}

inline long long query_max(long long l, long long r) {
    long long k = lg[r - l + 1];
    return max(st_max[l][k], st_max[r - (1 << k) + 1][k]);
}

inline long long query_min(long long l, long long r) {
    long long k = lg[r - l + 1];
    return min(st_min[l][k], st_min[r - (1 << k) + 1][k]);
}

inline void solve(long long left, long long right) {
    if (right - left + 1 < L) return;
    if (left == right) {
        if (L <= 1 && 1 <= R) {
            ans[left] = max(ans[left], sum[left] - sum[left - 1]);
        }
        return;
    }

    long long mid = left + (right - left) / 2;
    solve(left, mid);
    solve(mid + 1, right);

    long long max_score = -INF;
    for (long long i = left; i <= mid; i++) {
        long long l = i;
        long long r_min = max(mid + 1, l + L - 1);
        long long r_max = min(right, l + R - 1);

        if (r_min <= r_max) {
            long long max_r_val = query_max(r_min, r_max);
            max_score = max(max_score, max_r_val - sum[l - 1]);
        }
        ans[i] = max(ans[i], max_score);
    }

    long long max_score_r = -INF;
    for (long long i = right; i >= mid + 1; i--) {
        long long r = i;
        long long l_min = max(left, r - R + 1);
        long long l_max = min(mid, r - L + 1);

        if (l_min <= l_max) {
            long long min_x_val = query_min(l_min - 1, l_max - 1); // x = l - 1
            max_score_r = max(max_score_r, sum[r] - min_x_val);
        }
        ans[i] = max(ans[i], max_score_r);
    }
}

int main() {
    n = read();
    L = read();
    R = read();

    for (long long i = 1 ; i <= n ; ++i) {
        sum[i] = sum[i-1] + read();
        ans[i] = -INF;
    }

    build_ST();

    solve(1, n);

    for (long long i = 1; i <= n; i++) {
        write(ans[i]);
        putchar(' ');
    }

    return 0;
}