#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e7;
int pmt[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;

    cin>>n;
    string s;
    for (int t = 0 ; t < n ; ++t) {
        cin>>s;
        memset(pmt,0,sizeof(int)*maxn);
        pair<int,int> cur_max = {0,0};
        for (int i = s.length() , j = 0 ; i >= 0 ; --i) {
            while (j && s[i]!=s[j]) j = pmt[j-1];
            if (s[i] == s[j]) ++j;
            pmt[i] = j;
            if (j >= cur_max.first) {
                cur_max = {j,i};
            }
        }

        int idx = cur_max.second;
        while (cur_max.first--) {
            cout<<s[idx];
            ++idx;
        }
        cout<<endl;
    }



    return 0;
}