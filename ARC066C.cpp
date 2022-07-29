/*
 * Author: chenkaifeng @BDFZ
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)

const ll inf = 0x3f3f3f3f3f3f3f3f;
const int N = 2e5 + 5;

ll dp[N][2];
int a[N]; char op[N];
int n;
ll b[N], nn;
char bop[N];

void solve() {
	cin >> n;
	cin >> a[1]; op[1] = '+';
	
	nn = 0;
	
	rep(i, 2, n) cin >> op[i] >> a[i];
	for(int i = 1; i <= n;) {
		vector<int> cur;
		int s = i;
		while(i <= n && op[i] == op[s]) {
			cur.pb(a[i]);
			++i;
		}
		if(op[s] == '+') {
			ll sum = 0;
			for(int x : cur) sum += x;
			b[++nn] = sum;
			bop[nn] = '+';
		} else {
			b[++nn] = -cur[0];
			bop[nn] = '-';
			if(cur.size() == 1) continue;
			ll sum = 0;
			for(int j = 1; j < cur.size(); j++) sum += cur[j];
			b[++nn] = -sum;
			bop[nn] = '-';
		}
	}
	
	rep(i, 0, nn) dp[i][0] = dp[i][1] = -inf;
	
	dp[0][0] = 0;
	
	
	rep(i, 1, nn) {
		dp[i][0] = max(dp[i-1][0] + b[i], dp[i-1][1] + b[i]);
		if(bop[i] == '-') dp[i][1] = max(dp[i][1], dp[i-1][0] + b[i]);
		if(bop[i] == '+') {
			if(i > 1) {
				dp[i][1] = max(dp[i][1], dp[i-2][1] + (-b[i-1]) + b[i]);
			}
		}
		dp[i][1] = max(dp[i][1], dp[i-1][1] - b[i]);
	}
	
	cout << max(dp[nn][0], dp[nn][1]) << "\n";
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	cout << fixed << setprecision(15); cerr << fixed << setprecision(15);
	
	int t;
	t = 1;
	while(t--) solve();
	
	return 0;
}