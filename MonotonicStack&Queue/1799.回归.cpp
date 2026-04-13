#include <bits/stdc++.h>

using namespace std;


int main() {
    long long n;
    cin>>n;

    vector<long long> card(n) , perfix(n+1,0);
    for (long long i = 0 ; i < n ; ++i) {
        cin>>card[i];
        perfix[i+1] = perfix[i] + card[i];
    }

    vector<long long> L(n) , R (n);

    stack<long long> st;

    for (long long i = 0; i < n; ++i) {

        while (!st.empty() && card[st.top()] >= card[i]) {
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

    for (long long i = n - 1; i >= 0; --i) {

        while (!st.empty() && card[st.top()] >= card[i]) {
            st.pop();
        }

        if (st.empty()) {
            R[i] = n;
        } else {
            R[i] = st.top();
        }
        st.push(i);
    }

    long long ans = 0;

    for (long long i = 0 ; i < n ; ++i) {
        long long current_val = (perfix[R[i]] - perfix[L[i]+1])*card[i];
        ans = max(ans,current_val);

        //cout<<card[i]<<" "<<ans<<endl;
    }

    cout<<ans<<endl;
    return 0;
}