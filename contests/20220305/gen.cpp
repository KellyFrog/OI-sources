#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

mt19937_64 mtrnd(chrono::system_clock::now().time_since_epoch().count());

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n = 500;
    int k = mtrnd() % n + 1;
    cout << n << " " << k << "\n";
    vector<int> a(n+1);
    rep(i, 1, n) a[i] = i;
    rep(i, 1, n) {
	int x = mtrnd() % n + 1;
	int y = mtrnd() % n + 1;
	swap(a[x], a[y]);
    }
    rep(i, 1, n) cout << a[i] << " \n"[i== n];
    
    return 0;
}
