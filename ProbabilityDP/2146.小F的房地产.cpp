#include <bits/stdc++.h>

using namespace std;

int main() {
    int N,M;
    long long ans = 0;
    cin>>N>>M;
    vector<vector<int>>land(N,vector<int>(M,0));
    char c;
    for (int i = 0 ; i < N ; ++i) {
        for (int j = 0 ; j < M ; ++j) {
            cin>>c;
            if (i == 0) {
                land[i][j] = (c == '.' ? 1 : 0);
            }else {
                land[i][j] = (c == '.' ? 1 + land[i-1][j] : 0);
            }
        }
    }
    vector<int> L(M),R(M);
    for (auto row : land) {
        stack<int> st;
        for (int i = 0 ; i < M ; ++i) {
            while (!st.empty() && row[st.top()] >= row[i]) {
                st.pop();
            }

            if (st.empty()) {
                L[i] = -1;
            } else {
                L[i] = st.top();
            }
            st.push(i);
        }

        while (!st.empty()) st.pop();

        for (int i = M - 1; i >= 0; --i) {

            while (!st.empty() && row[st.top()] > row[i]) {
                st.pop();
            }

            if (st.empty()) {
                R[i] = M;
            } else {
                R[i] = st.top();
            }
            st.push(i);
        }

        for (int i = 0 ; i < M ; ++i) {
            long long H = row[i] *(row[i]+1) / 2;
            int X = i - L[i];
            int Y = R[i] - i;

            long long W = X * Y + Y * (X * (X-1))/2 + X * (Y * (Y-1))/2;

            ans += H*W;
        }
    }

    cout<<ans<<endl;
    return 0;
}