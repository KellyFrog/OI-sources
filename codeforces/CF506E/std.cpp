#include<cstdio>
#include<algorithm>
using namespace std;const int N=2*1e2+10;const int mod=10007;
int tr[N][N];int tp[N*N];int n;char mde[N];int m;int ctt;int trp[N<<1][N<<1];int S;int ans;
struct Grph
{
	int v[2*N*N];int x[2*N*N];int ct;int al[N*N];int dp[N][N*N];bool book[N][N*N];
	inline void add(int u,int V){v[++ct]=V;x[ct]=al[u];al[u]=ct;}
	inline int dfs(int cnt,int u)
	{
		if(cnt<0)return 0;if(book[cnt][u])return dp[cnt][u];book[cnt][u]=true;
		for(int i=al[u];i;i=x[i])(dp[cnt][u]+=dfs(cnt-tp[u],v[i]))%=mod;
		return dp[cnt][u];
	}
}g2;//转移的dag
struct mar//矩阵类
{
	int mp[N<<1][N<<1];
	inline int* operator [](const int x){return mp[x];}
	void operator *=(const mar& b)
	{
		for(int i=1;i<=S;i++)for(int j=1;j<=S;j++)trp[i][j]=0;
		for(int i=1;i<=S;i++)
			for(int k=i;k<=S;k++)
				for(int j=k;j<=S;j++)(trp[i][j]+=mp[i][k]*b.mp[k][j])%=mod;
		for(int i=1;i<=S;i++)for(int j=1;j<=S;j++)mp[i][j]=trp[i][j];
	}
}trs,res;int f[N];int g[N];
int main()
{
	scanf("%s",mde+1);scanf("%d",&m);for(n=1;mde[n+1]!='\0';n++);
	for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)tr[i][j]=++ctt;++ctt;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			if(mde[i]==mde[j])//建图
			{if(j-i<=1)g2.add(ctt,tr[i][j]);else g2.add(tr[i+1][j-1],tr[i][j]);}
			else {tp[tr[i][j]]=1;g2.add(tr[i+1][j],tr[i][j]),g2.add(tr[i][j-1],tr[i][j]);}
	for(int i=0;i<n;i++)g2.book[i][tr[1][n]]=true;g2.dp[tp[tr[1][n]]][tr[1][n]]=1;
	for(int i=0;i<n;i++)g2.dfs(i,ctt);//记忆化搜索
	for(int i=1;i<n;i++)trs[i][i]=24;int t=(n+1)/2;//构建矩阵
	for(int i=0;i<t;i++)trs[n+i][n+i]=25;
	for(int i=0;i<t;i++)trs[n+t+i][n+t+i]=26;
	for(int i=1;i<n+t-1;i++)trs[i][i+1]++;
	for(int i=0;i<t;i++)trs[n+i][n+t+i]++;S=n+(t<<1)-1;
	for(int i=1;i<=S;i++)res[i][i]=1;
	for(int p=(n+m)>>1;p;p>>=1,trs*=trs)if(p&1)res*=trs;
	for(int i=0,v;i<n;i++)v=(n-i+1)/2,f[i]=res[n-i][n+t+v-1],g[i]=res[n-i][n+v-1];
	if((n+m)&1)
	{
		for(int i=0;i<n;i++)(ans+=f[i]*g2.dp[i][ctt])%=mod;(ans*=26)%=mod;
		for(int i=1;i<=26;i++)
			for(int j=1;j<=n;j++)
				if(mde[j]=='a'+i-1)for(int k=0;k<n;k++)(ans+=g[k]*g2.dp[k][tr[j][j]])%=mod;
	}
	else{for(int i=0;i<n;i++)(ans+=f[i]*g2.dp[i][ctt])%=mod;}printf("%d",ans);return 0;//拜拜程序~
}

