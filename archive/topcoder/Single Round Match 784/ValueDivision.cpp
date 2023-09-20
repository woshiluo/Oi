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
	class ValueDivision {
		private:
			int mp[3100], sum[3100];
		public:
			std::vector<int> getArray( std::vector<int> _a ) {
				std::vector<int> a = _a;
				int n = a.size();
				std::sort( a.begin(), a.end() );
				int mp_cnt = 0;
				for( int i = 0; i < n; i ++ ) {
					if( i == 0 || a[i] != a[ i - 1 ] )
						mp_cnt ++;
					sum[ mp_cnt ] ++;
					mp[ mp_cnt ] = a[i];
				}
				std::vector<int> ans = _a;
				for( int i = mp_cnt; i >= 1; i -- ) {
						if( sum[i] / 2 <= 0 )
							continue;
						else {
							int cur = mp[i], cnt = sum[i], nxt_cnt = 0, nxt_sum = 0;
							int cur_sum = cnt;
							while( cnt ) {
								if( cur == 1 ) 
									break;
								nxt_cnt = nxt_sum = 0;
								while( cur_sum / 2 > 0 ) {
									int tmp = cur_sum / 2;
									nxt_cnt += tmp;
									for( int i = 0; i < n; i ++ ) {
										if( ans[i] == cur ) {
											ans[i] --;
											tmp --;
										}
										if( tmp == 0 )
											break;
									}
									nxt_sum += cur_sum / 2;
									cur_sum -= ( cur_sum / 2 );
								}
								cur --;
								if( cur == mp[ i - 1 ] ) {
									sum[ i - 1 ] += nxt_cnt;
									break;
								}
								cur_sum = nxt_sum;
								cnt = nxt_cnt;
							}
						}
				}
				return ans;
			}
	};
}

using::wsl::ValueDivision;

// CUT begin
using namespace std;
ifstream data("ValueDivision.sample");

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

template <typename T> void from_stream(vector<T> &ts) {
	int len;
	from_stream(len);
	ts.clear();
	for (int i = 0; i < len; ++i) {
		T t;
		from_stream(t);
		ts.push_back(t);
	}
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

template <typename T> string to_string(vector<T> ts) {
	stringstream s;
	s << "[ ";
	for (int i = 0; i < ts.size(); ++i) {
		if (i > 0) s << ", ";
		s << to_string(ts[i]);
	}
	s << " ]";
	return s.str();
}

bool do_test(vector<int> A, vector<int> __expected) {
	time_t startClock = clock();
	ValueDivision *instance = new ValueDivision();
	vector<int> __result = instance->getArray(A);
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
        vector<int> A;
        from_stream(A);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1587742538;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ValueDivision (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
