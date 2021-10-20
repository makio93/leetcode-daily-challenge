// 自力解法1 : 二分探索
// Time:O(N+MlogM)

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        unordered_map<int, int> ids1;
        for (int i=0; i<n; ++i) ids1[nums1[i]] = i;
        vector<pair<int, int>> pid2(m);
        for (int i=0; i<m; ++i) pid2[i] = { nums2[i], i };
        sort(pid2.rbegin(), pid2.rend());
        vector<int> ans(n, -1);
        set<int> ids2;
        ids2.insert(m);
        for (int i=0; i<m; ++i) {
            if (ids1.find(pid2[i].first)!=ids1.end() && *ids2.lower_bound(pid2[i].second)!=m) 
                ans[ids1[pid2[i].first]] = nums2[*ids2.lower_bound(pid2[i].second)];
            ids2.insert(pid2[i].second);
        }
        return ans;
    }
};
