#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

int n,s,num_edge,head[300008],dis[300008],maxx=-1,x,y,pre[300008],ans;

bool pd[300008];

struct Edge{
	int from,to,dis,next;
}edge[600008];

long long read()
{
	long long x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

void addedge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].from=from;
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}

void dfs(int xx,int fa,int f)//寻找直径 
{
	for(int i=head[xx];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==fa) continue;
		if(f) pre[v]=xx;
		dis[v]=dis[xx]+edge[i].dis;
		dfs(v,xx,f);
	}
}

int find(int xx,int len)//判断核的大小 
{
	for(int i=head[xx];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==pre[xx]&&len>=edge[i].dis)
		{
			return find(v,len-edge[i].dis);
		}
	}
	return xx;
}

int work(int xx,int len)//寻找最长距离 
{
	int num1=dis[xx],po=find(xx,len);
	int num2=dis[x]-dis[po];
	return max(num1,num2);
}

void ask(int xx,int fa)//寻找其他点到直径上的最大距离 
{
	for(int i=head[xx];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(pd[v]) continue;
		if(v==fa) continue;
		dis[v]=dis[xx]+edge[i].dis;
		ask(v,xx);
	}
}

int main()
{
	n=read();s=read();
	for(int i=1;i<n;++i)
	{
		int a,b,c;
		a=read();b=read();c=read();
		addedge(a,b,c);
		addedge(b,a,c);
	}
	dfs(1,0,0);//寻找直径一点 
	for(int i=1;i<=n;++i)
		if(dis[i]>maxx)
		{
			x=i;
			maxx=dis[i];
		}
	maxx=-1;
	dis[x]=0;
	dfs(x,0,1);//寻找直径另一点 
	for(int i=1;i<=n;++i)
		if(dis[i]>maxx)
		{
			maxx=dis[i];
			y=i;
		}
	memset(dis,0,sizeof(dis));
	int now=y;
	dis[now]=0;
	pd[now]=1;
	while(now!=x)//处理直径上每一个点到y的距离 
	{
		for(int j=head[now];j;j=edge[j].next)
		{
			int v=edge[j].to;
			if(v==pre[now])
			{
				pd[v]=1;
				dis[v]=dis[now]+edge[j].dis;
			}
		}
		now=pre[now];
	}
	now=y;
	int ans=1e9;
	while(now!=x)//处理直径端点的距离
	{
		ans=min(ans,work(now,s));
		now=pre[now];
	}
	ans=min(ans,work(x,s));
	memset(dis,0,sizeof(dis));
	now=y;
	while(now!=x)//处理其他点到直径的距离 
	{
		ask(now,0);
		now=pre[now];
	}
	ask(x,0);
	for(int i=1;i<=n;++i)
		ans=max(ans,dis[i]);
	printf("%d",ans);
	return 0;
}
