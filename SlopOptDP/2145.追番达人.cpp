#include <bits/stdc++.h>

using namespace std;

typedef __int128 lll;

long long n,C,t;
const lll maxn = 5e5;
lll sum[maxn] , k[maxn] , x[maxn] ;
long long dp[maxn];

lll y(lll i) {
    return (lll)dp[i] + (lll)x[i] * x[i];
}

int main() {
    cin>>n>>C;
    for (int i = 1 ; i <= n ; ++i) {
        cin>>t;
        sum[i] = sum[i-1] + t;
        k[i] = 2*(i+sum[i]);
    }

    for (int i = 0; i <= n; i++) {
        x[i] = (sum[i] + i) + C + 1;
    }

    deque<lll> q;
    q.push_back(0);

    for (lll i = 1 ; i <= n+1 ; ++i) {
        while (q.size() >= 2 &&
           (y(q[1]) - y(q[0])) <= k[i]*(x[q[1]] - x[q[0]])
           ) {
            q.pop_front();
           }

        lll ans_idx = q.front();
        dp[i] = y(ans_idx) - k[i]*x[ans_idx] + (i + sum[i]) * (i + sum[i]);

        while (q.size() >= 2 &&
            (y(i) - y(q.back()))*(x[i]-x[q[q.size() - 2]]) <=
            (y(i) - y(q[q.size() - 2]))*(x[i]-x[q.back()])
            ) {
            q.pop_back();
            }

        q.push_back(i);
    }

    cout<<dp[n]<<endl;

    return 0;
}