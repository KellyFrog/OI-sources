# include <bits/stdc++.h>

using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=1e5+5;

template<typename T> void read(T &x){
	x=0;int f=1;
	char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	x*=f;
}

int cnt;

int main()
{
	system("g++ A.cpp -o A.exe");
	system("g++ Ap.cpp -o Ap.exe");
	system("g++ Ad.cpp -o Ad.exe");
	while(cnt<100000){
		cnt++;
		system("Ad.exe>testdata.in");
		system("A.exe<testdata.in>test1.out");
		system("Ap.exe<testdata.in>test2.out");
		if(system("fc test1.out test2.out")){
			printf("WA on #%d\n",cnt);
			break;	
		}
		else printf("OK on #%d\n",cnt);
	}
	system("pause");
	return 0;
}
