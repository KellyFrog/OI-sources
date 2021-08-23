#include<bits/stdc++.h>
//dengyaotriangle!
using namespace std;

const int maxn=200005;

int n;
char s[maxn];
int sa[maxn],rnk[maxn],cnt[maxn],pre[maxn*2],h[maxn];
int m;

int fa[maxn*2],dep[maxn*2],mdep[maxn*2];

int grt(int u){return fa[u]==u?u:fa[u]=grt(fa[u]);}
pair<int,int> op[maxn];

const int poolsz=2e7;
struct node{
	int tg,cnt0,cnt1;
	int c[2];
}p[poolsz];int ps;


int nwnode(){
	return ++ps;
}
void pu(int rt,int ll,int rl){
	int vl=p[rt].c[0]?p[p[rt].c[0]].cnt0:ll;
	int vr=p[rt].c[1]?p[p[rt].c[1]].cnt0:rl;
	if(p[rt].tg==0){
		p[rt].cnt0=vl+vr;
		p[rt].cnt1=p[p[rt].c[0]].cnt1+p[p[rt].c[1]].cnt1;
	}else if(p[rt].tg==1){
		p[rt].cnt0=0;
		p[rt].cnt1=vl+vr;
	}else p[rt].cnt0=p[rt].cnt1=0;
}
int mrg(int a,int b,int cl,int cr){
	if(!a)return b;
	if(!b)return a;
	p[a].tg+=p[b].tg;
	int cm=(cl+cr)/2;
	if(cl==cr){
		p[a].cnt0=p[a].cnt1=0;
		if(p[a].tg==0)p[a].cnt0=1;
		if(p[a].tg==1)p[a].cnt1=1;
	}else{
		p[a].c[0]=mrg(p[a].c[0],p[b].c[0],cl,cm);
		p[a].c[1]=mrg(p[a].c[1],p[b].c[1],cm+1,cr);
		pu(a,cm-cl+1,cr-cm);
	}
	return a;
}
void chg(int rt,int cl,int cr,int l,int r,int v){
	int cm=(cl+cr)>>1;
	if(l==cl&&r==cr)p[rt].tg+=v;//,cerr<<l<<'/'<<r<<endl;
	else if(r<=cm){
		if(!p[rt].c[0])p[rt].c[0]=nwnode(); 
		chg(p[rt].c[0],cl,cm,l,r,v);
	}else if(l>cm){
		if(!p[rt].c[1])p[rt].c[1]=nwnode();
		chg(p[rt].c[1],cm+1,cr,l,r,v);
	}else{
		if(!p[rt].c[0])p[rt].c[0]=nwnode(); 
		if(!p[rt].c[1])p[rt].c[1]=nwnode();
		chg(p[rt].c[0],cl,cm,l,cm,v),chg(p[rt].c[1],cm+1,cr,cm+1,r,v);
	}
	if(cl==cr){
		p[rt].cnt0=p[rt].cnt1=0;
		if(p[rt].tg==0)p[rt].cnt0=1;
		if(p[rt].tg==1)p[rt].cnt1=1;
	}else pu(rt,cm-cl+1,cr-cm);
	//cerr<<cl<<' '<<cr<<' '<<p[rt].cnt1<<endl;
}
int rt[maxn*2];
int c1;

int main(){
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;i++)cnt[s[i]]++;
	for(int i=1;i<256;i++)cnt[i]+=cnt[i-1];
	for(int i=n;i>=1;i--)sa[cnt[s[i]]--]=i;
	rnk[sa[1]]=1;
	for(int i=2;i<=n;i++)rnk[sa[i]]=rnk[sa[i-1]]+(s[sa[i]]!=s[sa[i-1]]);
	int m=rnk[sa[n]];
	for(int k=1;k<n&&m<n;k<<=1){
		int g=0;
		for(int i=1;i<=n;i++)if(sa[i]>k)pre[++g]=sa[i]-k;
		for(int i=n-k+1;i<=n;i++)pre[++g]=i;
		for(int i=1;i<=m;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)cnt[rnk[i]]++;
		for(int i=2;i<=m;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--)sa[cnt[rnk[pre[i]]]--]=pre[i];
		for(int i=1;i<=n;i++)pre[i]=rnk[i];
		rnk[sa[1]]=1;for(int i=2;i<=n;i++)rnk[sa[i]]=rnk[sa[i-1]]+(pre[sa[i]]!=pre[sa[i-1]]||pre[sa[i]+k]!=pre[sa[i-1]+k]);
		m=rnk[sa[n]];
	}
	for(int i=1;i<=n;i++){
		if(rnk[i]==1)h[1]=0;
		else{
			int ch=h[rnk[i-1]];
			ch-=!!ch;
			while(s[i+ch]==s[sa[rnk[i]-1]+ch])ch++;
			h[rnk[i]]=ch;
		}
	}
	for(int i=1;i<=n;i++){
		fa[i]=i,dep[i]=mdep[i]=n-sa[i]+1;
		rt[i]=nwnode();
		int cm=n/2;
		pu(rt[i],cm+1,n-cm);
	}
	c1=n;
	for(int i=2;i<=n;i++){
		op[i]=make_pair(h[i],i);
	}
	sort(op+2,op+1+n,greater<pair<int,int> >());
	long long ans=0;
	for(int i=2;i<=n;i++){
		int ri=op[i].second,li=ri-1;
		//cerr<<li<<' '<<ri<<endl;
		int ch=op[i].first;
		++c1;
		li=grt(li);ri=grt(ri);
		//cerr<<ch<<endl;
		//cerr<<li<<' '<<ri<<endl;
		int vl=p[rt[li]].cnt1,kl=mdep[li]-ch;
		ans+=(2*vl+kl-1)*(long long)kl;
		int vr=p[rt[ri]].cnt1,kr=mdep[ri]-ch;
		ans+=(2*vr+kr-1)*(long long)kr;
		///cerr<<vl<<' '<<kl<<' '<<vr<<' '<<kr<<endl;
		fa[li]=c1;fa[ri]=c1;fa[c1]=c1;
		rt[c1]=mrg(rt[li],rt[ri],0,n);
		if(ch+1<=mdep[li])chg(rt[c1],0,n,ch+1,mdep[li],1);//,cerr<<ch+1<<mdep[li]<<'\n';
		if(ch+1<=mdep[ri])chg(rt[c1],0,n,ch+1,mdep[ri],1);//,cerr<<ch+1<<mdep[ri]<<'\n';
		mdep[c1]=ch;
	}
	int vl=p[rt[c1]].cnt1,kl=mdep[c1];
	ans+=(2*vl+kl-1)*(long long)kl;
	printf("%lld",ans/2);
	return 0;
}