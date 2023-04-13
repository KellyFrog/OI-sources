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
    int v,w,nt;
}pl[400005];
struct node{
    int u,dis;
    node(int u,int dis):u(u),dis(dis){}
    bool operator<(const node tp)const{
        return this->dis>tp.dis;
    }
};
priority_queue<node> q;
int n,m;
int dis1[40005],dis2[40005],lt1[40005],lt2[40005],dis3[40005],dis4[40005],lt3[40005],lt4[40005];
int vis1[40005],vis2[40005];
int h1[40005],h2[40005],cnt;
int ans=0x3f3f3f3f;
inline void add(int u,int v,int w1,int w2)
{
    pl[++cnt].nt=h1[u];
    pl[cnt].v=v;
    pl[cnt].w=w1;
    h1[u]=cnt;
    pl[++cnt].nt=h2[u];
    pl[cnt].v=v;
    pl[cnt].w=w2;
    h2[u]=cnt;
}
int main()
{
    // freopen("loop.in","r",stdin);
    // freopen("loop.out","w",stdout);
    n=read(),m=read();
    while(m--)
    {
        int u=read(),v=read(),w1=read(),w2=read();
        if(u==1&&v==1)
            ans=min(ans,min(w1,w2));
        if(u==v)
            continue;
        add(u,v,w1,w2);
        add(v,u,w2,w1);
    }
    memset(dis1,0x3f,sizeof(dis1));
    memset(dis2,0x3f,sizeof(dis2));
    memset(dis3,0x3f,sizeof(dis3));
    memset(dis4,0x3f,sizeof(dis4));
    vis1[1]=1;
    dis1[1]=dis2[1]=0;
    q.push(node(1,0));
    while(!q.empty())
    {
        int u=q.top().u,d=q.top().dis;
        q.pop();
        if(vis1[u]>1)
            continue;
        if(vis1[u]==1&&d!=dis2[u])
            continue;
        int k=lt1[u];
        if(vis1[u]==1)
            k=lt2[u];
        vis1[u]++;
        for(int i=h1[u];i;i=pl[i].nt)
        {
            int v=pl[i].v,w=pl[i].w;
            if(dis1[v]>d+w)
            {
                if(lt1[v]!=k||u==1)
                    lt2[v]=lt1[v],dis2[v]=dis1[v];
                dis1[v]=d+w;
                if(u==1)
                    lt1[v]=v;
                else
                    lt1[v]=lt1[u];
                q.push(node(v,dis1[v]));
            }
            else if((lt1[v]!=k||u==1)&&dis2[v]>d+w)
            {
                dis2[v]=d+w;
                if(u==1)
                    lt2[v]=v;
                else
                    lt2[v]=lt2[u];
                q.push(node(v,dis2[v]));
            }
        }
    }
    vis2[1]=1;
    dis3[1]=dis4[1]=0;
    q.push(node(1,0));
    while(!q.empty())
    {
        int u=q.top().u,d=q.top().dis;
        q.pop();
        if(vis2[u]>1)
            continue;
        if(vis2[u]==1&&d!=dis4[u])
            continue;
        int k=lt3[u];
        if(vis2[u]==1)
            k=lt4[u];
        vis2[u]++;
        for(int i=h2[u];i;i=pl[i].nt)
        {
            int v=pl[i].v,w=pl[i].w;
            if(dis3[v]>d+w)
            {
                if(lt3[v]!=k||u==1)
                    lt4[v]=lt3[v],dis4[v]=dis3[v];
                dis3[v]=d+w;
                if(u==1)
                    lt3[v]=v;
                else
                    lt3[v]=lt3[u];
                q.push(node(v,dis3[v]));
            }
            else if((lt3[v]!=k||u==1)&&dis4[v]>d+w)
            {
                dis4[v]=d+w;
                if(u==1)
                    lt4[v]=v;
                else
                    lt4[v]=lt4[u];
                q.push(node(v,dis4[v]));
            }
        }
    }
    for(int i=2;i<=n;i++)
    {
        if(lt1[i]==lt3[i])
            ans=min(ans,min(dis1[i]+dis4[i],dis3[i]+dis2[i]));
        else
            ans=min(ans,dis1[i]+dis3[i]);
    }
    write(ans==0x3f3f3f3f?-1:ans);
    putchar('\n');
    return 0;
}
