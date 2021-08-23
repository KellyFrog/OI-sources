//Author: Chenkaifeng

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define rg register
#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for(rg int i = s; i <= t; i++)
#define per(i, s, t) for(rg int i = t; i >= s; i--)
#define debug(x) cerr << (#x) << " = " << (x) << "\n"

const int N = 1e5 + 5;

int a[N], n, k;

void Solve() {
	scanf("%d%d", &n, &k);
	rep(i, 1, n) scanf("%d", &a[i]);
	int ans = n + 1;
	int left = 0, right = 0;
	int sum = 0;
	while(left <= n && right <= n) {
		sum -= a[left++];
		while(sum < k && right <= n) sum += a[++right];
		if(right > n) break;
		while(sum - a[left] >= k) sum -= a[left++];
		ans = min(ans, right - left + 1);
	}
	printf("%d\n", ans == n + 1 ? 0 : ans);
}

int main() {
	int t; scanf("%d", &t);
	while(t--) Solve();
	return 0;
}
