#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 100;

int n, a[N], b[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n;
    rep(i, 1, n) cin >> a[i], b[i] = i;

    int ans = 0;
    do {
	int res = 0;
	rep(i, 1, n-1) res += (b[i+1] == a[b[i]]);
	ans = max(ans, res);
    } while(next_permutation(b + 1, b + n + 1));
    cout << ans << "\n";

    return 0;
}
