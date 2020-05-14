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
	template <class T> 
		T aabs( T a ) { return a < 0? -a: a; }
	class EllysDifferentPrimes {
		private: 
			int pcnt = 0;
			bool is_prime[80000005];
			int prime[5000005];
			void get_prime( int n = 8e7 ) {
				for(int i = 0; i <= n; ++i) 
					is_prime[i] = 1;
				is_prime[0] = is_prime[1] = 0;
				for(int i = 2; i <= n; ++i) {
					if( is_prime[i] ) {
						prime[ ++ pcnt ] = i; 
						for (long long j = 1LL * i * i; j <= n; j += i) 
							is_prime[j] = 0;
					}
				}
			}
			bool is_dig_prime( int n ) {
				bool dig[10];
				for( int i = 0; i <= 9; i++ ) 
					dig[i] = 0;
				while( n ) {
					int tmp = n % 10;
					if( dig[tmp] )
						return false;
					dig[tmp] = true;
					n /= 10;
				}
				return true;
			}
		public:
			int getClosest( int n ) {
				get_prime();
				int ans = 2;
				for( int i = 1; i <= pcnt; i ++ ) {
					if( is_dig_prime( prime[i] ) && aabs( prime[i] - n ) < aabs( ans - n ) ) 
						ans = prime[i];
				}
				return ans;
			}
	};
}

using::wsl::EllysDifferentPrimes;

// CUT begin
using namespace std;
ifstream data("EllysDifferentPrimes.sample");

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
    EllysDifferentPrimes *instance = new EllysDifferentPrimes();
    int __result = instance->getClosest(N);
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
        int T = time(NULL) - 1588073236;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "EllysDifferentPrimes (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
