#include "meetings.h"
#include <bits/stdc++.h>

using namespace std;

mt19937 mtrnd(chrono::steady_clock::now().time_since_epoch().count());

const int N = 2e3 + 5;

bool vis[N];
int bel[N];
map<tuple<int, int, int>, int> mem;
vector<int> adj[N];

int query(int x, int y, int z) {
	if(x == y || x == z) return x;
	if(y == z) return y;
	if(x > y) swap(x, y);
	if(y > z) swap(y, z);
	if(x > y) swap(x, y);
	if(mem.count(make_tuple(x, y, z))) return mem[make_tuple(x, y, z)];
	return mem[make_tuple(x, y, z)] = Query(x, y, z);
}

void answer(int x, int y) {
	if(x > y) swap(x, y);
	Bridge(x, y);
}

void solve(vector<int> v) {
	if(v.size() == 2) {
		answer(v[0], v[1]);
		return;
	}
	if(v.size() < 2) return;
	int x, y;
	do { x = mtrnd() % v.size(), y = mtrnd() % v.size(); } while(x == y);
	vis[v[x]] = vis[v[y]] = 1;
	vector<int> path;
	for(int x : v) adj[x].clear(), vis[x] = 0;
	for(int i = 0; i < v.size(); ++i) {
		int z = query(v[i], v[x], v[y]);
		bel[v[i]] = z;
		if(!vis[z]) {
			path.push_back(z);
			vis[z] = 1;
		}
	}
	stable_sort(path.begin(), path.end(), [&](int i, int j) { return query(i, j, v[y]) == j;	});
	for(int i = 0; i+1 < path.size(); ++i) answer(path[i], path[i+1]);
	for(int x : v) adj[bel[x]].push_back(x);
	for(int x : path) solve(adj[x]);
}

void Solve(int N) {
	vector<int> u;
	for(int i = 0; i < N; ++i) u.push_back(i);
	solve(u);
}
