#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)

const int N = 1e6 + 5;

int n, m = 300;
int sa[N], rk[N<<1], oldrk[N], cnt[N], tmp[N];
char s[N];

inline bool compare(int i, int j, int w) {
    return oldrk[i] == oldrk[j] && oldrk[i + w] == oldrk[j + w];
}

void SA() {
    rep(i, 1, n) rk[i] = s[i];
    int p = 300;
    rep(j, 0, 20) {
        memcpy(oldrk, rk, sizeof oldrk);
        rep(i, 0, p) cnt[i] = 0;
        rep(i, 1, n) ++cnt[rk[i + (1 << j)]];
        rep(i, 1, p) cnt[i] += cnt[i-1];
        per(i, 1, n) tmp[cnt[rk[i + (1 << j)]]--] = i;
        rep(i, 0, p) cnt[i] = 0;
        rep(i, 1, n) ++cnt[rk[i]];
        rep(i, 1, p) cnt[i] += cnt[i-1];
        per(i, 1, n) sa[cnt[rk[tmp[i]]]--] = tmp[i];
        p = 1;
        rk[sa[1]] = 1;
        rep(i, 2, n) {
            p += !compare(sa[i], sa[i-1], 1 << j);
            rk[sa[i]] = p;
        }
        if(p == n) break;
    }
}

int main() {
    cin >> (s + 1);
    n = strlen(s + 1);
    SA();
    rep(i, 1, n) cout << sa[i] << " \n"[i == n];
    return 0;
}
