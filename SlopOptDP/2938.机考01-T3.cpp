#include <bits/stdc++.h>
using namespace std;

typedef __int128 lll;
typedef long long ll;

ll g, n, m, p, td, h, t;
const ll maxn = 1e4+7, maxp = 1e3+7, INF = 1e12;
ll d[maxn], T[maxn], S[maxn];
vector<vector<ll>> dp(maxn,vector<ll>(maxp,0));

inline ll e_v(ll j) {
    return T[j]*j  - S[j];
}
inline ll l_y(ll k ,ll cur_p) {
    return dp[k][cur_p-1] + S[k];
}
inline ll k(ll j) {
    return T[j];
}
int main() {
    cin>>g;
    d[1] = 0; S[0] = 0;
    for (ll i = 1; i <= g; ++i) {
        cin>>n>>m>>p;
        for (ll j = 1 ; j <= m ; ++j) {
            dp[j][0] = INF;
        }
        for (ll j = 2; j <= n ; ++j) {
            cin>>td;
            d[j] = d[j-1] + td;
        }
        for (ll j = 1 ; j <= m ; ++j) {
            cin>>h>>t;
            T[j] = (ll)t - d[h];
        }
        std::sort(T+1, T+m+1);
        for (ll j = 1 ; j <= m ; ++j) {
            S[j] = S[j-1] + T[j];
        }
        for (ll num_p = 1 ; num_p <= p ; ++num_p) {
            deque<ll> q;
            q.emplace_back(0);
            for (ll j = 1 ; j <= m ; ++j) {
                while (q.size() >= 2 && (ll)l_y(q[1],num_p) - l_y(q[0],num_p) <= (ll)k(j) * (q[1] - q[0])) {
                    q.pop_front();
                }
                dp[j][num_p] = l_y(q.front(),num_p) - q.front() * k(j) + e_v(j);

                if (dp[j][num_p-1] != INF) {
                    while (q.size() >= 2 && (ll)(l_y(j,num_p) - l_y(q[q.size()-1],num_p)) * (j - q[q.size()-2]) <=
                        (ll)(l_y(j,num_p) - l_y(q[q.size()-2],num_p)) * (j - q[q.size()-1])) {
                        q.pop_back();
                        }
                    q.emplace_back(j);
                }
            }
        }
        cout<<dp[m][p]<<endl;
    }


}