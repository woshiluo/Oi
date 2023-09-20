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
	class EllysCandies {
		public:
			std::string getWinner( std::vector<int> boxes ) {
				std::sort( boxes.begin(), boxes.end() );
				int ans1 = 0, ans2 = 0, cnt = 0, size = boxes.size();
				for( int i = 0; i < size; i ++ ) {
					if( i & 1 )
						ans1 += boxes[i] + cnt;
					else 
						ans2 += boxes[i] + cnt;
					cnt += boxes[i];
				}
				if( ans2 == ans1 )
					return "Draw";
				if( ans2 > ans1 ) 
					return "Elly";
				else 
					return "Kris";
			}
	};
}

using::wsl::EllysCandies;

// CUT begin
using namespace std;
ifstream data("EllysCandies.sample");

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

bool do_test(vector<int> boxes, string __expected) {
    time_t startClock = clock();
    EllysCandies *instance = new EllysCandies();
    string __result = instance->getWinner(boxes);
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
        vector<int> boxes;
        from_stream(boxes);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(boxes, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1588072188;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "EllysCandies (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
