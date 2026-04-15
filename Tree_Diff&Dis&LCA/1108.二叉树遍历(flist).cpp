#include <bits/stdc++.h>
using namespace std;

string s1,s2;
char root;

string solve(const string& inorder, const string& level) {
    if (inorder.empty()) return "";

    char root = level[0];
    int pos = inorder.find(root);

    string left = inorder.substr(0,pos);
    string right = inorder.substr(pos+1);

    std::unordered_map<char,bool> right_ch;
    for (auto i : left) {
        right_ch[i] = false;
    }for (auto i : right) {
        right_ch[i] = true;
    }

    string leftlevel, rightlevel;
    for (auto i : level.substr(1)) {
        if (right_ch[i]) rightlevel.push_back(i);
        else leftlevel.push_back(i);
    }

    return string(1,root) + solve(left,leftlevel) + solve(right,rightlevel);
}

int main() {
    cin>>s1>>s2;
    cout<<solve(s1,s2)<<endl;

}
