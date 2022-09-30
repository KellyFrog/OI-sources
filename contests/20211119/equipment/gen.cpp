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
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1e5 + 5;

int a[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n = 1e5;
    int m = mtrnd() % n + 1, k = mtrnd() % 100 + 1;
    cout << n << " " << m << " " << k << "\n";

    rep(i, 1, n) cout << mtrnd() % n + 1 << " \n"[i == n];
    rep(i, 1, n) a[i] = i;
    rep(i, 1, n) {
	int x = mtrnd() % n + 1, y = mtrnd() % n + 1;
	swap(a[x], a[y]);
    }
    rep(i, 1, m) {
	int x = a[i], y = a[i];
	while(y == x) y = mtrnd() % n + 1;
	cout << x << " " << y << "\n";
    }
    
    return 0;
}
    
