#include<bits/stdc++.h>

using namespace std;

long long n,L,R,ans=0;
const long long maxn = 1e6+10;
long long a[maxn], tr[maxn];

long long lowbit(long long x) {
    return x & -x;
}
void update(long long i, long long val) {
    for (;i <= maxn; i += lowbit(i)) {
        tr[i] += val;
    }
}
void build(long long l, long long r) {
    for (long long i = l ; i <= r ; ++i) {
        update(a[i] , 1);
    }
}
long long query(long long x) {
    long long ret = 0;
    for (; x > 0; x -= lowbit(x)) {
        ret += tr[x];
    }
    return ret;
}

int main() {
    cin>>n>>L>>R;
    for (long long i = 1; i <= n; ++i) {
        cin>>a[i];
    }

    long long init_l = 1+L , init_r = 1+R;
    if (init_l > n) {
        cout<<0<<endl;
        return 0;
    }
    if (init_r > n) {
        init_r = n;
    }
    build(init_l,init_r);
    for (long long i = 1;  i < n; ++i) {
        ans += query(maxn) - query(a[i]);
        long long l = i+L , r = i+R;
        if (l + 1 > n) break;
        update(a[l] , -1);
        if (r + 1 <= n) update(a[r+1],1);
    }

    cout<<ans<<endl;
}