#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+7;
int N,Q;
int a[maxn] , pos[maxn] , st[maxn][20] , lg[maxn];

inline int query(int l, int r) {
    int q = lg[r - l + 1];
    return max(st[l][q] , st[r - (1<<q) + 1][q]);
}

inline int solve(int l, int r) {
    int low = 0, high = ((r - l + 1)>>1) + 1;
    while (high - low > 1) {
        int mid = (low + high)>>1;
        if (query(l,l+mid-1) <= r - l - mid + 1) {
            low = mid;
        }else {
            high = mid;
        }
    }
    return low;
}

int main() {
    cin>>N;
    memset(pos,-1,sizeof(int)*maxn);
    lg[1] = 0;
    for (int i = 2; i <= N; i++) {
        lg[i] = lg[i>>1] + 1;
    }
    for (int i = 1; i <= N ; ++i) {
        cin>>a[i];
    }
    for (int i = 1; i <= N; ++i) {
        auto it = std::lower_bound(a + 1, a + N + 1, 2 * a[i]);
        if (it != a + N + 1) {
            pos[i] = it - a;
        } else {
            pos[i] = N + 1;
        }
        st[i][0] = pos[i] - i;
    }
    for (int j = 1; j <= lg[N]; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= N; ++i) {
            st[i][j] = std::max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }

    cin>>Q;
    int l , r;
    for (int i = 1; i <= Q ; ++i) {
        cin>>l>>r;
        cout<<solve(l,r)<<endl;
    }

}