#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int n,m,x,y;
vector<vector<double>> dp;
vector<double> e,f,d;

inline void reset_d() {
    std::fill(d.begin(),d.end(),0.0);
    d[1] -= 1.0; d[m] -= 1.0;
}
inline void set_d(int current_row) {
    for (int i = 1 ; i <= m ; ++i) {
        d[i] += dp[current_row+1][i];
    }
}
inline void set_ef() {
    e[1] = 0.5;
    f[1] = (d[1] + 4.0)/2.0;
    for (int i = 2 ; i < m ; ++i) {
        e[i] = 1.0/(3.0 - e[i-1]);
        f[i] = (d[i] + 4.0 + f[i-1])/(3.0 - e[i-1]);
    }

}
inline void fill_dp(int current_row) {
    dp[current_row][m] = (d[m] + 4.0 + f[m-1])/(2.0 - e[m-1]);
    for (int i = m-1 ; i >= 1 ; --i) {
        dp[current_row][i] = e[i]*dp[current_row][i+1] + f[i];
    }
}


int main() {
    cin>>n>>m>>x>>y;

    if (m == 1) {
        cout<<fixed<<setprecision(5)<<(n-x)*2.0<<endl;
        return 0;
    }

    dp.resize(n+1,vector<double>(m+1,0.0));

    d.resize(m+1,0.0);
    reset_d();

    e.resize(m+1,0.0);
    f.resize(m+1,0.0);


    for (int current_row = n-1; current_row >= x ; --current_row) {
        set_d(current_row);
        set_ef();

        fill_dp(current_row);
        reset_d();
    }
    cout<<fixed<<setprecision(5)<<dp[x][y]<<endl;

    return 0;
}