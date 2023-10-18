/*
 * f.cpp 2023-09-26
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */


#include <bits/stdc++.h>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;


struct BigInt {
    std::vector<int> v;
};

constexpr int P = 1E9;

BigInt operator+(const BigInt &a, const BigInt &b) {
    BigInt c;
    c.v.resize(std::max(a.v.size(), b.v.size()) + 1);
    for (int i = 0; i < a.v.size(); i++) {
        c.v[i] += a.v[i];
    }
    for (int i = 0; i < b.v.size(); i++) {
        c.v[i] += b.v[i];
    }
    for (int i = 0; i < c.v.size(); i++) {
        if (c.v[i] >= P) {
            c.v[i] -= P;
            c.v[i + 1]++;
        }
    }
    if (c.v.back() == 0) {
        c.v.pop_back();
    }
    return c;
}

bool operator<(const BigInt &a, const BigInt &b) {
    if (a.v.size() != b.v.size()) {
        return a.v.size() < b.v.size();
    }
    for (int i = int(a.v.size()) - 1; i >= 0; i--) {
        if (a.v[i] != b.v[i]) {
            return a.v[i] < b.v[i];
        }
    }
    return false;
}

void print(const BigInt &a) {
    const auto &v = a.v;
    if (v.empty()) {
        std::cout << "0\n";
        return;
    }
    std::cout << v.back();
    for (int i = int(v.size()) - 2; i >= 0; i--) {
        std::cout << std::setw(9) << std::setfill('0') << v[i];
    }
    std::cout << "\n";
}

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; isdigit(ch) == 0; ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}
template <class T> 
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 1e6 + 5;
const int K = 10;

typedef BigInt BigInteger;

int cnt = 0;
char str[N];
BigInteger f[N][K];

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		auto make = []( cint left, cint rig ) {
			BigInt ans;
			int st = left;
			for( ; st + 9 <= rig; st += 9 ) {
				int t = 1;
				int res = 0;
				for( int p = st; p < st + 9; p ++ ) {
					res += t * ( str[p] - '0' );
					t *= 10;
				}
				ans.v.push_back(res);
			}
			if( st <= rig ) {
				int t = 1;
				int res = 0;
				for( int p = st; p <= rig; p ++ ) {
					res += t * ( str[p] - '0' );
					t *= 10;
				}
				ans.v.push_back(res);
			}
			return ans;
		};
		cint n = read<int>();
		cint k = read<int>();
		cint p = n / ( k + 1 ) + 2;
		scanf( "%s", str + 1 );
		std::reverse( str + 1, str + n + 1 );

		for( int i = 1; i <= n; i ++ ) {
			for( int j = 0; j <= k + 1; j ++ ) 
				f[i][j].v.resize(0);
		}
		for( int j = 1; j <= k + 1; j ++ ) {
			for( int i = Max( 1, n - p * ( k - j + 1 ) ); i <= n; i ++ ) {
				for( int t = Max( 0, i - p ); t <= ( j - 1 ) * p && t < i; t ++ ) {
					if( t == 0 || !f[t][ j - 1 ].v.empty() ) {
						const auto res = f[t][ j - 1 ] + make( t + 1, i );
						if( f[i][j].v.empty() || res < f[i][j] ) 
							f[i][j] = res;
					}
				}
			}
		}

		print(f[n][ k + 1 ]);
	}

}
