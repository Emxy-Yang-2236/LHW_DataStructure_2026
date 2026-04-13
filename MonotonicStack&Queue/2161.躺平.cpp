#include <bits/stdc++.h>

using namespace std;

template<class T>
void PrintVec(vector<vector<T>> v) {
    for (auto i : v) {
        for (auto j : i) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
}

int main() {
    int a,b,m,n;
    int ans = 2e9+7;
    cin>>a>>b>>m>>n;
    vector<vector<int>> land(a,vector<int>(b));

    for (int i = 0 ; i < a ; ++i) {
        for (int j = 0 ; j < b ; ++j) {
            cin>>land[i][j];
        }
    }

    vector<vector<int>> mid_max(a);
    vector<vector<int>> mid_min(a);

    for (int i = 0 ; i < a ; ++i) {
        deque<int> dq_max;
        deque<int> dq_min;

        for (int j = 0 ; j < b ; ++j) {
            while (!dq_max.empty() && land[i][dq_max.back()] <= land[i][j]) {
                dq_max.pop_back();
            }
            while (!dq_min.empty() && land[i][dq_min.back()] >= land[i][j]) {
                dq_min.pop_back();
            }

            dq_max.emplace_back(j);
            dq_min.emplace_back(j);

            if (dq_max.front() <= j - n) {
                dq_max.pop_front();
            }
            if (dq_min.front() <= j - n) {
                dq_min.pop_front();
            }

            if (j >= n - 1) {
                mid_max[i].emplace_back(land[i][dq_max.front()]);
                mid_min[i].emplace_back(land[i][dq_min.front()]);
            }
        }
    }
    //PrintVec(mid_max);
    //PrintVec(mid_min);
    //cerr<<mid_max.size()<<endl<<mid_max[0].size()<<endl;
    for (int i = 0 ; i < b - n + 1 ; ++i) {
        deque<int> dq_max;
        deque<int> dq_min;

        for (int j = 0 ; j < a ; ++j) {
            while (!dq_max.empty() && mid_max[dq_max.back()][i] <= mid_max[j][i]) {
                dq_max.pop_back();
            }
            while (!dq_min.empty() && mid_min[dq_min.back()][i] >= mid_min[j][i]) {
                dq_min.pop_back();
            }

            dq_max.emplace_back(j);
            dq_min.emplace_back(j);

            if (dq_max.front() <= j - m) {
                dq_max.pop_front();
            }
            if (dq_min.front() <= j - m) {
                dq_min.pop_front();
            }

            if (j >= m - 1) {
                ans = min(ans,mid_max[dq_max.front()][i] - mid_min[dq_min.front()][i]);
            }
        }
    }

    cout<<ans<<endl;
    return 0;
}