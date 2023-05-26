#include "Baijan.h"
#include <vector>
#include <climits>
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

namespace {

const int N = 2e3 + 5;

int n;
vector<pair<int, int>> adj[N];
int stage;
int c, cv;
bool vis[N];
int dis[N], last, ddis;
bool comp;

void send(int x, int b) {
	if(comp) return;
	per(i, 0, b-1) SendB(x >> i & 1);
}

void updstage() {
	comp = 1;
	rep(i, 0, n-1) comp &= !vis[i];
	int mi = INT_MAX, u = n;
	rep(i, 0, n-1) if(!vis[i] && dis[i] < mi) mi = dis[i], u = i;
	if(ddis > dis[u]) {
		send(u, 11);
		ddis = -1;
		last = dis[u];
		vis[u] = 1;
		for(auto [v, w] : adj[u]) dis[v] = min(dis[v], dis[u] + w);
		int mii = INT_MAX, uu = n;
		rep(i, 0, n-1) if(!vis[i] && dis[i] < mii) mii = dis[i], uu = i;
		send(min(501, mii  - last), 9);
		stage = 1;
		c = 9;
	} else if(ddis != -1) {
		last = ddis;
		stage = 2;
		c = 11;
	} else {
		stage = 1;
		c = 9;
	}
}

void senddis() {
	int mi = INT_MAX, u = n;
	rep(i, 0, n-1) if(!vis[i] && dis[i] < mi) mi = dis[i], u = i;
	send(min(501, dis[u] - last), 9);
	updstage();
}

void recdis(int x) {
	ddis = last + x;
	updstage();
}

void recp(int u) {
	assert(ddis != -1);
	assert(stage == 2);
	dis[u] = ddis;
	vis[u] = 1;
	for(auto [v, w] : adj[u]) dis[v] = min(dis[v], dis[u] + w);
	ddis = -1;
	senddis();
}

void rec(int x) {
	cv = 0;
	if(stage == 1) {
		recdis(x);
	} else { //recieve 
		recp(x);
	}
}
}  // namespace

void InitB(int N, int B, std::vector<int> S, std::vector<int> T, std::vector<int> D) {
	::n = N;
	for(int i = 0; i < B; ++i) {
		adj[S[i]].emplace_back(T[i], D[i]);
		adj[T[i]].emplace_back(S[i], D[i]);
	}
	memset(dis, 0x3f, sizeof dis);
	vis[0] = 1;
	dis[0] = 0;
	ddis = -1;
	for(auto [v, w] : adj[0]) dis[v] = min(dis[v], dis[0] + w);
	stage = 1, c = 9;
	senddis();
}

void ReceiveB(bool x) {
	cv = cv << 1 | x;
	if(--c == 0) rec(cv);
}
