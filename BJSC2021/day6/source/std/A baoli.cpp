#include <bits/stdc++.h>
#define FR first
#define SE second

using namespace std;

typedef long long ll;
typedef pair<int,int> pr;

int pos1[5005],pos2[5005],sz1,sz2;
vector <int> vt1[5005],vt2[5005];

pr val[5005]; 

ll query(int x,int y,int m) {
  if (!x||!y||x==m||y==m) return 0;
  int ans=0;
  int lx=lower_bound(pos1+1,pos1+sz1+1,x)-pos1;
  int minn=0,maxn=m;
  for(int i=lx;i<=sz1+1;i++) {
  	val[i]=pr(minn,maxn);
  	for(int j=0;j<vt1[i].size();j++) {
  	  if (vt1[i][j]<=y) minn=max(minn,vt1[i][j]);
  	  if (vt1[i][j]>=y) maxn=min(maxn,vt1[i][j]);
    }
  }
  minn=0;maxn=m;
  int r=sz1+1;
  for(int i=lx-1;i>=0;i--) {
  	while (pos1[r-1]>x&&min(maxn,val[r-1].SE)-max(minn,val[r-1].FR)<=pos1[r-1]-pos1[i]) r--;
  	int t=min(maxn,val[r].SE)-max(minn,val[r].FR);
  	if (t<=pos1[r]-pos1[i]) ans=max(ans,t);
  	for(int j=0;j<vt1[i].size();j++) {
  	  if (vt1[i][j]<=y) minn=max(minn,vt1[i][j]);
  	  if (vt1[i][j]>=y) maxn=min(maxn,vt1[i][j]);
    }
  }
  lx=lower_bound(pos2+1,pos2+sz2+1,y)-pos2;
  minn=0;maxn=m;
  for(int i=lx;i<=sz2+1;i++) {
  	val[i]=pr(minn,maxn);
  	for(int j=0;j<vt2[i].size();j++) {
  	  if (vt2[i][j]<=x) minn=max(minn,vt2[i][j]);
  	  if (vt2[i][j]>=x) maxn=min(maxn,vt2[i][j]);
    }
  }
  minn=0;maxn=m;
  r=sz2+1;
  for(int i=lx-1;i>=0;i--) {
  	while (pos2[r-1]>y&&min(maxn,val[r-1].SE)-max(minn,val[r-1].FR)<=pos2[r-1]-pos2[i]) r--;
  	int t=min(maxn,val[r].SE)-max(minn,val[r].FR);
  	if (t<=pos2[r]-pos2[i]) ans=max(ans,t);
  	for(int j=0;j<vt2[i].size();j++) {
  	  if (vt2[i][j]<=x) minn=max(minn,vt2[i][j]);
  	  if (vt2[i][j]>=x) maxn=min(maxn,vt2[i][j]);
    }
  }
  return (ll)ans*ans;
}

pr a[5005];

int main() {
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout); 
  int cases;
  scanf("%d",&cases);
  for(;cases;cases--) {
  	int n,m;
  	scanf("%d%d",&m,&n);
  	for(int i=0;i<=n+1;i++) {
  		vt1[i].clear();
  		vt2[i].clear();
	  }
  	sz1=sz2=0;
  	for(int i=1;i<=n;i++) {
  		int x,y;
  		scanf("%d%d",&x,&y);
  		a[i]=pr(x,y);
  		if (x&&x<m) pos1[++sz1]=x;
  		if (y&&y<m) pos2[++sz2]=y;
	  }
	sort(pos1+1,pos1+sz1+1);
	sort(pos2+1,pos2+sz2+1);
	sz1=unique(pos1+1,pos1+sz1+1)-pos1-1;
	sz2=unique(pos2+1,pos2+sz2+1)-pos2-1;
	pos1[0]=pos2[0]=0;
	pos1[sz1+1]=pos2[sz2+1]=m;
	for(int i=1;i<=n;i++)
	  if (a[i].FR&&a[i].SE&&a[i].FR<m&&a[i].SE<m) {
	  	int t1=lower_bound(pos1+1,pos1+sz1+1,a[i].FR)-pos1;
	  	int t2=lower_bound(pos2+1,pos2+sz2+1,a[i].SE)-pos2;
	  	vt1[t1].push_back(a[i].SE);
	  	vt2[t2].push_back(a[i].FR);
	  }
	int k;
	scanf("%d",&k);
	for(int i=1;i<=k;i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%lld\n",query(x,y,m));
	}
  }
  return 0;
}
