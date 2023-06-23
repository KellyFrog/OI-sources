/*
 * Author: ChenKaifeng@codeforces
 * Create Time: 2023.06.23, 13:15:03 (UTC +8)
 */
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 1e5 + 5;

int n, k;
char s[N];
int pre[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> k;
	cin >> (s+1);
	rep(i, 1, n) pre[i] = pre[i-1] + s[i] - '0';
	rep(i, k, n) {
		if(pre[i] - pre[i-k] == pre[n] || k-(pre[i]-pre[i-k]) == n-pre[n]) {
			cout << "tokitsukaze" << "\n";
			return 0;
		}
	}
	int p1, p2, p3, p4;
	rep(i, 1, n) if(s[i] == '0') {
		p1 = i;
		break;
	}
	rep(i, 1, n) if(s[i] == '1') {
		p2 = i;
		break;
	}
	per(i, 1, n) if(s[i] == '0') {
		p3 = i;
		break;
	}
	per(i, 1, n) if(s[i] == '1') {
		p4 = i;
		break;
	}
	rep(i, k, n) {
		if(pre[i] - pre[i-k] == k || pre[i] - pre[i-k] == 0) {
			cout << "once again" << "\n";
			return 0;
		}
	}
	if(p3 - p1 <= k && p4 - p2 <= k) {
		cout << "quailty" << "\n";
		return 0;
	}
	cout << "once again" << "\n";
	
	return 0;
}
