#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
#define ls p<<1
#define rs (p<<1|1)
#define c_m int mid = (l+r)>>1;
    vector<int> tr, tag, height;
    void push_up(int p) {
        tr[p] = max(tr[ls], tr[rs]);
    }
    void apply(int p, int h) {
        tr[p] = max(tr[p], h);
        tag[p] = max(tag[p], h);
    }
    void push_down(int p) {
        if (tag[p] == 0) return ;
        apply(ls,tag[p]), apply(rs,tag[p]);
        tag[p] = 0;
    }
    void update_range(int nl, int nr, int l, int r, int p, int h) {
        if (nl <= l && nr >= r) {
            apply(p, h);
            return ;
        }
        push_down(p);

        c_m
        if (nl <= mid) update_range(nl,nr,l,mid,ls,h);
        if (nr >= mid+1) update_range(nl,nr,mid+1,r,rs,h);

        push_up(p);
    }
    void collect(int l, int r, int p, vector<int>& h) {
        if (l == r) {
            h[l-1] = tr[p];
            return;
        }
        push_down(p);

        c_m
        collect(l,mid,ls,h), collect(mid+1,r,rs,h);
    }
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<int> xs;

        for (auto &b : buildings) {
            xs.push_back(b[0]);
            xs.push_back(b[1]);
        }

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        auto getId = [&](int x) {
            return static_cast<int>(lower_bound(xs.begin(), xs.end(), x) - xs.begin() + 1);
        };

        int n = xs.size();
        tr.resize((n+1)<<2, 0), tag.resize((n+1)<<2,0), height.resize(n+1);

        for (auto &b : buildings) {
            int l = getId(b[0]);
            int r = getId(b[1]);
            int h = b[2];
            update_range(l,r-1,1,n-1,1,h);
        }
        collect(1,n-1,1,height);

        vector<vector<int>> ans;
        int his = -1;
        for (int i = 0 ; i < n-1 ; ++i) {
            if (height[i] != his) {
                his = height[i];
                //cout<<xs[i]<<" "<<height[i]<<endl;
                ans.push_back({xs[i], height[i]});
            }
        }
        int i = xs.back();
        ans.push_back({i,0});
        return ans;
    }
};

int main() {
    vector<vector<int>> sample = {{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
    Solution s;
    auto ans = s.getSkyline(sample);
    for (const auto& i : ans) {
        for (auto j : i) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
}
