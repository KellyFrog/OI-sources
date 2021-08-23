#include<bits/stdc++.h>
using namespace std;

template<typename T> void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar())if(c == '-')f = -1;
	for(;  isdigit(c); c = getchar())x = x * 10 + c - '0';
	x = x * f;
}

const int N = 5005;
int T;
int n, m;
struct node {
	int x, y;
}a[N];
int Q;

bool cmpx(node a, node b) {
	return a.x < b.x;
}
bool cmpy(node a, node b) {
	return a.y < b.y;
}
int cntx[N][N], cnty[N][N];

int main() {
	read(T);
	while(T --) {
		read(m), read(n);
		for(int i = 1; i <= n; ++ i)
			read(a[i].x), read(a[i].y);
		read(Q);
		while(Q --) {
			int u, v;
			read(u), read(v);
			sort(a + 1, a + 1 + n, cmpx);
			for(int i = 1; i <= n; ++ i)
				for(int j = 1; j <= n; ++ j) {
					cnt[i][j] = min
				}
			for(int i = 1; i <= n; ++ i)
				for(int j = i + 1; j <= n; ++ j)
		}
	}
	
	return 0;
}
