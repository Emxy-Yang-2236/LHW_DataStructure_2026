#ifndef INC_2026_3___4_LEETCODE1178_猜字谜_HPP
#define INC_2026_3___4_LEETCODE1178_猜字谜_HPP
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<std::string>& puzzles) {
        std::unordered_map<int,int> wordmask;
        for (const auto& i : words) {
            int mask = 0;
            for (auto c : i) {
                mask |= 1 << (c - 'a');
            }
            wordmask[mask]++;
        }

        vector<int> ans;
        for (auto s : puzzles) {
            int pmask = 0, cur_ans  = 0;
            for (int c = 1; c < s.size(); ++c) {
                pmask |= 1<<(s[c]-'a');
            }

            int submask = pmask;
            int fix = 1<<(s[0]-'a');
            while (true) {
                if (wordmask.count(submask | fix)) {
                    cur_ans += wordmask[submask | fix];
                }
                if (submask == 0) break;
                submask = (submask-1)&pmask;
            }
            ans.emplace_back(cur_ans);
        }

        return ans;
    }
};

#endif //INC_2026_3___4_LEETCODE1178_猜字谜_HPP
