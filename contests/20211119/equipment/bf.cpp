#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-')f^=1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+c-'0';
        c=getchar();
    }
    return f?x:-x;
}
inline void write(int x)
{
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x<10)
    {
        putchar('0'+x);
        return;
    }
    write(x/10);
    putchar('0'+x%10);
}
struct Node{
    int v,nt;
}pl[200005];
int hd[200005],cnt;
inline void add(int u,int v)
{
    pl[++cnt].nt=hd[u];
    pl[cnt].v=v;
    hd[u]=cnt;
}
bool vis[200005];
int dep[200005];
int fa[25][200005];
int n,m,k,cur;
int a[100005],b[100005],c[100005],pos[100005];
int q[100005],ans;
inline void dfs(int u)
{
    dep[u]++;
    vis[u]=1;
    for(int i=1;i<=20;i++)
        fa[i][u]=fa[i-1][fa[i-1][u]];
    for(int i=hd[u];i;i=pl[i].nt)
    {
        int v=pl[i].v;
        dep[v]=dep[u];
        fa[0][v]=u;
        dfs(v);
    }
}
inline int htop(int x)
{
    for(int i=20;i>=0;i--)
        if(vis[fa[i][x]])
            x=fa[i][x];
    return fa[0][x];
}
inline void gtans(int x)
{
    int tk=0;
    while(vis[x])
        q[ans-tk]=x,tk++,x=fa[0][x];
}
inline void clr(int u)
{
    if(!vis[u])
        return;
    vis[u]=0;
    for(int i=hd[u];i;i=pl[i].nt)
    {
        int v=pl[i].v;
        clr(v);
    }
}
int main()
{
//    freopen("equipment.in","r",stdin);
//    freopen("equipment.out","w",stdout);
    n=read(),cur=m=read(),k=read();
    for(int i=1;i<=n;i++)
        c[i]=read();
    for(int i=1;i<=m;i++)
    {
        a[i]=read(),b[i]=read();
        pos[a[i]]=i;
    }
    for(int i=1;i<=n;i++)
        if(!pos[i])
            pos[i]=++cur;
    for(int i=1;i<=m;i++)
        add(pos[b[i]],i);
    for(int i=m+1;i<=cur;i++)
    {
        dfs(i);
        vis[i]=0;
    }
    for(int i=m;i>0;i--)
    {
        if(!vis[i])
            continue;
        if(c[b[i]]>c[a[i]])
        {
            int tt=htop(i);
            int x=dep[i]-dep[tt];
            if(ans+x<=k)
                ans+=x,gtans(i),vis[i]=0,vis[tt]=1,clr(tt);
        }
        else
        {
            clr(i);
        }
    }
    write(ans),putchar('\n');
    for(int i=1;i<=ans;i++)
        write(q[i]),putchar('\n');
    return 0;
}
