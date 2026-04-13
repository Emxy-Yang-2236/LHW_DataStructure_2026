#include <bits/stdc++.h>

using namespace std;

long long N;

struct land {
    long long w ;
    long long l ;
    land(long long w_ , long long l_):w(w_) , l(l_) {}
    land():w(0) , l(0){}
};
vector<land> lands ;
int main() {
    cin>>N;
    lands.resize(N+1);

    for (long long i = 1 ; i <= N ; ++i) {
        cin>>lands[i].w>>lands[i].l;
    }

    std::sort(lands.begin() + 1 , lands.end() , [](const land& a , const land& b)->bool {
       if (a.w != b.w) {
           return a.w < b.w;
       } else return a.l < b.l;
    });

    deque<land> q;

    for (long long i = 1 ; i <= N ; ++i) {
        while (!q.empty() && q.back().l <= lands[i].l) {
            q.pop_back();
        }
        q.emplace_back(lands[i]);
    }

    lands.clear();
    lands.emplace_back(0,0);
    while (!q.empty()) {
        lands.emplace_back(q.front());
        q.pop_front();
    }
    N = lands.size() -1;
    vector<long long>dp(N+1,0);

    deque<long long> dq;
    dq.push_back(0);

    for (long long i = 0 ; i <= N ; ++i) {
        while (dq.size() >= 2 && dp[dq[0]] - dp[dq[1]] >= (-lands[i].w) * (lands[dq[0]+1].l - lands[dq[1]+1].l)) {
            dq.pop_front();
        }
        dp[i] = dp[dq.front()] + lands[dq.front() + 1].l * lands[i].w;

        while (dq.size() >= 2 && (dp[dq[dq.size() - 1]] - dp[i]) * (lands[dq[dq.size() - 2] + 1].l - lands[i+1].l) >=
             (dp[dq[dq.size() - 2]] - dp[i]) * (lands[dq[dq.size() - 1] + 1].l - lands[i+1].l)
        ) {
            dq.pop_back();
        }

        dq.emplace_back(i);
    }

    cout<<dp[N]<<endl;

    return 0;
}