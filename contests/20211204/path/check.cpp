#include <bits/stdc++.h>

using namespace std;

int main() {
    int t = 1e8;
    for(int tt = 1; tt <= t; ++tt) {
	cerr << "test #" << tt << "... ";
	system("./gen.exe > in");
	system("./test.exe < in > out");
	system("./bf.exe < in > ans");
	if(system("diff -Z out ans")) {
	    cerr << "WA!" << "\n";
	    return 0;
	}
	cerr << "ok" << "\n";
    }
    return 0;
}
