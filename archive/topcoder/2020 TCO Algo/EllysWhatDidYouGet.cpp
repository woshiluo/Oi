#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

namespace wsl {
	template <class T> 
		T Max( T a, T b ) { return a > b? a: b; }
	template <class T> 
		T Min( T a, T b ) { return a < b? a: b; }
	template <class T> 
		void chk_Max( T &a, T b ) { if( b > a ) a = b; }
	template <class T> 
		void chk_Min( T &a, T b ) { if( b < a ) a = b; }
	class EllysWhatDidYouGet {
		private:
			int dig_sum( int a ) {
				int res = 0;
				while( a ) {
					res += a % 10;
					a /= 10;
				}
				return res;
			} 
			inline int calc( int i, int x, int y, int z ) { return dig_sum( ( ( i * x ) + y ) * z ); }
		public:
			int getCount( int n ) {
				int ans = 0;
				for( int x = 1; x <= 50; x ++ ) {
					for( int y = 1; y <= 50; y ++ ) {
						for( int z = 1; z <= 50; z ++ ) {
							int lst = calc( 1, x, y, z );
							bool flag = true;
							for( int i = 2; i <= n; i ++ ) {
								if( calc( i, x, y, z ) != lst ) {
									flag = false;
									break;
								}
							}
							ans += flag;
						}
					}
				}
				return ans;
			}
	};
}

using::wsl::EllysWhatDidYouGet;

// CUT begin
using namespace std;
ifstream data("EllysWhatDidYouGet.sample");

string next_line() {
	string s;
	getline(data, s);
	return s;
}

template <typename T> void from_stream(T &t) {
	stringstream ss(next_line());
	ss >> t;
}

void from_stream(string &s) {
	s = next_line();
}

template <typename T>
string to_string(T t) {
	stringstream s;
	s << t;
	return s.str();
}

string to_string(string t) {
	return "\"" + t + "\"";
}

bool do_test(int N, int __expected) {
	time_t startClock = clock();
	EllysWhatDidYouGet *instance = new EllysWhatDidYouGet();
	int __result = instance->getCount(N);
	double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
	delete instance;

	if (__result == __expected) {
		cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
		return true;
	}
	else {
		cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
		cout << "           Expected: " << to_string(__expected) << endl;
		cout << "           Received: " << to_string(__result) << endl;
		return false;
	}
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
	int cases = 0, passed = 0;
	while (true) {
		if (next_line().find("--") != 0)
			break;
		int N;
		from_stream(N);
		next_line();
		int __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if ( do_test(N, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1588072843;
		double PT = T / 60.0, TT = 75.0;
		cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
		cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);
	set<int> cases;
	bool mainProcess = true;
	for (int i = 1; i < argc; ++i) {
		if ( string(argv[i]) == "-") {
			mainProcess = false;
		} else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "EllysWhatDidYouGet (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
