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

int a[100];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n = mtrnd() % 10 + 1;
    cout << n << "\n";
    rep(i, 1, n) cout << mtrnd() % n + 1 << " \n"[i == n];
    
    return 0;
}
