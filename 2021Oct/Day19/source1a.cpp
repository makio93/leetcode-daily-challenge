// 想定解法1 : Stackを用いる
// Time:O(N+M),Space:O(N+M)

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        unordered_map<int, int> nvals;
        for (int val : nums2) {
            while (!st.empty() && st.top()<val) {
                nvals[st.top()] = val;
                st.pop();
            }
            st.push(val);
        }
        vector<int> ans;
        for (int val : nums1) ans.push_back(nvals.find(val)!=nvals.end()?nvals[val]:-1);
        return ans;
    }
};
