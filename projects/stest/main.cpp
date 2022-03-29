/*
 * Author: chenkaifeng @BDFZ
 */
 
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

#define OK debug("OK!\n")
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

const int mod = 1e9 + 7;
// const int mod = 998244353;

int qpow(int x, ll p) {
    int res = 1, base = x;
    while(p) {
	if(p & 1) res = 1ll * res * base % mod;
	base = 1ll * base * base % mod;
	p >>= 1;
    }
    return res;
}

template<typename T> inline void upd(T& x, const T& y) { x += y; if(x >= mod) x -= mod; }
template<typename T> inline void upd(T& x, const T& y, const T& z) { x = y + z; if(x >= mod) x -= mod;}

/* template ends here */

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const string whighlight = "\033[1m";
const string wclear = "\033[0m";
const string wred = "\033[31m";
const string wgreen = "\033[32m";
const string wyellow = "\033[33m";
const string wblue = "\033[34m";
const string wpurple = "\033[35m";
const string wwhite = "\033[37m";

int argc; char** argv;

struct Program {
    string infile, outfile, name;
} sol, gen, bf;
string checker, cases;
int t = 1e8;

void quitFatalError() {
    cout << whighlight << argv[0] << wclear << ": " << wred << whighlight << "fatal error" << wclear << endl
	 << "unable to open solution/bruteforce/generator file" << endl
	 << "use --help for help" << endl;
    exit(1);
}

void quitNotFound(string filename) {
    cout << whighlight << argv[0] << wclear << ": " << wred << whighlight << "fatal error" << wclear << endl
	 << "unable to open file '" << filename << "'" << endl
	 << "use --help for help" << endl;
    exit(1);
}

void quitUnrecognized(string command) {
    
    cout << whighlight << argv[0] << wclear << ": " << wred << whighlight << "fatal error" << wclear << endl
	 << "Unrecognized option '" << command << "'" << endl
	 << "use --help for help" << endl;
    exit(1);
}

void quitRepeated(string command) {

    cout << whighlight << argv[0] << wclear << ": " << wred << whighlight << "fatal error" << wclear << endl
	 << "Option '" << command << "' appeared more than once" << endl
	 << "use --help for help" << endl;
    exit(1);
}

void quitExpectArg(string command) {
    cout << whighlight << argv[0] << wclear << ": " << wred << whighlight << "fatal error" << wclear << endl
	 << "Option '" << command << "' expect more arguments" << endl
	 << "use --help for help" << endl;
    exit(1);
}

bool examine(string filename) {
    return !access(filename.c_str(), F_OK);
}

string parseFileName(const char* s) {
    string word = s;
    if(!examine(word)) quitNotFound(word);
    return word;
}

void quitHelp() {
    cout << "execution format: " << argv[0] << " <generator> <solution> <bruteforce> [options]" << endl
	 << "options:" << endl
	 << "  -sol-in-file=<file>\t" << "set input of solution from stdin to <file>" << endl
	 << "  -sol-out-file=<file>\t" << "set output of solution from stdout to <file>" << endl
	 << "  -bf-in-file=<file>\t" << "set input of bruteforce from stdin to <file>" << endl
	 << "  -bf-out-file=<file>\t" << "set output of bruteforce from stdout to <file>" << endl
//	 << "  -gen-in-file=<file>\t" << "set input of generator from stdin to <file>" << endl
	 << "  -gen-out-file=<file>\t" << "set output of generator from stdout to <file>" << endl
	 << "  -checker=<prog>\t" << "use <prog> as checker(testlib format) instead of diff -Z" << endl
	 << "  -checker-log=<file>\t" << "print checker's log to <file>" << endl
	 << "  -test=<number>\t" << "do <number> tests" << endl
	;
    exit(2);
}

void quitVersion() {
    cout << "stress test version 1.0 by ckf" << endl;
    exit(3);
}

string compare(string s, string t) {
    if(s.size() < t.size()) return "";
    for(int i = 0; i < t.length(); ++i) if(s[i] != t[i]) return "";
    if(s.length() == t.length()) return "";
    return s.substr(t.length(), s.length());
}

bool parseRedirect(string& tar, string s, string t) {
    string res = compare(s, t);
    if(res != "") {
	if(tar != "") {
	    quitRepeated(t);
	}
	tar = res;
	return 1;
    } else {
	if(s == t) {
	    quitExpectArg(t);
	}
    }
    return 0;
}

string dir = "/tmp/";

string randomString(int len = 6) {
    string res = "";
    rep(i, 1, len) res += char(mtrnd() % 26 + 'a');
    return res;
}

void getTempDir() {
    dir += randomString();
}

void parseOption() {
    if(argc == 2 && (string(argv[1]) == "--help" || string(argv[1]) == "-h")) quitHelp();
    if(argc == 2 && (string(argv[1]) == "--version" || string(argv[1]) == "-v")) quitVersion();
    if(argc < 4) quitFatalError();

    sol.name = parseFileName(argv[2]);
    bf.name = parseFileName(argv[3]);
    gen.name = parseFileName(argv[1]);

    for(int i = 4; i < argc; ++i) {
	string word = string(argv[i]);
	if(parseRedirect(sol.infile, word, "-sol-in-file=")) continue;
	if(parseRedirect(sol.outfile, word, "-sol-out-file=")) continue;
	if(parseRedirect(gen.outfile, word, "-gen-out-file=")) continue;
	if(parseRedirect(bf.infile, word, "-bf-in-file=")) continue;
	if(parseRedirect(bf.outfile, word, "-bf-out-file=")) continue;
	if(parseRedirect(checker, word, "-checker=")) continue;
	if(parseRedirect(cases, word, "-test=")) continue;

	quitUnrecognized(word);
    }
}

string psol, cpsol, pgen, cpgen, pbf, cpbf;
string cgen, csol, cbf, ccheck, makedir;
string tempin, tempout, tempans;
string gotodir;

void initCommand() {
    makedir = "mkdir " + dir;
    gotodir = "cd " + dir;
    tempin = dir + "/" + randomString() + "_in";
    tempout = dir + "/" + randomString() + "_out";
    tempans = dir + "/" + randomString() + "_ans";
    psol = dir + "/" + randomString() + "_sol.exe";
    pgen = dir + "/" + randomString() + "_gen.exe";
    pbf = dir + "/" + randomString() + "_bf.exe";
    cpsol = "cp " + sol.name + " " + psol;
    cpgen = "cp " + gen.name + " " + pgen;
    cpbf = "cp " + bf.name + " " + pbf;

    if(gen.outfile == "") cgen = pgen + " > " + tempin;
    else cgen = pgen + " && " + "cp " + gen.outfile + " " + tempin;

    if(sol.infile == "" && sol.outfile == "") csol = psol + " < " + tempin + " > " + tempout;
    else if(sol.infile == "") csol = psol + " < " + tempin +
				  " && " + "cp " + sol.outfile + " " + tempout;
    else if(sol.outfile == "") csol = "cp " + tempin + " " + sol.infile +
				   " && " + psol + " > " + tempout;
    else csol = "cp " + tempin + " " + sol.infile +
	     " && " + psol +
	     " && " + "cp " + sol.outfile + " " + tempout;

    if(bf.infile == "" && bf.outfile == "") cbf = pbf + " < " + tempin + " > " + tempans;
    else if(bf.infile == "") cbf = pbf + " < " + tempin +
				  " && " + "cp " + bf.outfile + " " + tempans;
    else if(bf.outfile == "") cbf = "cp " + tempin + " " + bf.infile +
				   " && " + pbf + " > " + tempans;
    else cbf = "cp " + tempin + " " +  bf.infile +
	     " && " + pbf +
	     " && " + "cp " + bf.outfile + " " + tempans;

    
    if(checker == "") ccheck = "diff -Z " + tempout + " " + tempans;
    else ccheck = checker + " " + tempin + " " + tempout + " " + tempans;
    
}

int runCommand(string s) {
    // debug("[debug] run command = {}\n", s);
    return system(s.c_str());
}

void startTest() {
    if(cases != "") t = atoi(cases.c_str());

    cout << "ready for " << t << " tests" << endl;
    cout << "temp dir = " << dir << endl;
    cout << "temp files =" << endl;
    cout << "gen:\t" << pgen << "\t" << gen.name << endl;
    cout << "bf:\t" << pbf << "\t" << bf.name << endl;
    cout << "sol:\t" << psol << "\t" << sol.name << endl;

    cout << "start? [Y/N]" << endl;

    char opt = getchar();
    if(opt == 'Y' || opt == 'y') {
	runCommand(makedir);
	cout << "copying files..." << endl;
	runCommand(cpsol);
	runCommand(cpgen);
	runCommand(cpbf);
	rep(tt, 1, t) {
	    cout << "running on test #" << tt << "..." << endl;

	    cout << "generating... "; cout.flush();
	    if(runCommand(cgen)) {
		cout << "generator exited with non-zero exit code" << endl;
		exit(8);
	    }

	    cout << "running bruteforce... "; cout.flush();
	    if(runCommand(cbf)) {
		cout << "bruteforce exited with non-zero exit code" << endl;
		exit(8);
	    }

	    cout << "running solution... "; cout.flush();
	    if(runCommand(csol)) {
		cout << "solution exited with non-zero exit code" << endl;
		exit(8);
	    }

	    if(runCommand(ccheck)) {
		cout << wred << "WA!" << wclear << endl;
		exit(9);
	    }
	    cout << wgreen << "Accepted!" << wclear << endl;
	}
	exit(0);
    } else {
	cout << "Abort" << endl;
	exit(7);
    }
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(15);
    cerr << fixed << setprecision(15);

    ::argc = argc, ::argv = argv;

    parseOption();    
    getTempDir();
    initCommand();
    startTest();
    
    cout.flush();
    return 0;
}
