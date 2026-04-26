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

constexpr long long maxn = 2e5 + 1;
long long n,m,l,r,ans;
long long lg[maxn] , a[maxn] , len[maxn] , st[maxn][20] , max_l[maxn];

unordered_map<long long,long long> last_pos;

inline long long query_max(long long l, long long r) {
    long long k = lg[r - l + 1];
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}


int main() {
    lg[1] = 0;
    n = read();
    m = read();
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i>>1] + 1;
    }

    for (long long i = 1 ; i <= n ; ++i) {
        a[i] = read();
        if (i == 1) {
            max_l[i] = 1;
        }else if (!last_pos.count(a[i])) {
            max_l[i] = max(static_cast<long long>(1) , max_l[i-1]);
        }else {
            max_l[i] = max(last_pos[a[i]] + 1 , max_l[i-1]);
        last_pos[a[i]] = i;
        }
        len[i] = i - max_l[i] + 1;

        st[i][0] = len[i];
    }

    // for (int i = 1 ; i <= n ; ++i) {
    //     cerr<<len[i]<<" ";
    // }



    for (int j = 1 ; j <= lg[n] ; ++j) {
        for (int i = 1 ; i <= n - (1<<j) + 1 ; ++i) {
            st[i][j] = max(st[i][j-1] , st[i + (1<<(j-1))][j-1]);
        }
    }

    while (m--) {
        cin>>l>>r;

        ++l; ++r;

        auto edge = std::upper_bound(max_l+l ,max_l+r+1,l );
        auto idx = edge - max_l  ;

        ans = max(static_cast<long long>(idx - l ) , min(query_max(idx,r) , r - l + 1));

        //cerr<<query_max(idx,r)<<endl;

        write(ans);
        putchar('\n');
    }

    return 0;
}