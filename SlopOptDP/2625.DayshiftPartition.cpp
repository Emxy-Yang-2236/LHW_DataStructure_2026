#include <bits/stdc++.h>

using namespace std;
typedef __int128 lll;

const lll maxn = 2e5;
long long n;
long long w[maxn] , t[maxn] ;
lll S[maxn] , W[maxn] , P[maxn];
long long ans = 1e18;
inline lll x(lll j) {
    return W[j+1];
}
inline lll y(lll j) {
    return S[j-1]*W[1] - S[j-1]*W[j+1];
}
inline lll k_(lll k) {
    return -S[k-1];
}
inline lll get_c(lll k) {
    return S[n]*W[k+1] - S[k-1]*W[k+1] - P[1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for (lll i = 1 ; i <= n ; ++i) {
        cin>>w[i]>>t[i];
        S[i] = S[i-1] +(lll) t[i];
    }
    for (lll i = n ; i >= 1 ; --i) {
        W[i] = W[i+1] + (lll)w[i];
        P[i] = P[i+1] + (lll)w[i]*S[i-1];
    }
    deque<lll> q;
    for (lll k = 2 ; k <= n ; ++k) {
        lll c = get_c(k);
        lll j = k-1;
        while (q.size() >= 2 &&
            y(q[0]) - y(q[1]) >= k_(k) * (x(q[0]) - x(q[1]))
        ) {
            q.pop_front();
        }
        lll cur_idx = q.front();
        lll cur_ans = y(cur_idx) + c - k_(k) * x(cur_idx);
        ans = min(ans , static_cast<long long>(cur_ans));
        //cerr<<'1';

        //lll b = q[q.size() - 1] , fb = q[q.size() - 2];
        while (q.size() >= 2 &&
            (y(q[q.size() - 1]) - y(j))*(x(q[q.size() - 2]) - x(j)) >=
            (y(q[q.size() - 2]) - y(j))*(x(q[q.size() - 1]) - x(j))
        ) {
            q.pop_back();
        }
        q.push_back(j);
        //cerr<<'2';
    }

    cout<<ans<<endl;

    return 0;
}