#include<cstdio>
#include<algorithm>
#define ll long long
#define mid ((l+r)>>1)
#define N 310
#define M 2010
using namespace std;
int a[M],b[M],A[M],B[M],n,id[N][N],cnt;
ll p[M],q[M],fac[M],ifac[M];
int s[M][N][N],ss[M][N],dp[M][N][N];
const int mod=1e9+7;
inline int Mod(int a){return a<mod?a:a-mod;}
ll fastpow(ll a,int b)
{
	ll s=1;
	while(b)
	{
		if(b&1) s=s*a%mod;
		a=a*a%mod, b>>=1;
	}
	return s;
}
int Lagrange(int n,int m,int*a)
{
	if(m<=n) return a[m];
	p[0]=m,q[n+1]=1;
	ll sum=0;
	for(int i=1;i<=n;i++) p[i]=p[i-1]*(m-i)%mod;
	for(int i=n;i>=0;i--) q[i]=q[i+1]*(m-i)%mod;
	for(int i=0;i<=n;i++) sum=(sum+a[i]*(i>0?p[i-1]*ifac[i]%mod:1)%mod*q[i+1]%mod*ifac[n-i]%mod*((n-i)%2?mod-1:1)%mod+mod)%mod;
	return sum;
}
struct node{
	int l,r;
}t[M];
bool cmp(node a,node b)
{
	return a.r-a.l>b.r-b.l;
}
void init(int l,int r)
{
	if(l>r||id[l][r]) return;
	id[l][r]=1;
	t[++cnt]=(node){l,r};
	if(l==r) return;
	if((r-l)&1)
	{
		init(l,mid-1);init(mid+1,r);
		init(l,mid);init(mid+2,r);
	}
	else
	{
		init(l,mid-1);init(mid+1,r);
		init(l,mid-2);init(mid,r);
		init(l,mid);init(mid+2,r);
	}
}
void work(int i,int w,int x1,int y1)
{
	for(int j=A[w];j<B[w];j++)
	{
		dp[i][j][0]=(dp[i][j][0]+1ll*s[x1][j][0]*ss[y1][j-1])%mod;
		for(int k=1;k<=n;k++)
			dp[i][j][k]=(dp[i][j][k]+1ll*s[x1][j][k]*s[y1][j][k-1])%mod;
	}
}
int x[M],len,l,r,x1,x2,x3,y1,y2,y3,ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		x[++len]=a[i],x[++len]=++b[i];
	}
	sort(x+1,x+len+1);
	len=unique(x+1,x+len+1)-x-1;
	for(int i=1;i<=n;i++)
		A[i]=lower_bound(x+1,x+len+1,a[i])-x,
		B[i]=lower_bound(x+1,x+len+1,b[i])-x;
	fac[0]=ifac[0]=1;
	for(int i=1;i<=n*2;i++) fac[i]=fac[i-1]*i%mod;
	ifac[n<<1]=fastpow(fac[n<<1],mod-2);
	for(int i=n*2-1;i;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
	for(int j=0;j<len;j++)
	{
		ss[0][j]=1;
		for(int k=0;k<=n;k++)
			s[0][j][k]=1;
	}
	init(1,n);
	sort(t+1,t+cnt+1,cmp);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			id[i][j]=0;
	for(int i=1;i<=cnt;i++)
		id[t[i].l][t[i].r]=i;
	for(int i=cnt;i;i--)
	{
		l=t[i].l,r=t[i].r;
		if(l==r)
		{
			for(int j=A[l];j<B[l];j++)
				for(int k=0;k<=n;k++) dp[i][j][k]=1;
		}
		else if((l-r)&1)
		{
			work(i,mid,id[l][mid-1],id[mid+1][r]);
			work(i,mid+1,id[l][mid],id[mid+2][r]);
		}
		else
		{
			work(i,mid,id[l][mid-1],id[mid+1][r]);
			work(i,mid-1,id[l][mid-2],id[mid][r]);
			work(i,mid+1,id[l][mid],id[mid+2][r]);
		}
		for(int j=1;j<len;j++)
		{
			s[i][j][0]=Mod(ss[i][j-1]+dp[i][j][0]);
			for(int k=1;k<=n;k++)
				s[i][j][k]=Mod(s[i][j][k-1]+dp[i][j][k]);
			ss[i][j]=Lagrange(n,x[j+1]-x[j]-1,s[i][j]);
		}
	}
	printf("%d",ss[1][len-1]);
}