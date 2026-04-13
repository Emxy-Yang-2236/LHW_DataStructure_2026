#include <bits/stdc++.h>
using namespace std;

int main() {
    int length,h;
    long long max_s = 0;
    cin>>length;
    stack<pair<int,int>> st;
    st.emplace(0,0);
    for (int i = 1 ; i <= length+1 ; ++i) {
        cin>>h;
        if (i == length+1) {
            h = 0;
        }
        while (h < st.top().first) {
            auto tmp = st.top();
            st.pop();
            max_s = max(max_s,static_cast<long long>(tmp.first*(i-st.top().second-1)));
        }
        st.emplace(h,i);
    }

    cout<<max_s<<endl;


    return 0;
}