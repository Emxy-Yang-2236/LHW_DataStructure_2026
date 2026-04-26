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

    deque<long long> dq_l;
    long long ptr = max(mid + 1, left + L - 1);

    for (long long i = left; i <= mid; i++) {
        long long l = i;
        long long r_min = max(mid + 1, l + L - 1);
        long long r_max = min(right, l + R - 1);

        if (r_min > r_max) {
            ans[i] = max(ans[i], max_score);
            continue;
        }

        if (ptr < r_min) ptr = r_min;

        while (!dq_l.empty() && dq_l.front() < r_min) {
            dq_l.pop_front();
        }

        while (ptr <= r_max) {
            while (!dq_l.empty() && sum[dq_l.back()] <= sum[ptr]) {
                dq_l.pop_back();
            }
            dq_l.push_back(ptr);
            ++ptr;
        }

        if (!dq_l.empty()) {
            long long max_r_val = sum[dq_l.front()];
            max_score = max(max_score, max_r_val - sum[l - 1]);
        }

        ans[i] = max(ans[i], max_score);
    }

    long long max_score_r = -INF;

    dq_l.clear();
    ptr = min(mid, right - L + 1) - 1;

    for (long long i = right; i >= mid + 1; i--) {
        long long r = i;
        long long l_min = max(left, r - R + 1) - 1;
        long long l_max = min(mid, r - L + 1) - 1;

        if (l_min > l_max) {
            ans[i] = max(ans[i], max_score_r);
            continue;
        }

        if (ptr > l_max) ptr = l_max;

        while (!dq_l.empty() && dq_l.front() > l_max) {
            dq_l.pop_front();
        }

        while (ptr >= l_min) {
            while (!dq_l.empty() && sum[dq_l.back()] >= sum[ptr]) {
                dq_l.pop_back();
            }
            dq_l.push_back(ptr);
            --ptr;
        }

        if (!dq_l.empty()) {
            long long min_l_val = sum[dq_l.front()];
            max_score_r = max(max_score_r, sum[r] - min_l_val);

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


    solve(1, n);

    for (long long i = 1; i <= n; i++) {
        write(ans[i]);
        putchar(' ');
    }

    return 0;
}