#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
template <typename T> bool chkmin(T &x,T y){return y<x?x=y,1:0;}
template <typename T> bool chkmax(T &x,T y){return x<y?x=y,1:0;}
template <typename T> void readint(T &x)
{
	x=0;int f=1;char c;
	for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+(c-'0');
	x*=f;
}
const int MAXN=10005;

int m,n,q,res[MAXN];
pii a[MAXN],b[MAXN],tmpa[MAXN],tmpb[MAXN];
int pb[MAXN],yvl[MAXN];
vector<int> tr[MAXN];
void work()
{
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i)yvl[i]=a[i].y;
	for(int i=1;i<=q;++i)pb[i]=i,yvl[i+n]=b[i].y;
	sort(pb+1,pb+q+1,[&](int x,int y){return b[x]<b[y];});
	sort(yvl+1,yvl+1+n+q);yvl[1+n+q]=m;
	for(int i=1;i<=n;++i)a[i].y=lower_bound(yvl+1,yvl+1+n+q,a[i].y)-yvl;
	for(int i=1;i<=q;++i)b[i].y=lower_bound(yvl+1,yvl+1+n+q,b[i].y)-yvl;
	a[n+1]=mp(m,0);
//cerr<<b[1].x<<" "<<b[1].y<<" "<<a[1].x<<" "<<a[1].y<<endl;
	for(int i=n,bst=q+1;i;--i)
	{
		while(b[pb[bst-1]].x>a[i].x)--bst;
		for(int y=1;y<=n+q;++y)tr[y].clear();
		for(int j=i+1,kk=bst,yl=0,yr=n+q+1;j<=n+1;++j)
		{
			for(;kk<=q && b[pb[kk]].x<a[j].x;++kk)
			{
				int k=pb[kk];
				if(b[k].y<=yl || b[k].y>=yr)continue;
				tr[b[k].y].pb(k);
			}
			int d=min(yvl[yr]-yvl[yl],a[j].x-a[i].x);
			if(j<=n)
			{
				if(a[j].y<a[i].y)
				{
					if(a[j].y<=yl)continue;
					for(int y=yl+1;y<=a[j].y;++y)
						for(auto k:tr[y])
							chkmax(res[k],d);
					yl=a[j].y;
				}
				else
				{
					if(a[j].y>=yr)continue;
					for(int y=yr-1;y>=a[j].y;--y)
						for(auto k:tr[y])
							chkmax(res[k],d);
					yr=a[j].y;
				}
			}
			if(j==n+1 || yvl[yr]-yvl[yl]<a[j].x-a[i].x)
			{
				for(int y=yl+1;y<=yr-1;++y)
					for(auto k:tr[y])
						chkmax(res[k],d);
				break;
			}
//cerr<<a[j].x<<" "<<yvl[a[j].y]<<" "<<yvl[yl]<<" "<<yvl[yr]<<endl;
		}
//cerr<<i<<" : ";for(int j=1;j<=q;++j)cerr<<res[j]<<" ";cerr<<endl;
	}
	memcpy(a,tmpa,sizeof(a));
	memcpy(b,tmpb,sizeof(b));
}
void solve()
{
	readint(m),readint(n);
	for(int i=1;i<=n;++i)readint(a[i].x),readint(a[i].y),tmpa[i]=a[i];
	readint(q);
	for(int i=1;i<=q;++i)readint(b[i].x),readint(b[i].y),tmpb[i]=b[i],res[i]=0;
	for(int w=0;w<4;++w)
	{
		for(int j=0;j<w;++j)
		{
			for(int i=1;i<=n;++i)a[i]=mp(a[i].y,m-a[i].x);
			for(int i=1;i<=q;++i)b[i]=mp(b[i].y,m-b[i].x);
		}
		work();
	}
	for(int i=1;i<=q;++i)printf("%lld\n",1ll*res[i]*res[i]);
}

int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	int T;
	readint(T);
	while(T--)solve();
	return 0;
}
