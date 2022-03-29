#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue> 
using namespace std;
const int maxn=200010;
int n,k,q;
struct FHQ
{
    int rt,cnt,lc[maxn],rc[maxn],siz[maxn],pri[maxn],val[maxn];
	int sum[maxn],tag[maxn],minu[maxn];
    void print(int o)
    {
        if(!o)return;
        pushdown(o);
        print(lc[o]);
        //printf("%d ",val[o]);
        print(rc[o]);
    }
    void maintain(int o){siz[o]=siz[lc[o]]+siz[rc[o]]+1;}
    void pushdown(int o)
    {
    	if(tag[o])
    	{
    		if(lc[o])tag[lc[o]]+=tag[o],sum[lc[o]]+=tag[o];
			if(rc[o])tag[rc[o]]+=tag[o],sum[rc[o]]+=tag[o];
			tag[o]=0; 
		}
		if(minu[o])
		{
			if(lc[o])minu[lc[o]]+=minu[o],val[lc[o]]-=minu[o];
			if(rc[o])minu[rc[o]]+=minu[o],val[rc[o]]-=minu[o];
			minu[o]=0;
		}
	}
    int merge(int x,int y)
    {
        if(x==0||y==0)return x+y;
        pushdown(x);pushdown(y);
        maintain(x);maintain(y);
        if(pri[x]<pri[y])
        {
            rc[x]=merge(rc[x],y);
            maintain(x);return x;
        }
        else
        {
            lc[y]=merge(x,lc[y]);
            maintain(y);return y;
        }
    }
    void split_val(int o,int k,int&x,int&y)
    {
        if(!o){x=y=0;return;}
        pushdown(o); 
        if(val[o]<=k)x=o,split_val(rc[o],k,rc[o],y);
        else y=o,split_val(lc[o],k,x,lc[o]);
        maintain(o);
    }
    void split_siz(int o,int k,int&x,int&y)
    {
        if(!o){x=y=0;return;}
        pushdown(o);
        if(siz[lc[o]]>=k)y=o,split_siz(lc[o],k,x,lc[o]);
        else x=o,split_siz(rc[o],k-siz[lc[o]]-1,rc[o],y);
        maintain(o);
    }
    int newnode(int v)
    {
        cnt++;
        lc[cnt]=rc[cnt]=0;
        val[cnt]=v;
        siz[cnt]=1;
        pri[cnt]=rand();
        tag[cnt]=sum[cnt]=0;
        minu[cnt]=0;
        return cnt;
    }
}st;
struct node
{
	int c,q;
	bool operator<(node x)const{if(q==x.q)return c<x.c;return q>x.q;}
}s[maxn];
//int q[maxn],id[maxn],ans[maxn];
queue<int>Q;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&s[i].c,&s[i].q);
	sort(s+1,s+n+1);
	scanf("%d",&k);
	/*
	for(int i=1;i<=k;i++)scanf("%d",q+i),id[i]=i;
	sort(id+1,id+k+1);
	for(int i=1;i<=n;i++)for(int j=1;j<=k;j++)
	if(q[id[j]]>=s[i].c)q[id[j]]-=s[i].c,ans[id[j]]++;
	for(int i=1;i<=k;i++)printf("%d ",ans[i]);
	printf("\n");
	*/
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&q);
		int x,y;
		st.split_val(st.rt,q,x,y);
		st.rt=st.merge(st.merge(x,st.newnode(q)),y); 
	}
	for(int i=1;i<=n;i++)
	{
		int x,y,z;
		st.split_val(st.rt,s[i].c-1,x,y);
		st.split_val(y,s[i].c+s[i].c-1,y,z);
		st.minu[z]+=s[i].c;st.val[z]-=s[i].c;
		st.tag[z]++;st.sum[z]++;
		while(!Q.empty())Q.pop();
		Q.push(y);
		while(!Q.empty())
		{
			int t=Q.front();Q.pop();
			st.pushdown(t);
			if(st.lc[t])Q.push(st.lc[t]);
			if(st.rc[t])Q.push(st.rc[t]);
			int a,b;
			st.split_val(x,st.val[t]-s[i].c,a,b);
			st.lc[t]=st.rc[t]=0;
			st.val[t]-=s[i].c;
			st.siz[t]=1;
			st.tag[t]=0;
			st.sum[t]++;
			st.minu[t]=0;
			x=st.merge(st.merge(a,t),b); 
		}
		st.rt=st.merge(x,z);
	}
	st.print(st.rt);
	for(int i=1;i<=k;i++)printf("%d\n",st.sum[i]);
	return 0;
}