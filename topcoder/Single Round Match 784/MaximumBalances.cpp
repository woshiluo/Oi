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
	class MaximumBalances {
		private:
			const int N = 3000;
			char *s;
		public:
			int solve( std::string _s ) {
				s = (char*)_s.c_str();
				int n = strlen(s), left = 0, rig = 0;
				for( int i = 0; i < n; i ++ ) {
					if( s[i] == '(' )
						left ++;
					if( s[i] == ')' ) 
						rig ++;
				}
				chk_Min( left, rig );
				chk_Min( rig, left );
				n = left * 2;
				left = rig = 0;
				int ans = 0, cnt = 0;
				for( int i = 1; i <= n; i ++ ) {
					if( i & 1 ) 
						left ++;
					else {
						cnt ++;
						left --;
						ans += cnt;
					}
				}
				return ans;
			}
	};
}

using::wsl::MaximumBalances;

// CUT begin
using namespace std;
ifstream data("MaximumBalances.sample");

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

bool do_test(string s, int __expected) {
    time_t startClock = clock();
    MaximumBalances *instance = new MaximumBalances();
    int __result = instance->solve(s);
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
        string s;
        from_stream(s);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1587740977;
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
        cout << "MaximumBalances (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
