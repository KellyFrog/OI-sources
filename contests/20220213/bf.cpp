#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;

int solve() {
cin >> n;
		if(n <= 2){
			cout << -1 << endl; return 0;
		}
		if(n % 4 == 0){
			cout << n + 1 << endl; return 0;
		}
		if(n % 4 == 3){
			cout << n << endl; return 0;
		}
		if(n % 4 == 1){
			ll cnt = 0;
			for(ll i = 62;i >= 0;i--){
				if(((n + 3) >> i) & 1) cnt++;
			}
			if(cnt > 1){
				ll x = 0, y = 0;
				for(int i = 62;i >= 0;i--){
					if(((n + 3) >> i) & 1){
						x = (1ll << i); y = n + 3 - x; break;
					}
				}
				cout << n + 3 << endl; return 0;
			}
			cout << n + 4 << endl; return 0;
		}
		if(n % 4 == 2){
			ll cnt = 0;
			for(ll i = 62;i >= 0;i--){
				if(((n + 2) >> i) & 1) cnt++;
			}
			if(cnt > 1){
				ll x = 0, y = 0;
				for(int i = 62;i >= 0;i--){
					if(((n + 2) >> i) & 1){
						x = (1ll << i); y = n + 2 - x; break;
					}
				}
				cout << n + 2 << endl; return 0;
			}
			cout << n + 3 << endl; return 0;
		}
		return 0;
}
int main(){
	// freopen("xor.in", "r", stdin);
	// freopen("xor.out", "w", stdout);

	int t;
	cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}
