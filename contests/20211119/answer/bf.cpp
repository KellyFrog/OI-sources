# include <bits/stdc++.h>
# define ll long long
using namespace std;
const int MAXN = 30051;
int n, m, a, b;
string str[MAXN];
string s1;
int cnt[MAXN];
int main(){
	// freopen("answer.in", "r", stdin);
	// freopen("answer.out", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &a, &b);
	for (int i = 1; i <= n; i++) cin >> str[i];
	sort(str + 1, str + n + 1);
	for (int i = 1; i <= n; i++){
		cnt[i] = (i > 1 && str[i] == str[i - 1]) ? cnt[i - 1] + 1 : 1;
		// cout << str[i] << ' ' << cnt[i] << '\n';
	}
	for (int i = n; i >= 1; i--){
		cnt[i] = (i < n && str[i] == str[i + 1]) ? cnt[i + 1] : cnt[i];
		// cout << str[i] << ' ' << cnt[i] << '\n';
	}
	if (a == 0 && b == 0){
		string sn, s1;
		sn.resize(m + 1);
		s1.resize(m + 1);
		int p1 = 1, p2 = n;
		for (int i = 0; i < 2 * n; i++){
			bool flag = true;
			for (int j = 0; j < m; j++) sn[j] = 'N';
			for (int j = 0; j < 20; j++){
				if ((i >> j) & 1){
					if (m - j - 1 < 0){
						flag = false;
						break;
					}
					sn[m - j - 1] = 'Y';
				}
			}
			if (!flag) break;
			for (int j = 0; j < m; j++) s1[j] = 'Y' ^ 'N' ^ sn[j];
			while (p1 <= n && str[p1] < sn) p1++;
			while (p2 > 0 && str[p2] > s1) p2--;
			if (str[p1] != sn && str[p2] != s1){
				cout << sn << '\n';
				return 0;
			}
		}
	} else if (a == 0){
		int p = 1;
		for (int i = n; i >= 1; i--){
			s1.resize(m + 1);
			for (int j = 0; j < m; j++) s1[j] = 'Y' ^ 'N' ^ str[i][j];
			while (p <= n && str[p] < s1) p++;
			if (str[p] != s1){
				cout << s1 << '\n';
				return 0;
			}
		}
	} else {
		int p = n;
		for (int i = 1; i <= n; i++){
			s1.resize(m + 1);
			for (int j = 0; j < m; j++) s1[j] = 'Y' ^ 'N' ^ str[i][j];
			while (p > 0 && str[p] > s1) p--;
			// cout << str[i] << '\n' << str[p] << "\n" << cnt[i] << ' ' << cnt[p] << '\n';
			if (b == 0 && cnt[i] == a && str[p] != s1 || cnt[i] == a && cnt[p] == b && str[p] == s1){
				cout << str[i] << '\n';
				return 0;
			}
		}
	}
	printf("-1\n");
	return 0;
}
