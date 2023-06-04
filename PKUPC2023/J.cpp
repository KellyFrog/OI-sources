
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 205;

int n;
int a[N];
bool f[N][2];
int s1[N], s2[N];
int ans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> n;
	rep(i, 1, 2*n) cin >> a[i];
	rep(i, 2, 2*n) {
		s1[i] = s1[i-1] + (a[i] == 0);
		s2[i] = s2[i-1] + (a[i] == 1);
	}
	int ans = 0;
	rep(i, 2, 2*n) ans += s1[i-1] != s2[i-1];
	cout << ans << "\n";
	return 0;
}
