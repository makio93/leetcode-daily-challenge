# [(2021.10.22) 451. Sort Characters By Frequency (Diff:Medium)](https://leetcode.com/problems/sort-characters-by-frequency/)

元ページURL: [451. Sort Characters By Frequency (Diff:Medium)](https://leetcode.com/problems/sort-characters-by-frequency/)

## 問題の概要

文字列sが与えられるので，これを文字の出現頻度の大きい順にソートせよ．  

- 制約条件 
    sは英大文字，英小文字，文字列からなる 
    sの長さは1～5e5文字

## 自力での解法 : 文字頻度を集計してソート

初めに文字種ごとの総数をカウントしてから，それをpair<char, int>型配列に直して降順ソートすればよさそう． 
計算量は，文字列長をN，文字種をMとすると，O(N)かO(MlogM)の大きい方．

#### ソースコード : 自力解法

```cpp
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> ccnt;
        for (char ci : s) ccnt[ci]++;
        vector<pair<int, char>> clst;
        for (auto pi : ccnt) clst.emplace_back(pi.second, pi.first);
        sort(clst.rbegin(), clst.rend());
        string res;
        for (auto pi : clst) res += string(pi.first, pi.second);
        return res;
    }
};
```

## 想定解法

解法は2通り．いずれも初めに出現頻度をカウントする必要がある点は同じ．

### O(N)解 : 出現頻度ごとに文字列構築

出現頻度を集計した後，個数が同じ文字ごとに文字列を構築して最後に連結する．  

計算量はO(N)．

#### ソースコード : 想定解法1

```cpp
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
```

### O(NlogN)解 : 出現頻度を基準に降順ソート

sort()関数の第3引数に，ソートの基準とする比較関数定義をラムダ式にて指定することができる．  

ソートなので，計算量はO(NlogN)．

#### ソースコード : 想定解法2

```cpp
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
```
