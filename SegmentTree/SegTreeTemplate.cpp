#include <bits/stdc++.h>
using namespace std;

const int maxn=1e5;
int tr[maxn << 2] , tag[maxn << 2] , arr[maxn];
int n;

void push_up(int p) {
    tr[p] = tr[p<<1] + tr[p<<1|1];  //前者是左儿子，后者是右儿子
}

void apply(int p, int k) {
    tr[p] *= k;
    tag[p] *= k;
}

void push_down(int p) {
    if (tag[p] == 1) return;
    apply(p<<1,tag[p]) , apply(p<<1|1 , tag[p]);
    tag[p] = 1;    //传递lazy tag后自身tag重置
}

void build(int l, int r, int p) {
    tag[p] = 1;
    if (l == r) {
        tr[p] = arr[l];
        return;
    }
    int mid = (l+r)>>1;
    build(l , mid , p<<1) , build(mid+1,r,p<<1|1);
    push_up(p);
}

void update_range(int nl, int nr, int l, int r, int p, int k) { //p 为当前树的下标 ， k为乘的倍数
    if (nl <= l && nr >= r) {   //需要更改的区间将当前区间完全覆盖
        return (void) apply(p,k);   //处理：更新该区间值并且打上lazy tag
    }
    push_down(p);   //说明修改区间只是部分覆盖了当前区间，需要往下查找儿子，在此之前需要结算当层的lazy tag，并且把lazytag传到下一层
    //为什么此时要结算？因为做完递归的update后每层都会push_up，为确保遍历过的层（上层）数据的正确性，需要确保我看过的数据都是对的

    int mid = (l+r)>>1;
    if (nr <= mid) update_range(nl, nr, l, mid, p<<1, k);
    if (nl >= mid+1) update_range(nl, nr, mid+1, r, p<<1|1, k);

    push_up(p);  //确保上层数据一定是对的，下层数据允许不更新
}

int query(int nl, int nr, int l, int r, int p) {
    if (nl <= l && nr >= r) return tr[p];
    push_down(p);   //如果有lazy tag 显然需要结算

    int mid = (l+r)>>1;
    if (nl <= mid) return query(nl, nr, l, mid, p<<1);
    if (nr >= mid+1) return query(nl, nr, mid+1, r, p<<1|1);
    return query(nl, nr, l, mid, p<<1) + query(nl, nr, mid+1, r, p<<1|1);
}

int main() {
    cin>>n;
    for (int i = 1 ; i <= n ; ++i) {
        cin>>arr[i];
    }

    return 0;
}