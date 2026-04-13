#include <bits/stdc++.h>

using namespace std;

long long n,a,b,c,s;
const long long maxn = 1e7;
long long sum[maxn] , dp[maxn];

inline long long y(long long j) {
    return dp[j] - b*sum[j] + a*sum[j]*sum[j];
}
inline long long x(long long   j) {
    return sum[j];
}
inline long long k(long long i) {
    return a*2*sum[i];
}
inline long long else_v(long long i) {
    return a*sum[i]*sum[i] + b*sum[i] + c;
}


int main() {
    cin>>n>>a>>b>>c;
    for (long long i = 1 ; i <= n ; ++i) {
        cin>>s;
        sum[i] = sum[i-1] + s;
    }

    deque<long long> q;
    q.emplace_back(0);

    for (long long i = 1 ; i <= n ; ++i) {
        while (q.size() >= 2 && y(q[1]) - y(q[0]) >= k(i) * (x(q[1]) - x(q[0]))) {
            q.pop_front();
        }
        dp[i] = y(q.front()) - k(i)*x(q.front()) + else_v(i);

        while (q.size() >= 2 && (y(i) - y(q[q.size() - 1])) * (x(i) - x(q[q.size() - 2])) >=
        (y(i) - y(q[q.size() - 2])) * (x(i) - x(q[q.size() - 1]))
        ) {
            q.pop_back();
        }
        q.emplace_back(i);
    }

    cout<<dp[n]<<endl;
    return 0;
}