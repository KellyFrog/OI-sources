#include <bits/stdc++.h>

using namespace std;

int main() {
	int T = 1000; //���� 1000 �飬���Ե���
	for(int test = 1; test <= T; test++) {
		//�������е��ļ��������Ի����Լ���
		system("./gen.exe > testin"); //ͨ�������� gen.exe ������������� testin
		system("./source.exe < testin > outfile"); //������Ҫ���ĵĳ��� source.exe������ testin������� outfile
		system("./bruteforce.exe < testin > ansfile"); //���б������� bruteforces.exe������ testin������� ansfile
		if(system("cmp outfile ansfile")) {
			cerr << "Wrong Answer on test #" << test << "!!!\n";
			return 0;
		}
	}
	cerr << "OK passed " << T << " test(s)\n";
	return 0;
}