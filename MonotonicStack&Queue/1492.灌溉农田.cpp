#include <bits/stdc++.h>

using namespace std;


int main() {

    int n;
    cin >> n;

    vector<int> h(n);
    vector<int> c(n);
    for(int i=0; i<n; ++i) cin >> h[i];
    for(int i=0; i<n; ++i) cin >> c[i];


    vector<int> L(n), R(n);
    stack<int> st;

    for (int i = 0; i < n; ++i) {

        while (!st.empty() && h[st.top()] <= h[i]) {
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

    for (int i = n - 1; i >= 0; --i) {

        while (!st.empty() && h[st.top()] <= h[i]) {
            st.pop();
        }

        if (st.empty()) {
            R[i] = n;
        } else {
            R[i] = st.top();
        }
        st.push(i);
    }

    long long max_val = -1;
    int best_id = -1;

    for (int i = 0; i < n; ++i) {
        long long width = (long long)R[i] - L[i] - 1;
        long long current_val = width * c[i];

        if (current_val > max_val) {
            max_val = current_val;
            best_id = i;
        } else if (current_val == max_val) {

            if (best_id == -1 || i < best_id) {
                best_id = i;
            }
        }
    }

    cout << best_id << " " << max_val << endl;

    return 0;
}