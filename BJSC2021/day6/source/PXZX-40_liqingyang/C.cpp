#include<iostream>
using namespace std;
int a,b;
inline double X(int y)
{
	return double(a)/b*y;
}
inline bool judge(int x1,int x2,int y)
{
	double x=X(y);
	return x1<=x&&x<=x2;
}
int f[6];
inline void up()
{
	int i=f[0],j=f[1],k=f[2],l=f[3],m=f[4],n=f[5];
	f[0]=m,f[1]=i,f[2]=k,f[3]=l,f[4]=n,f[5]=j;
}
inline void right()
{
	int i=f[0],j=f[1],k=f[2],l=f[3],m=f[4],n=f[5];
	f[0]=i,f[1]=l,f[2]=j,f[3]=m,f[4]=k,f[5]=n;
}
int main()
{
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	cin>>a>>b;
	for(int i=0;i<6;i++)
	{
		cin>>f[i];
	}
	long long ans=f[4];
	for(int i=1,x=1,y=1;i<a+b-1;i++)
	{
		judge(x-1,x,y)?(y++,up()):(x++,right());
		ans+=f[4];
	}
	cout<<ans<<endl;
	return 0;
}
