#include<iostream>
#include<map>
#include<vector>
using namespace std;
const int base=131;
int n,num=0,ans=0;
char s[310];
map<unsigned long long,int> id;
vector<int> a[90010];
unsigned long long p[310],h[310];
inline unsigned long long H(int l,int r)
{
	return h[r]-h[l-1]*p[r-l+1];
}
int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	cin>>n>>s+1;
	p[0]=1;
	for(int i=1;i<=n;i++)
	{
		p[i]=p[i-1]*base;
		h[i]=h[i-1]*base+s[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			int ID=id[H(i,j)];
			if(!ID)
			{
				ID=id[H(i,j)]=++num;
			}
			a[ID].push_back(j);
		}
	}
	for(int i=1;i<=num;i++)
	{
		for(int j=1,k=a[i].size()-1;j<=n;j++)
		{
			while(k>=0&&n-a[i][k]<j)
			{
				k--;
			}
			if(k<0)
			{
				break;
			}
			bool flag=1;
			for(int l=1;l<=k;l++)
			{
				if(H(a[i][l]+1,a[i][l]+j)!=H(a[i][0]+1,a[i][0]+j))
				{
					flag=0;
					break;
				}
			}
			ans+=flag;
		}
	}
	cout<<ans<<endl;
	return 0;
}
