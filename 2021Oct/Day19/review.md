# [(2021.10.19) 496. Next Greater Element I (Easy)](https://leetcode.com/problems/next-greater-element-i/)

元ページURL: [496. Next Greater Element I (Easy)](https://leetcode.com/problems/next-greater-element-i/)

## 問題の概要

2つの異なるdistinctな整数配列`nums1`と`nums2`が与えられる．`nums1`の各要素について，`nums1[i] == nums2[j]`となるような`nums2`内の要素が必ず1つだけ存在する．

添字`i`の各値について，`nums1[i] == nums2[j]`に対応する`j`に対し，`j < k` かつ `nums2[j] < nums2[k]` となるような`nums2`の要素`nums2[k]`のうち，最も左にある要素を求めよ．解が存在しない場合は`-1`とする．

ただし，時間計算量として，**`O(N+M)`となる解法を用いよ**．

## 自力での解法

最後の一文を見た瞬間，そんな解法が存在するのか，**`O(N+MlogM)`の間違いではないのか**，などと考えてとても思い至らなかったため，`O(N+MlogM)`解法を用いてACした．

### 自力解法1 : 二分探索

要は，`nums2`の要素を大きい順に見てって探索範囲に加えていきながら，値が`nums1[i]`のどれかと一致するときだけ，
その探索範囲に対してにぶたんを掛けて，`nums1[i]`よりちょっとだけ大きい値をその`i`に対する答えとすればよいことになる．

#### ソースコード : 自力解法1

```cpp
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
            if (ids1.find(pid2[i].first)!=ids1.end() && *ids2.lower_bound(pid2[i].second)!=m) ans[ids1[pid2[i].first]] = nums2[*ids2.lower_bound(pid2[i].second)];
            ids2.insert(pid2[i].second);
        }
        return ans;
    }
};
```

## 想定解法

想定解法ではStackを上手く使い，計算量`O(N+M)`を実現している．解説を見た瞬間，目から鱗が落ちた気がした．

### 想定解法1 : Stackを用いる

よく考えれば，`nums1`にある要素は全て`nums2`にも含まれるので，最初に`nums2`の先頭要素から順に見てって，
各要素`nums2[j]`に対して右側の直近のちょっと大きい値を探索して記録してしまえばよいことに気付く．  

そして，その処理をするだけならStackの仕様がちょうどぴったり適合して効率よく探索できる．  

最後に，上記の探索結果から`nums2[j] -> nums2[k]`みたいに参照できるように`unordered_map<int, int>`とかに記録しておけば，答えの構築にそのまま流用できる．それで終わり．   

#### ソースコード : 想定解法1

```cpp
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
```
