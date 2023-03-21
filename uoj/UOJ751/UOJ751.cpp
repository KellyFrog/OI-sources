// Problem: B. 神隐
// Contest: UOJ - UOJ NOI Round #6 Day2
// URL: https://uoj.ac/contest/78/problem/751
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// Create Time: 2022-08-07 09:44:49
// Input/Output: stdin/stdout
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#include "tree.h"

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 2005;

int cnt[N][N];

vector<pair<int, int>> solve(int n) {
	int h = 0;
	int nn = n-1;
	while(nn) nn >>= 1, ++h;
	--h;
	rep(i, 0, h) {
		vector<int> v1(n-1), v2(n-1);
		rep(j, 0, n-1) {
			if(j >> i & 1) v1[j] = 1;
			else v2[j] = 1;
		}
		vector<vector<int>> r1 = query(v1);
		vector<vector<int>> r2 = query(v2);
		for(auto& v : r1) for(int i = 0; i < v.size(); ++i) for(int j = i+1; j < v.size(); ++j) ++cnt[v[i]][v[j]], ++cnt[v[j]][v[i]];
		for(auto& v : r2) for(int i = 0; i < v.size(); ++i) for(int j = i+1; j < v.size(); ++j) ++cnt[v[i]][v[j]], ++cnt[v[j]][v[i]];
	}
	vector<pair<int, int>> res;
	rep(i, 0, n-1) rep(j, i+1, n-1) if(cnt[i][j] == h+1) res.emplace_back(i, j);
	assert(res.size() == n-1);
	return res;
}