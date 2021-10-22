// 想定解法2 : 出現頻度を基準に降順ソート
// Time:O(NlogN),Space:O(N)

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string frequencySort(string s) {
        int n = s.length();
        unordered_map<char, int> ccnt;
        for (char ci : s) ccnt[ci]++;
        sort(s.begin(), s.end(), [&](char a, char b){
            return (ccnt[a]>ccnt[b] || (ccnt[a]==ccnt[b]&&a<b)); }); 
        return s;
    }
};
