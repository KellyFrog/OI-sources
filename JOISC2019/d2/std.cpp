#include <bits/stdc++.h>
#define V vector
#define Vi vector<int>
#define sz(a) ((int)a.size())
#define fi first
#define se second
#define Int pair<int, int>
#define Inf ((int)1e9 + 10)
#define pb push_back
#define ins insert
#define For(i, x, y) for (auto i = (x); i <= (y); i++)
#define Rep(i, x, y) for (auto i = (x); i >= (y); i--)
#define seg int p, int l, int r
#define lid p << 1, l, mid
#define rid p << 1 | 1, mid + 1, r
#define mid ((l + r) / 2)
#define IO(x) freopen(#x ".in", "r", stdin), freopen(#x ".out", "w", stdout);
using namespace std;
#define int long long
signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    Vi a(n + 5), s(n + 5), P(n + 5), b(m + 5), T(m + 5), Q(m + 5);
    int res = 0;
    For(i, 1, n) {
        cin >> a[i] >> s[i] >> P[i], a[i] += a[i - 1];

        if (a[i] <= s[i])
            res += P[i];
    }
    V<Vi> D(n + 5);
    For(i, 1, m) {
        cin >> b[i] >> T[i] >> Q[i], b[i] += b[i - 1];

        if (b[i] <= T[i]) {
            res += Q[i];
            int t = upper_bound(&a[0], &a[n + 1], T[i] - b[i]) - (&a[0]);
            D[t].pb(i);
        }
    }
    set<int> ss;
    Vi v(m + 5);
    auto work = [&](int x, int z) {
        if (z >= 0)
            v[x] += z, ss.ins(x);
        else {
            int sum = -z;
            auto it = ss.lower_bound(x), sta = it;

            for (; it != ss.end(); it++) {
                if (v[*it] > sum) {
                    v[*it] -= sum;
                    break;
                } else
                    sum -= v[*it], v[*it] = 0;
            }

            ss.erase(sta, it);
        }
    };
    For(i, 1, n) {
        for (int j : D[i]) {
            if (Q[j] > 0)
                work(j, Q[j]);

            res -= Q[j];
        }

        if (a[i] <= s[i]) {
            int t = upper_bound(&b[0], &b[m + 1], s[i] - a[i]) - (&b[0]);

            if (t <= m)
                work(t, -P[i]);
        }

        for (int j : D[i])
            if (Q[j] < 0)
                work(j, Q[j]);
    }

    for (int i = 1; i <= m; i++)
        res += v[i];

    cout << res << '\n';
}
