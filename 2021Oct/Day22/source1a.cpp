// 想定解法1 : 出現頻度ごとに文字列構築
// Time:O(N),Space:O(N)

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string frequencySort(string s) {
        int n = s.length();
        unordered_map<char, int> ccnt;
        for (char ci : s) ccnt[ci]++;
        vector<string> slst(n+1);
        for (auto pi : ccnt) slst[pi.second].append(pi.second, pi.first);
        string res;
        for (int i=n; i>=0; --i) if (!slst[i].empty()) res.append(slst[i]);
        return res;
    }
};
