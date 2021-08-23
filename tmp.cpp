#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int _a[10000], _b[100000], _n;
int _cnt[10000];

int main() {
	
	ofstream outfile("test.out");
	for(int i = 1; i <= (int)1e6; i++) outfile << 1 << " " << 1 << "\n";
	outfile.flush();
	
	return 0;
}