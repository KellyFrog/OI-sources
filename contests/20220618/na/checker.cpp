#include<bits/stdc++.h>
#include "testlib.h"
#define ll long long
#define db double
#define mp make_pair
#define fi first
#define se second
#define pii pair<int,int>
using namespace std;
int read(){
	int sum=0,f=1;char st=getchar();
	while(st<'0'||st>'9'){
		if(st=='-')f=-1;
		st=getchar();
	}
	while('0'<=st&&st<='9'){
		sum=(sum<<3)+(sum<<1)+st-'0';
		st=getchar();
	}
	return sum*f;
}
const int maxn=1010;
struct qqq{
	int n,m;
	vector<int> a,b;
}Test_case[maxn];
int a[maxn],b[maxn],c[maxn],d[maxn];
int main(int argc, char **argv){
	registerTestlibCmd(argc, argv);
	int test_number = inf.readInt();
	int miScore=100;
	for(int I=1;I<=test_number;++I){
		int n=inf.readInt(),m=inf.readInt();
		for(int i=1;i<=n;++i)a[i]=inf.readInt();
		for(int i=1;i<=n;++i)d[i]=inf.readInt();
		string text1=ans.readToken();
		string text2=ouf.readToken();
		if(text1!=text2)
			quitf(_wa,"Case_test : %d wrong check yes/no",I);
		if(text1=="NO")continue;
		int k=ouf.readInt();
		if(k<0||k>n*n*n*2)
			quitf(_wa,"Case_test : %d  too many operation",I);
		for(int i=1;i<=k;++i){
			int x=ouf.readInt();
			if(x<=0||x+m-1>n)quitf(_wa,"Case_test : %d wrong x",I);
			int top=0,top2=0;
			for(int j=1;j<x;++j)b[++top]=a[j];
			for(int j=x+m;j<=n;++j)b[++top]=a[j];
			int y=ouf.readInt();
			if(y<=0||y>top+1)quitf(_wa,"Case_test : %d wrong y",I);
			for(int j=1;j<y;++j)c[++top2]=b[j];
			for(int j=x;j<x+m;++j)c[++top2]=a[j];
			for(int j=y;j<=top;++j)c[++top2]=b[j];
			memcpy(a,c,sizeof(int)*(n+1));
		}
		for(int i=1;i<=n;++i)
			if(a[i]!=d[i])
				quitf(_wa,"Case_test : %d your operation can't get the p",I);
		if(k<=n*n*n)
			miScore=min(miScore,100);
		else miScore=min(miScore,20);
	}
	if(miScore==100)quitf(_ok,"Accepted!");
	else quitp((db)miScore/100.0, "your Score is %d",miScore/100);
	return 0;
}
