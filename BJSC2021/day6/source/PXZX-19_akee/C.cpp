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
const int MAXN=1000005;

ll n,m;
int a[6];
void go_up()
{
	int b[6]={a[4],a[0],a[2],a[3],a[5],a[1]};
	memcpy(a,b,sizeof(int)*6);
}
void go_right()
{
	int b[6]={a[0],a[3],a[1],a[4],a[2],a[5]};
	memcpy(a,b,sizeof(int)*6);
}

int main()
{
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	readint(n),readint(m);
	for(int i=0;i<6;++i)readint(a[i]);
	ll res=0;
	for(int x=1,y=1;x<n || y<m;)
	{
		res+=a[4];
		if(x*m<y*n)go_right(),++x;
		else go_up(),++y;
	}
	res+=a[4];
	printf("%lld\n",res);
	return 0;
}
