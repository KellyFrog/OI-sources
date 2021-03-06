#include<bits/stdc++.h>
#define ll long long
using namespace std;
namespace fastio
{
    const int bufl=1<<16;
    char ibuf[bufl],*is=ibuf,*it=ibuf,obuf[bufl],*os=obuf,*ot=obuf+bufl;
    inline int getch()
    {
        if(is==it){it=(is=ibuf)+fread(ibuf,1,bufl,stdin);if(is==it)return EOF;}
        return *is++;
    }
    inline void read(char &a){a=getch();}
    template<typename Temp>
    inline void read(Temp &a)
    {
        a=0;int b=0,c=getch();
        while(c<48||c>57)b^=(c=='-'),c=getch();
        while(c>=48&&c<=57)a=(a<<1)+(a<<3)+c-48,c=getch();
        if(b)a=-a;
    }
    template<typename Temp1,typename... Temp2>
    inline void read(Temp1 &a,Temp2 &...b){read(a);read(b...);}
    inline void flush(){fwrite(obuf,1,os-obuf,stdout);os=obuf;}
    inline void putch(int a)
    {
        *os++=a;
        if(os==ot)flush();
    }
    inline void write(char a){putch(a);}
    template<typename Temp>
    inline void write(Temp a)
    {
        if(a<0){putch(45);a=-a;}
        if(a<10){putch(a+48);return;}
        write(a/10);putch(a%10+48);
    }
    template<typename Temp1,typename... Temp2>
    inline void write(Temp1 a,Temp2 ...b){write(a);write(b...);}
    struct Fline{~Fline(){flush();}}cpp_flusher;
}
using fastio::read;
using fastio::write;
struct Node{
    int u,v;
}pl[200005];
int n,m,tp,ans;
vector<int> adj[200005],ed[200005],a,b;
int dfn[200005],low[200005],dft;
bool vis[200005],zp[200005],f;
int pos[200005],cur,cn[200005],scc[200005];
int s[200005],nm;
int in[200005],out[200005];
inline void dfs(int u)
{
    dfn[u]=low[u]=++dft;
    s[++nm]=u;
    vis[u]=1;
    for(int i=0;i<adj[u].size();i++)
    {
        int v=adj[u][i];
        if(!dfn[v])
        {
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        if(vis[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(low[u]<dfn[u])
        return;
    pos[++cur]=u;
    while(1)
    {
        int k=s[nm--];
        vis[k]=0;
        scc[k]=cur;
        for(int i=0;i<adj[k].size();i++)
        {
            int v=scc[adj[k][i]];
            if(!v||v==cur||cn[v]==cur)
                continue;
            cn[v]=cur;
            ed[cur].push_back(v);
            in[v]++;
            out[cur]++;
        }
        if(u==k)
            break;
    }
}
inline void gtans(int u)
{
    vis[u]=1;
    if(!out[u])
    {
        pl[ans].u=pos[u];
        f=1;
        return;
    }
    for(int i=0;i<ed[u].size();i++)
    {
        int v=ed[u][i];
        if(!vis[v])
            gtans(v);
        if(f)
            return;
    }
}
int main()
{
    read(n,m,tp);
    while(m--)
    {
        int u,v;
        read(u,v);
        adj[u].push_back(v);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            dfs(i);
    if(cur==1) {
	cout << 0 << "\n";
	return 0;
    }
    for(int i=1;i<=cur;i++)
    {
        f=0;
        if(!in[i])
        {
            pl[++ans].v=pos[i];
            gtans(i);
            if(!f)
                ans--,vis[i]=0;
        }
    }
    for(int i=1;i<ans;i++)
        swap(pl[i].v,pl[i+1].v);
    for(int i=1;i<=cur;i++)
    {
        if(!in[i]&&!vis[i])
            a.push_back(i);
        if(!out[i]&&!vis[i])
            b.push_back(i);
    }
    if(a.size()>b.size())
    {
        for(int i=0;i<b.size();i++)
            pl[++ans].u=pos[b[i]],pl[ans].v=pos[a[i]];
        for(int i=b.size();i<a.size();i++)
            pl[++ans].u=pl[1].v,pl[ans].v=pos[a[i]];
    }
    else
    {
        for(int i=0;i<a.size();i++)
            pl[++ans].u=pos[b[i]],pl[ans].v=pos[a[i]];
        for(int i=a.size();i<b.size();i++)
            pl[++ans].v=pl[1].v,pl[ans].u=pos[b[i]];
    }
    write(ans,'\n');
    for(int i=1;i<=ans;i++)
        write(pl[i].u,' ',pl[i].v,'\n');
    return 0;
}
