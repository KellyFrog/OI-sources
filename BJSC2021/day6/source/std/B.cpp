#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
 
ll ans=0;
int id[400010],n;
char s[200010];
 
inline int rd()
{
    int x=0;char ch=getchar();
    for (;ch<'0'||ch>'9';ch=getchar());
    for (;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
    return x;
}
 
vector<int> v[400010];
 
int ch[400010][26],fa[400010],len[400010],mx[400010],tot,last;
bool bo[400010];
 
inline void init() { tot=last=1; }
 
inline int insert(int x)
{
    int p=last,np=++tot;bo[np]=true;
    len[np]=len[p]+1;
    for (;p&&!ch[p][x];p=fa[p]) ch[p][x]=np;
    if (!p) fa[np]=1;
    else
    {
        int q=ch[p][x];
        if (len[q]==len[p]+1) fa[np]=q;
        else
        {
            int nq=++tot;
            memcpy(ch[nq],ch[q],sizeof(ch[q]));
            len[nq]=len[p]+1;
            fa[nq]=fa[q];fa[q]=fa[np]=nq;
            for (;p&&ch[p][x]==q;p=fa[p]) ch[p][x]=nq;
        }
    }
    return last=np;
}
 
inline void dfs1(int x)
{
    mx[x]=len[x];
    for (int i=0;i<v[x].size();i++)
    {
    	int t=v[x][i];
    	dfs1(t),mx[x]=max(mx[x],mx[t]);
	}
}
 
set<pii> st1[400010];
 
int tt=0;
int sum[400010];
 
inline void dfs(int x)
{
    int hh=len[x]-len[fa[x]];
    ans+=(ll)hh*(hh-1)/2;
    for (int i=0;i<v[x].size();i++)
    {
    	int t=v[x][i];
    	dfs(t);
	}
    if (x==1) return;
    if (v[x].size())
    {
        int son=0;
        for (int i=0;i<v[x].size();i++)
 		{
    		int t=v[x][i];
    		if (mx[t]>mx[son]) son=t;
		}
        int mx1=0;
        for (int i=0;i<v[x].size();i++)
 		{
    		int t=v[x][i];
    		if (t!=son) mx1=max(mx1,mx[t]);
		}
        sum[x]=sum[son];swap(st1[x],st1[son]);
        while (!st1[x].empty()&&st1[x].begin()->first<=mx1)
        {
            sum[x]-=st1[x].begin()->first-st1[x].begin()->second;
            st1[x].erase(st1[x].begin());tt++;
        }
        if (!st1[x].empty())
        {
            pii hh=*st1[x].begin();
            if (hh.second<mx1)
            {
                sum[x]-=mx1-hh.second;
                st1[x].erase(hh);
                hh.second=mx1;tt++;
                st1[x].insert(hh);
            }
        }
    }
    if (bo[x])
    {
        if (!st1[x].empty())
        {
            pii hh=*st1[x].begin();
            if (hh.second<len[x])
            {
                sum[x]-=len[x]-hh.second;
                st1[x].erase(hh);tt++;
                hh.second=len[x];
                st1[x].insert(hh);
            }
        }
    }
    sum[x]+=len[x];
    st1[x].insert(pii(len[x],0));
    ans+=(ll)(sum[x]-len[x])*hh;
}
 
int main()
{
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout); 
    n=rd();scanf("%s",s+1);
    init();
    for (int i=n;i;i--) id[n-i+1]=insert(s[i]-'a');
    for (int i=2;i<=tot;i++) v[fa[i]].push_back(i);
    dfs1(1);dfs(1);
    printf("%lld\n",ans);
    return 0;
}
