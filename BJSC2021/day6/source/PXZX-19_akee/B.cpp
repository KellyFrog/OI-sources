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
const int MAXN=200005,MAXK=19;

int n;char a[MAXN];
struct sam
{
	int ch[MAXN][26],fa[MAXN],len[MAXN],rgt[MAXN],pos[MAXN],las,ctot;
	sam():las(1),ctot(1){}
	void extend(int c,int id)
	{
		int p=las,np=++ctot;las=np;
		len[np]=len[p]+1;rgt[np]=id;pos[id]=np;
		for(;p && !ch[p][c];p=fa[p])ch[p][c]=np;
		if(!p){fa[np]=1;return;}
		int q=ch[p][c];
		if(len[q]==len[p]+1){fa[np]=q;return;}
		int nq=++ctot;
		len[nq]=len[p]+1;fa[nq]=fa[q];memcpy(ch[nq],ch[q],sizeof(int)*26);
		for(;p && ch[p][c]==q;p=fa[p])ch[p][c]=nq;
		fa[q]=fa[np]=nq;
	}
};
sam sol,ccp;
int dep[MAXN],anc[MAXN][MAXK],que[MAXN],front,rear,deg[MAXN];
int lca(int u,int v)
{
	if(dep[u]<dep[v])swap(u,v);
	for(int i=MAXK-1;i>=0;--i)if((dep[u]-dep[v])&(1<<i))u=anc[u][i];
	if(u==v)return u;
	for(int i=MAXK-1;i>=0;--i)if(anc[u][i]!=anc[v][i])u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}
int lcp(int x,int y)
{
/*int res=ccp.len[lca(ccp.pos[x],ccp.pos[y])];
cerr<<res<<":"<<endl;
for(int i=x;i<=n;++i)cerr<<a[i];cerr<<endl;
for(int i=y;i<=n;++i)cerr<<a[i];cerr<<endl<<endl;*/
	return ccp.len[lca(ccp.pos[x],ccp.pos[y])];
}
vector<int> G[MAXN];
ll ans=0;
vector<int> ar[MAXN];
void dfs1(int u)
{
	for(auto v:G[u])
	{
		dfs1(v);
		for(auto i:ar[v])ar[u].pb(i);
	}
	if(sol.rgt[u])ar[u].pb(sol.rgt[u]);
	sort(ar[u].begin(),ar[u].end());
	int sum=0;
	for(int i=0,p=0;i<ar[u].size();++i)
	{
		int r=ar[u][i];
		if(i)chkmin(p,lcp(ar[u][0]+1,r+1));
		else p=n-r;
		sum+=max(0,p-(i==ar[u].size()-1?0:n-ar[u][i+1]));
	}
	ans+=1ll*(sol.len[u]-sol.len[sol.fa[u]])*sum;
}

int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	readint(n);scanf("%s",a+1);
	for(int i=1;i<=n;++i)sol.extend(a[i]-'a',i);
	for(int i=n;i;--i)ccp.extend(a[i]-'a',i);
	front=1,rear=0;
	for(int i=1;i<=ccp.ctot;++i)++deg[ccp.fa[i]];
	for(int i=1;i<=ccp.ctot;++i)if(!deg[i])que[++rear]=i;
	while(front<=rear)
	{
		int i=que[front++],u=ccp.fa[i];
		if(!(--deg[u]))que[++rear]=u;
	}
	for(int ii=ccp.ctot;ii;--ii)
	{
		int i=que[ii];
		dep[i]=dep[ccp.fa[i]]+1;
		anc[i][0]=ccp.fa[i];
		for(int j=1;j<MAXK;++j)anc[i][j]=anc[anc[i][j-1]][j-1];
	}
/*cerr<<ccp.ctot<<endl;
for(int i=1;i<=ccp.ctot;++i)
	for(int j=0;j<26;++j)
		if(ccp.ch[i][j])cerr<<i<<" "<<ccp.ch[i][j]<<" "<<(char)(j+'a')<<endl;
for(int i=1;i<=ccp.ctot;++i)cerr<<ccp.fa[i]<<" "<<ccp.len[i]<<endl;*/
	for(int i=1;i<=sol.ctot;++i)
		G[sol.fa[i]].pb(i);
	dfs1(1);
	printf("%lld\n",ans);
	return 0;
}
