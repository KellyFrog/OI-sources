#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=10005;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int t,m,n,q;
int up[N],down[N];
int ans;

struct node{
	int x,y;
}a[N],b[N];

bool cmpx(node a,node b){
	if(a.x!=b.x)return a.x<b.x;
	return a.y<b.y;	
}

bool cmpy(node a,node b){
	if(a.y!=b.y)return a.y<b.y;
	return a.x<b.x;	
}

bool check(int i,int j,int y){
	int L=max(down[i],down[j]),R=min(up[i],up[j]);
	return y>L&&y<R&&(R-L>=a[j].x-a[i].x);
}

void solve(int x,int y){
	int p1=0,p2=m+1;
	Rep(i,1,n)if(a[i].x<x)p1=i;
	_Rep(i,n,1)if(a[i].x>x)p2=i;
	Rep(i,1,n)up[i]=0,down[i]=m;
	int L=0,R=m;
	_Rep(i,p2-1,1){
		int j=i;
		while(j&&a[j].x==a[i].x){
			down[j]=L,up[j]=R;
			j--;
		}
		j++;
		Rep(k,j,i){
			if(a[k].y<=y)L=max(L,a[k].y);
			if(a[k].y>=y)R=min(R,a[k].y);
		}	
		i=j;
	}
	L=0,R=m;
	Rep(i,p1+1,n){
		int j=i;
		while(j<=n&&a[j].x==a[i].x){
			down[j]=L,up[j]=R; 
			j++;	
		}
		j--;
		Rep(k,i,j){
			if(a[k].y<=y)L=max(L,a[k].y);
			if(a[k].y>=y)R=min(R,a[k].y);	
		}
		i=j;
	}	
	Rep(i,1,p1){
		if(a[i].x>=x)break;
		int l=p2,r=n,res=i;
		while(l<=r){
			int mid=l+r>>1;
			if(check(i,mid,y))res=mid,l=mid+1;
			else r=mid-1;	
		}
		ans=max(ans,a[res].x-a[i].x);
	}
}

int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	read(t);
	while(t--){
		read(m),read(n);
		Rep(i,1,n)read(a[i].x),read(a[i].y);
		a[++n]=(node){0,0},a[++n]=(node){0,m};
		a[++n]=(node){m,0},a[++n]=(node){m,m};
		Rep(i,1,n)b[i].x=a[i].y,b[i].y=a[i].x; 
		sort(a+1,a+n+1,cmpx);
		sort(b+1,b+n+1,cmpx);
		read(q);
		while(q--){
			int x,y;
			read(x),read(y);
			ans=0;
			solve(x,y);
			swap(a,b);
			solve(y,x);
			swap(a,b);
			printf("%lld\n",1ll*ans*ans);
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
4
3 1
2 3
4 3
4 4

*/
