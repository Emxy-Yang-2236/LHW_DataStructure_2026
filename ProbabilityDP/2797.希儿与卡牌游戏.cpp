#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int n,h,q,x;
int num = 0;

int main() {
    cin>>n>>h;
    int current_num = 0;
    for (int i = 0 ; i < n ; ++i) {
        cin>>q>>x;
        if (q == 2) {
            h -= x;
            num = current_num;
        }else {
            current_num += x;
        }
    }
    if (h <= 0 || h <= num) {
        cout<<fixed<<setprecision(4)<<1.0<<endl;
        return 0;
    }
    if (h > num * 6) {
        cout<<fixed<<setprecision(4)<<0.0<<endl;
        return 0;
    }

    vector<long double> dp(6*num+1 , 0.0);
    std::fill(dp.begin()+1,dp.begin()+7,1.0/6.0);

    for (int i = 2 ; i <= num ; ++i) {
        vector<long double> new_dp(6*num+1 , 0.0);
        for (int j = i ; j <= 6*i && j < h ; ++j) {
            for (int t = 1 ; t <= 6 && j - t > 0 ; ++t) {
                new_dp[j] += 1.0/6.0 * dp[j-t];
            }
        }
        dp = new_dp;
    }

    long double ans = 1.0;
    for (int i = num ; i < h ; ++i) {
        ans -= dp[i];
    }

    cout<<fixed<<setprecision(4)<<ans<<endl;
    return 0;

}

//未解决，挂了六个点