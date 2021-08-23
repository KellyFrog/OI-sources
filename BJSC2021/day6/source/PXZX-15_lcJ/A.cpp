#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

const int maxn=5e3,inf=1e9+2;
int T;
int keyx[maxn+5],keyy[maxn+5],cx,cy;
vector<int> vx[maxn+5],vy[maxn+5];

struct node {
	int x,y; 
} a[maxn+5];
int h1=1,t1=0,h2=1,t2=0; 
pair<int,int> que1[maxn+5],que2[maxn+5];

void ins1(int x,int t) {
	while (h1<=t1&&x>=que1[t1].first) t1--; 
	que1[++t1]={x,t};
}
void ins2(int x,int t) {
	while (h2<=t2&&x<=que2[t2].first) t2--;
	que2[++t2]={x,t}; 
}
void del(int L)  {
	while (h1<=t1&&que1[h1].second<=L) h1++;
	while (h2<=t2&&que2[h2].second<=L) h2++; 
}

void solve() {
	int m,n; 
	cx=cy=0;
	cin>>m>>n;
	for (int i=1;i<=n;i++) {
		scanf("%d %d",&a[i].x,&a[i].y);
		keyx[++cx]=a[i].x;
		keyy[++cy]=a[i].y;
	}
	keyx[++cx]=0,keyx[++cx]=m;
	keyy[++cy]=0,keyy[++cy]=m; 
	sort(keyy+1,keyy+cy+1);
	sort(keyx+1,keyx+cx+1);
	cx=unique(keyx+1,keyx+cx+1)-keyx-1;
	cy=unique(keyy+1,keyy+cy+1)-keyy-1;
	for (int i=1;i<=cx;i++) vx[i].clear();
	for (int i=1;i<=cy;i++) vy[i].clear();
	for (int i=1;i<=n;i++) {
		a[i].x=lower_bound(keyx+1,keyx+cx+1,a[i].x)-keyx;
		a[i].y=lower_bound(keyy+1,keyy+cy+1,a[i].y)-keyy; 
		vx[a[i].x].push_back(keyy[a[i].y]);
		vy[a[i].y].push_back(keyx[a[i].x]);
	//	cout<<a[i].x<<' '<<a[i].y<<'\n'; 
	}
	keyx[cx+1]=m;
	keyy[cy+1]=m; 
	int q;
	cin>>q;
	for (int i=1;i<=q;i++) {
		int u,v;
		scanf("%d %d",&u,&v);
		if (n==0) {
			printf("%lld\n",1ll*(m+1)*(m+1));
			continue ;  
		}
		int R=2;
		int mn=m,mx=0; 
		h1=1,t1=0,h2=1,t2=0; 
		int anslen=0; 
		for (int L=1;L<=cx&&keyx[L]<u;L++) {
			del(L);
			if (L==R) {
				R=L+1;
			}
			if (h1<=t1)mx=que1[h1].first; else mx=0;
			if (h2<=t2)mn=que2[h2].first; else mn=m; 
			while (R<=cx) {
				int nwmn=mn,nwmx=mx;
		//		cout<<R<<' '<<nwmn<<' '<<nwmx<<'\n'; 
				if (nwmn>v&&nwmx<v&&nwmn-nwmx>=keyx[R]-keyx[L]) {
					for (auto x:vx[R]) {
						if (x<=v) ins1(x,R);
						if (x>=v) ins2(x,R);
					}
					for (auto y:vx[R]) {
						if (y>=v) nwmn=min(nwmn,y); 
						if (y<=v) nwmx=max(nwmx,y);
					}
					mn=nwmn,mx=nwmx; 
					R++; 
				}
				else {
					break ; 
				}
			}
		//	cout<<L<<' '<<R<<' '<<mn<<' '<<mx<<'\n'; 
			if (keyx[L]<u&&keyx[R-1]>u) {
				anslen=max(anslen,keyx[R-1]-keyx[L]); 
			}
		//	cout<<L<<' '<<R<<' '<<mn<<' '<<mx<<'\n';
		}
		R=2;
		mn=inf,mx=-inf; 
		h1=1,t1=0,h2=1,t2=0; 
		for (int L=1;L<=cy&&keyy[L]<v;L++) {
			del(L); 
			if (L==R) {
				R=L+1;
			}
			if (h1<=t1)mx=que1[h1].first; else mx=0;
			if (h2<=t2)mn=que2[h2].first; else mn=m; 
			while (R<=cy) {
				int nwmn=mn,nwmx=mx;
				
				if (nwmn>u&&nwmx<u&&nwmn-nwmx>=keyy[R]-keyy[L]) {
					for (auto x:vy[R]) {
						if (x<=u) ins1(x,R); 
						if (x>=u) ins2(x,R);
					}
					for (auto y:vy[R]) {
						if (y>=u) nwmn=min(nwmn,y); 
						if (y<=u) nwmx=max(nwmx,y);
					}
					mn=nwmn,mx=nwmx; 
					R++; 
				}
				else {
					break ; 
				}
			}
			if (keyy[L]<v&&keyy[R-1]>v) {
				anslen=max(anslen,keyy[R-1]-keyy[L]); 
			}
		}
		printf("%lld\n",1ll*anslen*anslen); 
	}
}

int main() {
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout); 
	cin>>T;
	while (T--) {
		solve();
	}	
	return 0;
}

/*
1
5 5
1 4
2 1
3 2
4 1
4 4
3
3 1
2 3
4 3
*/
