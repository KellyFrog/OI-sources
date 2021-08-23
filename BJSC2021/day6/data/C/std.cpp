#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define pll pair<int,ll>
 
map<pii,int> mp;
 
const int d[6][4]=
{
1,2,4,3,
0,3,5,2,
1,5,4,0,
1,0,4,5,
0,2,5,3,
1,3,4,2
};
 
int to1[25][2],lst[25],h[25];
ll num1[25][2],lst1[25],h1[25];
 
int to[25][2],Num[25],tt;
ll num[25][2],pre_num[6],a,b;
 
inline ll rd()
{
    ll x=0;char ch=getchar();
    for (;ch<'0'||ch>'9';ch=getchar());
    for (;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
    return x;
}
 
inline void pre_gao()
{
    tt=0;
    for (int i=0;i<6;i++) for (int j=0;j<4;j++) mp[pii(i,d[i][j])]=++tt;
    for (int i=0;i<6;i++) for (int j=0;j<4;j++)
    {
        to[mp[pii(i,d[i][j])]][0]=mp[pii(d[i][(j+1)&3],d[i][j])];
    }
    for (int i=0;i<6;i++) for (int j=0;j<4;j++)
    {
        int x=i,y=d[i][j],id=0;
        for (int l=0;l<4;l++) if (d[y][l]==x) id=l;
        int z=d[y][(id+2)&3];
        to[mp[pii(y,x)]][1]=mp[pii(z,y)];
    }
    if (a<b)
    {
        swap(a,b);
        for (int i=1;i<=24;i++) swap(to[i][0],to[i][1]);
    }
    for (int i=0;i<6;i++) for (int j=0;j<4;j++) num[mp[pii(i,d[i][j])]][0]=pre_num[i];
    for (int i=1;i<=24;i++)
    {
        num[i][1]=num[i][0]+num[to[i][1]][0];
        to[i][1]=to[to[i][1]][0];
    }
    for (int i=1;i<=24;i++) lst[i]=to[i][0],lst1[i]=num[i][0];
}
 
ll sum[25][70];
int fa[25][70];
 
inline void gao(int hh)
{
    memset(fa,0,sizeof(fa));
    memset(sum,0,sizeof(sum));
    for (int i=1;i<=24;i++) sum[i][0]=num[i][hh],fa[i][0]=to[i][hh];
    for (int j=1;j<64;j++) for (int i=1;i<=24;i++)
    {
        fa[i][j]=fa[fa[i][j-1]][j-1];
        sum[i][j]=sum[i][j-1]+sum[fa[i][j-1]][j-1];
    }
}
 
inline pll query(int x,ll y)
{
    ll res=0;
    for (int i=63;~i;i--) if ((y>>i)&1) res+=sum[x][i],x=fa[x][i];
    return pll(x,res);
}
 
inline pll gao(pll hh)
{
    hh.second+=num[hh.first][1];
    hh.first=to[hh.first][1];
    return hh;
}
 
inline pll gao1(pll hh)
{
    hh.second+=lst1[hh.first];
    hh.first=lst[hh.first];
    return hh;
}
 
inline void gcd(ll a,ll b,int st,int flag,ll sum)
{
    gao(0);ll hh=a/b;
    if (a%b==0)
    {
        printf("%lld\n",gao1(query(st,hh-1)).second+sum);
        return;
    }
    sum+=num[st][0];st=to[st][0];
    for (int i=1;i<=24;i++)
    {
        pll now=gao(query(i,hh));
        to1[i][0]=now.first;num1[i][0]=now.second;
        now=gao(query(i,hh-1));
        to1[i][1]=now.first;num1[i][1]=now.second;
    }
    for (int i=1;i<=24;i++)
    {
        pll now=gao1(query(i,hh-1));
        h[i]=now.first;h1[i]=now.second;
    }
    for (int i=1;i<=24;i++) lst[i]=h[i],lst1[i]=h1[i];
    memcpy(to,to1,sizeof(to));
    memcpy(num,num1,sizeof(num));
    for (int i=1;i<=24;i++) swap(to[i][0],to[i][1]),swap(num[i][0],num[i][1]);
    gcd(b,a%b,st,flag^1,sum);
}
 
int main()
{
    a=rd();b=rd();
    for (int i=0;i<6;i++) pre_num[i]=rd();
    pre_gao();
    gcd(a,b,17,0,0);
    return 0;
}
