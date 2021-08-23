#include <algorithm>
#include <iostream>
#include <cstdio>
#define LL long long
using namespace std;
LL read(){
	LL x=0,k=1;char ch=getchar();
	while('0'>ch || ch>'9'){if(ch=='-')k=-1;ch=getchar();}
	while('0'<=ch && ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*k;
}
int n,m;
struct node{
	LL x,y;
}p[5010];
bool cmp(node a,node b){
	if(a.x==b.x)return a.y<b.y;
	return a.x<b.x;
}
int find(int xx){
	int l=1,r=n;int ans=1;
	while(l<=r){
		int mid=(l+r)/2;
		if(p[mid].x<=xx){
			ans=mid;l=mid+1;
		}else{
			r=mid-1;
		}
	}
	return ans;
}

LL U,D;
LL L[5010],R[5010];
int main(){
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&m,&n);
		for(int i=1;i<=n;i++){
			scanf("%d%d",&p[i].x,&p[i].y);
		}
		sort(p+1,p+n+1,cmp);
		p[n+1].x=m;
		p[0].x=0;
		int q;
		scanf("%d",&q);
		int x,y;
		while(q--){
			scanf("%d%d",&x,&y);
			int posl=find(x),posr=posl+1;
			LL u,d;
			LL ans=0;
			U=m;D=0;
			for(int i=posl;p[i].x==x;i++){
				posr=i+1;
				if(p[i].y>=y)U=min(U,p[i].y);
				if(p[i].y<=y)D=max(D,p[i].y);
			}
			for(int i=posl;p[i].x==x;i--){
				posl=i-1;
				if(p[i].y>=y)U=min(U,p[i].y);
				if(p[i].y<=y)D=max(D,p[i].y);
			}
			ans=min(U-D,p[posr].x-p[posl].x);
			
			
			u=U;d=D;for(int i=posl;i>=1;i--){
				if(p[i].y>=y)u=min(u,p[i].y);if(p[i].y<=y)d=max(d,p[i].y);
				L[i]=d;R[i]=u;
			}
			u=U;d=D;for(int i=posr;i<=n;i++){
				if(p[i].y>=y)u=min(u,p[i].y);if(p[i].y<=y)d=max(d,p[i].y);
				L[i]=d;R[i]=u; 
			}
			
			
			/*u=m,d=0;
			for(int i=posr;i<=n;i++){
				if(p[i].y>=y)u=min(u,p[i].y);
				if(p[i].y<=y)d=max(d,p[i].y);		
				ans=max(ans,min(p[i+1].x-x,u-d));
			}
			u=m,d=0;
			for(int i=posl;i>=1;i--){
				if(p[i].y>=y)u=min(u,p[i].y);
				if(p[i].y<=y)d=max(d,p[i].y);
				ans=max(ans,min(x-p[i-1].x,u-d));
			}*/
		/*	for(int i=2;i<=posl;i++){
				if(p[i].x==p[i-1].x)L[i]=L[i-1];R[i]=R[i-1];
			}
			for(int i=n-1;i>=posr;i--){
				if(p[i].x==p[i+1].x)L[i]=L[i+1];R[i]=R[i+1];
			}
			*/
			/*for(int i=1;i<=n;i++){
				cout<<L[i]<<" "<<R[i]<<endl;
			}*/
		for(int i=1;i<=posl;i++){ 
				ans=max(ans,min(p[posr].x-p[i-1].x,min(R[i],U)-max(L[i],D)));
			//	cout<<i<<" "<<ans<<endl; 
			}
			for(int i=n;i>=posr;i--){
				ans=max(ans,min(p[i+1].x-p[posl].x,min(R[i],U)-max(L[i],D)));
			//	cout<<i<<" "<<ans<<endl;
			}
			for(int i=1;i<=posl;i++){
				int l=posr,r=n;
				int anspos=0;
				while(l<=r){
					int mid=(l+r)/2;
					LL F=p[mid+1].x-p[i-1].x;
					LL G=min(R[i],R[mid])-max(L[i],L[mid]);
					if(F>G){
						r=mid-1;
					}else{
						anspos=mid;
						l=mid+1;
					}
				}
				if(n>500){
					for(int j=max(posl,anspos-10);j<=min(n,anspos+10);j++){
						ans=max(ans,min(p[j+1].x-p[i-1].x,min(R[i],R[j])-max(L[i],L[j])));
					}
				}
				else{
					for(int j=posr;j<=n;j++){
						ans=max(ans,min(p[j+1].x-p[i-1].x,min(R[i],R[j])-max(L[i],L[j])));
					}
				}
			}
			cout<<ans*ans<<endl;
		}
	}
	return 0;
}
/*
1
5 5
1 4
2 1
3 2
4 1
4 4
3
3 1
2 3
4 3


1
5 4
0 1
1 1
1 3
4 1
3
3 2

*/
