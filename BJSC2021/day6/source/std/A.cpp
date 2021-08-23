#include<bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

template <typename T> bool chkmax(T &x,T y){return x<y?x=y,true:false;}
template <typename T> bool chkmin(T &x,T y){return x>y?x=y,true:false;}

int readint(){
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int n,m,q;
int rmx[5005],rmn[5005],lmx[5005],lmn[5005];
ll ans[5005];
pii a[5005],b[5005];

void work(){
	int x,y;
	for(int Q=1;Q<=q;Q++){
		x=b[Q].fi,y=b[Q].se;
		int pl=lower_bound(a+1,a+n+1,mp(x,y))-a;
		if(a[pl]==mp(x,y)||x==0||x==m||y==0||y==m){
			ans[Q]=0;
			continue;
		}
		lmx[pl]=rmx[pl-1]=m,lmn[pl]=rmn[pl-1]=0;
		for(int i=pl;i<=n;i++){
			rmx[i]=rmx[i-1],rmn[i]=rmn[i-1];
			if(a[i].se>=y) chkmin(rmx[i],a[i].se);
			if(a[i].se<=y) chkmax(rmn[i],a[i].se);
		}
		rmx[n+1]=rmx[n],rmn[n+1]=rmn[n];
		for(int i=pl-1;i>=1;i--){
			lmx[i]=lmx[i+1],lmn[i]=lmn[i+1];
			if(a[i].se>=y) chkmin(lmx[i],a[i].se);
			if(a[i].se<=y) chkmax(lmn[i],a[i].se);
		}
		lmx[0]=lmx[1],lmn[0]=lmn[1];
		int now=n+1;
		for(int i=pl-1;i>=0;i--){
			while(a[now].fi>x&&min(lmx[i+1],rmx[now-1])-max(lmn[i+1],rmn[now-1])<a[now].fi-a[i].fi) now--;
			if(a[now].fi>x&&a[i].fi<x) chkmax(ans[Q],1ll*(a[now].fi-a[i].fi)*(a[now].fi-a[i].fi));
		}
	}
}

void solve(){
	m=readint(); n=readint();
	for(int i=1;i<=n;i++) a[i].fi=readint(),a[i].se=readint();
	sort(a+1,a+n+1);
	a[n+1].fi=m;
	q=readint();
	for(int i=1;i<=q;i++) b[i].fi=readint(),b[i].se=readint(),ans[i]=0;
	work();
	for(int i=1;i<=n;i++) swap(a[i].fi,a[i].se);
	for(int i=1;i<=q;i++) swap(b[i].fi,b[i].se);
	sort(a+1,a+n+1);
	work();
	for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
}

int main(){
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout); 
	int T=readint();
	while(T--) solve();
	return 0;
}
