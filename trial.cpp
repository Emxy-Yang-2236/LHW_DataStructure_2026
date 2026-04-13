#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 lll;

const int MAXN = 50005;
ll dp[MAXN], s[MAXN];
ll f[MAXN];
ll X[MAXN];

lll Y(int j) {
    return (lll)dp[j] + (lll)X[j] * X[j];
}

int q[MAXN];

int main() {
    int n;
    ll C;
    scanf("%d%lld", &n, &C);
    ll L = C + 1;

    for (int i = 1; i <= n; i++) {
        ll t;
        scanf("%lld", &t);
        s[i] = s[i - 1] + t;
    }
    for (int i = 0; i <= n; i++) {
        f[i] = s[i] + i;
        X[i] = f[i] + L;
    }

    dp[0] = 0;
    int head = 0, tail = 0;
    q[tail++] = 0;

    for (int i = 1; i <= n; i++) {

        while (head + 1 < tail) {
            int a = q[head], b = q[head + 1];
            lll lhs = Y(b) - Y(a);
            lll rhs = (lll)2 * f[i] * (X[b] - X[a]);
            if (lhs <= rhs)
                head++;
            else
                break;
        }

        int j = q[head];
        ll diff = f[i] - f[j] - L;
        dp[i] = dp[j] + diff * diff;


        while (head + 1 < tail) {
            int a = q[tail - 2], b = q[tail - 1];
            lll lhs = (Y(b) - Y(a)) * ((lll)X[i] - X[b]);
            lll rhs = (Y(i) - Y(b)) * ((lll)X[b] - X[a]);
            if (lhs >= rhs)
                tail--;
            else
                break;
        }

        q[tail++] = i;
    }

    printf("%lld\n", dp[n]);
    return 0;
}