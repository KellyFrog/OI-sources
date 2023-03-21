#include<bits/stdc++.h>
#define MAXN 10000006
using namespace std;
typedef long long ll;
int n,k;
int t[MAXN];
struct node{
	int a,b,c,d;
} q[MAXN];

bool cmp(node& n1, node& n2){
	if(n1.b == n2.b) return n1.a > n2.a;
	return n1.b > n2.b;
}

inline int lowbit(int x) { return x & (-x); }
inline void add(int x, int val) { for(int x0 = x; x0 <= k; x0 += lowbit(x0)) t[x0] += val; }
inline int query(int x) { int ret = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) ret += t[x0]; return ret; }

int ans[MAXN], ans0[MAXN];

void solve(int l, int r){
	if(l==r) return;
	
	int mid = (l+r)/2;
	
	solve(l, mid);
	solve(mid+1, r);
	
	//[l,mid] -> [mid+1,r]
	sort(q + l, q + r + 1, [&](const node& x, const node& y) {
		if(x.b != y.b) return x.b < y.b;
		if(x.c != y.c) return x.c < y.c;
		if(x.a != y.a) return x.a < y.a;
		return x.d > y.d;
	});
	for(int i = l; i <= r; ++i) {
		if(q[i].d <= mid) {
			add(q[i].c, 1);
		} else {
			ans[q[i].d] += query(q[i].c);
		}
	}
	for(int i = l; i <= r; ++i) {
		if(q[i].d <= mid) add(q[i].c, -1);
	}
}


int main(){
	
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		cin>>q[i].a>>q[i].b>>q[i].c;
	}
	sort(q + 1, q + n + 1, [&](const node& x, const node& y) { return make_tuple(x.a, x.b, x.c) < make_tuple(y.a, y.b, y.c); });//
	for(int i = 1; i <= n; ++i) q[i].d = i;
	for(int i = 1; i <= n;) {
		int j = i;
		while(j <= n && q[j].a == q[i].a && q[j].b == q[i].b && q[j].c == q[i].c) ++j;
		for(int k = i; k < j; ++k) ans[i] += j - k - 1;
		i = j;
	}
	
	solve(1,n);
	for(int i = 1; i <= n; ++i) ++ans0[ans[i]];
	for(int i = 0; i < n; ++i) cout << ans0[i] << "\n";
	
	
	return 0;
}